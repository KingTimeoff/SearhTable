#include "searchtable.h"

SearchTable::SearchTable(QObject* parent): SearchTableBase(parent)
{
    for(int i = 1; i < rowCount() + 1;i++)
    {
        verticalHeaders.append(QString::number(i));
    }
    for(int i = 1; i < columnCount() + 1;i++)
    {
        horizontalHeaders.append(QString::number(i));
    }
    roles.insert(DisplayHeaderRole,"displayHeaderRole");
    roles.insert(EditHeaderRole,"editHeaderRole");

    connect(this,SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),this,SLOT(insertHeaderVertical(QModelIndex,int,int)));
    connect(this,SIGNAL(columnsAboutToBeInserted(QModelIndex,int,int)),this,SLOT(insertHeaderHorizontal(QModelIndex,int,int)));
    connect(this,SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),this,SLOT(removeHeaderVertical(QModelIndex,int,int)));
    connect(this,SIGNAL(columnsAboutToBeRemoved(QModelIndex,int,int)),this,SLOT(removeHeaderHorizontal(QModelIndex,int,int)));
}

QVariant SearchTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != DisplayHeaderRole)
        return QVariant();

    switch (orientation) {
    case Qt::Horizontal:
        if(section > horizontalHeaders.size() - 1)
            return QVariant();
        return horizontalHeaders[section];
    case Qt::Vertical:
        if(section > verticalHeaders.size() - 1)
            return QVariant();
        return verticalHeaders[section];
        break;
    default:
        return QVariant();
    }
    return QVariant();
}

bool SearchTable::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(role != EditHeaderRole || !value.isValid())
        return false;

    switch (orientation) {
    case Qt::Horizontal:
        if(section > horizontalHeaders.size() - 1)
            return false;
        horizontalHeaders[section] = value.toString();
        return true;
    case Qt::Vertical:
        if(section > verticalHeaders.size() - 1)
            return false;
        verticalHeaders[section] = value.toString();
        return true;
        break;
    default:
        return false;
    }
    return false;
}

void SearchTable::insertHeaderVertical(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)

    if(rowCount() == verticalHeaders.capacity())
    {
        verticalHeaders.reserve(reserveCapasity);
    }
    if(first < 0 || first > verticalHeaders.size() - 1)
        return;
    for(int i = last; i > first; i--)
    {
        if(first == verticalHeaders.size() - 1)
        {
            verticalHeaders.append(QString::number(verticalHeaders.size() + 1));
        }else{
            verticalHeaders.insert(first,QString::number(i));
        }
    }

}

void SearchTable::insertHeaderHorizontal(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    if(first < 0 || first > horizontalHeaders.size() - 1)
        return;
    if(columnCount() == horizontalHeaders.capacity())
    {
        horizontalHeaders.reserve(reserveCapasity);
    }
    for(int i = last; i > first; i--)
    {
        if(first == horizontalHeaders.size() - 1)
        {
            horizontalHeaders.append(QString::number(horizontalHeaders.size() + 1));
        }else{
            horizontalHeaders.insert(first,QString::number(i));
        }
    }

}

void SearchTable::removeHeaderVertical(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    if(first < 0 || first > verticalHeaders.size() - 1 ||  verticalHeaders.size() - (first - last + 1)  < 0){return;}
    verticalHeaders.remove(first, first - last + 1);


}

void SearchTable::removeHeaderHorizontal(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent)
    if(first < 0 || first > horizontalHeaders.size() - 1 || horizontalHeaders.size() - (first - last + 1)  < 0)
        return;

    horizontalHeaders.remove(first,first - last + 1);



}
