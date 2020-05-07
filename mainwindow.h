#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

#ifndef SHUTDOWN_FLAGS
#define SHUTDOWN_FLAGS
    #ifdef Q_OS_UNIX
        #define SHUTDOWN_COMMAND "shutdown"
        #define SHUTDOWN "-P"
        #define RESTART "-r"
        #define HALT "-H"
        #define CANCEL "-c"
        #define TIME "-t"
    #elif defined Q_OS_WIN
        #define SHUTDOWN_COMMAND "shutdown"
        #define SHUTDOWN "/s"
        #define RESTART "/r"
        #define HALT "/s"
        #define CANCEL "/c"
        #define TIME "/t"
    #endif // Q_OS_UNIX
#endif // SHUTDOWN_FLAGS

#ifndef TO_SECONDS
#define TO_SECONDS
    #define SECONDS_IN_YEAR 32140800
    #define SECONDS_IN_MONTH 2678400
    #define SECONDS_IN_DAY 86400
    #define SECONDS_IN_HOUR 3600
    #define SECONDS_IN_MINUTE 60
#endif

class QAction;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

Q_SIGNALS:
    void uiExtended(bool extended = true);


public Q_SLOTS:
    void changeUi(bool extended);
    void save();
    void saveAs();
    void open();
    void shutdown();
    void about();
    void aboutQt();
    void exit();

private Q_SLOTS:
    void scheduleShutdown(QDateTime dateTime,
                          int shutdownType,
                          int shutdownTime,
                          bool addToPreset = false);

public:
    void readSettings();
    void writeSettings();
    void writeFile();
    void readFile();

public: //accessor function
    bool isExtended() const { return this->showExtendedUi; }

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private:
    void createAction();
    void createStatusBar();
    void createMenu();
    void createContextMenu();
    void createConnection();
    void shutdownNow(std::string flag = SHUTDOWN);
    void shutdownAt(QDateTime dateTime, std::string flag = SHUTDOWN);
    void shutdownAfter(uint32_t seconds, std::string flag = SHUTDOWN);
    void extendUi();
    void shrinkUi();
    uint64_t dateTimeToSeconds(QDateTime dateTime);

private: // date members
    Ui::MainWindow *ui;

    // actions
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *showExtendedUiAction;
    QAction *shutdownAction;
    QAction *exitAction;

    // checkables
    bool showExtendedUi;
};
#endif // MAINWINDOW_H
