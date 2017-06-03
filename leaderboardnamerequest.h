#ifndef LEADERBOARDNAMEREQUEST_H
#define LEADERBOARDNAMEREQUEST_H

#include "ui_leaderboardnamerequest.h"
#include <QDialog>
#include <QFile>

namespace Ui {
class leaderBoardNameRequest;
}
namespace game {
class GameDialog;
class LeaderBoardNameRequest : public QDialog
{
    Q_OBJECT

public:
    explicit LeaderBoardNameRequest(QString filename, game::GameDialog* gDialog, QWidget* parent = 0);
    ~LeaderBoardNameRequest();
    Ui::leaderBoardNameRequest *ui;
    QString filename;
    game::GameDialog* gDialog;
private slots:
    void on_buttonBox_accepted();
    void reject();
};
}
#endif // LEADERBOARDNAMEREQUEST_H
