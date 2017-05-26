#include "cursor.h"
#include "fighterstate.h"

namespace game{
Cursor::Cursor() : cursorX(0), cursorY(0), leftClick(false), rightClick(false), radius(5)
{
//    CursorState* fighter = new FighterState();
//    cursorStatesList[FIGHTER] = fighter;

//    currentState = cursorStatesList[FIGHTER];
}

Cursor::~Cursor(){
    // free all cursor state
//    for(auto&& entry: cursorStatesList){
//        delete entry.second;
//    }
}

void Cursor::updateLoc(int x, int y){
    cursorX = x;
    cursorY = y;
}
void Cursor::leftClickPressed(bool pressed){
    leftClick = pressed;
}
void Cursor::rightClickPressed(bool pressed){
    rightClick = pressed;
}
int Cursor::getX() const{
    return cursorX;
}
int Cursor::getY() const{
    return cursorY;
}
int Cursor::getRadius() const{
    return radius;
}
QPixmap Cursor::getPixmap(int width){
    radius = width / 2; // update the radius

    QPixmap pixmap;
    pixmap.load(":/Images/ship_tiefighter.png");
    return pixmap.scaledToWidth(width);
}
void Cursor::draw(QPainter* p) const{
    if(leftClick){
        p->setPen(Qt::blue);
        p->drawEllipse(cursorX - radius, cursorY - radius, radius*2, radius*2);
    }

}

//void Cursor::update(){
//    for (int i = 0; i < bullets.size(); i++) {
//        Bullet* b = bullets[i];
//        double dist = qSqrt(qPow(b->get_y() - cursorY,2) + qPow(b->get_x() - cursorX,2));
//      a  qDebug() << QString::number(dist);
//        if (dist < radius) {
//            delete b;
//            bullets.erase(bullets.begin() + i);
//            i--;
//        }
//    }
//}
}
