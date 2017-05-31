#include "commandgamepause.h"
#include "command.h"
#include "gamedialog.h"
#include <QTimer>

namespace game {
CommandGamePause::CommandGamePause(GameDialog* gDialog) : Command(gDialog){
}

void CommandGamePause::execute(){
    gDialog->paused = true;
    gDialog->timer->stop();

    if(gDialog->legacyMode){
        gDialog->menu->displayMenu(gDialog->paused);
        return;
    }

    // revert cursor state to whatever it was before
    gDialog->cursor.setCursorState(NORMAL);
}
}
