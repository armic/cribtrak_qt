#include "csvreader.h"
#include <QDebug>

CsvReader::CsvReader(QObject *parent) : QObject(parent)
{
    m_separator = ',';
    m_encloser = '"';
}

QStringList CsvReader::parseLine(QString line)
{
    QStringList result;
    bool insideString = false;
    QString token;
    //QChar separator = ',';
    //QChar stringEncloser = '\"';
    for (int i = 0; i < line.length(); ++i)
    {
        QChar ch = line.at(i);
        if (ch == m_separator)
        {
            if (insideString)
            {
                token += ch;
            }
            else
            {
                result << token;
                //qDebug() << __FUNCTION__ << "Token:" << token;
                token = "";
            }
        }
        else if (ch == m_encloser)
        {
            if (insideString)
            {
                if (line.at(i + 1) == m_encloser)
                {
                    token += m_encloser;
                    ++i;
                }
                else
                {
                    insideString = false;
                }
            }
            else
            {
                insideString = true;
            }
        }
        else if (i == line.length() - 1)
        {
            token += ch;
            result << token;
            //qDebug() << __FUNCTION__ << "Token:" << token;
            token = "";
        }
        else
        {
            token += ch;

            // NOTE: Nasty little hack to stop sql statement from breaking.
            if (ch == '\'')
            {
                token += ch;
            }
        }

        if ((i == line.length() - 1) && (ch == m_encloser || ch == m_separator))
        {
            result << token;
        }
    }
    //qDebug() << __FUNCTION__ << result.length();
    return result;
}
