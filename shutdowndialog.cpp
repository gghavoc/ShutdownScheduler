#include "shutdowndialog.h"
#include "ui_shutdowndialog.h"

#include "QDebug"

ShutdownDialog::ShutdownDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShutdownDialog)
{
    this->ui->setupUi(this);

    this->layout()->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

    // add items to time combo box
    this->ui->timeComboBox->addItem(tr("Now"));
    this->ui->timeComboBox->addItem(tr("At"));
    this->ui->timeComboBox->addItem(tr("After"));

    // add items to type combo box
    this->ui->typeComboBox->addItem(tr("Shutdown"));
    this->ui->typeComboBox->addItem(tr("Restart"));
//    this->ui->typeComboBox->addItem(tr("Log Out")); // don't allow logging out

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
    this->connect(this->ui->timeComboBox, SIGNAL(currentIndexChanged(int)),
                  this, SLOT(changeUi(int)));
}

ShutdownDialog::~ShutdownDialog()
{
    delete ui;
}

void ShutdownDialog::okClicked()
{
    int typeFlag = this->ui->typeComboBox->currentIndex();
    int timeFlag = this->ui->timeComboBox->currentIndex();

    QDateTime dateTime;

    switch (timeFlag)
    {
    case ShutdownTime::Now:
        dateTime.setTime(QTime(0, 0, 0, 0));    // h, m, s, ms
        dateTime.setDate(QDate(0, 0, 0));       // y, m, d
        break;
    case ShutdownTime::At:
        dateTime = this->ui->dateTimeEdit->dateTime();
        break;
    case ShutdownTime::After:
        dateTime.setTime(this->ui->timeEdit->time());
        dateTime.setDate(QDate(0, 0, 0));       // y, m, d
        break;
    default:
        break;
    }

    qDebug() << typeFlag << timeFlag;
    Q_EMIT this->shutdownSet(dateTime,
                             typeFlag,
                             timeFlag,
                             this->ui->addToPresetsCheckBox->isChecked());

}

void ShutdownDialog::changeUi(int shutdownType)
{
    switch (shutdownType)
    {
    case ShutdownTime::Now:
        this->ui->dateTimeEdit->hide();
        this->ui->timeEdit->hide();
        this->ui->addToPresetsCheckBox->hide();
        this->ui->formatLabel->hide();
        break;
    case ShutdownTime::At:
        this->ui->dateTimeEdit->show();
        this->ui->timeEdit->hide();
        this->ui->addToPresetsCheckBox->show();
        this->ui->formatLabel->setText(tr("M D - HH:MM:SS"));
        this->ui->formatLabel->show();

        break;
    case ShutdownTime::After:
        this->ui->dateTimeEdit->hide();
        this->ui->timeEdit->show();
        this->ui->addToPresetsCheckBox->show();
        this->ui->formatLabel->setText(tr("HH:MM:SS"));
        this->ui->formatLabel->show();
        break;
    default:
        break;
    }
}
