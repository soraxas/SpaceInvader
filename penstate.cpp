#include "penstate.h"
#include "gamedialog.h"
#include <QtMath>

#define BLOCK_DIMENSION 30

namespace game {
PenState::PenState(Cursor* c, GameDialog* gDialog) : game::CursorState(c, gDialog)
{
    blockDimension = BLOCK_DIMENSION;
}

void PenState::processMouseEvent(QMouseEvent *event){
    // update cursor location
    cursorX = event->pos().x();
    cursorY = event->pos().y();
}

void PenState::leftClickEvent(){
}

void PenState::leftReleaseEvent(){
}

void PenState::rightClickEvent(){
}

void PenState::rightReleaseEvent(){
}

void PenState::updateCursorDisplay(){
    // set the cursor as a pen
    QPixmap pixmap;
    pixmap.load(":/Images/pen.png");
    pixmap = pixmap.scaledToWidth(cursor->radius*2);
    gDialog->setCursor(QCursor(pixmap, 0, pixmap.height()));
}

void PenState::update(){
    // try adding block to the existing screen
    if(cursor->leftPressing){
        // get the current cursor location that is aligned to the grid of block dimension
        int x = cursorX - (cursorX % blockDimension);
        int y = cursorY - (cursorY % blockDimension);

        // loop through the vector of blocks. If none existing found, add the new block
        for(BarrierBlock& b : gDialog->barriers){
            if(b.x == x && b.y == y)
                return;
        }

        // None exists yet, add the block to the location
        gDialog->barriers.push_back(BarrierBlock(x, y, blockDimension));
    }
}

void PenState::draw(QPainter* p){
}


}
