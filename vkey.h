#ifndef VKEY_H
#define VKEY_H

#include <QToolButton>

// Virtual Key class.
class VKey : public QToolButton
{
    Q_OBJECT
public:
    explicit VKey(const QString &text, QWidget *parent = 0);
};

#endif // VKEY_H
