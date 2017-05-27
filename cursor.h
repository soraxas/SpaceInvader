#ifndef CURSOR_H
#define CURSOR_H

#include <QPixmap>
#include <QPainter>
#include <vector>
#include "cursorstate.h"
#include "fighterstate.h"
#include "normalstate.h"

namespace game{

enum CURSOR_STATE{NORMAL, FIGHTER, END_OF_CURSOR_STATE};
class GameDialog;
class Cursor
{
public:
    Cursor(GameDialog* gDialog);
    ~Cursor();

    void processMousePress(QMouseEvent* event);
    void processMouseRelease(QMouseEvent* event);
    CursorState* getCurState();
    void setCursorState(CURSOR_STATE state);

    bool leftPressing; // keep track if left button is currently pressing
    bool rightPressing; // keep track if right button is currently pressing
    int radius; // radius of the cursor

    CURSOR_STATE state;
    CursorState* currentState;
    std::map<CURSOR_STATE, CursorState*> cursorStatesList;
};
}
#endif // CURSOR_H
