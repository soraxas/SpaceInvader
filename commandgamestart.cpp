#include "commandgamestart.h"
#include "command.h"
#include "gamedialog.h"
#include <QTimer>

namespace game {
CommandGameStart::CommandGameStart(GameDialog* gDialog) : Command(gDialog){
}

void CommandGameStart::execute(){
    gDialog->paused = false;
    gDialog->timer->start(static_cast<int>(gDialog->frames * gDialog->timerModifier));

    if(gDialog->legacyMode){
        gDialog->menu->displayMenu(gDialog->paused);
        return;
    }

    // revert cursor state to whatever it was before
    gDialog->cursor.setCursorState(gDialog->cursor.preState);
    // show the main game menu
    gDialog->gameMenu.hide();
}
}
