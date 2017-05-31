#ifndef LEADERBOARDNAMEREQUEST_H
#define LEADERBOARDNAMEREQUEST_H

#include "ui_leaderboardnamerequest.h"
#include <QDialog>

namespace Ui {
class leaderBoardNameRequest;
}

class LeaderBoardNameRequest : public QDialog
{
    Q_OBJECT

public:
    explicit LeaderBoardNameRequest(QWidget *parent = 0);
    ~LeaderBoardNameRequest();
    Ui::leaderBoardNameRequest *ui;
private slots:
    void on_buttonBox_accepted();

};

#endif // LEADERBOARDNAMEREQUEST_H
