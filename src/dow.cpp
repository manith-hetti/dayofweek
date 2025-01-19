///////////////////////////////////////////////////////////////////////////////////////////////
///			Distributed under the GNU Lesse General Public Licence, Version 3				///
/// 					(See accompanying file LICENSE or copy at: 							///
/// 					https://www.gnu.org/licenses/lgpl-3.0.en.html)						///
///////////////////////////////////////////////////////////////////////////////////////////////


#include "dow.h"
#include "./ui_dow.h"
#include "dategenerator.h"


DOW::DOW(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DOW)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setupConnections();
    updateDisplay();

};

DOW::~DOW() {
    delete ui;
}

void DOW::setupConnections() {
    connect(ui->NormalModeButton, &QPushButton::clicked, this, &DOW::startNormalMode);
    connect(ui->ChallengeModeButton, &QPushButton::clicked, this, &DOW::startChallengeMode);

    QList<QPushButton*> weekdayButtons = {
        ui->monday, ui->tuesday, ui->wednesday, ui->thursday,
        ui->friday, ui->saturday, ui->sunday
    };

    for (auto* button : weekdayButtons) {
        connect(button, &QPushButton::clicked, this, &DOW::handleWeekdayButton);
    }

    connect(ui->helpButton, &QPushButton::clicked, this, &DOW::showHelp);
    connect(ui->backButton, &QPushButton::clicked, this, &DOW::goBack);
    connect(ui->goHome, &QPushButton::clicked, this, &DOW::handleGameOver);

}

void DOW::updateDisplay() {
    if (!currentGame) return;

    const Date& date = currentGame->getCurrentDate();
    QString question = QString("What day of the week was: %1/%2/%3")
        .arg(date.getYear())
        .arg(date.getMonth())
        .arg(date.getDay());

    ui->dateLabel->setText(question);
    ui->scoreLabel->setText("Score: " + QString::number(currentGame->getScore()));
    ui->livesLabel->setText("Lives: " + QString::number(currentGame->getLives()));
    ui->highScoreLabel->setText("HighScore: " + QString::number(currentGame->getHighScore()));
}

void DOW::startNormalMode() {
    currentGame = std::make_unique<Game>();
    ui->stackedWidget->setCurrentIndex(1);
    ui->timerLabel->setVisible(false);
    updateDisplay();
}

void DOW::startChallengeMode() {
    auto challengeGame = std::make_unique<ChallengeMode>();
    ChallengeMode* challengeModePtr = static_cast<ChallengeMode*>(challengeGame.get());
    connect(challengeModePtr, &ChallengeMode::timeUpdated,
            this, &DOW::updateTimerDisplay);
    connect(challengeModePtr, &ChallengeMode::timeExpired,
            this, &DOW::handleTimeExpired);
    connect(challengeModePtr, &ChallengeMode::livesUpdated, this, &DOW::updateLivesDisplay);


    currentGame = std::move(challengeGame);
    ui->timerLabel->setVisible(true);
    static_cast<ChallengeMode*>(currentGame.get())->startTimer();

    ui->stackedWidget->setCurrentIndex(1);
    updateDisplay();
}

void DOW::updateTimerDisplay(int secondsLeft) {
    if (ui->timerLabel) {
        QString time_left = QString("Time Left: %1 seconds").arg(secondsLeft);
        ui->timerLabel->setText(time_left);

        if (secondsLeft <= 10) {
            ui->timerLabel->setStyleSheet("color: red;");
        } else {
            ui->timerLabel->setStyleSheet("");
        }
    }
}

void DOW::handleWeekdayButton() {
    if (!currentGame) return;

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    bool correct = currentGame->checkAnswer(button->text().toStdString());
    ui->userResponse->setText(correct ? "You're Correct!" : "You're Wrong!");

    if (currentGame->isGameOver()) {
        handleGameOver();
    } else {
        updateDisplay();
    }
}

void DOW::handleGameOver() {
    if (currentGame->isNewHighScore()) {
    }
    ui->stackedWidget->setCurrentIndex(0);
}

void DOW::handleTimeExpired() {
    if (!currentGame) return;
    ui->stackedWidget->setCurrentIndex(0);
}

void DOW::showHelp() {
    if (!currentGame) return;

    const Date& date = currentGame->getCurrentDate();

    int century = date.getYear() / 100;
    int year = date.getYear();
    int month = date.getMonth();
    int day = date.getDay();

    // Century map (as in your original code)
    std::map<int, int> centuryMap;
    centuryMap[17] = 0;
    centuryMap[18] = 5;
    centuryMap[19] = 3;
    centuryMap[20] = 2;

    int duodecenial = (year - century*100) / 12;
    int yearDiff = (year - century*100) - duodecenial*12;

    // Leap year handling
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int doomsdays[12] = {3, 28, 14, 4, 9, 6, 11, 8, 5, 10, 7, 12};
    if (leap) {
        doomsdays[0] = 4;
        doomsdays[1] = 29;
    }
    int doomsday = doomsdays[month - 1];

    int doomsdayDiff = (((day - doomsday) % 7) + 7) % 7;

    int answer = (centuryMap[century] + duodecenial + yearDiff + (yearDiff/4) + doomsdayDiff) % 7;

    std::string weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    std::string weekday = weekdays[answer];

    // Update help page labels
    ui->problemLabel->setText(
        QString("This method involves adding up numbers based on the given date. In this instance we'll be working through %1/%2/%3.")
        .arg(year).arg(month).arg(day)
    );

    ui->centuryLabel->setText(
        QString("Since the century is %1, we'll add %2")
        .arg(century).arg(centuryMap[century])
    );

    ui->yearLabel1->setText(
        QString("We first add the corresponding duodecenial value: %1")
        .arg(duodecenial)
    );

    if (yearDiff == 0) {
        ui->yearLabel2->setText("We have nothing else to do since the year is a multiple of 12");
    } else {
        ui->yearLabel2->setText(
            QString("Secondly we add the difference between the year and the nearest multiple of 12: %1")
            .arg(yearDiff)
        );
    }

    if (yearDiff / 4 >= 1) {
        ui->yearLabel3->setText(
            QString("In this instance we have to account for the leap years passed, so we finally add: %1")
            .arg(yearDiff/4)
        );
    }

    ui->doomsdayLabel->setText(
        QString("In this instance the doomsday we're concerned with is: %1")
        .arg(doomsday)
    );

    ui->doomsdayCalcLabel->setText(
        QString("We're going to take away our date %1 from our doomsday value, and take its modulo 7 value, which leads to: %2")
        .arg(day).arg(doomsdayDiff)
    );

    ui->answerLabel->setText(
        QString("We add up all of our values and take the modulo of 7 again to find: %1, which is a %2.")
        .arg(answer).arg(QString::fromStdString(weekday))
    );

    ui->stackedWidget->setCurrentIndex(2);
}

void DOW::goBack() {
    if (!currentGame) {
        ui->stackedWidget->setCurrentIndex(1);
        return;
    }

    currentGame->lostLife();

    if (currentGame->isGameOver()) {
        ui->stackedWidget->setCurrentIndex(0);
        return;
    }

    currentGame->generateNewDate();

    updateDisplay();

    ui->stackedWidget->setCurrentIndex(1);
}

void DOW::updateLivesDisplay(int lives) {
    ui->livesLabel->setText("Lives: " + QString::number(lives));
}

