#include "gamemenu.h"

#include "stagemaker.h"
#include "gamedialog.h"
#include <QPair>
#include <vector>
#define BLOCK_DIMENSION 30

namespace game {
/**
    This is the class that defines the entire looking of the stage maker mode.
    It is to provide a way for player to define a stage that he/she likes or if
    they want to try it out.

    @todo provide a way to save the stage.
*/
StageMaker::StageMaker(GameDialog* gDialog) : gDialog(gDialog), holdingObject(SMAKER_HOLDING_NONE)
{}

StageMaker::~StageMaker(){
}

/**
    initialise all the internal variables to setup the stage maker.
    Load every aliens images into a qrect to define the hitbox of it.
    So it could be used to track if a mouse is clicked on top of it.
*/
void StageMaker::init(){
    QPixmap pixmap;
    SMakerPlacedObject obj;
    // blue alien
    pixmap.load(":/Images/blueInvader.png");
    obj.pixmap = pixmap;
    obj.hitBox = QRect(gDialog->SCALEDWIDTH * 0.1, gDialog->SCALEDHEIGHT + gDialog->STATUSBARHEIGHT*0.2,
                       pixmap.width(),pixmap.height());
    obj.type = SMAKER_HOLDING_ALIEN_BLUE;
    objectTemplate[obj.type] = obj;

    // red alien
    pixmap.load(":/Images/redInvader.png");
    obj.pixmap = pixmap;
    obj.hitBox = QRect(gDialog->SCALEDWIDTH * 0.2, gDialog->SCALEDHEIGHT + gDialog->STATUSBARHEIGHT*0.2,
                       pixmap.width(),pixmap.height());
    obj.type = SMAKER_HOLDING_ALIEN_RED;
    objectTemplate[obj.type] = obj;

    // dumb alien
    pixmap.load(":/Images/dumbInvader.png");
    obj.pixmap = pixmap;
    obj.hitBox = QRect(gDialog->SCALEDWIDTH * 0.3, gDialog->SCALEDHEIGHT + gDialog->STATUSBARHEIGHT*0.2,
                       pixmap.width(),pixmap.height());
    obj.type = SMAKER_HOLDING_ALIEN_DUMB;
    objectTemplate[obj.type] = obj;

    // hunter alien
    pixmap.load(":/Images/hunterInvader.png");
    obj.pixmap = pixmap;
    obj.hitBox = QRect(gDialog->SCALEDWIDTH * 0.4, gDialog->SCALEDHEIGHT + gDialog->STATUSBARHEIGHT*0.2,
                       pixmap.width(),pixmap.height());
    obj.type = SMAKER_HOLDING_ALIEN_HUNTER;
    objectTemplate[obj.type] = obj;

    // barrierBlock
    pixmap.load(":/Images/barrier.png");
    pixmap = pixmap.scaledToWidth(BLOCK_DIMENSION);
    obj.pixmap = pixmap;
    obj.hitBox = QRect(gDialog->SCALEDWIDTH * 0.5, gDialog->SCALEDHEIGHT + gDialog->STATUSBARHEIGHT*0.2,
                       pixmap.width(),pixmap.height());
    obj.type = SMAKER_HOLDING_BARRIER_BLOCK;
    objectTemplate[obj.type] = obj;

    // Instruction box
    obj = {};
    obj.hitBox = QRect(gDialog->SCALEDWIDTH * 0.55, gDialog->SCALEDHEIGHT + gDialog->STATUSBARHEIGHT*0.2,
                       gDialog->SCALEDWIDTH * 0.2, gDialog->STATUSBARHEIGHT*0.6);
    obj.type = SMAKER_HOLDING_INSTRUCTION_BOX;
    objectTemplate[obj.type] = obj;

    // Now initialise button for tool bar
    clearAllBtn = QRect(gDialog->SCALEDWIDTH * 0.8, gDialog->SCALEDHEIGHT + gDialog->STATUSBARHEIGHT*0.2,
                        gDialog->STATUSBARHEIGHT*0.7, gDialog->STATUSBARHEIGHT*0.6);
    testStageBtn = QRect(gDialog->SCALEDWIDTH * 0.9, gDialog->SCALEDHEIGHT + gDialog->STATUSBARHEIGHT*0.2,
                         gDialog->STATUSBARHEIGHT*0.7, gDialog->STATUSBARHEIGHT*0.6);
}

/**
    draw the entire scence of stage maker. This takes over the main game engine and
    do all the draw of elements such as the dragging motions and the status bar
    @param QPainter of the dialog box
*/
void StageMaker::draw(QPainter* p){
    QFont f;
    f.setPointSize(static_cast<int>(gDialog->STATUSBARHEIGHT * 0.3));
    p->setFont(f);
    p->setPen(Qt::red);
    // calculate where to draw the stage maker tag
    int drawAtY = gDialog->SCALEDHEIGHT - 10;
    if(gDialog->currentState == GAME_STATUS_STAGE_MAKER_TESTING)
        // we draw on top of status bar if it is currently being tested
        drawAtY += gDialog->STATUSBARHEIGHT;
    p->drawText(10, drawAtY, "SpaceInvade Stage Maker!!");
    if(gDialog->currentState == GAME_STATUS_STAGE_MAKER_TESTING){
        // only draw the instruction to escape testing mode, but do not draw the placed object
        p->setPen(Qt::yellow);
        p->drawText(50, 50, "PRESS [ESC] to exit testing mode");
        return;
    }else{
        if(gDialog->cursor.state != STAGEMAKER)
            gDialog->cursor.setCursorState(STAGEMAKER);
    }
    f.setPointSize(12);
    p->setFont(f);
    p->setPen(Qt::NoPen);

    // first draw the bottom tool box bar
    p->setBrush(Qt::gray);
    p->drawRect(0, gDialog->SCALEDHEIGHT, gDialog->SCALEDWIDTH, gDialog->STATUSBARHEIGHT);

    // draw all available objects
    for(auto&& obj : objectTemplate){
        if(obj.second.type != SMAKER_HOLDING_INSTRUCTION_BOX)
            p->drawPixmap(obj.second.hitBox.x(), obj.second.hitBox.y(), obj.second.pixmap);
        else{
            drawInstructionBox(p, obj.second.hitBox);
        }
    }

    // draw all the placed object
    for(auto&& obj : objects){
        if(obj.type == SMAKER_HOLDING_INSTRUCTION_BOX){
            drawInstructionBox(p, obj.hitBox);
            // draw the inner text
            p->setPen(Qt::black);
            p->drawText(obj.hitBox, Qt::AlignCenter, obj.instructions);
        }else{
            p->drawPixmap(obj.hitBox.x(), obj.hitBox.y(), obj.pixmap);
            // if it is connected, also draw that line
            if(obj.connected){
                p->setPen(Qt::yellow);
                p->drawLine(obj.hitBox.x() + obj.pixmap.width()/2, obj.hitBox.y() + obj.pixmap.height()/2,
                            obj.connectedPoint.x(), obj.connectedPoint.y());
            }
        }
    }

    p->setPen(Qt::black);
    p->setBrush(Qt::red);
    // draw the button on tool bar
    p->drawRect(clearAllBtn);
    p->setPen(Qt::black);
    p->drawText(clearAllBtn, Qt::AlignCenter, "Clear All");

    p->setBrush(Qt::green);
    // draw the button on tool bar
    p->drawRect(testStageBtn);
    p->drawText(testStageBtn, Qt::AlignCenter, "Test Stage");

    // draw the thing on the cursor
    if(holdingObject != SMAKER_HOLDING_NONE){
        if(holdingObject == SMAKER_HOLDING_INSTRUCTION_BOX){
            QRect instructionBox= objectTemplate[holdingObject].hitBox;
            instructionBox.moveTo(gDialog->cursor.getCurState()->cursorX - objectTemplate[holdingObject].hitBox.width()/2,
                                  gDialog->cursor.getCurState()->cursorY - objectTemplate[holdingObject].hitBox.height()/2);
            drawInstructionBox(p, instructionBox);
        }else if(holdingObject == SMAKER_HOLDING_LINE) {
            // draw a line from origin point to the current cursor location
            p->setPen(Qt::yellow);
            p->drawLine(lineOrigin.x(), lineOrigin.y(), gDialog->cursor.getCurState()->cursorX, gDialog->cursor.getCurState()->cursorY);
        }else{
            p->drawPixmap(gDialog->cursor.getCurState()->cursorX - objectTemplate[holdingObject].pixmap.width()/2,
                          gDialog->cursor.getCurState()->cursorY - objectTemplate[holdingObject].pixmap.height()/2,
                          objectTemplate[holdingObject].pixmap);

        }
    }
}

/**
    Helper method to draw the instruction box

    @param the painter and the qrect that defines the dimension of the box
*/
void StageMaker::drawInstructionBox(QPainter* p, const QRect& hitBox){
    p->setBrush(Qt::gray);
    p->setPen(Qt::yellow);
    p->drawText(hitBox.x(), hitBox.y()-hitBox.height(), hitBox.width(), hitBox.height(),
                Qt::AlignBottom, "INSTRUCTIONS");
    p->drawRect(hitBox);
}

/**
    Tiggered when the cursor is pressed. Triggers will be sent from the StageMaker Cursor stage
*/
void StageMaker::buttonPressed(){
    if(gDialog->currentState == GAME_STATUS_STAGE_MAKER_TESTING)
        return;
    if(gDialog->cursor.getCurState()->cursorY > gDialog->SCALEDHEIGHT){
        // CURSOR ON TOOL BOX:

        // loop through all template objects, if the cursor's x and y is within an object's hit box, select that object
        for(auto&& obj : objectTemplate){
            if(obj.second.hitBox.contains(gDialog->cursor.getCurState()->cursorX, gDialog->cursor.getCurState()->cursorY)){
                holdingObject = obj.second.type;
                return;
            }
        }

        // see if the cursor clicked on any of the button, if so run the corresponding functions
        if(clearAllBtn.contains(gDialog->cursor.getCurState()->cursorX, gDialog->cursor.getCurState()->cursorY))
            clearAll();
        else if(testStageBtn.contains(gDialog->cursor.getCurState()->cursorX, gDialog->cursor.getCurState()->cursorY))
            testStage();
    }else{
        // CURSOR CLICKED ON MAIN SCREEN:
        // loop through all objects, if the cursor's x and y is within an object's hit box, select that object
        // we are trying to re-move thet objects on screen
        std::vector<SMakerPlacedObject>::iterator it = objects.begin();
        while (it != objects.end()) {
            SMakerPlacedObject obj = (*it);
            // re-move objects
            if(obj.hitBox.contains(gDialog->cursor.getCurState()->cursorX, gDialog->cursor.getCurState()->cursorY)){
                if(obj.connected){
                    // one exception is we cannot move object that already has a connected line
                    ++it;
                    continue;
                }

                // special case of connecting instruction box to aliens
                if(obj.type == SMAKER_HOLDING_INSTRUCTION_BOX){
                    // connect instruction box
                    holdingObject = SMAKER_HOLDING_LINE;
                    lineOrigin = QPoint(obj.hitBox.x() + obj.hitBox.width()/2, obj.hitBox.y() + obj.hitBox.height()/2);
                    break;
                }
                objects.erase(it);
                holdingObject = obj.type;
                break;

            }
            ++it;
        }
    }
}

void StageMaker::buttonReleased(){
    if(gDialog->currentState == GAME_STATUS_STAGE_MAKER_TESTING)
        return;
    // the cursor must be holding "something" and NOT on top of the tool bar when it release, for the placing of object works
    if(holdingObject != SMAKER_HOLDING_NONE && gDialog->cursor.getCurState()->cursorY < gDialog->SCALEDHEIGHT){
        // special case of connecting line from instruction box to object (alines)
        if(holdingObject == SMAKER_HOLDING_LINE){
            for(auto&& obj : objects){
                if(obj.type != SMAKER_HOLDING_INSTRUCTION_BOX && obj.type != SMAKER_HOLDING_BARRIER_BLOCK){
                    if(obj.hitBox.contains(gDialog->cursor.getCurState()->cursorX, gDialog->cursor.getCurState()->cursorY)){
                        obj.connected = true;
                        obj.connectedPoint = QPoint(lineOrigin);
                    }
                }
            }
        }else{
            // drop the currently holding object at this location (if valid)
            SMakerPlacedObject obj = objectTemplate[holdingObject];
            // calculate the final location
            int x = gDialog->cursor.getCurState()->cursorX;
            int y = gDialog->cursor.getCurState()->cursorY;
            if(obj.type == SMAKER_HOLDING_INSTRUCTION_BOX){
                x -= obj.hitBox.width()/2;
                y -= obj.hitBox.height()/2;
            }else if (obj.type == SMAKER_HOLDING_BARRIER_BLOCK){
                // we need to aligh it to the block grid
                x -= obj.pixmap.width()/2;
                y -= obj.pixmap.height()/2;
                x -= x % BLOCK_DIMENSION;
                y -= y % BLOCK_DIMENSION;
            }else{
                x -= obj.pixmap.width()/2;
                y -= obj.pixmap.height()/2;
            }
            obj.hitBox.moveTo(x, y);
            // place the new object
            objects.push_back(obj);

            if(obj.type == SMAKER_HOLDING_INSTRUCTION_BOX){
                // request instruction list from dialog box
                req.instructionBox = &objects.back(); // set the requesting instruction box pointer
                req.show();
            }
        }
    }
    holdingObject = SMAKER_HOLDING_NONE;
}

/**
    Clear every stage maker object on screen
*/
void StageMaker::clearAll(){
    objects.clear();
    gDialog->commandClearStage->execute();
    gDialog->currentState = GAME_STATUS_STAGE_MAKER;
}

/**
    method / button to allow player to try out the stage they built. We need to take the input
    of the gui location of each aliens / barrier blocks / instruction box to translate them into the
    generateAliens method that was made in Stage 1.
*/
void StageMaker::testStage(){
    // Now we need to try use all the user inputs to generate a swarminfo file and run the stage.
    int defaultShootInterval = 10;

    // list to assign the placed object (aliens) to the corresponding instruction box
    std::vector<std::pair<SMakerPlacedObject, std::vector<SMakerPlacedObject>>> instructionsList;
    // default instructionbox for all that has no connected line

    std::pair<SMakerPlacedObject, std::vector<SMakerPlacedObject>> defaultInstruction = std::make_pair(objectTemplate[SMAKER_HOLDING_INSTRUCTION_BOX], std::vector<SMakerPlacedObject>());

    // first loop through it and retrieve all instructions
    for(SMakerPlacedObject obj : objects){
        if(obj.type == SMAKER_HOLDING_INSTRUCTION_BOX){
            auto pair = std::make_pair(obj, std::vector<SMakerPlacedObject>());
            instructionsList.push_back(pair);
        }
    }

    // for all other alien objects, pair it with the instructions (if exists). if not, use the default instruction (do nothing)
    for(SMakerPlacedObject& obj : objects){
        switch(obj.type){
        case(SMAKER_HOLDING_ALIEN_BLUE):
        case(SMAKER_HOLDING_ALIEN_RED):
        case(SMAKER_HOLDING_ALIEN_HUNTER):
        case(SMAKER_HOLDING_ALIEN_DUMB):
            // search through the list to pair it with the instruction box
            std::pair<SMakerPlacedObject, std::vector<SMakerPlacedObject>> *instructionBox = NULL;
            if(obj.connected){
                for(auto&& instruction : instructionsList){
                    if(instruction.first.hitBox.contains(obj.connectedPoint)){
                        instructionBox = &instruction;
                        break;
                    }
                }
            }
            // if none are found, use the default instruction box.
            if(!instructionBox)
                instructionBox = &defaultInstruction;

            // place the object into the instruction list
            instructionBox->second.push_back(obj);
            break;
        }
    }

    // push back the default instruction box
    instructionsList.push_back(defaultInstruction);

    // Now build up the QList of swarm info to send to the alien builder from Stage 1
    QList<SwarmInfo> swarms;
    for(auto&& instruction : instructionsList){
        QStringList strList = instruction.first.instructions.split(",");

        for(auto&& obj : instruction.second){
            QString type;
            switch(obj.type){ // convert enum to qstring
            case(SMAKER_HOLDING_ALIEN_BLUE):
                type = "blue";
                break;
            case(SMAKER_HOLDING_ALIEN_RED):
                type = "red";
                break;
            case(SMAKER_HOLDING_ALIEN_HUNTER):
                type = "hunter";
                break;
            case(SMAKER_HOLDING_ALIEN_DUMB):
                type = "dumb";
                break;
            }
            QList<QPair<int, int>> p;
            p.append(QPair<int, int> (obj.hitBox.x(),obj.hitBox.y()));
            SwarmInfo info(type, p, strList, defaultShootInterval);
            swarms.push_back(info);
        }
    }
    // tell the main window to generate swarms
    gDialog->generateAliens(swarms);
    gDialog->cursor.setCursorState(FIGHTER);

    // append all the barrier blocks into the game engine
    for(auto&& obj : objects){
        if(obj.type == SMAKER_HOLDING_BARRIER_BLOCK){
            gDialog->barriers.push_back(BarrierBlock(obj.hitBox.x(), obj.hitBox.y(),BLOCK_DIMENSION));
        }
    }

    // set current state as testing
    gDialog->currentState = GAME_STATUS_STAGE_MAKER_TESTING;
}

}
