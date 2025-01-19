#include "normal_mode.hpp"

NormalMode::NormalMode() : Game() {}

bool NormalMode::checkAnswer(const std::string& answer) {
    auto weekday = date.getWeekday();
    bool correct = (std::to_string(weekday.c_encoding()) == answer);

    if (correct) {
        score++;
    } else {
        lives--;
        if (lives <= 0) {
            saveHighScore();
        }
    }

    generateNewDate();
    return correct;
}
