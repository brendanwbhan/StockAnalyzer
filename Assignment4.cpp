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
    cout << "Content-type: text/html" << endl << endl; // important
    cout << "<html><head><title>Quantify</title></head>" << endl;
    cout << "<link rel=\"stylesheet\"href=\"main.css\">" << endl;

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
    bool loggedIn;
    
    if (
    Get["username"] != "" &&
    Get["password"] != "" &&
    Get["firstname"] != "" &&
    Get["lastname"] != "" &&
    Get["email"] != "" &&
    Get["street"] != "" &&
    Get["city"] != "" &&
    Get["state"] != "" &&
    Get["zipcode"] != "" &&
    Get["country"] != "") 
    {
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
            std::string message = "Welcome " + Get["username"] + "!";
            cout << "<h4 class=\"message\">" + message + "</h4>";
            
            cout << "<body><h1 class=\"title\">Quantify</h1>" << endl;
            cout << "<h3 class=\"exploreStks\"><a href=\"explore.html\">Explore Stocks</a></h3>" << endl;
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
            cout << "<body><h1 class=\"title\">Quantify</h1>" << endl;
            cout << "<h4 class=\"errormsg\">Form not filled</h4>"<<endl;
            cout << "<h4 class=\"tryagain\"><a href=\"createAcc.html\">Try Again</a></h4>" << endl;
        }
    } else {
        cout << "<body><h1 class=\"title\">Quantify</h1>" << endl;
        cout << "<h4 class=\"errormsg\">Form not filled</h4>"<<endl;
        cout << "<h4 class=\"tryagain\"><a href=\"createAcc.html\">Try Again</a></h4>" << endl;
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
            cout << "" << endl;
        } else {
            cerr << "Query error: " << query.error() << endl;
        }
        return(0);
    } else {
        cerr << "Connection failed: " << conn.error() <<endl;
        return(1);
    }
}
