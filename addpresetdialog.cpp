#include "addpresetdialog.h"
#include "ui_addpresetdialog.h"

AddPresetDialog::AddPresetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPresetDialog)
{
    ui->setupUi(this);
}

AddPresetDialog::~AddPresetDialog()
{
    delete ui;
}
