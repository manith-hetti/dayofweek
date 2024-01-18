///////////////////////////////////////////////////////////////////////////////////////////////
///			Distributed under the GNU Lesse General Public Licence, Version 3				///
/// 					(See accompanying file LICENSE or copy at: 							///
/// 					https://www.gnu.org/licenses/lgpl-3.0.en.html)						///
///////////////////////////////////////////////////////////////////////////////////////////////


#include "dow.h"
#include "./ui_dow.h"
#include "dategenerator.h"

using namespace std;


DateGenerator ydm;

DOW::DOW(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DOW)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);


    //Loads the highScore and initialises the lives and score
    highScore = DOW::loadHighScore();
    lives = 3;
    score = 0;;

    //Assigns fonts to labels.
    QFont f("Ariel", 18, QFont::Bold);
    ui->dateLabel->setFont(f);
    ui->scoreLabel->setFont(f);
    ui->livesLabel->setFont(f);
    ui->highScoreLabel->setFont(f);

    /**
     * @brief connect: assinging all the slots to signals
     */
    connect(ui->monday, &QPushButton::clicked, this, &DOW::checkWeekday);
    connect(ui->tuesday, &QPushButton::clicked, this, &DOW::checkWeekday);
    connect(ui->wednesday, &QPushButton::clicked, this, &DOW::checkWeekday);
    connect(ui->thursday, &QPushButton::clicked, this, &DOW::checkWeekday);
    connect(ui->friday, &QPushButton::clicked, this, &DOW::checkWeekday);
    connect(ui->saturday, &QPushButton::clicked, this, &DOW::checkWeekday);
    connect(ui->sunday, &QPushButton::clicked, this, &DOW::checkWeekday);
    connect(ui->helpButton, &QPushButton::clicked, this, &DOW::changePage);
    connect(ui->pushButton, &QPushButton::clicked, this, &DOW::goBack);

    // Assigning values to labels.
    ui->dateLabel->setText(generateDate());
    ui->highScoreLabel->setText("HighScore: " + QString::number (highScore));
    ui->livesLabel->setText("Lives: " + QString::number (lives));
    ui->scoreLabel->setText("Score: " + QString::number (score));

 }

DOW::~DOW()
{
    delete ui;
}

QString DOW::generateDate()
{
    year = ydm.getYear();
    month = ydm.getMonth();
    date = ydm.getDate();
    century = year / 100;
    leap = ydm.isLeap();
    QString question = "What day of the week was: " + QString::number (year) + "/" + QString::number (month) + "/" + QString::number (date);
    return question;
}

void DOW::checkWeekday() {
    string wday = ydm.getWeekday();
    QPushButton* button = qobject_cast<QPushButton*>(sender());	// Checks what button the user pressed.
    string pressed = button->text().toStdString();				// Converts the button text to string to check if the user input matches the correct weekday(wday).
    if (wday == pressed) {
        score++;
        ui->userResponse->setText("You're Correct!");
        ui->dateLabel->setText(generateDate());
    }
    else {
        lives--;
        if (lives == 0 && score >= highScore) {
            DOW::saveHighScore(score);
            this->close();
        }
        else if (lives <= 0) {
            this ->close();
        }
        ui->userResponse->setText("You're Wrong!");
        ui->dateLabel->setText(generateDate());
    }
    ui->livesLabel->setText("Lives: " + QString::number (lives));
    ui->scoreLabel->setText("Score: " + QString::number (score));
}

void DOW::saveHighScore(int score) {
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

int DOW::loadHighScore() {
    QFile file("highScore.xml");
    int score = 0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(&file);
        while (!xml.atEnd()) {
            xml.readNext();
            if (xml.isStartElement() && xml.name() == QString( "score")) {
                score = xml.readElementText().toInt();
            }
        }
        file.close();
    }
    return score;
}


void DOW::changePage()
{
    ui->stackedWidget->setCurrentIndex(1);

    /**
     * centuryMap: The values corresponding to each century.
     * duodecenial: The multiple of 12 below the year.
     * yearDiff: The difference between the year and the duodecenial, e.g if the given year is 1950 the difference (1950 - 1948) would be 2.
     * doomsday: The doomsday corresponding to the given month, chosen from an array of days for each month.
     */
    map<int, int> centuryMap;
    centuryMap[17] = 0;
    centuryMap[18] = 5;
    centuryMap[19] = 3;
    centuryMap[20] = 2;

    int duodecenial = (year - century*100) / 12;

    int yearDiff = (year - century*100) - duodecenial*12;

    int doomsdays[12] = {3, 28, 14, 4, 9, 6, 11, 8, 5, 10, 7, 12};
        if (leap) {
            doomsdays[0] = 4;
            doomsdays[1] = 29;
    }
    int doomsday = doomsdays[month - 1];

    int doomsdayDiff = (((date - doomsday) % 7) + 7) % 7;

    int answer = (centuryMap[century]+duodecenial+yearDiff+(yearDiff/4)+doomsdayDiff) % 7;

    string weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    string weekday = weekdays[answer];

    ui->problemLabel->setText(
        "This method involves adding up numbers based on the given date. In this instance we'll be working through "
        + QString::number (year) + "/"
        + QString::number (month) + "/"
        + QString::number (date) + ".");
    ui->centuryLabel->setText(
        "Since the century is " + QString::number (century)
        + ", we'll add " + QString::number (centuryMap[century]));   
    ui->yearLabel1->setText("We first add the corresponding duodecenial value: " + QString::number(duodecenial));
    if (yearDiff == 0) {
        ui->yearLabel2->setText("We have nothing else to do since the year is a multiple of 12");
    }
    else {
        ui->yearLabel2->setText("Secondly we add the difference between the year and the nearest multiple of 12: " + QString::number (yearDiff));
    }
    if (yearDiff / 4 >= 1) {
        ui->yearLabel3->setText("In this instance we have to account for the leap years passed, so we finally add: " + QString::number (yearDiff/4));
    }
    ui->doomsdayLabel->setText("In this instance the doomsday we're concerned with is: " + QString::number (doomsday));
    ui->doomsdayCalcLabel->setText("We're going to take away our date " + QString::number (date) + " from our doomsday value, and take its modulo 7 value, which leads to: " + QString::number (doomsdayDiff));
    ui->answerLabel->setText("We add up all of our values and take the modulo of 7 again to find: " + QString::number (answer) + ", which is a " + QString::fromStdString(weekday) + ".");
}

void DOW::goBack()
{
    if (lives <= 0) {
        this->close();
    }
    ui->dateLabel->setText(generateDate());
    lives--;
    ui->livesLabel->setText("Lives: " + QString::number (lives));
    ui->stackedWidget->setCurrentIndex(0);
}

