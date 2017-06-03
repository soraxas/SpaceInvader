#ifndef COMMANDGAMEPAUSE_H
#define COMMANDGAMEPAUSE_H

/**
    Command used to Pause the timer and animations of the game elements
*/

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
