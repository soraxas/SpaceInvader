#include "commandgamestart.h"
#include "command.h"
#include "gamedialog.h"
#include <QTimer>

namespace game {
CommandRestartStage::CommandRestartStage(GameDialog* gDialog) : Command(gDialog){
}

void CommandRestartStage::execute(){
    // first clear/reset everything
    gDialog->ship->dead = false;
    gDialog->ship->set_x(gDialog->SCALEDWIDTH/2);
    for(auto&& b : gDialog->bullets)
        delete b;
    gDialog->bullets.clear();
    gDialog->powerups.clear();
    gDialog->explosions.clear();
    gDialog->laserBeam.exists = false;
    gDialog->statusBar.barrierEnergy = 0;
    gDialog->statusBar.plasmaEnergy = 100;
    gDialog->statusBar.plasmaDrained = false;
    gDialog->cursor.setCursorState(FIGHTER);

    // reset all aliens
    gDialog->generateAliens(gDialog->c->getSwarmList()[gDialog->curStageNum]);
}
}
