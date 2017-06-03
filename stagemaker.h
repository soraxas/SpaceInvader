#ifndef STAGEMAKER_H
#define STAGEMAKER_H

#include <QPainter>
#include <vector>
#include <QDialog>
#include "ui_instructionrequest.h"
#include "instructionirequest.h"

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
    QString instructions;
};

class StageMaker
{
public:
    StageMaker(GameDialog* gDialog);
    ~StageMaker();
    void init();
    void draw(QPainter* p);
    void buttonPressed();
    void buttonReleased();
    void clearAll();
    void testStage();

    // available objects template
    std::map<SMakerObjectType, SMakerPlacedObject> objectTemplate;
    QPoint lineOrigin;

    // variables
    QRect clearAllBtn;
    QRect testStageBtn;
    SMakerObjectType holdingObject;
    GameDialog* gDialog;
private:
    void drawInstructionBox(QPainter* p, const QRect& hitBox);
    std::vector<SMakerPlacedObject> objects;
    InstructionRequest req;
};




}

#endif // STAGEMAKER_H
