#include "commandgotoleaderboardmode.h"
#include "command.h"
#include "gamedialog.h"


namespace game {
class GameMenu;
CommandGotoLeaderBoardMode::CommandGotoLeaderBoardMode(GameDialog* gDialog) : Command(gDialog){
}

void CommandGotoLeaderBoardMode::execute(){
    // reload the leader board
    gDialog->leaderBoard.reset();
    // set the state and change in-game status
    gDialog->currentState = GAME_STATUS_LEADER_BOARD;
    gDialog->commandClearStage->execute();

    // change the menu item visibility
    gDialog->gameMenu.ui->startGameBtn->setHidden(true);
    gDialog->gameMenu.ui->stageMakerBtn->setHidden(true);
    gDialog->gameMenu.ui->leaderBoardBtn->setHidden(true);
    gDialog->gameMenu.ui->returnToTitleBtn->setHidden(false);
}
}
