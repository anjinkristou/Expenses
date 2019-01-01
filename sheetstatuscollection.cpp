#include "sheetstatuscollection.h"

#include "datamanager.h"
#include "sheetstatus.h"

SheetStatusCollection::SheetStatusCollection(DataManager *dataManager, QObject *parent)
    : QObject(parent)
    , m_dataManager(dataManager)
{
    if(m_dataManager) {
        loadStatus();
    }

    if (m_statuses.size() == 0){
        SheetStatus *s;
        s = new SheetStatus(this);
        addSheetStatus(s);
        s->setName("Unsubmitted");

        s = new SheetStatus(this);
        addSheetStatus(s);
        s->setName("Submitted");

        s = new SheetStatus(this);
        addSheetStatus(s);
        s->setName("Verified");

        s = new SheetStatus(this);
        addSheetStatus(s);
        s->setName("Reimbursed");
    }
}

DataManager *SheetStatusCollection::dataManager() const
{
    return m_dataManager;
}

int SheetStatusCollection::sheetStatusCount() const
{
    return m_statuses.size();
}

SheetStatus *SheetStatusCollection::sheetStatusAt(int index) const
{
    return m_statuses.at(index);
}

void SheetStatusCollection::setDataManager(DataManager *dataManager)
{
    if (m_dataManager == dataManager)
        return;

    emit beginReset();
    m_dataManager = dataManager;

    qDeleteAll(m_statuses);
    m_statuses.clear();
    endReset();

    loadStatus();

    emit dataManagerChanged(m_dataManager);
}

void SheetStatusCollection::loadStatus()
{
    if(m_dataManager){
        DataManager *manager = m_dataManager;
        m_dataManager->forEach(SheetStatus::tableName(), [this, manager](int id){
            SheetStatus *s = new SheetStatus(this);
            s->setId(id);
            s->setDataManager(manager);
            addSheetStatus(s);
        });
    }
}

void SheetStatusCollection::addSheetStatus(SheetStatus *status)
{
    if(status){
        int index = m_statuses.size();
        beginInsert(index, index);
        m_statuses.append(status);
        endInsert();
        connect(status, &SheetStatus::changed, this, [index, this](){
            emit this->sheetStatusChanged(index);
        });

        if(status->id() < 0 && m_dataManager){
            int id = m_dataManager->add(SheetStatus::tableName());
            status->setId(id);
            status->setDataManager(m_dataManager);
        }
    }
}
