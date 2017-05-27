#ifndef BARRIERBLOCK_H
#define BARRIERBLOCK_H

#include <QPainter>

namespace game {
class BarrierBlock
{
public:
    BarrierBlock(int x, int y, unsigned width);
    void draw(QPainter* p);

// Variables
    QPixmap pixmap;
    int x;
    int y;
    unsigned width;
};
}

#endif // BARRIERBLOCK_H
