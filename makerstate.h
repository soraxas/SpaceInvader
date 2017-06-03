#ifndef MAKERSTATE_H
#define MAKERSTATE_H

/**
    State design pattern implementation
*/

#include "cursorstate.h"
#include "cursor.h"

namespace game {
class MakerState : public CursorState
{
public:
    MakerState(Cursor* c, GameDialog* dialog);

    void processMouseEvent(QMouseEvent *event);
    void processMousePress(QMouseEvent* event);
    void processMouseRelease(QMouseEvent* event);

    void updateCursorDisplay();
    void draw(QPainter* p);
    void update();
};
}

#endif // MAKERSTATE_H
