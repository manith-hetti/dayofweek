#pragma once
#include "game.hpp"
#include "normal_mode.hpp"
#include <QTimer>
#include <QObject>
#include <QDebug>

class ChallengeMode : public QObject, public Game {
    Q_OBJECT
private:
    QTimer* timer;
    const int TIME_LIMIT = 300000;
    int remainingTime;

public:
    ChallengeMode();
    ~ChallengeMode();

    void startTimer();
    void resetTimer();
    int getRemainingTime() const { return remainingTime; }
    void handleTimeExpired();
    void lostLife();

signals:
    void timeUpdated(int secondsLeft);
    void timeExpired();
    void livesUpdated(int lives);

private slots:
    void updateTimer();
};
