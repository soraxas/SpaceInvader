#ifndef SPACEINVADERUNITTEST_H
#define SPACEINVADERUNITTEST_H

/**
    Unit testing of the entire game
*/

#include <QtTest/QtTest>
#include "gamedialog.h"

namespace game {
class GameDialog; // forward declare
}

class UnitTestSpaceInvader : public QObject
{
    Q_OBJECT
private slots:
    // to initialise variable before the entire test
    void initTestCase();
    // to clean up after the entire test
    void cleanupTestCase();
    // to initialise the variable before each test case
    void init();
    // to clean up after each test case
    void cleanup();
    // testing the correctness of the cursor state
    void testCursorState();
    // testing the command patterns and each commands
    void testCommandPattern();
    // testing the correctness of the stage maker m ode
    void testStageMaker();
    // testing the correctness of the status bar
    void testStatusBar();
private:
    game::GameDialog* gd;
};

#endif // SPACEINVADERUNITTEST_H
