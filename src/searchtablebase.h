#ifndef SEARCHTABLEBASE_H
#define SEARCHTABLEBASE_H

#include <QObject>
#include <QAbstractTableModel>
#include <QVariantList>
class SearchTableBase : public QAbstractTableModel
{
public:
    SearchTableBase();

    QVariant data(const QModelIndex & index,int role = Qt::DisplayRole)const override;

    QHash<int,QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex& parent = QModelIndex())const override;

    int rowCount(const QModelIndex& parent)const override;
    int columnCount(const QModelIndex& parent)const override;

    bool isEmpty()const;
private:
    QList<QVariantList> dataList;
};

#endif // SEARCHTABLEBASE_H
