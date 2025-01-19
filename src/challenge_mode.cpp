#include "challenge_mode.hpp"

ChallengeMode::ChallengeMode() : Game(), remainingTime(15) {
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &ChallengeMode::updateTimer);
}

ChallengeMode::~ChallengeMode() {
    if (timer) {
        timer->stop();
        delete timer;
    }
}


void ChallengeMode::startTimer() {
    remainingTime = 15;
    timer->start();
}

void ChallengeMode::resetTimer() {
    remainingTime = 15;
    timer->start();
}

void ChallengeMode::updateTimer() {
    remainingTime--;
    emit timeUpdated(remainingTime);

    if (remainingTime <= 0) {
        timer->stop();
        handleTimeExpired();
    }
}

void ChallengeMode::handleTimeExpired() {
    qDebug() << "Time Expired";
    if (getLives() < 1) {
        qDebug() << "Lives less than 1";
        emit timeExpired();
        return;
    }
    lostLife();
    resetTimer();
}

void ChallengeMode::lostLife() {
    if (lives > 0) {
        Game::lostLife();
        emit livesUpdated(Game::getLives());
    }
}
