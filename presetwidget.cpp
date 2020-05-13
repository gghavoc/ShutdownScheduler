#include "presetwidget.h"
#include "ui_presetwidget.h"

PresetWidget::PresetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresetWidget)
{
    ui->setupUi(this);
}

PresetWidget::~PresetWidget()
{
    delete ui;
}
