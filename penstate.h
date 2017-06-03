#ifndef PENSTATE_H
#define PENSTATE_H

/**
    State design pattern implementation
*/

#include "cursorstate.h"
#include "cursor.h"
#include "barrierblock.h"

namespace game{
class PenState : public CursorState
{
public:
    PenState(Cursor* c, GameDialog* gDialog);

    void processMouseEvent(QMouseEvent *event);
    void processMousePress(QMouseEvent* event);
    void processMouseRelease(QMouseEvent* event);

    void updateCursorDisplay();
    void draw(QPainter* p);
    void update();

private:
    unsigned blockDimension;
};
}

#endif // PENSTATE_H
