#ifndef TRAKCORE_H
#define TRAKCORE_H

namespace Trak{

    // NOTE: DataManger doesn't always use these enums. Fix.

    // enums and constants
    enum{Issued = 0, Returned = 1 };
    enum{Unserviceable = 0, Serviceable = 1};
    enum{NotAKit = 0, AKit = 1};
    enum{Transferred = 1, NotTransferred = 0};

    enum{MinDrawerNumber = 1, MaxDrawerNumber = 10};
    enum{UserAccess = 0, AdminAccess = 1};
    enum{NonCalibratedTool = 0, CalibratedTool = 1};
    enum{ToolMissing = 1, ToolNotMissing = 0};
    enum{ToolWithdrawn = 1, ToolNotWithdrawn = 0};
    enum{ToolRemoved = 1, ToolAvaliable = 0};
    enum{Yes = 1, No = 0};

    enum{UnknownError = 1, AdminRequestExit = 2, NoIniFile = 3, NoCabinetConnection = 4, NoDatabaseConnection = 5};
}


#endif // TRAKCORE_H
