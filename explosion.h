#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QPixmap>
#include <QPainter>
#include <vector>

enum ExplosionType{AlienExplosion, ShipExplosion};

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


#endif // EXPLOSION_H
