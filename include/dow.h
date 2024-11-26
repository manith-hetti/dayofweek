///////////////////////////////////////////////////////////////////////////////////////////////
///			Distributed under the GNU Lesse General Public Licence, Version 3				///
/// 					(See accompanying file LICENSE or copy at: 							///
/// 					https://www.gnu.org/licenses/lgpl-3.0.en.html)						///
///////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DOW_H
#define DOW_H

#include <QMainWindow>
#include <QList>
#include <QSignalMapper>
#include <QFont>
#include <QFile>
#include <QIODevice>
#include <QXmlStreamWriter>
#include <QStringView>
#include <QAbstractScrollArea>
#include "game.hpp"
#include "challenge_mode.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class DOW; }
QT_END_NAMESPACE

class DOW : public QMainWindow
{
    Q_OBJECT

public:
    DOW(QWidget *parent = nullptr);
    ~DOW();

private slots:

    void startNormalMode();
    void startChallengeMode();

    void updateTimerDisplay(int secondsLeft);
    void updateLivesDisplay(int lives);

    void showHelp();
    void goBack();

    void handleTimeExpired();
    void handleWeekdayButton();

private:
    Ui::DOW* ui;
    std::unique_ptr<Game> currentGame;
    void setupConnections();
    void updateDisplay();
    void handleGameOver();

};
#endif
