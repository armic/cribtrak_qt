#include "toolstablemodel.h"

ToolsTableModel::ToolsTableModel(QObject *parent): QSqlTableModel(parent)
{


}


void ToolsTableModel::setQuery(QSqlQuery &query)
{
    QSqlTableModel::setQuery(query);
}


