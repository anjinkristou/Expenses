#include "sheet.h"

#include <QVariantMap>

#include "record.h"
#include "datamanager.h"

Sheet::Sheet(QObject *parent)
    : QObject(parent)
    , m_id(-1)
    , m_name("No name")
    , m_status(-1)
    , m_submittedDate(QDate::currentDate())
    , m_dataManager(nullptr)
{
    connect(this, &Sheet::nameChanged, this, &Sheet::changed);
    connect(this, &Sheet::statusChanged, this, &Sheet::changed);
    connect(this, &Sheet::submittedDateChanged, this, &Sheet::changed);    
    connect(this, &Sheet::recordCountChanged, this, &Sheet::changed);
    connect(this, &Sheet::recordChanged, this, &Sheet::changed);
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

DataManager *Sheet::dataManager() const
{
    return m_dataManager;
}

void Sheet::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;

    if(m_dataManager){
        m_dataManager->setField(tableName(), m_id, "name", m_name);
    }
    emit nameChanged(m_name);
}

void Sheet::setStatus(int status)
{
    if (m_status == status)
        return;

    m_status = status;

    if(m_dataManager){
        m_dataManager->setField(tableName(), m_id, "status", m_status);
    }
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
    if(record){
        int index = m_records.size();
        beginInsert(index, index);
        m_records.append(record);
        endInsert();
        connect(record, &Record::changed, this, [index, this](){
            emit this->recordChanged(index);
        });

        if(record->id() < 0 && m_dataManager){
            int id = m_dataManager->add(Record::tableName());
            m_dataManager->setField(Record::tableName(), id, "sheet", m_id);
            record->setId(id);
            record->setDataManager(m_dataManager);
        }
        emit recordCountChanged(m_records.size());
    }
}

Record *Sheet::addRecord()
{
    Record *r = new Record(this);
    addRecord(r);
    return r;
}

void Sheet::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void Sheet::setDataManager(DataManager *dataManager)
{
    if (m_dataManager == dataManager)
        return;

    emit beginReset();
    m_dataManager = dataManager;

    qDeleteAll(m_records);
    m_records.clear();
    endReset();

    updateFields();

    loadRecords();

    emit dataManagerChanged(m_dataManager);
}

void Sheet::updateFields()
{
    if(m_dataManager){
        QStringList fileds;
        fileds << "name" << "status";
        QVariantMap props = m_dataManager->fields(tableName(), m_id, fileds);

        m_name = props["name"].toString();
        m_status = props["status"].toInt();
    }
}

void Sheet::loadRecords()
{
    if(m_dataManager){
        DataManager *manager = m_dataManager;
        m_dataManager->forEachDenpendent(Record::tableName(), "sheet", m_id, [this, manager](int id){
            Record *r = new Record(this);
            r->setId(id);
            r->setDataManager(manager);
            addRecord(r);
        });
    }
}
