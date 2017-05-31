#include "leaderboardnamerequest.h"
#include "ui_leaderboardnamerequest.h"

LeaderBoardNameRequest::LeaderBoardNameRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::leaderBoardNameRequest)
{
    ui->setupUi(this);
}

LeaderBoardNameRequest::~LeaderBoardNameRequest()
{
    delete ui;
}

void LeaderBoardNameRequest::on_buttonBox_accepted()
{

}
