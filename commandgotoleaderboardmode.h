#ifndef COMMANDGOTOLEADERBOARDMODE_H
#define COMMANDGOTOLEADERBOARDMODE_H

/**
    Command used as the functionality of the game menu, to go to the leader board mode
*/

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
