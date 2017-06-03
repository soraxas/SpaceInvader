#ifndef CURSOR_H
#define CURSOR_H

#include <QPixmap>
#include <QPainter>
#include <vector>
#include "cursorstate.h"
#include "normalstate.h"
#include "fighterstate.h"
#include "makerstate.h"
#include "penstate.h"

/**
    Class that provide the functionality of a cursor, that is, to function as the cursor when it's
    on top of the dialog box
*/

namespace game{

enum CURSOR_STATE{NORMAL, FIGHTER, PEN, STAGEMAKER, END_OF_CURSOR_STATE};
class GameDialog;
class Cursor{
public:
    Cursor(GameDialog* gDialog);
    ~Cursor();
    CursorState* getCurState();
    void setCursorState(CURSOR_STATE state);

    // ==== VARIABLES ====
    int radius; // radius of the cursor
    CURSOR_STATE state;
    CURSOR_STATE preState; // keep a record of previous state
    CursorState* currentState;
    std::map<CURSOR_STATE, CursorState*> cursorStatesList;
};
}
#endif // CURSOR_H
