#ifndef SHUTDOWNDIALOG_H
#define SHUTDOWNDIALOG_H

#include <QDialog>
#include <QDateTime>

#include "shutdownscheduler.h"
#include "presetitem.h"

namespace Ui {
class ShutdownDialog;
}

class ShutdownDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShutdownDialog(QWidget *parent = nullptr);
    ~ShutdownDialog();

public:
    virtual void showEvent(QShowEvent * event) override;

Q_SIGNALS:
    void shutdownSet(PresetItem presetItem, bool addToPreset = false);

private Q_SLOTS:
    void okClicked();
    void changeUi(int uiType);

private:
    Ui::ShutdownDialog *ui;
};

#endif // SHUTDOWNDIALOG_H
