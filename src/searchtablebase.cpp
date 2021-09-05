#include "searchtablebase.h"

SearchTableBase::SearchTableBase()
{
    dataList.append(QVariantList(5));

}

QVariant SearchTableBase::data(const QModelIndex &index, int role) const
{
    if(index.isValid() || role != Qt::DisplayRole || dataList.isEmpty())
        return QVariant();
    if(dataList[0].isEmpty())
        return QVariant();
    int row = index.row();
    int column = index.column();
    if(row > dataList.size() - 1 || column > dataList[0].size())
        return QVariant();
    return dataList[row][column];
}

QHash<int, QByteArray> SearchTableBase::roleNames() const
{
    QHash<int, QByteArray> roles
    {{Qt::DisplayRole, "display"},
        {Qt::EditRole,"edit"}};
    return roles;
}

Qt::ItemFlags SearchTableBase::flags(const QModelIndex &parent) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsEditable | QAbstractTableModel::flags(parent);
}

int SearchTableBase::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if(this->isEmpty())
        return 0;
    return dataList.size();
}

int SearchTableBase::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if(this->isEmpty())
        return 0;

    return dataList[0].size();
}

bool SearchTableBase::isEmpty() const
{
    if(dataList.isEmpty())
        return true;
    if(dataList[0].isEmpty())
        return true;
    return false;
}
