#ifndef COMMANDGAMESTART_H
#define COMMANDGAMESTART_H

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
