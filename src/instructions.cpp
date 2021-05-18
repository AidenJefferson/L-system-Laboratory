#include "instructions.h"
#include "ui_instructions.h"
#include <QIcon>

Instructions::Instructions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Instructions)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/instructions.ico"));
}

Instructions::~Instructions()
{
    delete ui;
}
