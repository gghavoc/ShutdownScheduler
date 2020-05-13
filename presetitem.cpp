#include <QDateTime>
#include <QDebug>

#include "presetitem.h"

PresetItem::PresetItem(QDateTime dateTime,
                       ShutdownScheduler::Type shutdownType,
                       ShutdownScheduler::Timing shutdownTiming)
    : shutdownDateTime(dateTime)
    , shutdownType(shutdownType)
    , shutdownTiming(shutdownTiming)
{
}

PresetItem::~PresetItem()
{
}

void PresetItem::setDateTime(QDateTime dateTime)
{
    this->shutdownDateTime = dateTime;
}

void PresetItem::setShutdownType(ShutdownScheduler::Type type)
{
    this->shutdownType = type;
}

void PresetItem::setShutdownTiming(ShutdownScheduler::Timing timing)
{
    this->shutdownTiming = timing;
}

int64_t PresetItem::toRelativeSeconds() const
{
    switch (this->shutdownTiming) {
    case ShutdownScheduler::Timing::Now:
        return 0;
        break;
    case ShutdownScheduler::Timing::At:
        return PresetItem::dateTimeToSeconds(this->shutdownDateTime)
                - PresetItem::dateTimeToSeconds(QDateTime::currentDateTime());
        break;
    case ShutdownScheduler::Timing::After:
        return PresetItem::dateTimeToSeconds(this->shutdownDateTime);
        break;
    default:
        return 0;
        break;
    }
}

bool PresetItem::isValid() const
{
    bool checkValid = true;

    if (this->shutdownDateTime.isNull()) {
        qDebug() << "Null QDateTime found";
        checkValid = false;
    }

    if (this->shutdownType == ShutdownScheduler::Type::Invalid) {
        qDebug() << "Invalid ShutdownType found";
        checkValid = false;
    }

    if (this->shutdownTiming == ShutdownScheduler::Timing::Invalid) {
        qDebug() << "Invalid ShutdownTiming found";
        checkValid = false;
    }

    return checkValid;
}

int64_t PresetItem::dateTimeToSeconds(QDateTime dateTime)
{
    return  (dateTime.date().year() * (dateTime.date().daysInYear() * SECONDS_IN_DAY))
            + (dateTime.date().month() * (dateTime.date().daysInMonth() *SECONDS_IN_DAY))
            + (dateTime.date().day() * SECONDS_IN_DAY)
            + (dateTime.time().hour() * SECONDS_IN_HOUR)
            + (dateTime.time().minute() * SECONDS_IN_MINUTE)
            + dateTime.time().second();
}
