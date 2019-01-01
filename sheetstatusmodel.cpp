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

    beginResetModel();
    if(m_sheetStatusCollection) m_sheetStatusCollection->disconnect(this);

    m_sheetStatusCollection = sheetStatusCollection;
    if(sheetStatusCollection){
        connect(sheetStatusCollection, &SheetStatusCollection::sheetStatusChanged, this, [this](int index){
            emit this->dataChanged(this->index(index, 0), this->index(index, 0));
        });
        connect(sheetStatusCollection, &SheetStatusCollection::beginInsert, this, [this](int first, int last){
            emit this->beginInsertRows(QModelIndex(), first, last);
        });
        connect(sheetStatusCollection, &SheetStatusCollection::endInsert, this, &SheetStatusModel::endInsertRows);
        connect(sheetStatusCollection, &SheetStatusCollection::beginRemove, this, [this](int first, int last){
            emit this->beginRemoveRows(QModelIndex(), first, last);
        });
        connect(sheetStatusCollection, &SheetStatusCollection::endRemove, this, &SheetStatusModel::endRemoveRows);
        connect(sheetStatusCollection, &SheetStatusCollection::beginReset, this, &SheetStatusModel::beginResetModel);
        connect(sheetStatusCollection, &SheetStatusCollection::endReset, this, &SheetStatusModel::endResetModel);
    }
    endResetModel();
    emit sheetStatusCollectionChanged(m_sheetStatusCollection);
}
