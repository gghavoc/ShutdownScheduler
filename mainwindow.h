#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

#include "shutdownscheduler.h"
#include "presetitem.h"

class QAction;
class ShutdownDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
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
    void scheduleShutdown(PresetItem presetItem,
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
    void createModalDialog();
    void shutdownNow(std::string flag = SHUTDOWN);
    void shutdownAt(QDateTime dateTime, std::string flag = SHUTDOWN);
    void shutdownAfter(uint32_t seconds, std::string flag = SHUTDOWN);
    void extendUi();
    void shrinkUi();
    uint64_t dateTimeToSeconds(QDateTime dateTime);
    bool okToContinue();
    bool addToPreset(PresetItem presetItem);


private: // date members
    // strings
    QString currentFile;

    // ui
    Ui::MainWindow *ui;

    // dialogs
    ShutdownDialog *shutdownDialog;

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
