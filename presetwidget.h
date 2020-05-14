#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QWidget>
#include <QTimer>

#include "presetitem.h"

namespace Ui {
class PresetWidget;
}

class PresetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PresetWidget(PresetItem presetItem, QWidget *parent = nullptr);
    ~PresetWidget();

private:
    Ui::PresetWidget *ui;

    // preset item
    PresetItem presetItem;

    // timer
    QTimer timer;

};
#endif // PRESETWIDGET_H
