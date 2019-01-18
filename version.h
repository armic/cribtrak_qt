#ifndef VERSION_H
#define VERSION_H

#include <QString>


/*-------------------------------------------------------------------
 *
 *  Version 3.0.0      Released 23rd October 2017
 *
 * First release of cribtrak
 *
 *
 * Check tool in calibration message box.
 * Can enable/disable in Cabinet options.
 *
 * ------------------------------------------------------------------*/


namespace Version
{
QString getVersionString();

static const int major = 3;
static const int minor = 0;
static const int release = 0;

}
#endif // VERSION_H

