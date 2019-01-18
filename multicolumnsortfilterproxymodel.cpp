#include "multicolumnsortfilterproxymodel.h"
#include <QDebug>
#include <QBrush>

MultiColumnSortFilterProxyModel::MultiColumnSortFilterProxyModel(QObject *parent)
{

}

bool MultiColumnSortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
//    QModelIndex index0 = sourceModel()->index(sourceRow, 2, sourceParent);
//    QModelIndex index1 = sourceModel()->index(sourceRow, 3, sourceParent);
//    QModelIndex index2 = sourceModel()->index(sourceRow, 4, sourceParent);

    if (filterColumns.isEmpty())
    {
        return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
    }

    for (int i = 0; i < filterColumns.size(); ++i)
    {
        QModelIndex idx = sourceModel()->index(sourceRow, filterColumns.at(i), sourceParent);
        if (sourceModel()->data(idx).toString().contains(filterRegExp()))
        {
            return true;
        }
    }
    return false;

//    return (sourceModel()->data(index0).toString().contains(filterRegExp())
//            || sourceModel()->data(index1).toString().contains(filterRegExp()))
//            || sourceModel()->data(index2).toString().contains(filterRegExp());
}


QVariant MultiColumnSortFilterProxyModel::data ( const QModelIndex & index, int role ) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    QModelIndex sourceIndex = mapToSource( index );

    QString cellString = sourceModel()->data(sourceIndex).toString();
//    if (role == Qt::BackgroundRole && cellString.contains(filterRegExp()) && !filterRegExp().isEmpty() && (sourceIndex.column() == 2 || sourceIndex.column() == 3 || sourceIndex.column() == 4))
    if (role == Qt::BackgroundRole && cellString.contains(filterRegExp()) && !filterRegExp().isEmpty() && (filterColumns.contains(sourceIndex.column())))
    {
        //QBrush redBackground(Qt::yellow);
        //return redBackground;
        return QBrush(Qt::yellow);
    }
    else
    {
        return QSortFilterProxyModel::data( index, role );
    }
}

void MultiColumnSortFilterProxyModel::setFilterKeyColumns(QList<int> columns)
{
    filterColumns = columns;
}
