#ifndef CURSORSTATE_H
#define CURSORSTATE_H

/**
    Using stage design pattern for the different number of cursor states.
*/


#include <QDialog>
#include <QMouseEvent>
#include <QCursor>

namespace game{
class Cursor;
class GameDialog;
class CursorState{
public:
        CursorState(Cursor* c, GameDialog* gDialog) : cursor(c), gDialog(gDialog), leftPressing(false){}
        virtual ~CursorState() {}

        virtual void processMouseEvent(QMouseEvent* event) = 0;
        virtual void processMousePress(QMouseEvent* event) = 0;
        virtual void processMouseRelease(QMouseEvent* event) = 0;

        virtual void updateCursorDisplay() = 0;
        virtual void update() = 0; // update any logic

        int cursorX;
        int cursorY;
protected:
        Cursor* cursor;
        GameDialog* gDialog;
        bool leftPressing; // keep track if left button is currently pressing
};
}
#endif // CURSORSTATE_H
