#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>
#include <QRect>
#include <QPainter>
#include <QStringList>
#include <QFile>
#include <QTextStream>


namespace game{
class LeaderBoard
{
public:
    LeaderBoard();
    void init(int ScreenWidth, int ScreenHeight, QString filename);
    void draw(QPainter* p);
    void update();
    void reset();

    QRect leaderBoardTitle;
    std::vector<std::pair<QRect, QStringList>> players;
    bool finished;
    QString filename;
    int ScreenWidth;
    int ScreenHeight;
};
}

#endif // LEADERBOARD_H
