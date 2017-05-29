#include "powerup.h"
#include "gamedialog.h"

#define DELTA_X_PER_TICK 3
#define MAX_DELTA_X 35

#define Y_DESCEND_PER_TICK 2

namespace game {

Powerup::Powerup(PowerupType type, int x, int y, int radius) :
    radius(radius), type(type), centerX(x), centerY(y), deltaX(0)
{}

void Powerup::draw(QPainter* p){
    p->setPen(Qt::NoPen);

    switch(type){
    p->setBrush(Qt::gray);

    case(MachineGunPowerup):
        p->setPen(Qt::green);
        break;
    case(LaserPowerup):
        p->setPen(Qt::magenta);
//        p->setBrush(Qt::magenta);
        break;
    case(PenPowerup):
        p->setPen(Qt::red);
//        p->setBrush(Qt::red);
    }
    p->drawEllipse(x(), y(), radius*2, radius*2);

    QPixmap pixmap;
    switch (type) {
    case(MachineGunPowerup):
        pixmap.load(":/Images/MachineGun.png");
        break;
    case(LaserPowerup):
        pixmap.load(":/Images/LaserGun.png");
        break;
    case(PenPowerup):
        pixmap.load(":/Images/pen.png");
    }
    pixmap = pixmap.scaledToWidth(radius * 1.5);
    p->drawPixmap(x() + radius*0.25, y() + radius*0.25, pixmap);
}
void Powerup::update(){
    if(moveLeft){
        deltaX -= DELTA_X_PER_TICK;
        if(-deltaX > MAX_DELTA_X)
            moveLeft = false;
    }else{
        deltaX += DELTA_X_PER_TICK;
        if(deltaX > MAX_DELTA_X)
            moveLeft = true;
    }

    this->centerY += Y_DESCEND_PER_TICK;
}

int Powerup::x(){
    return centerX + deltaX;
}
int Powerup::y(){
    return centerY;
}

Powerup Powerup::generateRandomPowerup(int x, int y, int radius){
    // randomise the type of powerup
    int randomType= GameDialog::randInt(0, static_cast<int>(END_OF_POWERUP));
    if(randomType == END_OF_POWERUP)
        randomType--;
    PowerupType type = static_cast<PowerupType>(randomType);
    return Powerup(type, x, y, radius);
}
}
