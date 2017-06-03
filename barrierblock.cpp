#include "barrierblock.h"

namespace game {
/**
    This is the block that blocks incoming bullets and will be destoried once hit.
*/
BarrierBlock::BarrierBlock(int x, int y, unsigned width) : x(x), y(y), width(width)
{
    pixmap.load(":/Images/barrier.png");
    pixmap = pixmap.scaledToWidth(width);
}

void BarrierBlock::draw(QPainter* p){
    p->drawPixmap(x, y, pixmap);
}
}

