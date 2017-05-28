#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QPainter>

namespace game {
class GameDialog;
class StatusBar
{
public:
    StatusBar(GameDialog* dialog);
    void draw(QPainter* p);
    void update();
    void buildBrush();

    // variables
    double plasmaEnergy;
    double barrierEnergy;
    GameDialog* gd;

    QRect containerOuter;
    QRect containerInner;
    QRect statusBar;
    QRect plasmaBar;
    QRect barrierBar;

    QBrush statusBarBrush;
    QBrush plasmaBarBrush;
    QBrush barrierBarBrush;

    // determine if the plasma had been drained
    bool plasmaDrained;
};
}
#endif // STATUSBAR_H
