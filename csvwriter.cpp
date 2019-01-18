#include "csvwriter.h"

#include <QVariant>
#include <QVariantList>
#include <QDate>

CsvWriter::CsvWriter(QObject *parent) : QObject(parent)
{
    m_separator = ',';
    m_encloser = '"';
}

QString CsvWriter::escapeString(QString str)
{
    QString result;
    for (int i = 0; i < str.length(); ++i)
    {
        if (str.at(i) == m_encloser)
        {
            result += m_encloser;
        }
        result += str.at(i);
    }
    return result;
}

QString CsvWriter::constructLine(QVariantList list)
{
    QString result;
    for (int i = 0; i < list.length(); ++i)
    {
        QVariant item = list.at(i);
        switch (item.userType())
        {
        case QMetaType::Int:
            result += item.toString();
            break;
        case QMetaType::QString:
            result += QString(m_encloser) + escapeString(item.toString()) + QString(m_encloser);
            break;
        case QMetaType::QDate:
            result += QString(m_encloser) + item.toDate().toString(Qt::ISODate) + QString(m_encloser);
            break;
        }


        if (i < list.length() - 1)
        {
            result += m_separator;
        }
    }
    return result;
}

void CsvWriter::setSeparator(QChar separator)
{
    m_separator = separator;
}

void CsvWriter::setEncloser(QChar encloser)
{
    m_encloser = encloser;
}

QChar CsvWriter::separator()
{
    return m_separator;
}

QChar CsvWriter::encloser()
{
    return m_encloser;
}
