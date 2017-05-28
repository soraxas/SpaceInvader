#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QDialog>

namespace Ui {
class GameMenu;
}

class GameMenu : public QDialog
{
    Q_OBJECT

public:
    explicit GameMenu(QWidget *parent = 0);
    ~GameMenu();

private slots:
    void on_GameMenu_accepted();

private:
    Ui::GameMenu *ui;
};

#endif // GAMEMENU_H
