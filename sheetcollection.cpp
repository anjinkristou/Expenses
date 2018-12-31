#include "sheetcollection.h"

#include "sheet.h"
#include "datamanager.h"

SheetCollection::SheetCollection(DataManager *dataManager, QObject *parent)
    : QObject(parent)
    , m_dataManager(dataManager)
{
    if(m_dataManager) {
        loadSheets();
    }
}

void SheetCollection::addSheet(Sheet *sheet)
{
    if(sheet){
        int index = m_sheets.size();
        beginInsert(index, index);
        m_sheets.append(sheet);
        endInsert();
        connect(sheet, &Sheet::changed, this, [index, this](){
            emit this->sheetChanged(index);
        });

        if(sheet->id() < 0 && m_dataManager){
            int id = m_dataManager->add("sheets");
            sheet->setId(id);
            sheet->setDataManager(m_dataManager);
        }
    }
}

int SheetCollection::sheetCount() const
{
    return m_sheets.size();
}

Sheet *SheetCollection::sheetAt(int index) const
{
    return m_sheets.at(index);
}

Sheet *SheetCollection::addSheet()
{
    Sheet *s = new Sheet(this);
    addSheet(s);
    return s;
}

DataManager *SheetCollection::dataManager() const
{
    return m_dataManager;
}

void SheetCollection::removeAt(int index)
{
    beginRemove(index, index);
    Sheet *sheet = m_sheets.takeAt(index);
    if(m_dataManager){
        m_dataManager->remove("sheets", sheet->id());
    }
    sheet->deleteLater();
    endRemove();
}

void SheetCollection::setDataManager(DataManager *dataManager)
{
    if (m_dataManager == dataManager)
        return;

    emit beginReset();
    m_dataManager = dataManager;

    qDeleteAll(m_sheets);
    m_sheets.clear();
    endReset();

    loadSheets();

    emit dataManagerChanged(m_dataManager);
}

void SheetCollection::loadSheets()
{
    if(m_dataManager){
        DataManager *manager = m_dataManager;
        m_dataManager->forEach("sheets", [this, manager](int id){
            Sheet *s = new Sheet(this);
            s->setId(id);
            s->setDataManager(manager);
            addSheet(s);
        });
    }
}
