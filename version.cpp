#include "version.h"

namespace Version
{

QString getVersionString()
{
    QString str  = QString("Version %1.%2.%3 ").arg(major).arg(minor).arg(release);
    return str;
}

}
