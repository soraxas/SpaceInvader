#ifndef COMMANDGOTOGAMEMODE_H
#define COMMANDGOTOGAMEMODE_H

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
