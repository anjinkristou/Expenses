#ifndef SHEETSTATUSMODEL_H
#define SHEETSTATUSMODEL_H

#include <QAbstractListModel>
#include <QPointer>

class SheetStatusCollection;

class SheetStatusModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SheetStatusCollection* sheetStatusCollection READ sheetStatusCollection WRITE setSheetStatusCollection NOTIFY sheetStatusCollectionChanged)

public:
    enum SheetSatatusRole {
        NameRole = Qt::UserRole,
        IdRole,
    };
    Q_ENUM(SheetSatatusRole)
    explicit SheetStatusModel(QObject *parent = nullptr);

    SheetStatusCollection* sheetStatusCollection() const;

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void sheetStatusCollectionChanged(SheetStatusCollection* sheetStatusCollection);

public slots:
    void setSheetStatusCollection(SheetStatusCollection* sheetStatusCollection);

private:
    QPointer<SheetStatusCollection> m_sheetStatusCollection;
};

#endif // SHEETSTATUSMODEL_H
