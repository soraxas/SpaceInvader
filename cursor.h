#ifndef CURSOR_H
#define CURSOR_H

#include <QPixmap>

class Cursor
{
public:
    Cursor();
    void updateLoc(int x, int y);
    void leftClickPressed(bool pressed);
    void rightClickPressed(bool pressed);

    int getX() const;
    int getY() const;
    int getRadius() const;
    QPixmap getPixmap(int width);

    void update();

private:
    int cursorX;
    int cursorY;
    bool leftClick;
    bool rightClick;
    int radius; // radius of the cursor
};

#endif // CURSOR_H
