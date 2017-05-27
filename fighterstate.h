#ifndef FIGHTERSTATE_H
#define FIGHTERSTATE_H

#include "cursorstate.h"
#include "cursor.h"

namespace game{
class FighterState : public CursorState
{
public:
    FighterState(Cursor* c, GameDialog* dialog);

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

#endif // FIGHTERSTATE_H
