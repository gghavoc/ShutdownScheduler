#include <QDebug>
#include <QShowEvent>

#include "shutdowndialog.h"
#include "ui_shutdowndialog.h"

ShutdownDialog::ShutdownDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShutdownDialog)
{
    this->ui->setupUi(this);

    this->layout()->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    // add items to time combo box
    this->ui->timingComboBox->addItem(tr("Now"));
    this->ui->timingComboBox->addItem(tr("At"));
    this->ui->timingComboBox->addItem(tr("After"));

    // add items to type combo box
    this->ui->typeComboBox->addItem(tr("Shutdown"));
    this->ui->typeComboBox->addItem(tr("Restart"));
//    this->ui->typeComboBox->addItem(tr("Log Out"));

    // set current time at creation
    this->ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    // hide items at startup
    this->ui->dateTimeEdit->hide();
    this->ui->timeEdit->hide();
    this->ui->addToPresetsCheckBox->hide();
    this->ui->formatLabel->hide();

    // timeEdit show 24 hour format
    this->ui->dateTimeEdit->setDisplayFormat("MMM d - hh:mm:ss");
    this->ui->timeEdit->setDisplayFormat("hh:mm:ss");

    // connect okButton to okClicked()
    this->connect(this->ui->binaryButtonBox, SIGNAL(accepted()),
                  this, SLOT(okClicked()));

    // connect combo box to changeUi()
    this->connect(this->ui->timingComboBox, SIGNAL(currentIndexChanged(int)),
                  this, SLOT(changeUi(int)));

    // destroy on close
    // this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose)
}

ShutdownDialog::~ShutdownDialog()
{
    delete ui;
}

void ShutdownDialog::showEvent(QShowEvent *event)
{
    // reset ui every time it shows
    this->ui->typeComboBox->setCurrentIndex(0);
    this->ui->timingComboBox->setCurrentIndex(0);
    QDialog::showEvent(event);
}

void ShutdownDialog::okClicked()
{
    PresetItem presetItem;

    presetItem.setShutdownType((ShutdownScheduler::Type)this->ui->typeComboBox->currentIndex());
    presetItem.setShutdownTiming((ShutdownScheduler::Timing)this->ui->timingComboBox->currentIndex());

    switch (presetItem.timing())
    {
    case ShutdownScheduler::Timing::Now:
        presetItem.dateTime().setTime(QTime(0, 0, 0, 0));    // h, m, s, ms
        presetItem.dateTime().setDate(QDate(0, 0, 0));       // y, m, d
        break;
    case ShutdownScheduler::Timing::At:
        presetItem.dateTime() = this->ui->dateTimeEdit->dateTime();
        break;
    case ShutdownScheduler::Timing::After:
        presetItem.dateTime().setTime(this->ui->timeEdit->time());
        presetItem.dateTime().setDate(QDate(0, 0, 0));       // y, m, d
        break;
    default:
        break;
    }

    Q_EMIT this->shutdownSet(presetItem,
                             this->ui->addToPresetsCheckBox->isChecked());

}

void ShutdownDialog::changeUi(int uiType)
{
    ShutdownScheduler::Timing shutdownType = (ShutdownScheduler::Timing)uiType;

    switch (shutdownType)
    {
    case ShutdownScheduler::Timing::Now:
        this->ui->dateTimeEdit->hide();
        this->ui->timeEdit->hide();
        this->ui->addToPresetsCheckBox->hide();
        this->ui->formatLabel->hide();
        break;
    case ShutdownScheduler::Timing::At:
        this->ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        this->ui->dateTimeEdit->show();
        this->ui->timeEdit->hide();
        this->ui->addToPresetsCheckBox->show();
        this->ui->formatLabel->setText(tr("M D - HH:MM:SS"));
        this->ui->formatLabel->show();

        break;
    case ShutdownScheduler::Timing::After:
        this->ui->dateTimeEdit->hide();
        this->ui->timeEdit->time().setHMS(0, 0, 0);
        this->ui->timeEdit->show();
        this->ui->addToPresetsCheckBox->show();
        this->ui->formatLabel->setText(tr("HH:MM:SS"));
        this->ui->formatLabel->show();
        break;
    default:
        break;
    }
}
