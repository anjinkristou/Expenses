#ifndef RECORDMODEL_H
#define RECORDMODEL_H

#include <QAbstractListModel>
#include <QPointer>

class Sheet;

class RecordModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Sheet* sheet READ sheet WRITE setSheet NOTIFY sheetChanged)
public:
    enum RecordRole {
        PurposeRole = Qt::UserRole,
        TransactionDateRole,
        ServiceProviderRole,
        DescriptionRole,
        AmountRole
    };
    Q_ENUM(RecordRole)

    explicit RecordModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;


    Sheet* sheet() const;

public slots:
    void setSheet(Sheet *sheet);

signals:
    void sheetChanged(Sheet* sheet);

private:
    QPointer<Sheet> m_sheet;
};

#endif // RECORDMODEL_H
