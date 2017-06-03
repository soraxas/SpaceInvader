#include "gamedialog.h"
#include <QApplication>
#include "unittestspaceinvader.h"

using namespace game;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // first run unit test
    UnitTestSpaceInvader testSI;
    QTest::qExec(&testSI, argc, argv);

    // run the main game
    GameDialog w;
    w.show();
    return a.exec();
}
