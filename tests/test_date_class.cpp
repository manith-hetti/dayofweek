#include <gtest/gtest.h>
#include <boost/math/distributions/chi_squared.hpp>
#include <vector>
#include <iostream>
#include "Date.hpp"

TEST(DateClass, getYearFromInitialisedDate) {
    Date date(2000, 10, 5, std::chrono::Thursday );
    int year = date.getYear();
    EXPECT_EQ(2000, year);
}

TEST(DateClass, getMonthFromInitialisedDate) {
    Date date(2000, 10, 5, std::chrono::Thursday);
    int month = date.getMonth();
    EXPECT_EQ(10, month);
}

TEST(DateClass, getDayFromInitialisedDate) {
    Date date(2000, 10, 5, std::chrono::Thursday);
    int day = date.getDay();
    EXPECT_EQ(5, day);
}

TEST(DateClass, getWeekdayFromInitialisedDate) {
    Date date(2000, 10, 5, std::chrono::Thursday);
    weekday weekday_ = date.getWeekday();
    EXPECT_EQ(std::chrono::Thursday, weekday_);
}

TEST(DateClass, getDayAsZeroFromDefault) {
    Date date;
    int day = date.getDay();
    EXPECT_EQ(0, day);
}

TEST(DateClass, getWeekdayFromDateFirstDay) {
    Date date(1900, 1, 1);
    date.setWeekday();
    weekday weekday_ = date.getWeekday();
    EXPECT_EQ(std::chrono::Monday, weekday_);
}

TEST(DateClass, getWeekdayFromDateAnotherGivenDate) {
    Date date(1950, 4, 2);
    date.setWeekday();
    weekday weekday_ = date.getWeekday();
    EXPECT_EQ(std::chrono::Sunday, weekday_);
}

class DateTest : public ::testing::Test {
protected:
    bool chi_squared(const std::vector<int>& observed,
                     double expected_proportion,
                     double significance = 0.05) {
        int total = 0;
        for (int count : observed) {
            total += count;
        }
        double expected = total * expected_proportion;

        double chi_squared = 0;
        for (int count : observed) {
            double diff = count - expected;
            chi_squared += (diff * diff) / expected;
        }

        int degrees_freedom = observed.size() - 1;

        boost::math::chi_squared_distribution<double> dist(degrees_freedom);

        double p_value = 1 - boost::math::cdf(dist, chi_squared);

        return p_value > significance;
    }
};

TEST_F(DateTest, getRandomYear) {
    const int NUM_TESTS = 100000;
    const int YEAR_RANGE = 200;
    std::vector<int> year_counts(YEAR_RANGE, 0);

    for (int i = 0; i < NUM_TESTS; i++) {
        Date date;
        date.createRandomYear();
        int year = date.getYear();
        year_counts[year - 1900]++;
    }

    double expected_proportion = 1.0 / YEAR_RANGE;

    bool is_uniform = this->chi_squared(year_counts, expected_proportion);

    EXPECT_TRUE(is_uniform);
}

TEST_F(DateTest, getRandomMonth) {
    const int NUM_TESTS = 6000;
    const int MONTH_RANGE = 12;
    std::vector<int> month_counts(MONTH_RANGE, 0);

    for (int i = 0; i < NUM_TESTS; i++) {
        Date date;
        date.createRandomMonth();
        int month = date.getMonth();
        month_counts[month - 1]++;
    }

    double expected_proportion = 1.0 / MONTH_RANGE;

    bool is_uniform = this->chi_squared(month_counts, expected_proportion);

    EXPECT_TRUE(is_uniform);
}

TEST_F(DateTest, getRandomDayFebNonLeap) {
    const int NUM_TESTS = 14000;
    const int DATE_RANGE = 28;
    std::vector<int> day_counts(DATE_RANGE, 0);

    for (int i = 0; i < NUM_TESTS; i++) {
        Date date(2023, 2, 0, std::chrono::Monday);
        date.createRandomDay();
        int day = date.getDay();
        day_counts[day - 1]++;
    }

    double expected_proportion = 1.0 / DATE_RANGE;

    bool is_uniform = this->chi_squared(day_counts, expected_proportion);

    EXPECT_TRUE(is_uniform);
}

TEST_F(DateTest, getRandomDayFebLeap) {
    const int NUM_TESTS = 14500;
    const int DATE_RANGE = 29;
    std::vector<int> day_counts(DATE_RANGE, 0);

    for (int i = 0; i < NUM_TESTS; i++) {
        Date date(2024, 2, 0, std::chrono::Monday);
        date.createRandomDay();
        int day = date.getDay();
        day_counts[day - 1]++;
    }

    double expected_proportion = 1.0 / DATE_RANGE;

    bool is_uniform = this->chi_squared(day_counts, expected_proportion);

    EXPECT_TRUE(is_uniform);
}

TEST_F(DateTest, getRandomDayJune) {
    const int NUM_TESTS = 15000;
    const int DATE_RANGE = 30;
    std::vector<int> day_counts(DATE_RANGE, 0);

    for (int i = 0; i < NUM_TESTS; i++) {
        Date date(2024, 6, 0, std::chrono::Monday);
        date.createRandomDay();
        int day = date.getDay();
        day_counts[day - 1]++;
    }

    double expected_proportion = 1.0 / DATE_RANGE;

    bool is_uniform = this->chi_squared(day_counts, expected_proportion);

    EXPECT_TRUE(is_uniform);
}

