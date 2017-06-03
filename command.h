#ifndef COMMAND_H
#define COMMAND_H

/**
    Abstract class that defines how a command would look like. Every command needs to implement the
    execute method
*/

namespace game {
class GameDialog;

class Command{
public:
    Command(GameDialog* gamedialog) : gDialog(gamedialog){}
    virtual void execute() = 0;
protected:
    GameDialog* gDialog;
};
}

#endif // COMMAND_H
