#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include "config.h"
#include "menu.h"
#include "ship.h"
#include "bullet.h"
#include "swarm.h"
#include "swarminfo.h"
#include "background.h"
#include "cursor.h"
#include "explosion.h"
#include "barrierblock.h"
#include "statusbar.h"
#include "gamemenu.h"
#include "powerup.h"
#include "stagemaker.h"
#include "leaderboardnamerequest.h"
#include "leaderboard.h"
#include "qtsoundplayer.h"
// command design pattern
#include "command.h"
#include "commandgamestart.h"
#include "commandgamepause.h"
#include "commandclearstage.h"
#include "commonrestartstage.h"
#include "commandgototitlescreenmode.h"
#include "commandgotogamemode.h"
#include "commandgotostagemakermode.h"
#include "commandgotoleaderboardmode.h"
// QT and std library
#include <QTimer>
#include <QCursor>
#include <QtMath>
#include <QTime>
#include <stack>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QSound>
#include <QDialog>
#include <QWidget>
#include <vector>
#include <QMouseEvent>
#include <memory>

namespace game {
// enum that defines what sort of stage is the game currently in.
enum GAME_STATUS{GAME_STATUS_TITLE_SCREEN, GAME_STATUS_IN_GAME, GAME_STATUS_LEADER_BOARD,
                 GAME_STATUS_STAGE_MAKER, GAME_STATUS_STAGE_MAKER_TESTING};

class GameDialog : public QDialog {
    Q_OBJECT

public:
    GameDialog(QWidget* parent = nullptr);
    virtual ~GameDialog();
    void generateAliens(const QList<SwarmInfo>& swarms);
    void paintEvent(QPaintEvent* event);
    void updateBullets();
    void checkSwarmCollisions(AlienBase*& root);
    // keys
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    // collision...
    int get_collided_swarm(Bullet*& b, AlienBase*& root);
    int get_collided(Bullet*& b, AlienBase*& root);
    void addBullets(const QList<Bullet*>& list);
    // finished game, get info (name)
    void requestName(QString info);
    int countAliens(AlienBase* root);
    bool updateBullets_barrierChkHelper(int x, int y);
    void printDebugInfo(QPainter* p);
    // helper methods
    static int randInt(int low, int high);
    static void SeedRandInt();

    /////////////////////////////////////////////
    ////      Vairables
    ////////////////////////////////////////////
    // about the canvas
    int frames;
    const int WIDTH = 800;
    const int HEIGHT = 600;
    int SCALEDWIDTH;
    int SCALEDHEIGHT;
    int STATUSBARHEIGHT;
    int next_instruct;
    bool paused; // pausing
    bool playerOverride; //override the movement within config file if key pressed LEFT, RIGHT or SPACEBAR
    bool debugMode;
    double timerModifier;
    int powerUpDropRate;
    int gameScore;  // this run's score.
    bool legacyMode; // indicates if the game is running in the Stage 2 version
    int curStageNum;

    // transition of each stage
    QRect stageTransitionBox;
    bool stageTransition;

    // internal game management
    QTimer* timer;
    Menu* menu;
    StageMaker stageMaker;
    Ship* ship;
    std::vector<Explosion> explosions;
    std::vector<BarrierBlock> barriers;
    std::vector<Powerup> powerups;
    std::vector<Bullet*> bullets;
    AlienBase* swarms;  // swarms is the ROOT node of the composite
    LaserBeam laserBeam;
    StatusBar statusBar;
    Config* c;
    LeaderBoard leaderBoard;
    GameMenu gameMenu;
    LeaderBoardNameRequest leaderBoardNameRequest;
    std::map<int,bool> pressedKeys;
    Background bg;
    Cursor cursor; // cursor for various functions
    GAME_STATUS currentState;

    // All Available commands
    std::unique_ptr<Command> commandGameStart;
    std::unique_ptr<Command> commandGamePause;
    std::unique_ptr<Command> commandClearStage;
    std::unique_ptr<Command> commandRestartStage;
    std::unique_ptr<Command> commandGoToTitleScreenMode;
    std::unique_ptr<Command> commandGoToGameMode;
    std::unique_ptr<Command> commandGoToStageMakerMode;
    std::unique_ptr<Command> commandGoToLeaderBoardMode;

public slots:
    void nextFrame();
    // menus
    void showScore();
private:
    // helper functions for painting diferent objects
    void initCommands();
    void paintBullets(QPainter& painter);
    void paintSwarm(QPainter& painter, AlienBase*& root);
    void paintLaserBeam(QPainter& painter);
    void paintTitleScreen(QPainter& painter);
    void paintStageTransition(QPainter& painter);
};

}

#endif // end GAMEDIALOG
