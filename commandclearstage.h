#ifndef COMMANDCLEARSTAGE_H
#define COMMANDCLEARSTAGE_H

#include "command.h"

namespace game {
class GameDialog;
class CommandClearStage : public Command
{
public:
    CommandClearStage(GameDialog* gamedialog);
    virtual void execute();
};
}
#endif // COMMANDCLEARSTAGE_H
