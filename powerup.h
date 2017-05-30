#ifndef POWERUP_H
#define POWERUP_H

#include <QPixmap>
#include <QPainter>

enum PowerupType{MachineGunPowerup, LaserPowerup, PenPowerup, END_OF_POWERUP};

namespace game {
class Powerup
{
public:
    Powerup(PowerupType type, int x, int y, int radius);
    void draw(QPainter* p);
    void update();

    static Powerup generateRandomPowerup(int x, int y, int radius);

    int x();
    int y();
    int radius;
    PowerupType type;
    QPixmap pixmap;
private:
    // for drawing alpha value
    bool turnToInvisable;
    double alpha;
    int centerX;
    int centerY;
    int deltaX;
    bool moveLeft;
};
}
#endif // POWERUP_H
