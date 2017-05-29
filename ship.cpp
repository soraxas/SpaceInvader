#include "ship.h"
#include "bullet.h"
#include "config.h"
#define COOLDOWN 15
#define SHIPWIDTH 80
#define MACHINE_GUN_SHOOT_RATE 0.001

namespace game {
Ship::Ship(QPixmap image, double scale, int x, int y)
    : Base(image, scale, x, y - image.height() * scale,
           Config::getInstance()->get_SCALEDWIDTH(),
           Config::getInstance()->get_SCALEDWIDTH(), 0),
      velocity(10), bullet_velocity(15), builder(bullet_velocity, *this, "laser", true),
      dead(false), cannonType(Normal), cannonAmmo(-1)
{
    // adjust the image size according to scale
    this->set_image(this->get_image().scaledToWidth(SHIPWIDTH * scale));

    // readjust (x,y) since the image was resized
    boundaryX = Config::getInstance()->get_SCALEDWIDTH() - this->get_image().width();
    boundaryY = Config::getInstance()->get_SCALEDHEIGHT() - this->get_image().height();

    set_x(x);
    set_y(y);
    this->ShootCooldownLimit = COOLDOWN; // can only shoot after this cooldown
    this->ShootCooldownCounter = 0;
    this->machineGunShootAtLeft = true;
}

// A SHIP CAN MOVE LEFT, RIGHT AND SHOOT
Bullet* Ship::shoot() {
    if(ShootCooldownCounter == 0){
        Bullet* b = NULL;
        switch (cannonType) {
        case(Normal):
            ShootCooldownCounter = ShootCooldownLimit;
            b = builder.build_bullet("laser"); // normal bullet
            cannonAmmo = -1;
            break;
        case(MachineGun):
        {
            ShootCooldownCounter = static_cast<unsigned>(ShootCooldownLimit * MACHINE_GUN_SHOOT_RATE);
            b = builder.build_bullet("laser"); // normal bullet

            // alter the x-location for the bullet
            int deltaX = static_cast<int>(image.width()*0.4);
            if(machineGunShootAtLeft)
                b->set_x(b->get_x() - deltaX);
            else
                b->set_x(b->get_x() + deltaX);
            machineGunShootAtLeft = !machineGunShootAtLeft; // switch the bool toggle
            if(cannonAmmo > 0)
                --cannonAmmo;
            if(cannonAmmo <= 0){
                cannonType = Normal;
                cannonAmmo = -1;
            }
            break;
        }
        default:
            return NULL;
        }
        return b;
    }
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
