#include "background.h"

#define NUM_OF_STARS 100
#define STARS_SPEED 2

namespace game {

/**
    Initialise the background by some white stars in front and gray stars at back.
    This is to simulate the illusion of space.
    They also have different speed to give it a better visual effecs
*/
Background::Background(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight)
{
    // gray stars in distance
    for (int i = 0; i < NUM_OF_STARS; ++i){
        star s;
        s.x = qrand() % screenWidth;
        s.y = qrand() % screenHeight;
        s.speed = STARS_SPEED;
        s.color = Qt::gray;
        stars.push_back(s);
    }

    // white stars
    for (int i = 0; i < NUM_OF_STARS; ++i){
        star s;
        s.x = qrand() % screenWidth;
        s.y = qrand() % screenHeight;
        s.speed = STARS_SPEED + 2;
        s.color = Qt::white;
        stars.push_back(s);
    }
}

void Background::nextFrame(){
    // update the location of all starts
    for(star &s : stars){
        s.y += s.speed;
        if (s.y > screenHeight){
            s.y = 0;
            // randomise the star x location to make to look more realistic
            s.x = qrand() % screenWidth;
        }
    }
}

void Background::draw(QPainter* p){
    for (unsigned i = 0; i < stars.size(); ++i){
        p->setPen(stars[i].color);
        p->setBrush(stars[i].color);
        int r = 2;
        p->drawEllipse(stars[i].x, stars[i].y, r, r);
    }
}
}
