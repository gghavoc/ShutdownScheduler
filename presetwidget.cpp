#include <QDebug>

#include "presetwidget.h"
#include "ui_presetwidget.h"
#include "shutdownscheduler.h"


PresetWidget::PresetWidget(PresetItem presetItem, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PresetWidget)
    , presetItem(presetItem)
{   
    this->ui->setupUi(this);

    // size
    this->setMinimumSize(this->sizeHint());

    // set ui elements
    this->ui->dateLabel->setText(this->presetItem.date().toString());
    this->ui->timeLabel->setText(this->presetItem.time().toString());

    // hide timer at init
    this->ui->timerFrame->hide();

    switch (presetItem.type()) {
    case ShutdownScheduler::Type::Shutdown:
        this->ui->typeLabel->setText(tr("SHUTDOWN"));
        break;
    case ShutdownScheduler::Type::Restart:
        this->ui->typeLabel->setText(tr("RESTART"));
        break;
    case ShutdownScheduler::Type::LogOut:
        this->ui->typeLabel->setText(tr("LOG-OUT"));
        break;
    default:
        this->ui->typeLabel->setText(tr("[TYPE]"));
        break;
    }

    switch (presetItem.timing()) {
    case ShutdownScheduler::Timing::Now:
        this->ui->timingLabel->setText(tr("NOW"));
        break;
    case ShutdownScheduler::Timing::At:
        this->ui->timingLabel->setText(tr("AT"));
        break;
    case ShutdownScheduler::Timing::After:
        this->ui->dateLabel->hide();
        this->ui->timingLabel->setText(tr("AFTER"));
        break;
    default:
        this->ui->timingLabel->setText(tr("[TIMING]"));
        break;
    }
}

PresetWidget::~PresetWidget()
{
    delete ui;
}
