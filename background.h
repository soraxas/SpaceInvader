#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QPainter>
#include <vector>

/**
  Control the background animations of the entire game
*/
namespace game{
struct star{ // for the stars at the background
    int x, y;
    QColor color;
    int speed;
};

class Background
{
public:
    Background(int screenWidth, int screenHeight);
    void draw(QPainter* p);
    void nextFrame();
private:
    std::vector<star> stars;
    int screenWidth;
    int screenHeight;
};
}
#endif // BACKGROUND_H
