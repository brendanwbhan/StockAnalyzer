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
    cout << "<html><head><title>Quantify</title></head>" << endl;
    cout << "<link rel=\"stylesheet\"href=\"functions.css\">" << endl;
    
    std::string ticker;
    std::string month1;
    std::string year1;
    std::string month2;
    std::string year2;
    double start;
    double end;
    double change;

    if (Get.find("ticker") != Get.end() &&
        Get.find("month1") != Get.end() &&
        Get.find("year1") != Get.end() &&
        Get.find("month2") != Get.end() &&
        Get.find("year2") != Get.end())
    {
        ticker = Get["ticker"];
        month1 = Get["month1"];
        year1 = Get["year1"];
        month2 = Get["month2"];
        year2 = Get["year2"];
    }
    
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection conn(false); // Exceptions suppressed to keep code simple
    if(conn.connect("cse278", "localhost", "cse278", "MonSepM1am1")) {
        
        // Start
        mysqlpp::Query query1 = conn.query();
        query1 << "SELECT Close FROM " + ticker + " WHERE Date = '" + year1 + "-01-" + month1 + " 00:00:00';";
        query1.parse();  // check to ensure it is correct
        mysqlpp::StoreQueryResult result1 = query1.store();

        // End
        mysqlpp::Query query2 = conn.query();
        query2 << "SELECT Close FROM " + ticker + " WHERE Date = '" + year2 + "-01-" + month2 + " 00:00:00';";
        query2.parse();  // check to ensure it is correct
        mysqlpp::StoreQueryResult result2 = query2.store();

        // Always check for errors
        if(result1 && result2) {   
            start = result1[0]["Close"];
            end = result2[0]["Close"];

            change = ((end - start) / start) * 100;
        } else {
            cerr << "<p>Query error: " << query1.error() << endl;
        }

        cout << "<body><h1 class=\"title\"><a href=\"explore.html\">Quantify</a></h1>" << endl;
        cout << "<h3 class=\"description\">Max and Min</h3>" << endl;
        cout << "<h4 class=\"output\">Percent Change: " << change << "%</h4>" << endl;
        cout << "</body></html>" << endl;
        return(0);
    }
}
