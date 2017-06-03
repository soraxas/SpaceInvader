#include "commandgotostagemakermode.h"
#include "command.h"
#include "gamedialog.h"


namespace game {
class GameMenu;
CommandGotoStageMakerMode::CommandGotoStageMakerMode(GameDialog* gDialog) : Command(gDialog){
}

void CommandGotoStageMakerMode::execute(){
    // set the state and change in-game status
    gDialog->currentState = GAME_STATUS_STAGE_MAKER;
    gDialog->cursor.setCursorState(STAGEMAKER);
    gDialog->commandClearStage->execute();

    // change the menu item visibility
    gDialog->gameMenu.ui->startGameBtn->setHidden(true);
    gDialog->gameMenu.ui->stageMakerBtn->setHidden(true);
    gDialog->gameMenu.ui->leaderBoardBtn->setHidden(true);
    gDialog->gameMenu.ui->returnToTitleBtn->setHidden(false);
}
}
