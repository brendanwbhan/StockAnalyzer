Brendan Han
CSE278
# Assignment 4: Stock Market Data Analyzer

## About
This project is based on a personal career interest of seeking to work in the Quantitative Trading Industry. This project combines Finance and Computer Science to retrieve meaningful financial data.

## SQL Tables
There are in total 8 tables that this project utilizes: hanw4UserInfo, and seven tables dedicated to store historical data of 7 different companies in varying industries, ranging from fast food to capital management. Hanw4UserInfo tables takes in necessary user information from username, password, to user address. The company tables all store the date, high and low values, and open and close values. These data were downloaded from Yahoo Finance – data ranging from December 2017 to November 2022.

## Creating Account and Logging In
On the index page of the website, the user is presented with two options – they can either create an account or login using their pre-existing information. When creating an account, the user must fill out every section of the form in order to create an account. Otherwise, they will be prompted to try again. In order to login, the users must type in the correct credentials to be able to access the explore page.

## Functions
The two main functions in this program are finding minimum and maximum stock prices of a company in a given date range and finding the profit/loss rate from two given date ranges. For the minimum and maximum function, the form takes in the ticker symbol (AAPL, SBUX, MCD, and more) and the two dates the user wants to see. The SQL will then output the max and min stock closing values between the given dates using:

SELECT MAX(Close) FROM BX WHERE Date BETWEEN 2020-01-01 AND 2021-01-01
==> Finding the maximum closing value of Blackstone Inc. between Jan 1st, 2020 and Jan 1st, 2021.

The return rate function takes a similar input as the max and min function. However, we take another an extra step to figure out the growth rate of a specific stock. The user is prompted to enter the ticker value, the start date, and the end date. The query will retrieve the stock prices from the specified dates and compute the growth/loss rate using the growth formula.

Apart from the functions above, there is an additional feature where the user can gain a brief insight about the company, sourced from Yahoo Finance.
