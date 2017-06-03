#include "cursor.h"

namespace game{
Cursor::Cursor(GameDialog* gDialog) : radius(5), preState(NORMAL)
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
    // the stagemaker state for the cursor (drawing barrier on the screen)
    CursorState* maker = new MakerState(this, gDialog);
    cursorStatesList[STAGEMAKER] = maker;

    setCursorState(NORMAL); // default as normal
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
    preState = this->state;
    currentState = cursorStatesList[state];
    this->state = state;

    // update the display of the cursor
    currentState->updateCursorDisplay();
}

}
