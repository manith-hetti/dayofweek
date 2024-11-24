#include "Date.hpp"
#include <iostream>

Date::Date() {}

Date::Date(int year, int month, int day)
    : m_year{year}
    , m_month{month}
    , m_day{day}
{
}

Date::Date(int year, int month, int day, weekday weekday)
    : m_year{year}
    , m_month{month}
    , m_day{day}
    , m_weekday{weekday}
{
}

int Date::getDaysInMonth(int year, int month) {
    static const std::array<int, 12> daysInMonth {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return isLeapYear ? 29 : 28;
    }

    return daysInMonth[month - 1];
}

void Date::setWeekday() {
    std::chrono::sys_days date = std::chrono::year{m_year}/m_month/m_day;
    m_weekday = date;
}

void Date::createRandomYear() {
    std::mt19937 mt{static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count()
    )};

    std::uniform_int_distribution<> yearDist(1900, 2099);
    m_year = yearDist(mt);

}

void Date::createRandomMonth() {
    std::mt19937 mt{static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count()
    )};

    std::uniform_int_distribution<> monthDist(1, 12);
    m_month = monthDist(mt);

}

void Date::createRandomDay() {
    std::mt19937 mt{static_cast<std::mt19937::result_type>(
        std::chrono::steady_clock::now().time_since_epoch().count()
    )};

    std::uniform_int_distribution<> dayDist(1, getDaysInMonth(m_year, m_month));
    m_day = dayDist(mt);
    std::cout << "Day: " << m_day << std::endl;

}
