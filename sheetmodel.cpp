#include "sheetmodel.h"

#include "sheetcollection.h"
#include "sheet.h"
#include <QtDebug>

SheetModel::SheetModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_sheetCollection(nullptr)
{

}

int SheetModel::rowCount(const QModelIndex &) const
{
    return m_sheetCollection ? m_sheetCollection->sheetCount() : 0;
}

QVariant SheetModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount() && m_sheetCollection)
        switch (role) {
            case NameRole: return m_sheetCollection->sheetAt(index.row())->name();
            case submittedDateRole: return m_sheetCollection->sheetAt(index.row())->submittedDate().toString("yyyy/MM/dd");
            case StatusRole: return m_sheetCollection->sheetAt(index.row())->status();
            case RecordCountRole: return m_sheetCollection->sheetAt(index.row())->recordCount();
            case TotalAmountRole: return m_sheetCollection->sheetAt(index.row())->totalAmount();
            default: return QVariant();
        }
    return QVariant();
}

QHash<int, QByteArray> SheetModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { NameRole, "name" },
        { submittedDateRole, "submitted_date" },
        { StatusRole, "status" },
        { RecordCountRole, "record_count" },
        { TotalAmountRole, "total_amount" }
    };
    return roles;
}

SheetCollection *SheetModel::sheetCollection() const
{
    return m_sheetCollection;
}

void SheetModel::setSheetCollection(SheetCollection *collection)
{
    if(m_sheetCollection != collection){
        beginResetModel();
        if(m_sheetCollection) m_sheetCollection->disconnect(this);
        m_sheetCollection = collection;
        if(collection){
            connect(collection, &SheetCollection::sheetChanged, this, [this](int index){
                emit this->dataChanged(this->index(index, 0), this->index(index, 0));
            });
            connect(collection, &SheetCollection::beginInsert, this, [this](int first, int last){
                emit this->beginInsertRows(QModelIndex(), first, last);
            });
            connect(collection, &SheetCollection::endInsert, this, &SheetModel::endInsertRows);
            connect(collection, &SheetCollection::beginRemove, this, [this](int first, int last){
                emit this->beginRemoveRows(QModelIndex(), first, last);
            });
            connect(collection, &SheetCollection::endRemove, this, &SheetModel::endRemoveRows);
        }
        endResetModel();
        emit sheetCollectionChanged(collection);
    }
}
