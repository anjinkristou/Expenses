#include "sheetstatusmodel.h"

#include "sheetstatuscollection.h"
#include "sheetstatus.h"

SheetStatusModel::SheetStatusModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

SheetStatusCollection *SheetStatusModel::sheetStatusCollection() const
{
    return m_sheetStatusCollection;
}

int SheetStatusModel::rowCount(const QModelIndex &) const
{
return m_sheetStatusCollection ? m_sheetStatusCollection->sheetStatusCount() : 0;
}

QVariant SheetStatusModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount() && m_sheetStatusCollection)
        switch (role) {
            case NameRole: return m_sheetStatusCollection->sheetStatusAt(index.row())->name();
            case IdRole: return m_sheetStatusCollection->sheetStatusAt(index.row())->id();
            default: return QVariant();
        }
    return QVariant();
}

QHash<int, QByteArray> SheetStatusModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { NameRole, "name" },
        { IdRole, "id" }
    };
    return roles;
}

void SheetStatusModel::setSheetStatusCollection(SheetStatusCollection *sheetStatusCollection)
{
    if (m_sheetStatusCollection == sheetStatusCollection)
        return;

    m_sheetStatusCollection = sheetStatusCollection;
    emit sheetStatusCollectionChanged(m_sheetStatusCollection);
}
