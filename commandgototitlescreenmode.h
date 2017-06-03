#ifndef COMMANDGOTOTITLESCREENMODE_H
#define COMMANDGOTOTITLESCREENMODE_H

/**
    Command used as the functionality of the game menu, to go to the title screen
*/

#include "command.h"

namespace game {
class GameDialog;
class CommandGotoTitleScreenMode : public Command
{
public:
    CommandGotoTitleScreenMode(GameDialog* gamedialog);
    virtual void execute();
};
}

#endif // COMMANDGOTOTITLESCREENMODE_H
