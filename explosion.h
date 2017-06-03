#ifndef EXPLOSION_H
#define EXPLOSION_H

/**
    A class definition for defining an explosion within the game. It is to be spawn when something was destoried
*/

#include <QPixmap>
#include <QPainter>
#include <vector>

namespace game{
enum ExplosionType{SmallExplosion, ShipExplosion};

class Explosion
{
public:
    Explosion(int x, int y, int scaledToWidth, ExplosionType type);
    void draw(QPainter * painter);
    void nextFrame();
    int x;
    int y;
    bool finished;
private:
    std::vector<QPixmap> explosionImage;
    unsigned explosionImage_frame;
    unsigned explosionImage_frameDelay;
};
}

#endif // EXPLOSION_H
