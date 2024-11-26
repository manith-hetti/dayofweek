#pragma once
#include "Date.hpp"
#include <string>
#include <optional>

class Game {
protected:
    Date date;
    int score{0};
    int lives{3};
    int highScore{0};

    virtual void loadHighScore();
    virtual void saveHighScore();

public:
    Game();
    virtual ~Game() = default;

    bool checkAnswer(const std::string& answer);
    void generateNewDate();
    void lostLife() { lives--; }

    int getScore() const { return score; }
    int getLives() const { return lives; }
    int getHighScore() const { return highScore; }
    const Date& getCurrentDate() const { return date; }

    bool isGameOver() const { return lives <= 0; }
    bool isNewHighScore() const { return score > highScore; }

};
