#ifndef SEARCHTABLE_H
#define SEARCHTABLE_H
#include "searchtablebase.h"

///
/// \brief The SearchTable class
/// class SearchTableBase with Headers
///
class SearchTable : public SearchTableBase
{
    Q_OBJECT
public:
    ///
    /// \brief SearchTable
    /// \param parent

    SearchTable(QObject* parent = nullptr);

    ///
    /// \brief The HeaderRoles enum
    /// roles for Headers
    ///
    enum HeaderRoles{
        DisplayHeaderRole = 101,
        EditHeaderRole = 102,

    };
    ///
    /// \brief headerData
    /// \param section (index Cell) header
    /// \param orientation Vertical or Horizontal
    /// \param role
    /// \return if(orientation) == Vertical - verticalHeaders[section];
    ///         if(orientation) == Horizontal - horizontalHeaders[section]
    ///
    Q_INVOKABLE QVariant headerData(int section,Qt::Orientation orientation ,int role = DisplayHeaderRole)const override;
    Q_INVOKABLE bool setHeaderData(int section,Qt::Orientation orientation,const QVariant&value ,int role = EditHeaderRole)override;



public slots:

    /// connect with
    ///             rowsAboutToBeInserted
    ///             columnsAboutToBeInserted
    ///             rowsAboutToBeRemoved
    ///             columnsAboutToBeRemoved
    ///
    void insertHeaderVertical(const QModelIndex& parent,int first,int last);
    void insertHeaderHorizontal(const QModelIndex& parent,int first,int last);
    void removeHeaderVertical(const QModelIndex& parent,int first,int last);
    void removeHeaderHorizontal(const QModelIndex& parent,int first,int last);

private:
    QStringList verticalHeaders;
    QStringList horizontalHeaders;

};

#endif // SEARCHTABLE_H
