#include "commandgototitlescreenmode.h"
#include "command.h"
#include "gamedialog.h"
#include <QtDebug>

namespace game {
class GameMenu;
CommandGotoTitleScreenMode::CommandGotoTitleScreenMode(GameDialog* gDialog) : Command(gDialog){
}

void CommandGotoTitleScreenMode::execute(){
    // set the state and change in-game status
    gDialog->currentState = GAME_STATUS_TITLE_SCREEN;
    gDialog->commandClearStage->execute();
    gDialog->stageTransitionBox.moveTo(gDialog->SCALEDWIDTH, gDialog->stageTransitionBox.y());
    gDialog->stageTransition = false;
    gDialog->curStageNum = 0;
    gDialog->leaderBoard.reset();

    // change the menu item visibility
    gDialog->gameMenu.ui->startGameBtn->setHidden(false);
    gDialog->gameMenu.ui->stageMakerBtn->setHidden(false);
    gDialog->gameMenu.ui->leaderBoardBtn->setHidden(false);
    gDialog->gameMenu.ui->returnToTitleBtn->setHidden(true);
}
}
