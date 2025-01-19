#include <optional>
#include <random>
#include <chrono>

using weekday = std::chrono::weekday;

class Date {
private:

    std::mt19937 gen;
    int m_year{};
    int m_month{};
    int m_day{};
    weekday m_weekday{};

    static int getDaysInMonth(int year, int month);

public:
    Date();
    Date(int year, int month, int day);
    Date(int year, int month, int day, weekday weekday);

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
    weekday getWeekday() const { return m_weekday; }

    void setWeekday();
    void createRandomYear();
    void createRandomMonth();
    void createRandomDay();
};
