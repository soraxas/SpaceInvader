#ifndef COMMANDGOTOLEADERBOARDMODE_H
#define COMMANDGOTOLEADERBOARDMODE_H

#include "command.h"

namespace game {
class GameDialog;
class CommandGotoLeaderBoardMode : public Command
{
public:
    CommandGotoLeaderBoardMode(GameDialog* gamedialog);
    virtual void execute();
};
}
#endif // COMMANDGOTOLEADERBOARDMODE_H
