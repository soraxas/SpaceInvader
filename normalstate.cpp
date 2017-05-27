#include <QtMath>
#include "gamedialog.h"
#include "normalstate.h"

namespace game{
NormalState::NormalState(Cursor* c, GameDialog* gDialog) : game::CursorState(c, gDialog)
{

}

void NormalState::processMouseEvent(QMouseEvent *event){
}

void NormalState::leftClickEvent(){
}

void NormalState::leftReleaseEvent(){
}

void NormalState::rightClickEvent(){
}

void NormalState::rightReleaseEvent(){
}

void NormalState::updateCursorDisplay(){
    // set the cursor as the default
    gDialog->setCursor(Qt::ArrowCursor);
}

void NormalState::update(){
}

void NormalState::draw(QPainter* p){
}


}
