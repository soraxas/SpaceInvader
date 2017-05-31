#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>

namespace Ui { // forward declarate from auto generated header
class GameMenu;
}

namespace game{
class GameDialog;
class GameMenu : public QDialog
{
    Q_OBJECT

public:
    explicit GameMenu(GameDialog* gDialog, QWidget *parent = 0);
    ~GameMenu();

private slots:
    void reject();

    void on_gameSpeedSlider_valueChanged(int value);

    void on_dropRateSlider_valueChanged(int value);

    void on_applySetting_clicked();

private:
    GameDialog* gDialog;
    Ui::GameMenu *ui;
    int speedModifier;
    int powerupDropRate;
};
}
#endif // GAMEMENU_H
