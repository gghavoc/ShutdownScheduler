#include <QAction>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shutdowndialog.h"
#include "presetwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , shutdownDialog(nullptr)
    , showExtendedUi(false)
{
    this->readSettings();
    this->ui->setupUi(this);

    // create gui elements
    this->createAction();
    this->createMenu();
    this->createModalDialog();

    this->changeUi(this->showExtendedUi);

    // link signals and slots
    this->createConnection();

    // widget attribute
    //this->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);

    // set icon
    this->setWindowIcon(QIcon(":/resource/image/png/appicon.png"));
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
    } else {
        this->showExtendedUi = false;
        this->shrinkUi();
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
    this->shutdownDialog->exec();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Shutdown Scheduler"),
                       tr("<h3>Shutdown Scheduler</h3>"
                          "<p> Version " APP_VERSION " " APP_STATUS  " Build " APP_BUILD_NO "</p>"
                          "<h6>Copyright &copy; Clarence D. Manuel</h6>"
                          "<p>This small application is made using Qt Framework.\n"
                          "To learn more about Qt, "
                          "click \"About Qt\" under the help menu.</p>"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::exit()
{
    this->close();
}

void MainWindow::scheduleShutdown(PresetItem presetItem,
                                  bool addToPreset)
{
    if (presetItem.isValid()) {
        if (addToPreset) {
            qDebug() << "Added to presets";
            this->addToPreset(presetItem);
        }

        std::string flag;
        switch(presetItem.type())
        {
        case ShutdownScheduler::Type::Shutdown:
            flag = SHUTDOWN;
            break;
        case ShutdownScheduler::Type::Restart:
            flag = RESTART;
            break;
        case ShutdownScheduler::Type::LogOut:
            break;
        default:
            break;
        }

        this->shutdownAfter(presetItem.toRelativeSeconds(), flag);
    } else {
        qDebug() << "Invalid PresetItem";
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
    if (this->okToContinue()) {
        this->writeSettings();
//        event->accept(); same effect as QMainWindow::closeEvent(event);
        QMainWindow::closeEvent(event);
    } else {
        event->ignore();
    }
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

    // shutdownDialog connect to scheduleShutdown()
    this->connect(this->shutdownDialog, SIGNAL(shutdownSet(PresetItem, bool)),
                  this, SLOT(scheduleShutdown(PresetItem, bool)),
                  Qt::ConnectionType::UniqueConnection);

    // add preset button
    this->connect(this->ui->addPresetButton, SIGNAL(pressed()),
                  this->shutdownAction, SIGNAL(triggered()));
}

void MainWindow::createModalDialog()
{
    if (!this->shutdownDialog)
        this->shutdownDialog = new ShutdownDialog(this);
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
//    system(command.c_str());
}

void MainWindow::extendUi()
{
    // show
    this->menuBar()->show();
    this->statusBar()->show();
    this->ui->addPresetButton->show();
    this->ui->presetScrollArea->show();

    // hide
    this->ui->showExtendedUiCheckBox->hide();
    this->ui->shutDownButton->hide();
    this->ui->cancelButton->hide();

    // set adjustments
    this->ui->topLayout->setDirection(QBoxLayout::Direction::LeftToRight);
    this->setMinimumSize(400, 400);
    this->layout()->setSizeConstraint(QLayout::SizeConstraint::SetMinAndMaxSize);
    Q_EMIT this->uiExtended(this->showExtendedUi);
}

void MainWindow::shrinkUi()
{
    // show
    this->ui->showExtendedUiCheckBox->show();
    this->ui->shutDownButton->show();
    this->ui->cancelButton->show();

    // hide
    this->menuBar()->hide();
    this->statusBar()->hide();
    this->ui->addPresetButton->hide();
    this->ui->presetScrollArea->hide();

    // set adjustments
    this->ui->topLayout->setDirection(QBoxLayout::Direction::TopToBottom);
    this->layout()->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
    Q_EMIT this->uiExtended(this->showExtendedUi);
}

uint64_t MainWindow::dateTimeToSeconds(QDateTime dateTime)
{
    return  (dateTime.date().year() * (dateTime.date().daysInYear() * SECONDS_IN_DAY))
            + (dateTime.date().month() * (dateTime.date().daysInMonth() *SECONDS_IN_DAY))
            + (dateTime.date().day() * SECONDS_IN_DAY)
            + (dateTime.time().hour() * SECONDS_IN_HOUR)
            + (dateTime.time().minute() * SECONDS_IN_MINUTE)
            + dateTime.time().second();
}

bool MainWindow::okToContinue()
{
    if (this->isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Save"),
                                     tr("There are unsaved changes. \n"
                                        "Do you want to save them?"),
                                     QMessageBox::StandardButton::Yes
                                     | QMessageBox::StandardButton::No,
                                     QMessageBox::StandardButton::No);

        if (r == QMessageBox::StandardButton::Yes) {
            this->save();
            return true;
        } else {
            return false;
        }
    }

    return true;
}

bool MainWindow::addToPreset(PresetItem presetItem)
{
    QGridLayout *newLayout = new QGridLayout(this);
    newLayout->addWidget(new PresetWidget(presetItem, this));
    qDebug() << "Start";
    this->ui->presetScrollArea->setLayout(newLayout);
    qDebug() << "End";
    return true;
}

