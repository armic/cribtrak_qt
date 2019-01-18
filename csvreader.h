#ifndef CSVREADER_H
#define CSVREADER_H

#include <QObject>

class CsvReader : public QObject
{
    Q_OBJECT
public:
    explicit CsvReader(QObject *parent = nullptr);

    QStringList parseLine(QString line);
    void setSeparator(QChar separator);
    void setEncloser(QChar encloser);
    QChar separator();
    QChar encloser();

signals:

public slots:

protected:
    QChar m_separator, m_encloser;
};

#endif // CSVREADER_H
