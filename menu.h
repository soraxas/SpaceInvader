#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QPushButton>
namespace game {
class Menu {
public:
    Menu(QWidget* parent, QString name, int& playeScore, QList<QPair<QString, int>> scores);
    ~Menu();
    void displayMenu(bool paused);
    void openScore();

private:
    void makeButtons(QWidget* parent, QString name);
    void closeButtons();  // if any buttons are left open, close them
    int& gameScore;
    QPushButton* score;

    QLabel* playerName;
    QLabel* playerScoreLabel;
    void revealPlayerScore(bool open);
};
}
#endif  // SCOREBUTTON_H
