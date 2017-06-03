#ifndef COMMANDGOTOGAMEMODE_H
#define COMMANDGOTOGAMEMODE_H

/**
    Command used as the functionality of the game menu, to go to the actual game mode
*/

#include "command.h"

namespace game {
class GameDialog;
class CommandGotoGameMode : public Command
{
public:
    CommandGotoGameMode(GameDialog* gamedialog);
    virtual void execute();
};
}

#endif // COMMANDGOTOGAMEMODE_H
