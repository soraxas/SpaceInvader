#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "ui_gamemenu.h"
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
    explicit GameMenu(GameDialog* gDialog, QWidget *parent = 0, int powerupDropRate = 35);
    ~GameMenu();

    Ui::GameMenu *ui;
private slots:
    void reject();
    void on_gameSpeedSlider_valueChanged(int value);
    void on_dropRateSlider_valueChanged(int value);
    void on_applySetting_clicked();
    void on_exitBtn_clicked();
    void on_stageMakerBtn_clicked();
    void on_leaderBoardBtn_clicked();
    void on_startGameBtn_clicked();
    void on_returnToTitleBtn_clicked();

    void on_bgMusicSlider_valueChanged(int value);

    void on_resumeBtn_clicked();

private:
    GameDialog* gDialog;
    int speedModifier;
    int powerupDropRate;
    int bgMusicVolumeLevel;
};
}
#endif // GAMEMENU_H
