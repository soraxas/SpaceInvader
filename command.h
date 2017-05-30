#ifndef COMMAND_H
#define COMMAND_H

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
