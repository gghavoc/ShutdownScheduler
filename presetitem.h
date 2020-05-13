#ifndef PRESETITEM_H
#define PRESETITEM_H

#include <QDateTime>

#include "shutdownscheduler.h"

class PresetItem
{
public:


public:
    PresetItem(QDateTime getDateTime = QDateTime(),
               ShutdownScheduler::Type shutdownType = ShutdownScheduler::Type::Invalid,
               ShutdownScheduler::Timing shutdownTiming = ShutdownScheduler::Timing::Invalid);
    ~PresetItem();

public:
    void setDateTime(QDateTime getDateTime);
    void setShutdownType(ShutdownScheduler::Type type);
    void setShutdownTiming(ShutdownScheduler::Timing timing);

    QDateTime &dateTime() { return this->shutdownDateTime; }
    QTime time() const { return this->shutdownDateTime.time(); }
    QDate date() const { return this->shutdownDateTime.date(); }
    ShutdownScheduler::Type type() const { return this->shutdownType; }
    ShutdownScheduler::Timing timing() const { return this->shutdownTiming; }
    int64_t toRelativeSeconds() const;
    int64_t toSecsSinceEpoch() const { return this->shutdownDateTime.toSecsSinceEpoch(); }
    bool isValid() const;

private:
    static int64_t dateTimeToSeconds(QDateTime shutdownDateTime);

private:
    QDateTime shutdownDateTime;
    ShutdownScheduler::Type shutdownType;
    ShutdownScheduler::Timing shutdownTiming;
};

#endif // PRESETITEM_H
