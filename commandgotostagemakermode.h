#ifndef COMMANDGOTOSTAGEMAKERMODE_H
#define COMMANDGOTOSTAGEMAKERMODE_H

#include "command.h"

namespace game {
class GameDialog;
class CommandGotoStageMakerMode : public Command
{
public:
    CommandGotoStageMakerMode(GameDialog* gamedialog);
    virtual void execute();
};
}
#endif // COMMANDGOTOSTAGEMAKERMODE_H
