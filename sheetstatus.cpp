#include "sheetstatus.h"

SheetStatus::SheetStatus(QObject *parent)
    : QObject(parent)
    , m_dataManager(nullptr)
    , m_id(-1)
{

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
    emit nameChanged(m_name);
}
