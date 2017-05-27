#ifndef NORMALSTATE_H
#define NORMALSTATE_H

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
    void leftClickEvent();
    void leftReleaseEvent();
    void rightClickEvent();
    void rightReleaseEvent();

    void updateCursorDisplay();
    void draw(QPainter* p);
    void update();
};
}

#endif // NORMALSTATE_H
