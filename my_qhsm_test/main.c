/***********************************************************
File name : main.c
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-28 15:30:53
Description : 层次状态机的学习
***********************************************************/

#include "test_qhsm.h"
#include "qpc.h"

#include "safe_std.h" /* portable "safe" <stdio.h>/<string.h> facilities */
#include <stdlib.h>

Q_DEFINE_THIS_FILE

static FILE *l_outFile = (FILE *)0;
static void dispatch(QSignal sig);

int main(int argc, char *argv[])
{
    QF_init();
    QF_onStartup();

    QHsmTst_ctor(); /* instantiate the QHsmTst object */

    Q_ALLEGE(QS_INIT((void *)0));
    QS_OBJ_DICTIONARY(the_sm);
    QS_SIG_DICTIONARY(A_SIG, (void *)0);
    QS_SIG_DICTIONARY(B_SIG, (void *)0);
    QS_SIG_DICTIONARY(C_SIG, (void *)0);
    QS_SIG_DICTIONARY(D_SIG, (void *)0);
    QS_SIG_DICTIONARY(E_SIG, (void *)0);
    QS_SIG_DICTIONARY(F_SIG, (void *)0);
    QS_SIG_DICTIONARY(G_SIG, (void *)0);
    QS_SIG_DICTIONARY(H_SIG, (void *)0);
    QS_SIG_DICTIONARY(I_SIG, (void *)0);
    QS_SIG_DICTIONARY(J_SIG, (void *)0);
    QS_SIG_DICTIONARY(K_SIG, (void *)0);
    QS_SIG_DICTIONARY(L_SIG, (void *)0);
    QS_SIG_DICTIONARY(M_SIG, (void *)0);
    QS_SIG_DICTIONARY(N_SIG, (void *)0);
    QS_SIG_DICTIONARY(O_SIG, (void *)0);
    QS_SIG_DICTIONARY(P_SIG, (void *)0);
    QS_SIG_DICTIONARY(Q_SIG, (void *)0);
    QS_SIG_DICTIONARY(R_SIG, (void *)0);
    QS_SIG_DICTIONARY(S_SIG, (void *)0);
    QS_SIG_DICTIONARY(T_SIG, (void *)0);
    QS_SIG_DICTIONARY(U_SIG, (void *)0);
    QS_GLB_FILTER(QS_ALL_RECORDS);
    QS_GLB_FILTER(-QS_QF_TICK);

    if (argc > 1) { /* file name provided? */
        l_outFile = fopen(argv[1], "w");
    }

    if (l_outFile == (FILE *)0) { /* interactive version? */
        l_outFile = stdout;       /* use the stdout as the output file */

        PRINTF_S("QHsmTst example, built on %s at %s,\n"
                 "QP: %s.\nPress ESC to quit...\n",
                 __DATE__, __TIME__, QP_VERSION_STR);

        QHSM_INIT(the_sm, (void *)0, 0U); /* the top-most initial tran. */

        for (;;) { /* event loop */
            QEvt e;
            int c;

            PRINTF_S("\n");
            QS_OUTPUT(); /* handle the QS output */

            c = (uint8_t)QF_consoleWaitForKey();
            PRINTF_S("%c: ", (c >= ' ') ? c : 'X');

            if ('a' <= c && c <= 'u') { /* in range? */
                e.sig = (QSignal)(c - 'a' + A_SIG);
            } else if ('A' <= c && c <= 'I') { /* in range? */
                e.sig = (QSignal)(c - 'A' + A_SIG);
            } else if (c == '\33') {   /* the ESC key? */
                e.sig = TERMINATE_SIG; /* terminate the interactive test */
            } else {
                e.sig = IGNORE_SIG;
            }

            QHSM_DISPATCH(the_sm, &e, 0U); /* dispatch the event */
        }
    } else { /* batch version */
        PRINTF_S("QHsmTst example, built on %s at %s, QP %s\n"
                 "output saved to %s\n",
                 __DATE__, __TIME__, QP_VERSION_STR,
                 argv[1]);

        FPRINTF_S(l_outFile, "QHsmTst example, QP %s\n",
                  QP_VERSION_STR);

        QHSM_INIT(the_sm, (void *)0, 0U); /* the top-most initial tran. */
        /* testing of dynamic transitions... */
        dispatch(A_SIG);
        dispatch(B_SIG);
        dispatch(C_SIG);
        dispatch(D_SIG);
        dispatch(E_SIG);
        dispatch(F_SIG);
        dispatch(I_SIG);
        dispatch(J_SIG);
        dispatch(K_SIG);
        dispatch(L_SIG);
        dispatch(M_SIG);
        dispatch(N_SIG);
        dispatch(O_SIG);
        dispatch(P_SIG);
        dispatch(Q_SIG);
        dispatch(R_SIG);
        dispatch(S_SIG);
        dispatch(T_SIG);
        dispatch(U_SIG);
        fclose(l_outFile);
    }
    QF_onCleanup();
    return 0;
}
static void dispatch(QSignal sig)
{
    QEvt e;
    Q_REQUIRE((A_SIG <= sig) && (sig <= U_SIG));
    e.sig = sig;
    FPRINTF_S(l_outFile, "\n%c:", 'A' + sig - A_SIG);
    QHSM_DISPATCH(the_sm, &e, 0U); /* dispatch the event */
    QS_OUTPUT();                   /* handle the QS output */
}