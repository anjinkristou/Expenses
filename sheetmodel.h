#ifndef SHEETMODEL_H
#define SHEETMODEL_H

#include <QAbstractListModel>
#include <QPointer>

class SheetCollection;

class SheetModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SheetCollection* sheetCollection READ sheetCollection WRITE setSheetCollection NOTIFY sheetCollectionChanged)
public:
    enum SheetRole {
        NameRole = Qt::UserRole,
        submittedDateRole,
        StatusRole,
        RecordCountRole,
        TotalAmountRole
    };
    Q_ENUM(SheetRole)

    explicit SheetModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    SheetCollection* sheetCollection() const;

public slots:
    void setSheetCollection(SheetCollection *collection);

signals:
    void sheetCollectionChanged(SheetCollection* sheetCollection);

private:
    QPointer<SheetCollection> m_sheetCollection;
};

#endif // SHEETMODEL_H
