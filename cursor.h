#ifndef CURSOR_H
#define CURSOR_H

#include <QPixmap>
#include <QPainter>
#include <vector>
#include "cursorstate.h"

namespace game{

class GameDialog;

enum CURSOR_STATE{NORMAL, FIGHTER};

class Cursor
{
public:
    Cursor();
    ~Cursor();
    void updateLoc(int x, int y);
    void leftClickPressed(bool pressed);
    void rightClickPressed(bool pressed);

    int getX() const;
    int getY() const;
    int getRadius() const;
    QPixmap getPixmap(int width);

    void draw(QPainter* p) const;
    void update();

//    CursorState* getCurState(){return currentState;}
private:
    int cursorX;
    int cursorY;
    bool leftClick;
    bool rightClick;
    int radius; // radius of the cursor

//    CursorState* currentState;
//    std::map<CURSOR_STATE, CursorState*> cursorStatesList;
};
}
#endif // CURSOR_H
