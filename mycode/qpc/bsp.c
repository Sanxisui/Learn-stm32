/***********************************************************
File name     : bsp.c
Author name   : lancz
Email address : chengzhang.lan@jointligthing.com
Create time   : 2023-03-23 14:37:54
***********************************************************/
#include <stdlib.h>

#include "qpc.h"
#include "safe_std.h"
/*--------------------------------------------------------------------------*/
void QF_onStartup(void)
{
    QF_consoleSetup();
}
/*..........................................................................*/
void QF_onCleanup(void)
{
    QF_consoleCleanup();
}
/*..........................................................................*/
void QF_onClockTick(void)
{
}

/*..........................................................................*/
Q_NORETURN Q_onAssert(char const *const module, int_t const loc)
{
    FPRINTF_S(stderr, "Assertion failed in %s:%d\n", module, loc);
    QF_onCleanup();
    exit(-1);
}
/*..........................................................................*/
void BSP_display(char const *msg)
{
    FPRINTF_S(stdout, "%s", msg);
}
/*..........................................................................*/
void BSP_exit(void)
{
    PRINTF_S("\n%s\n", "Bye, Bye!");
    QF_onCleanup();
    exit(0);
}
