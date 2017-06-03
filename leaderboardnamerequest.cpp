#include "leaderboardnamerequest.h"
#include "ui_leaderboardnamerequest.h"
#include "gamedialog.h"
#include <QtDebug>
#include <QTextStream>

namespace game{
LeaderBoardNameRequest::LeaderBoardNameRequest(QString filename, game::GameDialog* gDialog, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::leaderBoardNameRequest), filename(filename), gDialog(gDialog)
{
    ui->setupUi(this);
}

LeaderBoardNameRequest::~LeaderBoardNameRequest()
{
    delete ui;
}

void LeaderBoardNameRequest::on_buttonBox_accepted()
{
    // prepare the string to append to
    QString str;
    // name
    str += ui->nameTextInput->text();
    // token between each string
    str += "=:=";
    // stage number
    str += "Stage " + QString::number(gDialog->curStageNum);
    // token between each string
    str += "=:=";
    // score
    str += QString::number(gDialog->gameScore);
    // new line
    str += "\r\n";

    // append to file
    QFile file(filename);
    QTextStream out(&file);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append)){
        out << str;
    }
    out.flush();
    // return to title screen
    gDialog->commandGoToLeaderBoardMode->execute();
}

// override close event
void LeaderBoardNameRequest::reject() {
    gDialog->commandGoToTitleScreenMode->execute();
    QDialog::reject();
}
}
