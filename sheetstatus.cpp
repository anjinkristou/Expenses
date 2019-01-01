#include "sheetstatus.h"

#include "datamanager.h"

SheetStatus::SheetStatus(QObject *parent)
    : QObject(parent)
    , m_dataManager(nullptr)
    , m_id(-1)
{
    connect(this, &SheetStatus::nameChanged, this, &SheetStatus::changed);
}

DataManager *SheetStatus::dataManager() const
{
    return m_dataManager;
}

void SheetStatus::setDataManager(DataManager *dataManager)
{
    if (m_dataManager == dataManager)
        return;

    m_dataManager = dataManager;

    updateFields();

    emit dataManagerChanged(m_dataManager);
}

void SheetStatus::setId(int id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged(m_id);
}

void SheetStatus::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;

    if(m_dataManager){
        m_dataManager->setField(tableName(), m_id, "name", m_name);
    }

    emit nameChanged(m_name);
}

void SheetStatus::updateFields()
{
    if(m_dataManager){
        QStringList fileds;
        fileds << "name";
        QVariantMap props = m_dataManager->fields(tableName(), m_id, fileds);

        m_name = props["name"].toString();
    }
}
