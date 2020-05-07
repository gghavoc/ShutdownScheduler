#ifndef SHUTDOWNDIALOG_H
#define SHUTDOWNDIALOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class ShutdownDialog;
}

class ShutdownDialog : public QDialog
{
    Q_OBJECT

public:
    enum ShutdownType : uint32_t
    {
        Shutdown = 0,
        Restart,
        LogOut,
    };

    enum ShutdownTime : uint32_t
    {
        Now = 0,
        At,
        After,
    };


public:
    explicit ShutdownDialog(QWidget *parent = nullptr);
    ~ShutdownDialog();

Q_SIGNALS:
    void shutdownSet(QDateTime dateTime, int shutdownType, int shutdownTime, bool addToPreset = false);

private Q_SLOTS:
    void okClicked();
    void changeUi(int uiType);

private:
    Ui::ShutdownDialog *ui;
};

#endif // SHUTDOWNDIALOG_H
