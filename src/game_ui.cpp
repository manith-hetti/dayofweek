#include "game_ui.hpp"
#include "./ui_dow.h"

GameUI::GameUI(QWidget* parent) : QMainWindow(parent), ui(new Ui::GameUI) {
    ui->setupUi(this);
    this->showFullScreen();
    setupConnections();
    updateDisplay();
}

GameUI::~GameUI() {
    delete ui;
}

void GameUI::setupConnections() {
    connect(ui->NormalModeButton, &QPushButton::clicked, this, &GameUI::startNormalMode);
    connect(ui->ChallengeModeButton, &QPushButton::clicked, this, &GameUI::startChallengeMode);

    // Connect weekday buttons
    QList<QPushButton*> weekdayButtons = {
        ui->monday, ui->tuesday, ui->wednesday, ui->thursday,
        ui->friday, ui->saturday, ui->sunday
    };

    for (auto* button : weekdayButtons) {
        connect(button, &QPushButton::clicked, this, &GameUI::handleWeekdayButton);
    }

    connect(ui->helpButton, &QPushButton::clicked, this, &GameUI::showHelp);
    connect(ui->backButton, &QPushButton::clicked, this, &GameUI::goBack);
}

void GameUI::updateDisplay() {
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

void GameUI::startNormalMode() {
    currentGame = std::make_unique<NormalMode>();
    ui->stackedWidget->setCurrentIndex(1);
    updateDisplay();
}

void GameUI::startChallengeMode() {
    auto challengeGame = std::make_unique<ChallengeMode>();
    connect(challengeGame.get(), &ChallengeMode::timeExpired,
            this, &GameUI::handleTimeExpired);

    currentGame = std::move(challengeGame);
    static_cast<ChallengeMode*>(currentGame.get())->startTimer();

    ui->stackedWidget->setCurrentIndex(1);
    updateDisplay();
}

void GameUI::handleWeekdayButton() {
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

void GameUI::handleGameOver() {
    if (currentGame->isNewHighScore()) {
        // Show high score message
    }
    this->close();
}

void GameUI::handleTimeExpired() {
    ui->userResponse->setText("Time's up!");
    handleGameOver();
}
