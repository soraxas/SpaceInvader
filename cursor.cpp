#include "cursor.h"

namespace game{
Cursor::Cursor(GameDialog* gDialog) : leftPressing(false), rightPressing(false), radius(5)
{
    // the normal state for the cursor (default)
    CursorState* normal= new NormalState(this, gDialog);
    cursorStatesList[NORMAL] = normal;
    // the TIE-Fighter plane state for the cursor (blocking incoming fire)
    CursorState* fighter = new FighterState(this, gDialog);
    cursorStatesList[FIGHTER] = fighter;
    // the pen state for the cursor (drawing barrier on the screen)
    CursorState* pen = new PenState(this, gDialog);
    cursorStatesList[PEN] = pen;

    setCursorState(NORMAL);
}

Cursor::~Cursor(){
    // free all cursor state
    for(auto&& entry: cursorStatesList){
        delete entry.second;
    }
}

CursorState* Cursor::getCurState(){
    return currentState;
}

void Cursor::setCursorState(CURSOR_STATE state){
    currentState = cursorStatesList[state];
    this->state = state;

    // update the display of the cursor
    currentState->updateCursorDisplay();
}

void Cursor::processMousePress(QMouseEvent* event){
    if(event->button() == Qt::LeftButton)
        leftPressing = true; // to keep track the state

    // let the current mouse state process this event
    currentState->leftClickEvent();
}

void Cursor::processMouseRelease(QMouseEvent* event){
    if(event->button() == Qt::LeftButton)
        leftPressing = false; // to keep track the state

    currentState->leftReleaseEvent();
}
}
