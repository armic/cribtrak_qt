#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <QObject>

class CsvWriter : public QObject
{
    Q_OBJECT
public:
    explicit CsvWriter(QObject *parent = nullptr);

    QString constructLine(QVariantList list);
    void setSeparator(QChar separator);
    void setEncloser(QChar encloser);
    QChar separator();
    QChar encloser();
    QString escapeString(QString str);
signals:

public slots:

protected:
    QChar m_separator, m_encloser;
};

#endif // CSVWRITER_H
