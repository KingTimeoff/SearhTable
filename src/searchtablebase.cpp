#include "searchtablebase.h"

SearchTableBase::SearchTableBase(QObject* parent):
    QAbstractTableModel(parent),selectItem(nullptr)
{

    roles.insert(Qt::DisplayRole, "display");
    roles.insert(Qt::EditRole,"edit");
    dataList.reserve(reserveCapasity);
    dataList.append(QVariantList(5));

#ifdef _DEBUG
    dataList.append(QVariantList(5));
    dataList.append(QVariantList(5));
    dataList.append(QVariantList(5));
    for(int i = 0; i < dataList.size();i++)
    {
        dataList[i].reserve(reserveCapasity);
        for(int j = 0; j < dataList[0].size(); j++)
        {
            dataList[i][j] = QString("Test");
        }
    }
#endif
}

QVariant SearchTableBase::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole || isEmpty())
        return QVariant();

    int row = index.row();
    int column = index.column();
    if(row > rowCount() - 1 || column > columnCount())
        return QVariant();
    return dataList[row][column];
}

bool SearchTableBase::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid() || isEmpty() || role != Qt::EditRole || !value.isValid())
        return false;
    if(index.row() > rowCount()|| index.column() > columnCount())
        return false;
    dataList[index.row()][index.column()] = value;
    emit dataChanged(index,index,{role});
    return true;
}

QHash<int, QByteArray> SearchTableBase::roleNames() const
{
    return roles;
}

Qt::ItemFlags SearchTableBase::flags(const QModelIndex &parent) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsEditable |Qt::ItemIsSelectable| QAbstractTableModel::flags(parent);
}

QModelIndex SearchTableBase::index(int row, int column, const QModelIndex &parent) const
{
    return QAbstractTableModel::index(row,column,parent);
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

bool SearchTableBase::appendRows(int count)
{
    if(count < 1)
        count = 1;
    int begin = rowCount() - 1;
    int end = rowCount() + count - 1;
    if(rowCount() == dataList.capacity())
    {
        dataList.reserve(reserveCapasity);
    }
    beginInsertRows(QModelIndex(),begin,end);
    do{
        dataList.emplace_back(QVariantList(columnCount()));
        begin++;
    }
    while(begin < end);
    clearRows(rowCount() - count,count);
    endInsertRows();
    return true;
}

bool SearchTableBase::insertRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 || row >= rowCount() || count < 1)
        return false;
    int end = row + count;
    beginInsertRows(parent,row,end);

    if(rowCount() == dataList.capacity())
    {

        dataList.reserve(reserveCapasity);
    }
    QList<QVariantList>::ConstIterator iter = &dataList[row];

    do{
        dataList.insert(iter,QVariantList(columnCount()));
        row++;
    }
    while(row < end);

    clearRows(row,count);
    endInsertRows();
    return true;
}

bool SearchTableBase::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0 || row >= rowCount() || count < 1 || row + count > rowCount() - 1)
        return false;

    int end = row + count;
    beginRemoveRows(parent,row,end);

    dataList.remove(row,row + end);

    endRemoveRows();
    return true;
}

bool SearchTableBase::removeFirstRow()
{
    if(rowCount() <= 1)
        return false;
    beginRemoveRows(QModelIndex(),0,0);
    dataList.removeFirst();
    endRemoveRows();
    return true;
}

bool SearchTableBase::removeLastRow()
{
    if(rowCount() <= 1)
        return false;
    beginRemoveRows(QModelIndex(),rowCount() - 1,rowCount() - 1);
    dataList.removeLast();
    endRemoveRows();
    return true;
}

bool SearchTableBase::appendColumns(int count)
{
    if(count < 1)
        count = 1;

    int temp = columnCount() - 1;
    int begin = temp;
    int end = columnCount() + count - 1;
    if(columnCount() == dataList[0].capacity())
    {
        for(int i = 0; i < dataList.size();i++)
        {
            dataList[i].reserve(reserveCapasity);
        }
    }
    beginInsertColumns(QModelIndex(),begin,end);
    for(auto it = dataList.begin(); it < dataList.end();it++)
    {
        do
        {
            (*it).emplace_back(QString(""));
            begin++;
        }
        while(begin < end);
        begin = temp;
    }
    endInsertColumns();

    return true;
}

bool SearchTableBase::insertColumns(int column, int count, const QModelIndex &parent)
{
    if(column < 0 || column >= columnCount() || count < 1)
        return false;
    int begin = column;
    int end = column + count ;

    beginInsertColumns(parent,begin,end);

    if(columnCount() == dataList[0].capacity())
    {
        for(int i = 0; i < dataList.size();i++)
        {
            dataList[i].reserve(reserveCapasity);
        }
    }

    for(auto it = dataList.begin(); it < dataList.end();it++)
    {
        do{
            (*it).insert(column,QString(""));
            begin++;
        }
        while(begin < end);
        begin = column;
    }

    endInsertColumns();
    return true;

}

bool SearchTableBase::removeColumns(int column, int count, const QModelIndex &parent)
{
    if(column < 0 || column >= columnCount() || count < 1 || column + count > columnCount() - 1 )
        return false;
    int begin = column;
    int end = column + count;
    beginRemoveColumns(parent,begin,end);

    for(auto it = dataList.begin(); it < dataList.end();it++)
    {
        (*it).remove(begin,end);
    }
    endRemoveColumns();
    return true;
}

bool SearchTableBase::removeFirstColumn()
{
    if(columnCount() <= 1)
        return false;
    beginRemoveColumns(QModelIndex(),0,0);
    for(auto it = dataList.begin(); it < dataList.end();it++)
    {
        (*it).removeFirst();
    }
    endRemoveColumns();

    return true;

}

bool SearchTableBase::removeLastColumn()
{
    if(columnCount() <= 1)
        return false;
    beginRemoveColumns(QModelIndex(),columnCount() - 1,columnCount() - 1);
    for(auto it = dataList.begin(); it < dataList.end();it++)
    {
        (*it).removeLast();
    }
    endRemoveColumns();
    return true;
}



bool SearchTableBase::clearRows(int row, int count)
{
    if(row < 0 || row >= dataList.size() || count < 1)
        return false;

    int end = row + count - 1;

    do
    {
        for(int i = 0; i < columnCount();i++)
        {
            dataList[row][i] = "";
        }
        row++;
    }while(row <end);

    return true;
}

bool SearchTableBase::isEmpty() const
{
    return dataList[0].isEmpty() || dataList.isEmpty();
}

QObject* SearchTableBase::getSelectItem() const
{
    return selectItem == nullptr ? nullptr : selectItem;
}

void SearchTableBase::setSelectItem(QObject* newSelectItem)
{
    if (selectItem == newSelectItem)
        return;
    selectItem = (QObject*)newSelectItem;
    emit selectItemChanged();
}

void SearchTableBase::resetSelectItem()
{
    setSelectItem({}); // TODO: Adapt to use your actual default value
}

