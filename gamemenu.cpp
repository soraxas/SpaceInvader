#include "gamemenu.h"
#include "gamedialog.h"
#include <QString>
#include "qtsoundplayer.h"

namespace game{
GameMenu::GameMenu(GameDialog* gDialog, QWidget *parent, int powerupDropRate) :
    QDialog(parent), ui(new Ui::GameMenu), gDialog(gDialog), powerupDropRate(powerupDropRate){
    ui->setupUi(this);
    speedModifier = 10;
    ui->returnToTitleBtn->setHidden(true);
    ui->dropRateSlider->setValue(powerupDropRate);
    ui->dropRate->setText(QString::number(powerupDropRate)+"%");
    bgMusicVolumeLevel = QTSoundPlayer::getInstance()->getBgMusicVolumeLevel();
    ui->bgMusicLabel->setText(QString::number(bgMusicVolumeLevel)+"%");
    ui->bgMusicSlider->setValue(bgMusicVolumeLevel);
}

GameMenu::~GameMenu(){
    delete ui;
}


// override close event
void GameMenu::reject() {
    // resume game (if it was in game mode)
    gDialog->commandGameStart->execute();

    // reset value
    ui->gameSpeedSlider->setValue(speedModifier);
    ui->dropRateSlider->setValue(powerupDropRate);
    // close
    QDialog::reject();
}


}
void game::GameMenu::on_gameSpeedSlider_valueChanged(int value) {
    ui->speedModifier->setText("x " + QString::number(value/10.0));
}

void game::GameMenu::on_dropRateSlider_valueChanged(int value){
    ui->dropRate->setText(QString::number(value)+"%");
}

void game::GameMenu::on_applySetting_clicked(){
    speedModifier = ui->gameSpeedSlider->value();
    powerupDropRate = ui->dropRateSlider->value();
    // apply settings to game dialog
    gDialog->timerModifier = 1 / (speedModifier/10.0);
    gDialog->powerUpDropRate = powerupDropRate;
}


void game::GameMenu::on_exitBtn_clicked(){
    gDialog->close();
    close();
}

void game::GameMenu::on_stageMakerBtn_clicked(){
    gDialog->commandGoToStageMakerMode->execute();
    close();
}

void game::GameMenu::on_leaderBoardBtn_clicked(){
    gDialog->commandGoToLeaderBoardMode->execute();
    close();
}

void game::GameMenu::on_resumeBtn_clicked(){
    // resume game
    gDialog->commandGameStart->execute();
    close();
}

void game::GameMenu::on_startGameBtn_clicked(){
    gDialog->commandGoToGameMode->execute();
    close();
}

void game::GameMenu::on_returnToTitleBtn_clicked(){
    gDialog->commandGoToTitleScreenMode->execute();
    close();
}

void game::GameMenu::on_bgMusicSlider_valueChanged(int value){
    bgMusicVolumeLevel = value;
    ui->bgMusicLabel->setText(QString::number(value)+"%");
    QTSoundPlayer::getInstance()->setBgMusicVolumeLevel(value);
}

