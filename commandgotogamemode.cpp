#include "commandgotogamemode.h"
#include "command.h"
#include "gamedialog.h"


namespace game {
class GameMenu;
CommandGotoGameMode::CommandGotoGameMode(GameDialog* gDialog) : Command(gDialog){
}

void CommandGotoGameMode::execute(){
    // set the state and change in-game status
    gDialog->currentState = GAME_STATUS_IN_GAME;
    gDialog->curStageNum = 0; // reset the stage number

    // change the menu item visibility
    gDialog->gameMenu.ui->startGameBtn->setHidden(true);
    gDialog->gameMenu.ui->stageMakerBtn->setHidden(true);
    gDialog->gameMenu.ui->leaderBoardBtn->setHidden(true);
    gDialog->gameMenu.ui->returnToTitleBtn->setHidden(false);
}
}