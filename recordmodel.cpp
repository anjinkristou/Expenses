#include "recordmodel.h"

#include "sheet.h"
#include "record.h"

RecordModel::RecordModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_sheet(nullptr)
{

}

int RecordModel::rowCount(const QModelIndex &) const
{
    return m_sheet ? m_sheet->recordCount() : 0;
}

QVariant RecordModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount() && m_sheet)
        switch (role) {
            case PurposeRole: return m_sheet->recordAt(index.row())->purpose();
            case TransactionDateRole: return m_sheet->recordAt(index.row())->transactionDate().toString("yyyy/MM/dd");
            case ServiceProviderRole: return m_sheet->recordAt(index.row())->serviceProvider();
            case DescriptionRole: return m_sheet->recordAt(index.row())->description();
            case AmountRole: return m_sheet->recordAt(index.row())->amount();
            default: return QVariant();
        }
    return QVariant();
}

QHash<int, QByteArray> RecordModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { PurposeRole, "purpose" },
        { TransactionDateRole, "transaction_date" },
        { ServiceProviderRole, "service_provider" },
        { DescriptionRole, "description" },
        { AmountRole, "amount" }
    };
    return roles;
}

void RecordModel::setSheet(Sheet *sheet)
{
    if(m_sheet != sheet){
        beginResetModel();
        if(m_sheet) m_sheet->disconnect(this);
        m_sheet = sheet;
        if(m_sheet){
            connect(sheet, &Sheet::recordChanged, this, [this](int index){
                emit this->dataChanged(this->index(index, 0), this->index(index, 0));
            });
            connect(sheet, &Sheet::beginInsert, this, [this](int first, int last){
                emit this->beginInsertRows(QModelIndex(), first, last);
            });
            connect(sheet, &Sheet::endInsert, this, &RecordModel::endInsertRows);
            connect(sheet, &Sheet::beginRemove, this, [this](int first, int last){
                emit this->beginRemoveRows(QModelIndex(), first, last);
            });
            connect(sheet, &Sheet::endRemove, this, &RecordModel::endRemoveRows);
            connect(sheet, &Sheet::beginReset, this, &RecordModel::beginResetModel);
            connect(sheet, &Sheet::endReset, this, &RecordModel::endResetModel);
        }
        endResetModel();
        emit sheetChanged(sheet);
    }
}

Sheet *RecordModel::sheet() const
{
    return m_sheet;
}
