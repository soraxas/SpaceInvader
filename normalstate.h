#ifndef NORMALSTATE_H
#define NORMALSTATE_H

/**
    State design pattern implementation
*/

#include "cursorstate.h"
#include "cursor.h"

namespace game {
class NormalState : public CursorState
{
public:
    NormalState(Cursor* c, GameDialog* gDialog);

    void processMouseEvent(QMouseEvent *event);
    void processMousePress(QMouseEvent* event);
    void processMouseRelease(QMouseEvent* event);

    void updateCursorDisplay();
    void draw(QPainter* p);
    void update();
};
}

#endif // NORMALSTATE_H
