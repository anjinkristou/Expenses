#include "sheet.h"

#include "sheetstatuses.h"
#include "record.h"

Sheet::Sheet(QObject *parent)
    : QObject(parent)
    , m_id(0)
    , m_name("No name")
    , m_status(SheetStatuses::PendingStatus)
    , m_submittedDate(QDate::currentDate())
{
        connect(this, &Sheet::nameChanged, this, &Sheet::changed);
    connect(this, &Sheet::statusChanged, this, &Sheet::changed);
    connect(this, &Sheet::submittedDateChanged, this, &Sheet::changed);

}

qreal Sheet::totalAmount() const
{
    return std::accumulate(m_records.begin(), m_records.end(), 0.0, [](qreal total, Record *record){
        return total + record->amount();
    });
}

Record *Sheet::recordAt(int index) const
{
    return m_records.at(index);
}



void Sheet::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Sheet::setStatus(int status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(m_status);
}

void Sheet::setSubmittedDate(const QDate &date)
{
    if (m_submittedDate == date)
        return;

    m_submittedDate = date;
    emit submittedDateChanged(m_submittedDate);
}

void Sheet::addRecord(Record *record)
{
    m_records.append(record);
}

void Sheet::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}
