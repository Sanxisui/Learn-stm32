/***********************************************************
File name : my_qhsm_test.c
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-27 09:30:23
Description : 层次状态机的学习
***********************************************************/

#include "test_qhsm.h"
#include "qep.h"
/*${HSMs::QHsmTst} .........................................................*/
typedef struct {
    /* protected: */
    QHsm super;

    /* private: */
    uint8_t foo;
} QHsmTst;

/* protected: */
static QState QHsmTst_initial(QHsmTst *const me, void const *const par);
static QState QHsmTst_s0(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s1(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s11(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s111(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s112(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s1121(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s2(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s22(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s222(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s3(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s33(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s334(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s333(QHsmTst *const me, QEvt const *const e);
static QState QHsmTst_s3333(QHsmTst *const me, QEvt const *const e);
/*$enddecl${HSMs::QHsmTst} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

static QHsmTst l_sm; /* the only instance of the QHsmTst class */

/* global-scope definitions ---------------------------------------*/
QHsm *const the_sm = &l_sm.super; /* the opaque pointer */

/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 700U) || (QP_VERSION != ((QP_RELEASE ^ 4294967295U) % 0x3E8U))
#error qpc version 7.0.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*$define${HSMs::QHsmTst_ctor} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${HSMs::QHsmTst_ctor} ....................................................*/
void QHsmTst_ctor(void)
{
    QHsmTst *me = &l_sm;
    QHsm_ctor(&me->super, Q_STATE_CAST(&QHsmTst_initial));
}
/*$enddef${HSMs::QHsmTst_ctor} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$define${HSMs::QHsmTst} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/

/*${HSMs::QHsmTst} .........................................................*/

/*${HSMs::QHsmTst::SM} .....................................................*/
static QState QHsmTst_initial(QHsmTst *const me, void const *const par)
{
    /*${HSMs::QHsmTst::SM::initial} */
    (void)par; /* unused parameter */
    me->foo = 0U;
    BSP_display("top-INIT;");

    QS_FUN_DICTIONARY(&QHsmTst_s0);
    QS_FUN_DICTIONARY(&QHsmTst_s1);
    QS_FUN_DICTIONARY(&QHsmTst_s11);
    QS_FUN_DICTIONARY(&QHsmTst_s111);
    QS_FUN_DICTIONARY(&QHsmTst_s112);
    QS_FUN_DICTIONARY(&QHsmTst_s1121);
    QS_FUN_DICTIONARY(&QHsmTst_s2);
    QS_FUN_DICTIONARY(&QHsmTst_s22);
    QS_FUN_DICTIONARY(&QHsmTst_s222);
    QS_FUN_DICTIONARY(&QHsmTst_s3);
    QS_FUN_DICTIONARY(&QHsmTst_s33);
    QS_FUN_DICTIONARY(&QHsmTst_s334);
    QS_FUN_DICTIONARY(&QHsmTst_s333);
    QS_FUN_DICTIONARY(&QHsmTst_s3333);
    return Q_TRAN(&QHsmTst_s1);
}
/*${HSMs::QHsmTst::SM::s0} ..................................................*/
static QState QHsmTst_s0(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    /*${HSMs::QHsmTst::SM::s0} */
    case Q_ENTRY_SIG: {
        BSP_display("s0-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s0} */
    case Q_EXIT_SIG: {
        BSP_display("s0-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s0::initial} */
    case Q_INIT_SIG: {
        BSP_display("s0-INIT;");
        status_ = Q_TRAN(&QHsmTst_s1);
        break;
    }
    /*${HSMs::QHsmTst::SM::s0::S} */
    case S_SIG: {
        BSP_display("s0-S_SIG;");
        status_ = Q_TRAN(&QHsmTst_s222);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsm_top);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s1(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s1-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_EXIT_SIG: {
        BSP_display("s1-EXIT;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_INIT_SIG: {
        BSP_display("s1-INIT;");
        status_ = Q_TRAN(&QHsmTst_s11);
        break;
    }
    case B_SIG: {
        BSP_display("s1-B_SIG;");
        status_ = Q_TRAN(&QHsmTst_s1121);
        break;
    }
    case C_SIG: {
        BSP_display("s1-S_SIG;");
        status_ = Q_TRAN(&QHsmTst_s111);
        break;
    }
    case F_SIG: {
        BSP_display("s1-F_SIG;");
        status_ = Q_TRAN(&QHsmTst_s2);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s0);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s11(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s11-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_EXIT_SIG: {
        BSP_display("s11-EXIT;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_INIT_SIG: {
        BSP_display("s11-INIT;");
        status_ = Q_TRAN(&QHsmTst_s111);
        break;
    }
    case G_SIG: {
        BSP_display("s11-G_SIG;");
        status_ = Q_TRAN(&QHsmTst_s222);
        break;
    }
    case M_SIG: {

        BSP_display("s11-M_SIG;");
        status_ = Q_TRAN(&QHsmTst_s11);

        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s1);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s111(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s111-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_EXIT_SIG: {
        BSP_display("s111-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    case A_SIG: {
        BSP_display("s111-A_SIG;");
        status_ = Q_TRAN(&QHsmTst_s1121);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s11);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s112(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s112-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_EXIT_SIG: {
        BSP_display("s112-EXIT;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_INIT_SIG: {
        BSP_display("s112-INIT;");
        status_ = Q_TRAN(&QHsmTst_s1121);
        break;
    }
    case L_SIG: {
        BSP_display("s112-L_SIG;");
        status_ = Q_TRAN(&QHsmTst_s3);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s11);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s1121(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s1121-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_EXIT_SIG: {
        BSP_display("s1121-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    case H_SIG: {
        BSP_display("s1121-G_SIG;");
        status_ = Q_TRAN(&QHsmTst_s222);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s112);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s2(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s2-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_EXIT_SIG: {
        BSP_display("s2-EXIT;");
        status_ = Q_HANDLED();
        break;
    }

    case Q_INIT_SIG: {
        BSP_display("s2-INIT;");
        status_ = Q_TRAN(&QHsmTst_s22);
        break;
    }
    case N_SIG: {

        BSP_display("s2-N_SIG;");
        status_ = Q_TRAN(&QHsmTst_s2);
        break;
    }
    case O_SIG: {
        BSP_display("s2-O_SIG;");
        status_ = Q_TRAN(&QHsmTst_s3);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s0);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s22(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s22-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s} */
    case Q_EXIT_SIG: {
        BSP_display("s22-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s::initial} */
    case Q_INIT_SIG: {
        BSP_display("s22-INIT;");
        status_ = Q_TRAN(&QHsmTst_s222);
        break;
    }
    case Q_SIG: {
        BSP_display("s22-Q_SIG;");
        status_ = Q_TRAN(&QHsmTst_s3);
        break;
    }
    case D_SIG: {
        BSP_display("s22-D_SIG;");
        status_ = Q_TRAN(&QHsmTst_s111);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s2);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s222(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s222-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s} */
    case Q_EXIT_SIG: {
        BSP_display("s222-EXIT;");
        status_ = Q_HANDLED();
        break;
    }

    case E_SIG: {
        BSP_display("s222-INIT;");
        status_ = Q_TRAN(&QHsmTst_s1121);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s22);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s3(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s3-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s} */
    case Q_EXIT_SIG: {
        BSP_display("s3-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s::initial} */
    case Q_INIT_SIG: {
        BSP_display("s3-INIT;");
        status_ = Q_TRAN(&QHsmTst_s33);
        break;
    }
    case P_SIG: {
        BSP_display("s3-P_SIG;");
        status_ = Q_TRAN(&QHsmTst_s2);
        break;
    }
    case J_SIG: {
        BSP_display("s3-J_SIG;");
        status_ = Q_TRAN(&QHsmTst_s1);
        break;
    }
    case K_SIG: {
        BSP_display("s3-K_SIG;");
        status_ = Q_TRAN(&QHsmTst_s11);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s0);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s33(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s33-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s} */
    case Q_EXIT_SIG: {
        BSP_display("s33-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s::initial} */
    case Q_INIT_SIG: {
        BSP_display("s33-INIT;");
        status_ = Q_TRAN(&QHsmTst_s333);
        break;
    }
    case R_SIG: {
        BSP_display("s33-R_SIG;");
        status_ = Q_TRAN(&QHsmTst_s222);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s3);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s334(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s334-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s} */
    case Q_EXIT_SIG: {
        BSP_display("s334-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s::initial} */
    case I_SIG: {
        BSP_display("s334-I_SIG;");
        status_ = Q_TRAN(&QHsmTst_s1121);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s33);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s333(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s333-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s} */
    case Q_EXIT_SIG: {
        BSP_display("s333-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s::initial} */
    case Q_INIT_SIG: {
        BSP_display("s333-INIT;");
        status_ = Q_TRAN(&QHsmTst_s3333);
        break;
    }
    case T_SIG: {
        BSP_display("s333-T_SIG;");
        status_ = Q_TRAN(&QHsmTst_s111);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s33);
        break;
    }
    }
    return status_;
}
static QState QHsmTst_s3333(QHsmTst *const me, QEvt const *const e)
{
    QState status_;
    switch (e->sig) {
    case Q_ENTRY_SIG: {
        BSP_display("s3333-ENTRY;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s} */
    case Q_EXIT_SIG: {
        BSP_display("s3333-EXIT;");
        status_ = Q_HANDLED();
        break;
    }
    /*${HSMs::QHsmTst::SM::s::initial} */
    case U_SIG: {
        BSP_display("s3333-U_SIG;");
        status_ = Q_TRAN(&QHsmTst_s334);
        break;
    }
    default: {
        status_ = Q_SUPER(&QHsmTst_s333);
        break;
    }
    }
    return status_;
}