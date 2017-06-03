#include "unittestspaceinvader.h"
#include "gamedialog.h"

using namespace game;

void UnitTestSpaceInvader::initTestCase(){}
void UnitTestSpaceInvader::cleanupTestCase(){}

void UnitTestSpaceInvader::init(){
    // initialise the game dialog
    gd = new game::GameDialog;
}
void UnitTestSpaceInvader::cleanup(){
    // clear everything
    delete gd;
}

void UnitTestSpaceInvader::testCommandPattern(){
    /////////////////////////////////////////////
    //// Check the command design patterns works
    ////////////////////////////////////////////

    // go to title screen
    gd->commandGoToTitleScreenMode->execute();
    QCOMPARE(gd->currentState, GAME_STATUS_TITLE_SCREEN);
    // go to Stage Maker
    gd->commandGoToStageMakerMode->execute();
    QCOMPARE(gd->currentState, GAME_STATUS_STAGE_MAKER);
    // go to Leader Board
    gd->commandGoToLeaderBoardMode->execute();
    QCOMPARE(gd->currentState, GAME_STATUS_LEADER_BOARD);
    // go to in game mode
    gd->commandGoToGameMode->execute();
    QCOMPARE(gd->currentState, GAME_STATUS_IN_GAME);


    /////////////////////////////////////////////
    //// Test the clearing of the stage
    ////////////////////////////////////////////

    // first there must be no aliens
    QCOMPARE(gd->countAliens(gd->swarms), 0);

    // add one alien to the swarms
    QList<SwarmInfo> swarms;
    QList<QPair<int,int>> pos;
    pos.push_back(QPair<int,int>(10,10));
    QStringList strList = {"L", "R"};
    SwarmInfo info("blue", pos, strList, 10);
    // generate the alien
    swarms.push_back(info);
    gd->generateAliens(swarms);

    //vertify the number of aliens is one
    QCOMPARE(gd->countAliens(gd->swarms), 1);

    // clear the stage
    gd->commandClearStage->execute();
    // should have zero alien
    QCOMPARE(gd->countAliens(gd->swarms), 0);
    // clear again
    gd->commandClearStage->execute();
    // should still have zero alien
    QCOMPARE(gd->countAliens(gd->swarms), 0);

    // push back five aliens
    swarms.clear();
    for(int i = 0; i < 5; ++i)
        swarms.push_back(info);
    gd->generateAliens(swarms);
    // should have 5 aliens now
    QCOMPARE(gd->countAliens(gd->swarms), 5);
    // clear stage
    gd->commandClearStage->execute();
    // should have zero alien
    QCOMPARE(gd->countAliens(gd->swarms), 0);


    /////////////////////////////////////////////
    //// Test the pause / start of the game
    ////////////////////////////////////////////

    // test the game pause and unpause
    gd->commandGameStart->execute();
    // the game should be running now
    QVERIFY(!gd->paused);
    // pause it
    gd->commandGamePause->execute();
    // the game should be running now
    QVERIFY(gd->paused);
    // pause again, should not affect it
    gd->commandGamePause->execute();
    // the game should be running now
    QVERIFY(gd->paused);
}

void UnitTestSpaceInvader::testCursorState(){
    Cursor c(gd);

    /////////////////////////////////////////////
    //// Check the changing of the cursor state
    ////////////////////////////////////////////
    // must be normal state at start
    QVERIFY(c.state == NORMAL);
    // get the current cursor state to compare with it later
    CursorState* NormalCursorState = c.getCurState();

    // now try to switch cursor state
    c.setCursorState(FIGHTER);
    QVERIFY(c.state == FIGHTER);
    CursorState* FighterCursorState = c.getCurState();
    // compare the normal cursor with the fighter state, must be different
    QCOMPARE(NormalCursorState == FighterCursorState, false);

    // test all other cursor state as well
    c.setCursorState(PEN);
    QVERIFY(c.state == PEN);
    CursorState* PenCursorState = c.getCurState();
    QVERIFY(PenCursorState != NormalCursorState);

    c.setCursorState(STAGEMAKER);
    QVERIFY(c.state == STAGEMAKER);
    CursorState* StageMakerCursorState = c.getCurState();
    QVERIFY(StageMakerCursorState != NormalCursorState);

    // revert back to the normal state
    c.setCursorState(NORMAL);
    // this state must be the same as the one we get before
    QCOMPARE(NormalCursorState, c.getCurState());
}

void UnitTestSpaceInvader::testStageMaker(){
    // go to stage maker state first
    gd->commandGoToStageMakerMode->execute();
    StageMaker& smaker = gd->stageMaker;
    // test initialise it again won't crash
    smaker.init();
    smaker.init();
    // test placing object. first cursor in the middle of screen
    gd->cursor.getCurState()->cursorX = gd->SCALEDWIDTH/2;
    gd->cursor.getCurState()->cursorY = gd->SCALEDHEIGHT/2;
    // simulate holding an alien
    smaker.holdingObject = SMAKER_HOLDING_ALIEN_BLUE;
    // simulate button release
    smaker.buttonReleased();

    //test stage
    smaker.testStage();
    // there should be one aliens in the main game
    QCOMPARE(gd->countAliens(gd->swarms), 1);
    // clear stage
    smaker.clearAll();
    // should have no aliens now
    QCOMPARE(gd->countAliens(gd->swarms), 0);

    // test placing 5 aliens
    smaker.holdingObject = SMAKER_HOLDING_ALIEN_BLUE;
    smaker.buttonReleased(); // first alien
    // change location
    smaker.holdingObject = SMAKER_HOLDING_ALIEN_BLUE;
    gd->cursor.getCurState()->cursorX = gd->SCALEDWIDTH/4;
    gd->cursor.getCurState()->cursorY = gd->SCALEDHEIGHT/4;
    smaker.buttonReleased(); // second alien
    // change alien type
    gd->cursor.getCurState()->cursorX = gd->SCALEDWIDTH/5;
    gd->cursor.getCurState()->cursorY = gd->SCALEDHEIGHT/5;
    smaker.holdingObject = SMAKER_HOLDING_ALIEN_RED;
    smaker.buttonReleased(); // thire alien
    smaker.holdingObject = SMAKER_HOLDING_ALIEN_BLUE;
    gd->cursor.getCurState()->cursorX = gd->SCALEDWIDTH/6;
    gd->cursor.getCurState()->cursorY = gd->SCALEDHEIGHT/6;
    smaker.buttonReleased(); // fourth alien
    gd->cursor.getCurState()->cursorX = gd->SCALEDWIDTH/7;
    gd->cursor.getCurState()->cursorY = gd->SCALEDHEIGHT/7;
    smaker.holdingObject = SMAKER_HOLDING_ALIEN_HUNTER;
    smaker.buttonReleased(); // fifth alien

    // test stage
    smaker.testStage();
    QCOMPARE(gd->countAliens(gd->swarms), 5);

    // clear stage
    smaker.clearAll();
    QCOMPARE(gd->countAliens(gd->swarms), 0);
}

void UnitTestSpaceInvader::testStatusBar(){
    // create a status bar
    StatusBar sBar(gd);
    // test the initial value of the energy bar
    QVERIFY(sBar.plasmaEnergy - 100 < 0.1 && sBar.plasmaEnergy - 100 > -0.1);
    QVERIFY(sBar.barrierEnergy - 0 < 0.1 && sBar.barrierEnergy - 0 > -0.1);
    for(int i = 0; i < 100; ++i)
        sBar.update();
    // test again and the value should be the same
    QVERIFY(sBar.plasmaEnergy - 100 < 0.1 && sBar.plasmaEnergy - 100 > -0.1);
    QVERIFY(sBar.barrierEnergy - 0 < 0.1 && sBar.barrierEnergy - 0 > -0.1);
}

