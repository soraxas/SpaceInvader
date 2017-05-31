#ifndef COMMANDGOTOTITLESCREENMODE_H
#define COMMANDGOTOTITLESCREENMODE_H

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
