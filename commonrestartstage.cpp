#include "commandgamestart.h"
#include "command.h"
#include "gamedialog.h"
#include <QTimer>

namespace game {
CommandRestartStage::CommandRestartStage(GameDialog* gDialog) : Command(gDialog){
}

void CommandRestartStage::execute(){
    // first clear/reset everything
    gDialog->commandClearStage->execute();

    gDialog->ship->set_x(gDialog->SCALEDWIDTH/2);
    // reset all aliens
    gDialog->generateAliens(gDialog->c->getSwarmList()[gDialog->curStageNum]);
}
}
