/**
 * Brendan Han
 * Assignment4
 */

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include "getpost.h"

using namespace std;

int main(int argc, char* argv[]) {

    map<string,string> Get;
    initializePost(Get);
    cout << "Content-type: text/html" << endl << endl;
    cout << "<html><body>" << endl;
    cout << "<h2>Form processed...here is what we got</h2>" << endl;

    std::string username;
    std::string password;
    
    if (Get.find("username")!=Get.end() && Get.find("password")!=Get.end()) {
        cout << "<p>You entered, username: "<< Get["username"]<<" and password: "<< Get["password"] << endl;
        username = Get["username"];
        password = Get["password"];
    } else {
        cout << "<p>Fill out the from and press submit"<<endl;
    }
    cout << "</body></html>" << endl;

    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false); // Exceptions suppressed to keep code simple
    if(conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {

        // Create a query
        mysqlpp::Query query = conn.query();

        query << "SELECT "+username+", md5("+password+" FROM haw4UserInfo";
        //query << "INSERT into Users (username, password) VALUES(%0q, md5(%1q));";

        query.parse();  // check to ensure it is correct

        // Run the query -- note INSERT does not return results so we are using SimpleResult
        mysqlpp::StoreQueryResult result = query.store();
        //mysqlpp::SimpleResult result = query.execute(username, password);

        // Always check for errors
        if(result) {
            cout <<"<p>Query success...\n";
            for (int i = 0; result.num_rows(); i++) {
                cout << "<p>Username: " << result[i]["username"] << " Password " << result[i]["password"] << endl;
                std::string u = result[i]["username"].c_str();
                std::string p = result[i]["password"].c_str();

                if (username == u && password == p) {
                    cout << "Correct username and password\n";
                }
            }
        } else {
            cerr << "Query error: " << query.error() << endl;
        }
        return(0);
    } else {
        cerr << "Connection failed: " << conn.error() <<endl;
        return(1);
    }
}
