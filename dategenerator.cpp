///////////////////////////////////////////////////////////////////////////////////////////////
///			Distributed under the GNU Lesse General Public Licence, Version 3				///
/// 					(See accompanying file LICENSE or copy at: 							///
/// 					https://www.gnu.org/licenses/lgpl-3.0.en.html)						///
///////////////////////////////////////////////////////////////////////////////////////////////

#include "dategenerator.h"

using namespace std;

DateGenerator::DateGenerator()
{
    year = 0;
    month = 0;
    day = 0;
    wday = 0;
}

int DateGenerator::getYear()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> years(1900, 2099);
    year = years(gen);
    return year;
}

int DateGenerator::getMonth()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> months(1, 12);
    month = months(gen);
    return month;
}

int DateGenerator::getDate()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    /**
     * February where it's a century and not a leap year.
     */
    if (year % 100 == 0 && year % 400 != 0 && month == 2) {
        std::uniform_int_distribution<> days(1, 28);
        day = days(gen);
    }

    /**
     * February where it's a century and a leap year
     */
    else if (year % 100 == 0 && year % 400 == 0 && month == 2) {
        std::uniform_int_distribution<> days(1, 29);
        day = days(gen);
    }

    /**
     * February during a leap year
     */
    else if (year % 4 == 0 && month == 2) {
        std::uniform_int_distribution<> days(1, 29);
        day = days(gen);
    }

    /**
     * February during non leap year
     */
    else if (year % 4 != 0 && month == 2) {
        std::uniform_int_distribution<> days(1, 28);
        day = days(gen);
    }

    /**
     * When it's July
     */
    else if (month == 6) {
        std::uniform_int_distribution<> days(1, 31);
        day = days(gen);
    }

    /**
     * Even months with only 30 days
     */
    else if (month % 2 == 0) {
        std::uniform_int_distribution<> days(1, 30);
        day = days(gen);
    }

    else {
        std::uniform_int_distribution<> days(1, 31);
        day = days(gen);
    }

    return day;
}

bool DateGenerator::isLeap() {
    if (year % 100 == 0 && year % 400 == 0) {
        return true;
    }
    else if (year % 4 == 0) {
        return true;
    }
    else {
        return false;
    }
}

string DateGenerator::getWeekday()
{
    std::chrono::sys_days date = std::chrono::year{year}/month/day;
    std::chrono::weekday wday = date;

    switch (wday.c_encoding())
    {
    case 0: return "Sunday";
    case 1: return "Monday";
    case 2: return "Tuesday";
    case 3: return "Wednesday";
    case 4: return "Thursday";
    case 5: return "Friday";
    case 6: return "Saturday";
    default: return "?";
    }
}
