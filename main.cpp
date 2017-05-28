#include "gamedialog.h"
#include <QApplication>
#include "unittestspaceinvader.h"

using namespace game;

int main(int argc, char* argv[]) {
    UnitTestSpaceInvader testSI;
    QTest::qExec(&testSI, argc, argv);

    QApplication a(argc, argv);
    GameDialog w;
    w.show();
    return a.exec();
}
