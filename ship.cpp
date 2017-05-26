#include "ship.h"
#include "bullet.h"
#include "config.h"
#define COOLDOWN 15
#define SHIPWIDTH 80

namespace game {
Ship::Ship(QPixmap image, double scale, int x, int y)
    : Base(image, scale, x, y - image.height() * scale,
           Config::getInstance()->get_SCALEDWIDTH(),
           Config::getInstance()->get_SCALEDWIDTH(), 0),
      velocity(10), bullet_velocity(15), builder(bullet_velocity, *this, "laser", true) {
    // adjust the image size according to scale
    this->set_image(this->get_image().scaledToWidth(/*this->get_image().width()*/ SHIPWIDTH * scale));

    // readjust (x,y) since the image was resized
    boundaryX = Config::getInstance()->get_SCALEDWIDTH() - this->get_image().width();
    boundaryY = Config::getInstance()->get_SCALEDHEIGHT() - this->get_image().height();

    set_x(x);
    set_y(y);
    this->ShootCooldownLimit = COOLDOWN; // can only shoot after this cooldown
    this->ShootCooldownCounter = 0;
}

// A SHIP CAN MOVE LEFT, RIGHT AND SHOOT
Bullet* Ship::shoot() {
    if(ShootCooldownCounter == 0){
        ShootCooldownCounter = ShootCooldownLimit;
        return builder.build_bullet("laser");
    }
    else
        return NULL;
}

// Setters
void Ship::move_left() {
    set_x(get_x() - velocity);
}

void Ship::move_right() {
    set_x(get_x() + velocity);
}

void Ship::update() {
    if(ShootCooldownCounter > 0)
        --ShootCooldownCounter;
}

Ship::~Ship() {}
}
