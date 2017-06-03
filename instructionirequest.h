#ifndef INSTRUCTIONIREQUEST_H
#define INSTRUCTIONIREQUEST_H

#include "ui_instructionrequest.h"
#include <QDialog>
#include <QString>

namespace Ui {
class InstructionRequest;
}

namespace game {
struct SMakerPlacedObject;
// class for the request UI dialog box
class InstructionRequest: public QDialog{
    Q_OBJECT

public:
    explicit InstructionRequest(QWidget *parent = 0);
    ~InstructionRequest();
    QString instructions;
    SMakerPlacedObject* instructionBox;

private slots:
    void on_pushButton_up_clicked();
    void on_pushButton_left_clicked();
    void on_pushButton_down_clicked();
    void on_pushButton_right_clicked();
    void on_pushButton_apply_clicked();

private:
    void appendText(QString s);
    Ui::InstructionRequest *ui;
};
}
#endif // INSTRUCTIONIREQUEST_H
