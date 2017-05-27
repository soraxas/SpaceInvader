#include "fighterstate.h"
#include <QtMath>
#include "gamedialog.h"

namespace game{
FighterState::FighterState(Cursor* c, GameDialog* gDialog) : game::CursorState(c, gDialog)
{

}

void FighterState::processMouseEvent(QMouseEvent *event){
    // update cursor location
    cursorX = event->pos().x();
    cursorY = event->pos().y();
}

void FighterState::leftClickEvent(){
    // set the cursor as the TIE Fighter image
    QPixmap pixmap;
    pixmap.load(":/Images/PlasmaBall.png");
    gDialog->setCursor(QCursor(pixmap.scaledToWidth(cursor->radius*2 * 1.3), -1, -1));
}
void FighterState::leftReleaseEvent(){
    // set the cursor as the TIE Fighter image
    QPixmap pixmap;
    pixmap.load(":/Images/ship_tiefighter.png");
    gDialog->setCursor(QCursor(pixmap.scaledToWidth(cursor->radius*2), -1, -1));
}

void FighterState::rightClickEvent(){
}
void FighterState::rightReleaseEvent(){
}

void FighterState::updateCursorDisplay(){
    // set the cursor as the TIE Fighter image
    QPixmap pixmap;
    pixmap.load(":/Images/ship_tiefighter.png");
    gDialog->setCursor(QCursor(pixmap.scaledToWidth(cursor->radius*2), -1, -1));
}

void FighterState::update(){
    // only delete nearby bullet when left button is held
    if(cursor->leftPressing){
    for (unsigned i = 0; i < gDialog->bullets.size(); i++) {
        Bullet* b = gDialog->bullets[i];
        double dist = qSqrt(qPow(b->get_y() - cursorY,2) + qPow(b->get_x() - cursorX,2));
        if (dist < cursor->radius) {
            delete b;
            gDialog->bullets.erase(gDialog->bullets.begin() + i);
            i--;
        }
    }
    }
}

void FighterState::draw(QPainter* p){
    return;
    int r = cursor->radius;
    if(cursor->leftPressing){
        QPixmap pixmap;
        pixmap.load(":/Images/PlasmaBall.png");
//        p->setPen(Qt::blue);
//        p->drawEllipse(cursorX - r, cursorY - r, r*2, r*2);
        p->drawPixmap(cursorX-cursor->radius, cursorY-cursor->radius, pixmap.scaledToWidth(cursor->radius*2));
    }
    else{
        // set the cursor as the TIE Fighter image
        QPixmap pixmap;
        pixmap.load(":/Images/ship_tiefighter.png");
        gDialog->setCursor(QCursor(pixmap.scaledToWidth(cursor->radius*2), -1, -1));
    }
}
}
