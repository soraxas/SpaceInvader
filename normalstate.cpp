#include "gamedialog.h"
#include "normalstate.h"
#include <QDebug>
namespace game{
NormalState::NormalState(Cursor* c, GameDialog* gDialog) : game::CursorState(c, gDialog)
{

}

void NormalState::processMouseEvent(QMouseEvent *event){
}


void NormalState::processMousePress(QMouseEvent* event){
}

void NormalState::processMouseRelease(QMouseEvent* event){
}


void NormalState::updateCursorDisplay(){
    // set the cursor as the default
    gDialog->setCursor(Qt::ArrowCursor);
}

void NormalState::update(){
}

}
