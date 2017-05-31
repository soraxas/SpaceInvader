#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include "config.h"
#include "menu.h"
#include "ship.h"
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

#include "command.h"
#include "commandgamestart.h"
#include "commandgamepause.h"
#include "commandclearstage.h"
#include "commonrestartstage.h"
#include "commandgototitlescreenmode.h"
#include "commandgotogamemode.h"
#include "commandgotostagemakermode.h"
#include "commandgotoleaderboardmode.h"

#include <QDialog>
#include <QSoundEffect>
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
    void generateAliens(const QList<SwarmInfo>& swarms);
    virtual ~GameDialog();

    QTimer* timer;
    void paintEvent(QPaintEvent* event);
    void paintBullets(QPainter& painter);
    void updateBullets();
    void paintSwarm(QPainter& painter, AlienBase*& root);
    void checkSwarmCollisions(AlienBase*& root);
    // ship and swarms
    Ship* ship;
    std::vector<Bullet*> bullets;
    AlienBase* swarms;  // swarms is the ROOT node of the composite
    QSoundEffect shipFiringSound;
    int next_instruct;

    // finished game, get info (name)
    void requestName(QString info);

    // keys
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

    // about the canvas
    int frames;
    const int WIDTH = 800;
    const int HEIGHT = 600;
    int SCALEDWIDTH;
    int SCALEDHEIGHT;
    int STATUSBARHEIGHT;

    // collision...
    int get_collided_swarm(Bullet*& b, AlienBase*& root);
    int get_collided(Bullet*& b, AlienBase*& root);
    void addBullets(const QList<Bullet*>& list);

    // pausing & menu
    bool paused;
    Menu* menu;
    int countAliens(AlienBase* root);

    // Game Settings
    StageMaker stageMaker;
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
    std::vector<Explosion> explosions;
    std::vector<BarrierBlock> barriers;
    std::vector<Powerup> powerups;
    LaserBeam laserBeam;
    StatusBar statusBar;
    Config* c;

    // Helper function
    static int randInt(int low, int high);
    static void SeedRandInt();

    GameMenu gameMenu;
    LeaderBoardNameRequest leaderBoardNameRequest;
    bool updateBullets_barrierChkHelper(int x, int y);
    void printDebugInfo(QPainter* p);
    bool playerOverride; //override the movement within config file if key pressed LEFT, RIGHT or SPACEBAR
    std::map<int,bool> pressedKeys;
    Background bg;
    Cursor cursor; // cursor for various functions
    GAME_STATUS currentState;

    void initCommands();
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
};

}

#endif // end GAMEDIALOG
