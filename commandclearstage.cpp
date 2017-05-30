#include "commandclearstage.h"
#include "command.h"
#include "gamedialog.h"
#include <QTimer>

namespace game {
CommandClearStage::CommandClearStage(GameDialog* gDialog) : Command(gDialog){
}

void CommandClearStage::execute(){
    // clear/reset everything
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
    gDialog->barriers.clear();
    gDialog->cursor.setCursorState(FIGHTER);
    delete gDialog->swarms;
    SwarmInfo def = SwarmInfo();
    gDialog->swarms = new Swarm(def, *gDialog->ship);
}
}
