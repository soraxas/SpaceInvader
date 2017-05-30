#ifndef STAGEMAKER_H
#define STAGEMAKER_H

#include <QPainter>
#include <vector>

namespace game {
class GameDialog;
// define what type of element is the cursor holding
enum SMakerObjectType{SMAKER_HOLDING_ALIEN_RED, SMAKER_HOLDING_ALIEN_BLUE,
                      SMAKER_HOLDING_ALIEN_HUNTER, SMAKER_HOLDING_ALIEN_DUMB,
                      SMAKER_HOLDING_INSTRUCTION_BOX, SMAKER_HOLDING_BARRIER_BLOCK,
                      SMAKER_HOLDING_LINE,
                      SMAKER_HOLDING_NONE};

// defines the placed object by cursor
struct SMakerPlacedObject{
    SMakerPlacedObject() : connected(false){}
    QRect hitBox;
    SMakerObjectType type;
    QPixmap pixmap;
    // determine if the object is connect to another object (to define instructions of swarms)
    bool connected;
    QPoint connectedPoint;
};

class StageMaker
{
public:
    StageMaker(GameDialog* gDialog);
    void init();
    void draw(QPainter* p);
    void update();
    void buttonPressed();
    void buttonReleased();

    // available objects template
    std::map<SMakerObjectType, SMakerPlacedObject> objectTemplate;
    QPoint lineOrigin;

    // variables
    SMakerObjectType holdingObject;
    GameDialog* gDialog;
    bool active;
    std::vector<SMakerPlacedObject> objects;
};
}

#endif // STAGEMAKER_H
