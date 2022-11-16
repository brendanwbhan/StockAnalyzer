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
    std::string firstname;
    std::string lastname;
    std::string email;
    std::string street;
    std::string city;
    std::string state;
    std::string zipcode;
    std::string country;
    
    if (Get.find("username")!=Get.end() && 
        Get.find("password")!=Get.end() &&
        Get.find("firstname")!=Get.end() && 
        Get.find("lastname")!=Get.end() &&
        Get.find("email")!=Get.end() &&
        Get.find("street")!=Get.end() &&
        Get.find("city")!=Get.end() &&
        Get.find("state")!=Get.end() &&
        Get.find("zipcode")!=Get.end() &&
        Get.find("country")!=Get.end()) 
        {
        cout << "<p>You entered, username: "<< Get["username"]<<" and password: "<< Get["password"] << endl;

        username = Get["username"];
        password = Get["password"];
        firstname = Get["firstname"];
        lastname = Get["lastname"];
        email = Get["email"];
        street = Get["street"];
        city = Get["city"];
        state = Get["state"];
        zipcode = Get["zipcode"];
        country = Get["country"];
    } else {
        cout << "<p>Fill out the from and press submit"<<endl;
    }
    cout << "</body></html>" << endl;

    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false); // Exceptions suppressed to keep code simple
    if(conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {

        // Create a query
        mysqlpp::Query query = conn.query();

        query << "INSERT into hanw4UserInfo VALUES('"+
        username+"', md5('"+password+"'), '"+firstname+"', '"+
        lastname+"', '"+email+"', '"+street+"', '"+city+"', '"+state+"', '"+zipcode+"', '"+country+"');";
        //query << "INSERT into Users (username, password) VALUES(%0q, md5(%1q));";

        query.parse();  // check to ensure it is correct

        // Run the query -- note INSERT does not return results so we are using SimpleResult
        mysqlpp::SimpleResult result = query.execute();
        //mysqlpp::SimpleResult result = query.execute(username, password);

        // Always check for errors
        if(result) {
            cout <<"<p>Query success...\n";
        } else {
            cerr << "Query error: " << query.error() << endl;
        }
        return(0);
    } else {
        cerr << "Connection failed: " << conn.error() <<endl;
        return(1);
    }
}
