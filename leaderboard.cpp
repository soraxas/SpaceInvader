#include "leaderboard.h"
#include <vector>
#include <QtDebug>
namespace game{
LeaderBoard::LeaderBoard() {
    
}

void LeaderBoard::init(int ScreenWidth, int ScreenHeight, QString filename) {
    this->finished = false;
    this->ScreenWidth = ScreenWidth;
    this->ScreenHeight = ScreenHeight;
    this->filename = filename;
    leaderBoardTitle = QRect(0, ScreenHeight, ScreenWidth, ScreenHeight*0.2);
};

void LeaderBoard::draw(QPainter* p){
    QFont f("Times");
    // first draw the Leader Board title
    p->save();

    f.setPixelSize(leaderBoardTitle.height() * 0.6);
    f.setBold(true);
    //    f.setOverline(true);
    f.setUnderline(true);
    f.setHintingPreference(QFont::PreferFullHinting);
    p->setFont(f);
    p->setPen(Qt::red);
    p->drawText(leaderBoardTitle, Qt::AlignCenter, "LEADER BOARD");
    
    p->setPen(QColor::fromRgb(72, 240, 120));
    f.setItalic(true);
    f.setBold(false);
    f.setOverline(false);
    f.setUnderline(false);

    // only draw the column header as green, other as white
    bool drawnHeader = false;

    // go through the vector and draw every players' name
    for(std::pair<QRect, QStringList>& player: players){
        if(!drawnHeader){
            drawnHeader = true;
        }else{
            p->setPen(Qt::white);
        }

        f.setPixelSize(player.first.height() * 0.6);
        p->setFont(f);
        // draw everything
        int itemNum = player.second.size();
        for(int i = 0; i < player.second.size(); ++i){
            int slotWidth = player.first.width() * (1.0/itemNum);
            p->drawText(player.first.x() + slotWidth*i, player.first.y(),
                        slotWidth, player.first.height(),
                        Qt::AlignCenter,
                        player.second[i]);
        }
    }
    
    p->restore();
}

void LeaderBoard::update(){
    if(finished)
        return;

    int ySpeed = 5;
    leaderBoardTitle.moveTop(leaderBoardTitle.y() - ySpeed);
    for(auto&& player : players)
        player.first.moveTop(player.first.y() - ySpeed);

    // check if the last item has passed the screen, if so finish this
    if(players.size() > 0 && players.back().first.bottom() < 0){
        this->finished = true;
    }
}

void LeaderBoard::reset(){
    finished = false;
    players.clear();
    leaderBoardTitle.moveTop(ScreenHeight);

    // determine the locatin of next item
    int yOffset = leaderBoardTitle.bottom();

    // push a default item for showing the title of each column
    QStringList strs = {"<NAME>", "<PROGRESS>", "<SCORE>"};
    std::pair<QRect, QStringList> pair = std::make_pair(QRect(0, yOffset, ScreenWidth, ScreenHeight*0.1), strs);
    players.push_back(pair);
    yOffset = players.back().first.bottom();


    std::vector<QStringList> playerList;
    // read the leaderboard file, put everything in a vector first
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString str = in.readLine().trimmed();
        if(!str.isEmpty()){
            QStringList strList = str.split("=:="); // special token for splitting
            while(strList.size() < 3)
                // if the list is < 3 (meaning there are some error), we pad it with empty space
                strList.append(" ");
            playerList.push_back(strList);
        }
    }

    // now we sort the players and have the top player appear first
    // sort the vector by decreasing score
    // use lambda expression for the nested pair
    std::sort(playerList.begin(), playerList.end(), [](const QStringList& lhs, const QStringList& rhs)
    {
        return lhs[2].toInt() > rhs[2].toInt();
    });
    // now for every player, we add it to the score board
    for(QStringList playerScores: playerList){
        QRect player = QRect(0, yOffset, ScreenWidth, ScreenHeight*0.1);
        std::pair<QRect, QStringList> pair = std::make_pair(player, playerScores);
        players.push_back(pair);
        yOffset = players.back().first.bottom();
    }
}

}
