#include <gtest/gtest.h>
#include <boost/math/distributions/chi_squared.hpp>
#include <vector>
#include <iostream>
#include "Date.hpp"
#include "Helper.cpp"

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
    const int NUM_TESTS = 10000;
    const int YEAR_RANGE = 200;
    std::vector<int> year_counts(YEAR_RANGE, 0);

    for (int i = 0; i < NUM_TESTS; i++) {
        Date date;
        date.createRandomDate();
        int year = date.getYear();
        std::cout << year << std::endl;
        year_counts[year - 1900]++;
    }

    double expected_proportion = 1.0 / YEAR_RANGE;

    bool is_uniform = this->chi_squared(year_counts, expected_proportion);

    EXPECT_TRUE(is_uniform);
}
