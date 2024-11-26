#include "game.hpp"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

Game::Game() : date() {
    loadHighScore();
    generateNewDate();
}

void Game::generateNewDate() {
    date.createRandomYear();
    date.createRandomMonth();
    date.createRandomDay();
    date.setWeekday();
}

void Game::loadHighScore() {
    QFile file("highScore.xml");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(&file);
        while (!xml.atEnd()) {
            xml.readNext();
            if (xml.isStartElement() && xml.name() == QString("score")) {
                highScore = xml.readElementText().toInt();
            }
        }
        file.close();
    }
}

void Game::saveHighScore() {
    if (score > highScore) {
        QFile file("highScore.xml");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QXmlStreamWriter xml(&file);
            xml.setAutoFormatting(true);
            xml.writeStartDocument();
            xml.writeStartElement("highscore");
            xml.writeTextElement("score", QString::number(score));
            xml.writeEndElement();
            xml.writeEndDocument();
            file.close();
        }
    }
}

bool Game::checkAnswer(const std::string& answer) {
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

