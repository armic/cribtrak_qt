#ifndef MULTICOLUMNSORTFILTERPROXYMODEL_H
#define MULTICOLUMNSORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QList>

class MultiColumnSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    explicit MultiColumnSortFilterProxyModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;

    void setFilterKeyColumns(QList<int> columns);

protected:
        bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

        QList<int> filterColumns;
};

#endif // MULTICOLUMNSORTFILTERPROXYMODEL_H
