#ifndef COMMONRESTARTSTAGE_H
#define COMMONRESTARTSTAGE_H

/**
    Command used restart the current stage and re-spawn every enemy aliens
*/

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
