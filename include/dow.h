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

QT_BEGIN_NAMESPACE
namespace Ui { class DOW; }
QT_END_NAMESPACE

class DOW : public QMainWindow
{
    Q_OBJECT

public:
    DOW(QWidget *parent = nullptr);
    ~DOW();

    /**
     * @brief generateDate runs the functions in dategenerator class and assigns
     *  	  the corresponding values to year, month, date century and leap.
     *  	  The dateLabel ui is also changed to reflect the new date.
     * @return QString question ("What day of the week was: ... ")
     */
    QString generateDate();

    /**
     * @brief saveHighScore takes the high score value as an input
     * 		  stores the high score value in an xml file,
     * 		  if a xml file doesn't exist it will create one.
     * @param highScore
     */
    void saveHighScore(int highScore);

    /**
     * @brief loadHighScore reads the highScore.xml file and reads the score value
     * @return score
     */
    int loadHighScore();

private slots:

    /**
     * @brief checkWeekday checks if the button pressed by the user is equal to the correct weekday value.
     * 		  if the input is correct the score is increased and a new date is generated
     * 		  else the lives are reduced by 1 and a new date is generated,
     * 		      if the lives were equal to 0 the program is closed.
     */
    void checkWeekday();

    /**
     * @brief changePage when button is pressed the page changes to the explanation page
     */
    void changePage();

    /**
     * @brief goBack generates a new date and returns to the original page.
     */
    void goBack();

private:
    Ui::DOW *ui;
    int lives;
    int score;
    int highScore;
    int year;
    int century;
    int month;
    int date;
    bool leap;
};
#endif // DOW_H
