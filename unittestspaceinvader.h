#ifndef SPACEINVADERUNITTEST_H
#define SPACEINVADERUNITTEST_H

#include <QtTest/QtTest>
#include "gamedialog.h"

using namespace game;
class UnitTestSpaceInvader : public QObject
{
    Q_OBJECT
public:
    GameDialog* gd;
private slots:
    void initTestCase();
    void cleanupTestCase();

    void testBullet();
    void testCursorState();
};

#endif // SPACEINVADERUNITTEST_H
