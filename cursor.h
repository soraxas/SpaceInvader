#ifndef CURSOR_H
#define CURSOR_H

#include <QPixmap>
#include <QPainter>
#include <vector>
#include "cursorstate.h"
#include "normalstate.h"
#include "fighterstate.h"
#include "penstate.h"

namespace game{

enum CURSOR_STATE{NORMAL, FIGHTER, PEN, END_OF_CURSOR_STATE};
class GameDialog;
class Cursor{
public:
    Cursor(GameDialog* gDialog);
    ~Cursor();
    CursorState* getCurState();
    void setCursorState(CURSOR_STATE state);

    // ==== VARIABLES ====
    bool leftPressing; // keep track if left button is currently pressing
    bool rightPressing; // keep track if right button is currently pressing
    int radius; // radius of the cursor
    CURSOR_STATE state;
    CursorState* currentState;
    std::map<CURSOR_STATE, CursorState*> cursorStatesList;
};
}
#endif // CURSOR_H
