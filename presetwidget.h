#ifndef PRESETWIDGET_H
#define PRESETWIDGET_H

#include <QWidget>

namespace Ui {
class PresetWidget;
}

class PresetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PresetWidget(QWidget *parent = nullptr);
    ~PresetWidget();

private:
    Ui::PresetWidget *ui;
};

#endif // PRESETWIDGET_H
