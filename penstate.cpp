#include "penstate.h"
#include "gamedialog.h"
#include <QtMath>

#define BLOCK_DIMENSION 30
#define ENERGYDRAIN_PER_PLACEMENT 3

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

void PenState::processMousePress(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        leftPressing = true; // to keep track the state
    }
}

void PenState::processMouseRelease(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        leftPressing = false; // to keep track the state
    }
}

void PenState::updateCursorDisplay(){
    // set the cursor as a pen
    QPixmap pixmap;
    pixmap.load(":/Images/pen.png");
    pixmap = pixmap.scaledToWidth(cursor->radius*2);
    gDialog->setCursor(QCursor(pixmap, 0, pixmap.height()));

    // initialise the energy amount in status bar
    gDialog->statusBar.barrierEnergy = 100;
}

void PenState::update(){
    // try adding block to the existing screen
    if(leftPressing){
        // ignore if cursor is on top of the tool bar / status bar
        if(cursorY > gDialog->SCALEDHEIGHT)
            return;
        // if all energy are used, revert back to TIE-fighter state
        if(gDialog->statusBar.barrierEnergy <= 0){
            cursor->setCursorState(FIGHTER);
            return;
        }

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

        // drain the energy by this amount.
        gDialog->statusBar.barrierEnergy -= ENERGYDRAIN_PER_PLACEMENT;
        if(gDialog->statusBar.barrierEnergy < 0)
            gDialog->statusBar.barrierEnergy = 0;
    }
}

}
