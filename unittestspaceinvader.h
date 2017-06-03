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
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void testBullet();
    void testCursorState();
    void testCommandPattern();
    void testStageMaker();
    void testStatusBar();
private:
    game::GameDialog* gd;
};

#endif // SPACEINVADERUNITTEST_H
