#ifndef COMMANDGAMESTART_H
#define COMMANDGAMESTART_H

/**
    Command used to start the timer and animations of the game elements
*/

#include "command.h"

namespace game {
class GameDialog;
class CommandGameStart : public Command
{
public:
    CommandGameStart(GameDialog* gamedialog);
    virtual void execute();
};
}
#endif // COMMANDGAMESTART_H
