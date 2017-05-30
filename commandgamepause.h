#ifndef COMMANDGAMEPAUSE_H
#define COMMANDGAMEPAUSE_H

#include "command.h"

namespace game {
class GameDialog;
class CommandGamePause : public Command
{
public:
    CommandGamePause(GameDialog* gamedialog);
    virtual void execute();
};
}

#endif // COMMANDGAMEPAUSE_H
