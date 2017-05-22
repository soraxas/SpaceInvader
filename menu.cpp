#include "menu.h"

namespace game {
Menu::Menu(QWidget* parent, QString name, int& playerScore, QList<QPair<QString, int>> scores)
        : gameScore(playerScore) {
    // Scores could be read in the future.
    makeButtons(parent, name);
}

Menu::~Menu() {
    delete score;
    delete playerName;
    delete playerScoreLabel;
}

void Menu::makeButtons(QWidget* parent, QString name) {
    score = new QPushButton("Score", parent);
    score->setGeometry(QRect(0, 0, 100, 30));
    score->setVisible(false);
    score->setStyleSheet("background-color: red");
    QObject::connect(score, SIGNAL(released()), parent, SLOT(showScore()));

    playerName = new QLabel(parent);
    playerName->setGeometry(0, 30, 100, 30);
    playerName->setText(name);
    playerName->setVisible(false);
    playerName->setStyleSheet("background-color: white");

    playerScoreLabel = new QLabel(parent);
    playerScoreLabel->setGeometry(100, 30, 100, 30);
    playerScoreLabel->setText(QString::number(gameScore));
    playerScoreLabel->setVisible(false);
    playerScoreLabel->setStyleSheet("background-color: gray");
}

// called when game is paused or unpaused
void Menu::displayMenu(bool paused) {
    if (!paused) {
        closeButtons();
    } else {
        score->setVisible(true);
    }
}

// helper, closes all the opened menus
void Menu::closeButtons() {
    score->setVisible(false);
    revealPlayerScore(false);
}

// helper function for OpenScore
void Menu::revealPlayerScore(bool open) {
    // recalculate playerScoreLabel
    playerScoreLabel->setText(QString::number(gameScore));
    playerName->setVisible(open);
    playerScoreLabel->setVisible(open);
}

void Menu::openScore() {
    if (playerName->isVisible()) {
        revealPlayerScore(false);
    } else {
        revealPlayerScore(true);
    }
}
}
