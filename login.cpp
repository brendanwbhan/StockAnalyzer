/**
 * Brendan Han
 * Assignment4
 */

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include "getpost.h"
#include "md5.h"

using namespace std;

int main(int argc, char* argv[]) {
    map<string,string> Get;
    initializePost(Get);
    MD5 pass;

    cout << "Content-type: text/html" << endl << endl;
    cout << "<html><head><title>Quantify</title></head>" << endl;
    cout << "<link rel=\"stylesheet\"href=\"login.css\">" << endl;

    std::string username;
    std::string password;
    bool correct = false;

    if (Get.find("username")!=Get.end() && Get.find("password")!=Get.end() ) {
        username = Get["username"];
        password = Get["password"];
    }
    
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false); // Exceptions suppressed to keep code simple
    if(conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {
        // Create a query
        mysqlpp::Query query = conn.query();
        query << "SELECT username, password FROM hanw4UserInfo WHERE username = '" + username + "' AND password = md5('" + password + "');";
        query.parse();  // check to ensure it is correct

        mysqlpp::StoreQueryResult result = query.store();
        // Always check for errors
        if(result) {           
            for (int i = 0; i < result.num_rows(); i++) {
                std::string u = result[i]["username"].c_str();
                std::string p = result[i]["password"].c_str();

                if (username == u && pass(password) == p) {
                    correct = true;
                } else {
                    correct = false;
                }
            }
        } else {
            cerr << "<p>Query error: " << query.error() << endl;
        }
        
        if (correct) {
            std::string message = "Welcome " + Get["username"] + "!";
            cout << "<h4 class=\"message\">" + message + "</h4>" << endl;
            cout << "<body><h1 class=\"title\">Quantify</h1>" << endl;
            cout << "<h3 class=\"explorestks\"><a href=\"explore.html\">Explore Stocks</a></h3>" << endl;
        } else {
            cout << "<body><h1 class=\"title\">Quantify</h1>" << endl;
            cout << "<div class=\"errormsg\">" << endl;
            cout << "<h3 class=\"wrongmsg\">Wrong Username or Password</h3>" << endl;
            cout << "<h3 class=\"tryagain\"><a href=\"login.html\">Try Again</a></h3>" << endl;
            cout << "</div>" << endl;
        }

        cout << "</body></html>" << endl;
        return(0);
    }
}
