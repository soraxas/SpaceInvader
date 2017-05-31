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
}

GameMenu::~GameMenu(){
    delete ui;
}


// override close event
void GameMenu::reject() {
    // resume game (if it was in game mode)
    //    if(gDialog->currentState == GAME_STATUS_IN_GAME)
    gDialog->commandGameStart->execute();

    // reset value
    ui->gameSpeedSlider->setValue(speedModifier);
    ui->dropRateSlider->setValue(powerupDropRate);
    // close
    QDialog::reject();
}

//void updateSettingDisplay(){}

}
void game::GameMenu::on_gameSpeedSlider_valueChanged(int value) {
    //    this->speedModifier = position;
    //    ui->GameSpeedHorizontalLayout->speedModifier
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
