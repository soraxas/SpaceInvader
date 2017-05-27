#ifndef CURSORSTATE_H
#define CURSORSTATE_H

#include <QDialog>
#include <QMouseEvent>
#include <QCursor>

namespace game{
class Cursor;
class GameDialog;
class CursorState{
public:
        CursorState(Cursor* c, GameDialog* gDialog) : cursor(c), gDialog(gDialog){}
        virtual ~CursorState() {}

        virtual void processMouseEvent(QMouseEvent* event) = 0;
        virtual void leftClickEvent() = 0;
        virtual void leftReleaseEvent() = 0;
        virtual void rightClickEvent() = 0;
        virtual void rightReleaseEvent() = 0;

        virtual void updateCursorDisplay() = 0;
        virtual void update() = 0; // update any logic
        virtual void draw(QPainter* p) = 0;

        int cursorX;
        int cursorY;
protected:
        Cursor* cursor;
        GameDialog* gDialog;

};
}
#endif // CURSORSTATE_H
