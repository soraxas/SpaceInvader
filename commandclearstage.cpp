#include "commandclearstage.h"
#include "command.h"
#include "gamedialog.h"
#include <QTimer>

namespace game {
CommandClearStage::CommandClearStage(GameDialog* gDialog) : Command(gDialog){
}

/**
    Clear everything that is currently on screen and reset every game status
*/
void CommandClearStage::execute(){
    // clear/reset everything
    if(gDialog->ship){
        gDialog->ship->dead = false;
        gDialog->ship->set_x(gDialog->SCALEDWIDTH/2);
    }
    // free all bullets
    for(auto&& b : gDialog->bullets)
        delete b;
    gDialog->bullets.clear();
    gDialog->powerups.clear();
    gDialog->explosions.clear();
    gDialog->laserBeam.exists = false;
    gDialog->statusBar.barrierEnergy = 0;
    gDialog->statusBar.plasmaEnergy = 100;
    gDialog->gameScore = 0;
    gDialog->statusBar.plasmaDrained = false;
    gDialog->barriers.clear();
    gDialog->cursor.setCursorState(FIGHTER);
    delete gDialog->swarms;
    // create a default swarms for the game
    SwarmInfo def = SwarmInfo();
    gDialog->swarms = new Swarm(def, *gDialog->ship);
}
}
