///////////////////////////////////////////////////////////////////////////////////////////////
///			Distributed under the GNU Lesse General Public Licence, Version 3				///
/// 					(See accompanying file LICENSE or copy at: 							///
/// 					https://www.gnu.org/licenses/lgpl-3.0.en.html)						///
///////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <chrono>
#include <random>
#include <QDate>

using namespace std;

#ifndef DATEGENERATOR_H
#define DATEGENERATOR_H


class DateGenerator
{
private:
    int year;
    int month;
    int day;
    char wday;
    bool leap;

public:
    /**
     * @brief DateGenerator intitializes year, month and the weekday.
     */
    DateGenerator();

    /**
     * @brief getYear chooses a random value from uniform distribution between 1900 and 2099.
     * @return year
     */
    int getYear();

    /**
     * @brief getMonth chooses a random a value from uniform distribution between 1 and 12.
     * @return month
     */
    int getMonth();

    /**
     * @brief getDate uses if else statements to choose a date, accounting for February (both in and out of leap years), and to give July 31 days.
     * @return date
     */
    int getDate();

    /**
     * @brief getWeekday creates a date from year, month, and day, which is then assigned the corresponding weekday.
     * @return string wday
     */
    string getWeekday();

    /**
     * @brief isLeap works out if the year is a leap year or not
     * @return boolean value
     */
    bool isLeap();

};

#endif
