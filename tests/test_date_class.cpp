#include <gtest/gtest.h>
#include "Date.hpp"

TEST(DateClass, getYearFromInitialisedDate) {
    Date date(2000, 10, 5, Weekday::thursday);
    int year = date.getYear();
    EXPECT_EQ(2000, year);
}

TEST(DateClass, getMonthFromInitialisedDate) {
    Date date(2000, 10, 5, Weekday::thursday);
    int month = date.getMonth();
    EXPECT_EQ(10, month);
}

TEST(DateClass, getDayFromInitialisedDate) {
    Date date(2000, 10, 5, Weekday::thursday);
    int day = date.getDay();
    EXPECT_EQ(5, day);
}

TEST(DateClass, getWeekdayFromInitialisedDate) {
    Date date(2000, 10, 5, Weekday::thursday);
    Weekday weekday = date.getWeekday();
    EXPECT_EQ(Weekday::thursday, weekday);
}

TEST(DateClass, getDayAsZeroFromDefault) {
    Date date;
    int day = date.getDay();
    EXPECT_EQ(0, day);
}

TEST(DateClass, createRandomDate) {
    Date date;
    date.createRandomDate()
}


