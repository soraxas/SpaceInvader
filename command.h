#ifndef COMMAND_H
#define COMMAND_H

namespace game {
class GameDialog;

class Command{
    Command(GameDialog* gamedialog) : gd(gamedialog){}
    virtual void execute() = 0;
protected:
    GameDialog* gd;
};
}

#endif // COMMAND_H
