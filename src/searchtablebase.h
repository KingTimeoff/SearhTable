#ifndef SEARCHTABLEBASE_H
#define SEARCHTABLEBASE_H

#include <QObject>
#include <QAbstractTableModel>
#include <QVariantList>

/*
 * SearchTableBase - the class that manages the qml table
*/

class SearchTableBase : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QObject* selectItem READ getSelectItem WRITE setSelectItem RESET resetSelectItem NOTIFY selectItemChanged)
public:

    SearchTableBase(QObject* parent = nullptr);

    ///
    /// \brief data
    /// \param index row and column table
    /// \param role The roles are used by the view to indicate to the model
    /// \return dataList[row][column];
    ///
    QVariant data(const QModelIndex & index,int role = Qt::DisplayRole)const override;
    ///
    /// \brief setData set data to QT (C++) table (dataList)
    /// \param index row and column table
    /// \param value set to datalist
    /// \param role The roles are used by the view to indicate to the model
    /// \return true -
    ///
    bool setData(const QModelIndex& index,const QVariant& value,int role = Qt::EditRole)override;

    ///
    /// \brief roleNames Stored in roles
    ///        The roles are used by the view to indicate to the model
    /// \return roles
    ///
    QHash<int,QByteArray> roleNames() const override;

    ///A combination of flags that enables the item
    /// (ItemIsEnabled) and allows it to be selected (ItemIsSelectable)
    /// \brief flags
    /// \param parent
    /// \returnreturn Qt::ItemIsEnabled | Qt::ItemIsEditable |Qt::ItemIsSelectable| QAbstractTableModel::flags(parent);
    ///
    ///
    Qt::ItemFlags flags(const QModelIndex& parent = QModelIndex())const override;

    QModelIndex index(int row,int column, const QModelIndex& parent = QModelIndex())const override;


    int rowCount(const QModelIndex& parent = QModelIndex())const override;
    int columnCount(const QModelIndex& parent = QModelIndex())const override;

    Q_INVOKABLE bool appendRows(int count);
    Q_INVOKABLE bool insertRows(int row,int count,const QModelIndex& parent = QModelIndex())override;

    Q_INVOKABLE bool removeRows(int row,int count,const QModelIndex& parent = QModelIndex())override;
    Q_INVOKABLE bool removeLastRow();
    Q_INVOKABLE bool removeFirstRow();

    Q_INVOKABLE bool appendColumns(int count);
    Q_INVOKABLE bool insertColumns(int column,int count,const QModelIndex& parent = QModelIndex())override;

    Q_INVOKABLE bool removeColumns(int column,int count,const QModelIndex& parent = QModelIndex())override;
    Q_INVOKABLE bool removeFirstColumn();
    Q_INVOKABLE bool removeLastColumn();

    bool clearRows(int row,int count);

    ///
    /// \brief isEmpty
    /// \return true - dataList is Empty, else false
    ///
    bool isEmpty()const;

    QObject* getSelectItem() const;
    void setSelectItem(QObject*newSelectItem);
    void resetSelectItem();

signals:
    void selectItemChanged();

protected:
    QHash<int,QByteArray> roles;
    ///
    /// \brief reserveCapasity
    /// reserve size dataList
    ///
    const uint8_t reserveCapasity = 5;
private:
    ///
    /// \brief selectItem
    /// object which is selected in qml
    ///
    QObject* selectItem;
    QList<QVariantList> dataList;

};

#endif // SEARCHTABLEBASE_H
