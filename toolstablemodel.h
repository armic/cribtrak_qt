#ifndef TOOLSTABLEMODEL_H
#define TOOLSTABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>


class ToolsTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    ToolsTableModel(QObject *parent = 0);

    void setQuery(QSqlQuery &query);

};

#endif // TOOLSTABLEMODEL_H
