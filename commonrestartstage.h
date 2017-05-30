#ifndef COMMONRESTARTSTAGE_H
#define COMMONRESTARTSTAGE_H

#include "command.h"

namespace game {
class GameDialog;
class CommandRestartStage : public Command
{
public:
    CommandRestartStage(GameDialog* gamedialog);
    virtual void execute();
};
}

#endif // COMMONRESTARTGAME_H
