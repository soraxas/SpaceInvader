#ifndef BARRIERBLOCK_H
#define BARRIERBLOCK_H

/**
    Barriers block defined to be a block in space that could block the incomoing of lasers/bullets
    This is to add protective material in game
*/

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
