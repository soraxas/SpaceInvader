#include "fighterstate.h"
#include <QtMath>
#include "gamedialog.h"

#define ENERGYDRAIN_PER_TICK 1
#define ENERGYDRAIN_PER_HIT 10
#define ENERGYRESTORE_PER_TICK 0.8
#define ENERGYRESTORE_PER_TICK_FULLYDRAINED 0.5

namespace game{
FighterState::FighterState(Cursor* c, GameDialog* gDialog) : game::CursorState(c, gDialog)
{}

/**
    Given a mouse event, process the event by updating the cursor location

    @param the QMouse event triggers
*/
void FighterState::processMouseEvent(QMouseEvent *event){
    // update cursor location
    cursorX = event->pos().x();
    cursorY = event->pos().y();
}


/**
    Set the cursor display as the fighter state

    @param whether set current display as normal (fighter image) or non-normal (fighter image with plasma energy sheild)
*/
void FighterState::setCursorDisplay(bool normalState){
    if(normalState){
        // set the cursor as the TIE Fighter image
        QPixmap pixmap;
        pixmap.load(":/Images/ship_tiefighter.png");
        gDialog->setCursor(QCursor(pixmap.scaledToWidth(cursor->radius*2), -1, -1));
    }else{
        // set the cursor as the plasma ball
        QPixmap pixmap;
        pixmap.load(":/Images/PlasmaBall.png");
        gDialog->setCursor(QCursor(pixmap.scaledToWidth(cursor->radius*2 * 1.3), -1, -1));
    }
}

void FighterState::processMousePress(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        leftPressing = true; // to keep track the state
        if(!gDialog->statusBar.plasmaDrained) // only switch if currently it can still use plasma
            setCursorDisplay(false);
    }
}

void FighterState::processMouseRelease(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        leftPressing = false; // to keep track the state
        setCursorDisplay(true);
    }
}

void FighterState::updateCursorDisplay(){
    setCursorDisplay(true);
}

/**
    Update the logic of this mouse event
    The idea is if the current cursor location is within range of any other bullets,
    it will try to desotry it as an attemp of "shielding the player"
    The limitation is it is goverened by the energy bar that the player currently has.
    The energy will drain every second that the mouse is pressed. Also when it actually
    Defended a bullet, it will drain a certain amount of energy immediately.
*/
void FighterState::update(){
    // only delete nearby bullet when left button is held
    if(leftPressing && !gDialog->statusBar.plasmaDrained){
        for (unsigned i = 0; i < gDialog->bullets.size(); i++) {
            Bullet* b = gDialog->bullets[i];
            double dist = qSqrt(qPow(b->get_y() - cursorY,2) + qPow(b->get_x() - cursorX,2));
            if (dist < cursor->radius) {
                delete b;
                gDialog->bullets.erase(gDialog->bullets.begin() + i);
                i--;

                // create explosion
                gDialog->explosions.push_back(Explosion(b->get_x()+b->get_image().width()/2,
                                               b->get_y()+b->get_image().height()/5,
                                               b->get_image().height()*1.4, SmallExplosion));

                // everytime it destory a bullet, it drains a bit of energy
                gDialog->statusBar.plasmaEnergy -= ENERGYDRAIN_PER_HIT;
            }
        }

        // use up energy every second pressing
        gDialog->statusBar.plasmaEnergy -= ENERGYDRAIN_PER_TICK;
        if(gDialog->statusBar.plasmaEnergy <= 0){
            gDialog->statusBar.plasmaEnergy = 0;
            gDialog->statusBar.plasmaDrained = true;
            // reset the cursor
            setCursorDisplay(true);
        }
    }else{
        // restore energy every update
        if(gDialog->statusBar.plasmaEnergy < 100){
            if(gDialog->statusBar.plasmaDrained){
                //if energy is drained, it restore more slowly
                gDialog->statusBar.plasmaEnergy += ENERGYRESTORE_PER_TICK_FULLYDRAINED;
            }else{
                gDialog->statusBar.plasmaEnergy += ENERGYRESTORE_PER_TICK;
            }
            if(gDialog->statusBar.plasmaEnergy >= 100){
                gDialog->statusBar.plasmaEnergy = 100;
                gDialog->statusBar.plasmaDrained = false;
                if(leftPressing){
                    // reset the cursor
                    setCursorDisplay(false);
                }
            }
        }
    }
}

}
