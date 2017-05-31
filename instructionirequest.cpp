#include "instructionirequest.h"
#include "stagemaker.h"

namespace game {
// Class implementation for the request instructions dialog box
InstructionRequest::InstructionRequest(QWidget *parent) : QDialog(parent),
    ui(new Ui::InstructionRequest) {
    ui->setupUi(this);
}

InstructionRequest::~InstructionRequest(){
    delete ui;
}

void InstructionRequest::appendText(QString s){
    // append a comma is it is not empty
    if(instructions.size() != 0)
        instructions += ",";
    instructions += s;
    // update text
    ui->label_instructions->setText(instructions);
}

void InstructionRequest::on_pushButton_up_clicked(){
    appendText("U");
}

void InstructionRequest::on_pushButton_down_clicked(){
    appendText("D");
}

void InstructionRequest::on_pushButton_left_clicked(){
    appendText("L");
}

void InstructionRequest::on_pushButton_right_clicked(){
    appendText("R");
}

void InstructionRequest::on_pushButton_apply_clicked() {
    // set the instruction to the instruction box
    instructionBox->instructions = instructions;
    // clear self text
    instructions.clear();
    ui->label_instructions->setText(instructions);
    close();
}

}






