#include "makerstate.h"
#include "gamedialog.h"
#include <QtMath>

namespace game {
MakerState::MakerState(Cursor* c, GameDialog* gDialog) : game::CursorState(c, gDialog)
{}

void MakerState::processMouseEvent(QMouseEvent *event){
    // update cursor location
    cursorX = event->pos().x();
    cursorY = event->pos().y();
}

void MakerState::processMousePress(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        leftPressing = true; // to keep track the state
    }
    gDialog->stageMaker.buttonPressed();
}

void MakerState::processMouseRelease(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        leftPressing = false; // to keep track the state
    }
    // call the internal stage maker method to trigger event
    gDialog->stageMaker.buttonReleased();
}

void MakerState::updateCursorDisplay(){
    gDialog->setCursor(Qt::PointingHandCursor);
}

void MakerState::update(){

}

}
