#pragma once
#include <QMainWindow>
#include "game.hpp"
#include "normal_mode.hpp"
#include "challenge_mode.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class GameUI; }
QT_END_NAMESPACE


class GameUI : public QMainWindow {
    Q_OBJECT

private:
    Ui::GameUI* ui;
    std::unique_ptr<Game> currentGame;
    void setupConnections();
    void updateDisplay();
    void handleGameOver();

public:
    explicit GameUI(QWidget* parent = nullptr);
    ~GameUI();

private slots:
    void startNormalMode();
    void startChallengeMode();
    void handleWeekdayButton();
    void showHelp();
    void goBack();
    void handleTimeExpired();
};
