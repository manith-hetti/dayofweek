#include "Date.hpp"

Date::Date() {}

Date::Date(int year, int month, int day, Weekday weekday)
    : m_year{year}
    , m_month{month}
    , m_day{day}
    , m_weekday{weekday}
{
}

