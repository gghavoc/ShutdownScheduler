#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shutdowndialog.h"
#include "shutdowndialog.h"

#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->readSettings();
    this->ui->setupUi(this);

    // create gui elements
    this->createAction();
    this->createMenu();

    this->changeUi(this->showExtendedUi);

    // link signals and slots
    this->createConnection();

    this->layout()->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
}

MainWindow::~MainWindow()
{
    this->writeSettings();
    delete ui;
}

void MainWindow::changeUi(bool extended)
{
    if (extended) {
        this->showExtendedUi = true;
        this->extendUi();
        Q_EMIT this->uiExtended(this->showExtendedUi);
    } else {
        this->showExtendedUi = false;
        this->shrinkUi();
        Q_EMIT this->uiExtended(this->showExtendedUi);
    }
}


void MainWindow::save()
{

}

void MainWindow::saveAs()
{

}

void MainWindow::open()
{

}

void MainWindow::shutdown()
{
    ShutdownDialog *d = new ShutdownDialog(this);
    this->connect(d, SIGNAL(shutdownSet(QDateTime,
                                        int,
                                        int,
                                        bool)),
                  this, SLOT(scheduleShutdown(QDateTime,
                                              int,
                                              int,
                                              bool)));
    if (d->exec()) {

    } else {

    }
    delete d;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Shutdown Scheduler"),
                       tr("<h1>Shutdown Scheduler</h1>"
                          "<h2>Copyright &copy; Clarence D. Manuel</h2>"
                          "<p>This small application is made using"
                          "Qt Widgets module from Qt Framework.\n"
                          "To learn more about Qt, "
                          "click \"About Qt\" under the help menu.</p>"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::exit()
{

}

void MainWindow::scheduleShutdown(QDateTime dateTime,
                                  int shutdownType,
                                  int shutdownTime,
                                  bool addToPreset)
{
    if (addToPreset) {
        qDebug() << "added to preset";
    }

    std::string flag;
    switch(shutdownType)
    {
    case ShutdownDialog::Shutdown:
        flag = SHUTDOWN;
        break;
    case ShutdownDialog::Restart:
        flag = RESTART;
        break;
    case ShutdownDialog::LogOut:
        break;
    default:
        break;
    }

    switch(shutdownTime)
    {
    case ShutdownDialog::Now:
        this->shutdownNow(flag);
        break;
    case ShutdownDialog::At:
        this->shutdownAt(dateTime,flag);
        break;
    case ShutdownDialog::After:
        this->shutdownAfter(this->dateTimeToSeconds(dateTime), flag);
        break;
    default:
        break;
    }
}

void MainWindow::readSettings()
{

}

void MainWindow::writeSettings()
{

}

void MainWindow::writeFile()
{

}

void MainWindow::readFile()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::close();
}

void MainWindow::createAction()
{
    // QAction *openAction;
    this->openAction = new QAction(tr("&Open Profile"), this);
    this->openAction->setShortcut(QKeySequence::StandardKey::Open);
    this->setStatusTip(tr("Open a preset file"));
    this->connect(this->openAction, SIGNAL(triggered()),
                  this, SLOT(open()));

    // QAction *saveAction;
    this->saveAction = new QAction(tr("&Save Profile"), this);
    this->saveAction->setShortcut(QKeySequence::StandardKey::Save);
    this->setStatusTip(tr("Open a preset file"));
    this->connect(this->saveAction, SIGNAL(triggered()),
                  this, SLOT(save()));

    // QAction *saveAsAction;
    this->saveAsAction = new QAction(tr("Sa&ve As"), this);
    this->saveAsAction->setShortcut(QKeySequence::StandardKey::SaveAs);
    this->setStatusTip(tr("Open a preset file"));
    this->connect(this->saveAsAction, SIGNAL(triggered()),
                  this, SLOT(saveAs()));

    // QAction *aboutAction;
    this->aboutAction = new QAction(tr("&About"), this);
    this->setStatusTip(tr("Show information about the application"));
    this->connect(this->aboutAction, SIGNAL(triggered()),
                  this, SLOT(about()));

    // QAction *aboutQtAction;
    this->aboutQtAction = new QAction(tr("About &Qt"), this);
    this->setStatusTip(tr("Show information about qt"));
    this->connect(this->aboutQtAction, SIGNAL(triggered()),
                  this, SLOT(aboutQt()));

    // QAction *showExtendedUiAction;
    this->showExtendedUiAction = new QAction(tr("Show &extended UI"), this);
    this->showExtendedUiAction->setShortcut(tr("Ctrl+Shift+X"));
    this->showExtendedUiAction->setCheckable(true);
    this->setStatusTip(tr("Schedule a shutdown request"));
    this->connect(this->showExtendedUiAction, SIGNAL(toggled(bool)),
                  this, SLOT(changeUi(bool)));

    // QAction *shutdownAction;
    this->shutdownAction = new QAction(tr("Shut&down"), this);
    this->shutdownAction->setShortcut(tr("Ctrl+Alt+X"));
    this->setStatusTip(tr("Schedule a shutdown request"));
    this->connect(this->shutdownAction, SIGNAL(triggered()),
                  this, SLOT(shutdown()));

    // QAction *exitAction;
    this->exitAction = new QAction(tr("E&xit"), this);
    this->exitAction->setShortcut(QKeySequence::StandardKey::Close);
    this->setStatusTip(tr("Exit the application"));
    this->connect(this->exitAction, SIGNAL(triggered()),
                  this, SLOT(exit()));

}

void MainWindow::createStatusBar()
{

}

void MainWindow::createMenu()
{
    // file
    this->ui->menuFile->addAction(this->openAction);
    this->ui->menuFile->addAction(this->saveAction);
    this->ui->menuFile->addAction(this->saveAsAction);
    this->ui->menuFile->addAction(this->exitAction);

    // options
    this->ui->menuOptions->addAction(this->showExtendedUiAction);

    // help
    this->ui->menuHelp->addAction(this->aboutAction);
    this->ui->menuHelp->addAction(this->aboutQtAction);
}

void MainWindow::createContextMenu()
{

}

void MainWindow::createConnection()
{
    this->connect(this->ui->shutDownButton, SIGNAL(pressed()),
                  this->shutdownAction, SIGNAL(triggered()));

    this->connect(this->ui->showExtendedUiCheckBox, SIGNAL(toggled(bool)),
                  this, SLOT(changeUi(bool)));

    // sync "show extended ui" checkbox on the form and menu
    this->connect(this, SIGNAL(uiExtended(bool)),
                  this->ui->showExtendedUiCheckBox, SLOT(setChecked(bool)));
    this->connect(this, SIGNAL(uiExtended(bool)),
                  this->showExtendedUiAction, SLOT(setChecked(bool)));
}

void MainWindow::shutdownNow(std::string flag)
{
    this->shutdownAfter(2, flag);
}

void MainWindow::shutdownAt(QDateTime schedDateTime, std::string flag)
{
    uint64_t totalSecondsNow = this->dateTimeToSeconds(QDateTime::currentDateTime());
    uint64_t totalSecondsAtSchedule = this->dateTimeToSeconds(schedDateTime);
    uint64_t secondsDelta = totalSecondsAtSchedule - totalSecondsNow;
    this->shutdownAfter(secondsDelta, flag);
}

void MainWindow::shutdownAfter(uint32_t seconds, std::string flag)
{
    std::string command = SHUTDOWN_COMMAND " " // add space between command and flags
            + flag
            + " " TIME " "
            + std::to_string(seconds);
    qDebug() << command.c_str();
    system(command.c_str());
}

void MainWindow::extendUi()
{
    this->menuBar()->show();
    this->statusBar()->show();
    this->ui->showExtendedUiCheckBox->hide();
    this->ui->topLayout->setDirection(QBoxLayout::Direction::LeftToRight);
}

void MainWindow::shrinkUi()
{
    this->menuBar()->hide();
    this->statusBar()->hide();
    this->ui->showExtendedUiCheckBox->show();
    this->ui->topLayout->setDirection(QBoxLayout::Direction::TopToBottom);
}

uint64_t MainWindow::dateTimeToSeconds(QDateTime dateTime)
{
    return  + (dateTime.date().year() * SECONDS_IN_YEAR)
            + (dateTime.date().month() * SECONDS_IN_MONTH)
            + (dateTime.date().day() * SECONDS_IN_DAY)
            + (dateTime.time().hour() * SECONDS_IN_HOUR)
            + (dateTime.time().minute() * SECONDS_IN_MINUTE)
            + dateTime.time().second();
}

