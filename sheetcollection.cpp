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

void SheetCollection::addSheet(Sheet *sheet, bool persist)
{
    if(sheet){
        int index = m_sheets.size();
        beginInsert(index, index);
        m_sheets.append(sheet);
        endInsert();
        connect(sheet, &Sheet::changed, this, [index, this](){
            emit this->sheetChanged(index);
        });

        if(m_dataManager){
            int id = m_dataManager->addSheet(sheet->name()
                                    , sheet->status());
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
    m_sheets.takeAt(index)->deleteLater();
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
        m_dataManager->forEachSheet([this](int id, const QString &name, int status){
            Sheet *s = new Sheet(this);
            s->setId(id);
            s->setName(name);
            s->setStatus(status);
            addSheet(s, false);
        });
    }
}
