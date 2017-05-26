//#include "fighterstate.h"
//#include <QtMath>
//#include "gamedialog.h"

//namespace game{
//FighterState::FighterState()
//{

//}

//void FighterState::processMouseEvent(QMouseEvent *event, QWidget* dialog){
//    GameDialog* gd = dynamic_cast<GameDialog*>(dialog);
//    for (int i = 0; i < gd->bullets.size(); i++) {
//        Bullet* b = gd->bullets[i];

//        double dist = qSqrt(qPow(b->get_y() - cursor->getY(),2) + qPow(b->get_x() - cursor->getX(),2));

//        if (dist < cursor->getRadius()) {
//            delete b;
//            gd->bullets.erase(gd->bullets.begin() + i);
//            i--;
//        }
//    }
//}
//void FighterState::updateCursorDisplay(QWidget *dialog){

//}
//}
