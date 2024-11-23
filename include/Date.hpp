#include <random>
#include <chrono>

enum class Weekday { monday, tuesday, wednesday, thursday, friday, saturday, sunday};

class Date {
private:

    std::mt19937 gen;
    int m_year{};
    int m_month{};
    int m_day{};
    Weekday m_weekday{};

    static int getDaysInMonth(int year, int month);

public:
    Date();
    Date(int year, int month, int day, Weekday weekday);

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
    Weekday getWeekday() const { return m_weekday; }
    void createRandomDate();
};
