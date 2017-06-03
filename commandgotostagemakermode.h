#ifndef COMMANDGOTOSTAGEMAKERMODE_H
#define COMMANDGOTOSTAGEMAKERMODE_H

/**
    Command used as the functionality of the game menu, to go to the stage maker mode
*/

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
