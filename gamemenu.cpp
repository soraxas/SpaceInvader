#include "gamemenu.h"
#include "gamedialog.h"
#include "ui_gamemenu.h"
#include <QString>

namespace game{
GameMenu::GameMenu(GameDialog* gDialog, QWidget *parent) :
    QDialog(parent), ui(new Ui::GameMenu), gDialog(gDialog){
    ui->setupUi(this);
    speedModifier = 10;
    powerupDropRate = 35;
    ui->returnToTitleBtn->setHidden(true);
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


void game::GameMenu::on_exitBtn_clicked()
{
    gDialog->close();
    close();
}

void game::GameMenu::on_stageMakerBtn_clicked()
{
    if(gDialog->currentState != GAME_STATUS_STAGE_MAKER){
        gDialog->currentState = GAME_STATUS_STAGE_MAKER;
        gDialog->commandClearStage->execute();
        gDialog->cursor.setCursorState(STAGEMMAKER);
        ui->startGameBtn->setHidden(true);
        ui->stageMakerBtn->setHidden(true);
        ui->leaderBoardBtn->setHidden(true);
        ui->returnToTitleBtn->setHidden(false);
        //        ui->stageMakerBtn->setHidden(true);
    }else{
        gDialog->currentState = GAME_STATUS_TITLE_SCREEN;
    }
    close();
}

void game::GameMenu::on_leaderBoardBtn_clicked()
{

}

void game::GameMenu::on_startGameBtn_clicked(){
    gDialog->currentState = GAME_STATUS_IN_GAME;
    gDialog->curStageNum = 0;
    close();
}

void game::GameMenu::on_returnToTitleBtn_clicked(){
    gDialog->currentState = GAME_STATUS_TITLE_SCREEN;
    gDialog->commandClearStage->execute();
    ui->startGameBtn->setHidden(false);
    ui->stageMakerBtn->setHidden(false);
    ui->leaderBoardBtn->setHidden(false);
    ui->returnToTitleBtn->setHidden(true);
    close();
}
