/***********************************************************
File name : test_qhsm.h
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-28 14:12:22
Description : 层次状态机的学习
**********************************************************/
#ifndef _TEST_QHSM_H_
#define _TEST_QHSM_H_

#include "qpc.h"

#ifdef __cplusplus
extern "C" {
#endif
enum QHsmTstSignals {
    A_SIG = Q_USER_SIG,
    B_SIG,
    C_SIG,

    D_SIG,
    E_SIG,
    F_SIG,
    G_SIG,
    H_SIG,
    I_SIG,
    J_SIG,
    K_SIG,
    L_SIG,
    M_SIG,
    N_SIG,
    O_SIG,
    P_SIG,
    Q_SIG,
    R_SIG,
    S_SIG,
    T_SIG,
    U_SIG,
    TERMINATE_SIG,
    IGNORE_SIG,
    MAX_SIG

};

extern QHsm *const the_sm; /* opaque pointer to the test SM */

/*$declare${HSMs::QHsmTst_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${HSMs::QHsmTst_ctor} ....................................................*/
void QHsmTst_ctor(void);
/*$enddecl${HSMs::QHsmTst_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/* BSP functions to dispaly a message and exit */
void BSP_display(char const *msg);
void BSP_exit(void);
#ifdef __cplusplus
}
#endif
#endif