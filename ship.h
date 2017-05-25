#pragma once
#include "base.h"
#include "bullet.h"
#include "bulletbuilder.h"
#include <QPixmap>

namespace game {

class Ship : public Base {
    // A SHIP CAN MOVE LEFT, RIGHT AND SHOOT (ALL WITH AN VELOCITY)

private:
    int velocity;
    int bullet_velocity;
    BulletBuilder builder;
    unsigned ShootCooldownCounter; // counter to count when can the ship shoot next
    unsigned ShootCooldownLimit; // the cooldown it takes for the ship can shoot again
public:
    Ship(QPixmap image, double scale, int x, int y);
    Bullet* shoot();
    void move_left();
    void move_right();
    void update();
    virtual ~Ship();
};
}
