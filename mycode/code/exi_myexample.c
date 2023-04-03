// /***********************************************************
// File name     : exi_mytest.cpp
// Author name   : xiongyansong
// Email address : sanxisui@gmail.com
// Create time   : 2023-03-07 23:48:36
// ***********************************************************/
// #include <stdio.h>
// #include <stdarg.h>
// #include <stdlib.h>
// #include <string.h>
// #include <gtest/gtest.h>

// #include "xlog.h"
// #include "EXITypes.h"
// #include "appHandEXIDatatypes.h"
// #include "appHandEXIDatatypesEncoder.h"
// #include "appHandEXIDatatypesDecoder.h"

// /* Activate support for DIN */
// #include "dinEXIDatatypes.h"
// #if DEPLOY_DIN_CODEC == SUPPORT_YES
// #include "dinEXIDatatypesEncoder.h"
// #include "dinEXIDatatypesDecoder.h"
// #endif /* DEPLOY_DIN_CODEC == SUPPORT_YES */

// /* Activate support for XMLDSIG */
// #include "xmldsigEXIDatatypes.h"
// #if DEPLOY_XMLDSIG_CODEC == SUPPORT_YES
// #include "xmldsigEXIDatatypesEncoder.h"
// #include "xmldsigEXIDatatypesDecoder.h"
// #endif /* DEPLOY_XMLDSIG_CODEC == SUPPORT_YES */

// /* Activate support for ISO1 */
// #include "iso1EXIDatatypes.h"
// #if DEPLOY_ISO1_CODEC == SUPPORT_YES
// #include "iso1EXIDatatypesEncoder.h"
// #include "iso1EXIDatatypesDecoder.h"
// #endif /* DEPLOY_ISO1_CODEC == SUPPORT_YES */

// /* Activate support for ISO2 */
// #include "iso2EXIDatatypes.h"
// #if DEPLOY_ISO2_CODEC == SUPPORT_YES
// #include "iso2EXIDatatypesEncoder.h"
// #include "iso2EXIDatatypesDecoder.h"
// #endif /* DEPLOY_ISO2_CODEC == SUPPORT_YES */

// #include "v2gtp.h"
// #define BUFFER_SIZE 256
// extern uint8_t buffer1[BUFFER_SIZE];
// extern uint8_t buffer2[BUFFER_SIZE];

// #define ERROR_UNEXPECTED_REQUEST_MESSAGE -601
// #define ERROR_UNEXPECTED_SESSION_SETUP_RESP_MESSAGE -602
// #define ERROR_UNEXPECTED_SERVICE_DISCOVERY_RESP_MESSAGE -602
// #define ERROR_UNEXPECTED_SERVICE_DETAILS_RESP_MESSAGE -603
// #define ERROR_UNEXPECTED_PAYMENT_SERVICE_SELECTION_RESP_MESSAGE -604
// #define ERROR_UNEXPECTED_PAYMENT_DETAILS_RESP_MESSAGE -605
// #define ERROR_UNEXPECTED_AUTHORIZATION_RESP_MESSAGE -606
// #define ERROR_UNEXPECTED_CHARGE_PARAMETER_DISCOVERY_RESP_MESSAGE -607
// #define ERROR_UNEXPECTED_POWER_DELIVERY_RESP_MESSAGE -608
// #define ERROR_UNEXPECTED_CHARGING_STATUS_RESP_MESSAGE -609
// #define ERROR_UNEXPECTED_METERING_RECEIPT_RESP_MESSAGE -610
// #define ERROR_UNEXPECTED_SESSION_STOP_RESP_MESSAGE -611
// #define ERROR_UNEXPECTED_CABLE_CHECK_RESP_MESSAGE -612
// #define ERROR_UNEXPECTED_PRE_CHARGE_RESP_MESSAGE -612
// #define ERROR_UNEXPECTED_CURRENT_DEMAND_RESP_MESSAGE -613
// #define ERROR_UNEXPECTED_WELDING_DETECTION_RESP_MESSAGE -614

// /* serializes EXI stream and adds V2G TP header */
// static int serialize1EXI2Stream(struct iso1EXIDocument *exiIn, bitstream_t *stream)
// {
//     int errn;
//     *stream->pos = V2GTP_HEADER_LENGTH; /* v2gtp header */
//     if ((errn = encode_iso1ExiDocument(stream, exiIn)) == 0) {
//         errn = write_v2gtpHeader(stream->data, (*stream->pos) - V2GTP_HEADER_LENGTH, V2GTP_EXI_TYPE);
//     }
//     return errn;
// }
// static int deserialize1Stream2EXI(bitstream_t *streamIn, struct iso1EXIDocument *exi)
// {
//     int errn;
//     uint32_t payloadLength;

//     *streamIn->pos = 0;
//     if ((errn = read_v2gtpHeader(streamIn->data, &payloadLength)) == 0) {
//         *streamIn->pos += V2GTP_HEADER_LENGTH;

//         errn = decode_iso1ExiDocument(streamIn, exi);
//     }
//     return errn;
// }
// static int CurrentDemandReq1(struct iso1EXIDocument *exiIn, struct iso1EXIDocument *exiOut)
// {
//     // printf("EVSE side: CurrentDemandReq called\n");
//     // printf("\tReceived data:\n");

//     // printf("\t\t  EVReady=%d\n", exiIn->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVReady);
//     // printf("\t\t  EVErrorCode=%d\n", exiIn->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVErrorCode);

//     /* Prepare data for EV */
//     exiOut->V2G_Message_isUsed = 1u;

//     init_iso1MessageHeaderType(&exiOut->V2G_Message.Header);
//     exiOut->V2G_Message.Header.SessionID.bytes[0] = 1;
//     exiOut->V2G_Message.Header.SessionID.bytes[1] = 2;
//     exiOut->V2G_Message.Header.SessionID.bytes[2] = 3;
//     exiOut->V2G_Message.Header.SessionID.bytes[3] = 4;
//     exiOut->V2G_Message.Header.SessionID.bytes[4] = 5;
//     exiOut->V2G_Message.Header.SessionID.bytes[5] = 6;
//     exiOut->V2G_Message.Header.SessionID.bytes[6] = 7;
//     exiOut->V2G_Message.Header.SessionID.bytes[7] = 8;
//     exiOut->V2G_Message.Header.SessionID.bytesLen = 8;

//     init_iso1BodyType(&exiOut->V2G_Message.Body);
//     exiOut->V2G_Message.Body.CurrentDemandRes_isUsed = 1u;
//     init_iso1CurrentDemandResType(&exiOut->V2G_Message.Body.CurrentDemandRes);

//     // DC_EVSE状态码
//     exiOut->V2G_Message.Body.CurrentDemandRes.DC_EVSEStatus.EVSEStatusCode = iso1DC_EVSEStatusCodeType_EVSE_Ready;
//     // 响应码
//     exiOut->V2G_Message.Body.CurrentDemandRes.ResponseCode = iso1responseCodeType_OK;
//     // EVSE的当前输出电压
//     exiOut->V2G_Message.Body.CurrentDemandRes.EVSEPresentVoltage.Multiplier = 3;
//     exiOut->V2G_Message.Body.CurrentDemandRes.EVSEPresentVoltage.Unit = iso1unitSymbolType_V;
//     exiOut->V2G_Message.Body.CurrentDemandRes.EVSEPresentVoltage.Value = 3;
//     // EVSE的当前输出电流
//     exiOut->V2G_Message.Body.CurrentDemandRes.EVSEPresentCurrent.Multiplier = 1;
//     exiOut->V2G_Message.Body.CurrentDemandRes.EVSEPresentCurrent.Unit = iso1unitSymbolType_A;
//     exiOut->V2G_Message.Body.CurrentDemandRes.EVSEPresentCurrent.Value = 2;
//     // 计费中的唯一值
//     exiOut->V2G_Message.Body.CurrentDemandRes.SAScheduleTupleID = 72;
//     return 0;
// }
// static int ChargeParameterDiscoveryReq1(struct iso1EXIDocument *exiIn, struct iso1EXIDocument *exiOut)
// {
//     exiOut->V2G_Message_isUsed = 1u;

//     init_iso1MessageHeaderType(&exiOut->V2G_Message.Header);
//     exiOut->V2G_Message.Header.SessionID.bytes[0] = 1;
//     exiOut->V2G_Message.Header.SessionID.bytes[1] = 2;
//     exiOut->V2G_Message.Header.SessionID.bytes[2] = 3;
//     exiOut->V2G_Message.Header.SessionID.bytes[3] = 4;
//     exiOut->V2G_Message.Header.SessionID.bytes[4] = 5;
//     exiOut->V2G_Message.Header.SessionID.bytes[5] = 6;
//     exiOut->V2G_Message.Header.SessionID.bytes[6] = 7;
//     exiOut->V2G_Message.Header.SessionID.bytes[7] = 8;
//     exiOut->V2G_Message.Header.SessionID.bytesLen = 8;

//     init_iso1BodyType(&exiOut->V2G_Message.Body);
//     exiOut->V2G_Message.Body.ChargeParameterDiscoveryRes_isUsed = 1u;
//     init_iso1ChargeParameterDiscoveryResType(&exiOut->V2G_Message.Body.ChargeParameterDiscoveryRes);
//     return 0;
// }
// static int create_response_message1(struct iso1EXIDocument *exiIn, struct iso1EXIDocument *exiOut)
// {
//     int errn = ERROR_UNEXPECTED_REQUEST_MESSAGE;

//     /* create response message as EXI document */
//     if (exiIn->V2G_Message_isUsed) {
//         init_iso1EXIDocument(exiOut);
//         if (exiIn->V2G_Message.Body.CurrentDemandReq_isUsed) {
//             errn = CurrentDemandReq1(exiIn, exiOut);
//         } else if (exiIn->V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed) {
//             errn = ChargeParameterDiscoveryReq1(exiIn, exiOut);
//             return errn;
//         }
//         return errn;
//     }
// }

// static int request_response1(struct iso1EXIDocument *exiIn, struct iso1EXIDocument *exiOut, uint8_t st_buff[], int len)
// {
//     int errn;
//     uint8_t st_buff[len] = {0};
//     bitstream_t stream1;
//     bitstream_t stream2;

//     size_t pos1;
//     size_t pos2;

//     stream1.size = BUFFER_SIZE;
//     stream1.data = buffer1;
//     stream1.pos = &pos1;

//     stream2.size = BUFFER_SIZE;
//     stream2.data = buffer2;
//     stream2.pos = &pos2;

//     /* EV side */
//     errn = serialize1EXI2Stream(exiIn, &stream1);
//     printf("--------------%d\n", errn);
//     /* --> Start of EVSE side */
//     /* deserialize request message */
//     XLOG_DH(stream1.data, *stream1.pos);
//     // st_buff[] = st_buff1;
//     XLOG_DH(st_buff, len);
//     memcpy(stream1.data, st_buff, len);

//     errn = deserialize1Stream2EXI(&stream1, exiOut);

//     if (exiOut->V2G_Message.Body.CurrentDemandReq_isUsed) {
//         XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVReady =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVReady);
//         XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVRESSSOC =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVRESSSOC);
//         XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVErrorCode =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVErrorCode);
//         XLOG_D("Receive CurrentDemandReq, EVTargetCurrent.Value =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.EVTargetCurrent.Value);
//         XLOG_D("Receive CurrentDemandReq, EVTargetVoltage.Value =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.EVTargetVoltage.Value);
//         XLOG_D("Receive CurrentDemandReq, ChargingComplete =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.ChargingComplete);
//         exiOut->V2G_Message.Body.CurrentDemandReq_isUsed = 0u;
//         printf("\n");
//     } else if (exiOut->V2G_Message.Body.CertificateInstallationReq_isUsed) {
//         // XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVReady =%d ", exiOut->V2G_Message.CertificateInstallationReq.DC_EVStatus.EVReady);
//         // XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVReady =%d ", exiOut->V2G_Message.CertificateInstallationReq.DC_EVStatus.EVRESSSOC);
//         exiOut->V2G_Message.Body.CertificateInstallationReq_isUsed = 0u;
//         printf("\n");
//     } else if (exiOut->V2G_Message.Body.CertificateUpdateReq_isUsed) {
//         XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVReady =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVReady);
//         XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVReady =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVRESSSOC);
//         exiOut->V2G_Message.Body.CertificateUpdateReq_isUsed = 0u;
//         printf("\n");
//     } else if (exiOut->V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed) {
//         XLOG_D("Receive ChargeParameterDiscoveryReq,RequestedEnergyTransferMode =%d ", exiOut->V2G_Message.Body.ChargeParameterDiscoveryReq.RequestedEnergyTransferMode);
//         XLOG_D("Receive ChargeParameterDiscoveryReq, AC_EVChargeParameter.DepartureTime =%d ", exiOut->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.DepartureTime);
//         XLOG_D("Receive ChargeParameterDiscoveryReq, AC_EVChargeParameter.EAmount.Value =%hd ", exiOut->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EAmount.Value);
//         XLOG_D("Receive ChargeParameterDiscoveryReq, AC_EVChargeParameter.EVMaxVoltage.Value =%hd ", exiOut->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMaxVoltage.Value);
//         XLOG_D("Receive ChargeParameterDiscoveryReq, AC_EVChargeParameter.EVMinCurrent.Value =%hd ", exiOut->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMinCurrent.Value);
//         XLOG_D("Receive ChargeParameterDiscoveryReq, AC_EVChargeParameter.EVMaxCurrent.Value =%hd ", exiOut->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMaxCurrent.Value);
//         exiOut->V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed = 0u;
//         printf("\n");
//     } else if (exiOut->V2G_Message.Body.WeldingDetectionReq_isUsed) {
//         XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVReady =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVReady);
//         XLOG_D("Receive CurrentDemandReq, DC_EVStatus.EVReady =%d ", exiOut->V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVRESSSOC);
//         exiOut->V2G_Message.Body.WeldingDetectionReq_isUsed = 0u;
//         printf("\n");
//     }
//     XLOG_DH(stream1.data, *stream1.pos);

//     /* create response message */
//     if (errn == 0) {
//         errn = create_response_message1(exiOut, exiIn);
//     }

//     /* serialize response message */
//     if (errn == 0) {
//         errn = serialize1EXI2Stream(exiIn, &stream2);
//     }
//     /* <-- End of EVSE side */
//     // XLOG_DH(stream2.data, *stream2.pos);
//     /* EV side */
//     /* deserialize response message */
//     if (errn == 0) {
//         errn = deserialize1Stream2EXI(&stream2, exiOut);
//     }

//     XLOG_DH(stream2.data, *stream2.pos);

//     printf("second_SAScheduleTupleID=%d", exiOut->V2G_Message.Body.CurrentDemandRes.SAScheduleTupleID);
//     printf("\n");

//     return errn;
// }
// static void printBinaryArray(uint8_t *byte, uint16_t len)
// {
//     unsigned int i;
//     for (i = 0; i < len; i++) {
//         printf("%d ", byte[i]);
//     }
//     printf("\n");
// }

// static int charging1()
// {
//     int errn = 0;

//     struct iso1EXIDocument exiIn = {0};
//     struct iso1EXIDocument exiOut = {0};

//     /* setup header information */
//     init_iso1EXIDocument(&exiIn);
//     exiIn.V2G_Message_isUsed = 1u;
//     init_iso1MessageHeaderType(&exiIn.V2G_Message.Header);
//     exiIn.V2G_Message.Header.SessionID.bytes[0] = 0; /* sessionID is always '0' at the beginning (the response contains the valid sessionID)*/
//     exiIn.V2G_Message.Header.SessionID.bytes[1] = 0;
//     exiIn.V2G_Message.Header.SessionID.bytes[2] = 0;
//     exiIn.V2G_Message.Header.SessionID.bytes[3] = 0;
//     exiIn.V2G_Message.Header.SessionID.bytes[4] = 0;
//     exiIn.V2G_Message.Header.SessionID.bytes[5] = 0;
//     exiIn.V2G_Message.Header.SessionID.bytes[6] = 0;
//     exiIn.V2G_Message.Header.SessionID.bytes[7] = 0;
//     exiIn.V2G_Message.Header.SessionID.bytesLen = 8;
//     exiIn.V2G_Message.Header.Signature_isUsed = 0u;

//     /*********************************
//      * CurrentDemand *
//      *********************************/

//     init_iso1BodyType(&exiIn.V2G_Message.Body);
//     exiIn.V2G_Message.Body.CurrentDemandReq_isUsed = 1u;

//     init_iso1CurrentDemandReqType(&exiIn.V2G_Message.Body.CurrentDemandReq);
//     // boolen类型，为True说明充满电了,
//     exiIn.V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVReady = 1;
//     // EV内部状态，枚举类型
//     exiIn.V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVErrorCode = iso1DC_EVErrorCodeType_NO_ERROR;
//     // 电池电量状态0~100
//     exiIn.V2G_Message.Body.CurrentDemandReq.DC_EVStatus.EVRESSSOC = 30;
//     // EVTargetCurrent0~400A
//     // 乘数Multiplier-3~+3
//     exiIn.V2G_Message.Body.CurrentDemandReq.EVTargetCurrent.Multiplier = 2;
//     // 单位
//     exiIn.V2G_Message.Body.CurrentDemandReq.EVTargetCurrent.Unit = iso1unitSymbolType_A;
//     // 值
//     exiIn.V2G_Message.Body.CurrentDemandReq.EVTargetCurrent.Value = 8;
//     printf("\nEV side: call EVSE CurrentDemand \n");

//     uint8_t st_buff[] = {0x01, 0xfe, 0x80, 0x01, 0x00, 0x00, 0x00, 0x18, 0x80, 0x98, 0x02, 0x0C, 0x0C, 0x4C, 0x8C, 0xCD, 0x0D, 0x4D, 0x8D, 0xD0, 0xD1, 0x00, 0x1B, 0x81, 0x86, 0x07, 0x84, 0x10, 0xC4, 0x0C, 0x20, 0x30, 0x00};

//     errn = request_response1(&exiIn, &exiOut, st_buff, sizeof(st_buff));

//     if (errn == 0) {
//         /* check, if this is the right response message */
//         if (exiOut.V2G_Message.Body.CurrentDemandRes_isUsed) {

//             /* show results of EVSEs answer message */
//             printf("EV side: received response message from EVSE\n");
//             printf("\tHeader SessionID=");
//             printBinaryArray(exiOut.V2G_Message.Header.SessionID.bytes, exiOut.V2G_Message.Header.SessionID.bytesLen);
//             printf("\t EVSEStatusCode=%d\n", exiOut.V2G_Message.Body.CurrentDemandRes.DC_EVSEStatus.EVSEStatusCode);
//             printf("\t ResponseCode=%d\n", exiOut.V2G_Message.Body.CurrentDemandRes.ResponseCode);
//             // printf("\t EVSEPresentVoltage=%d\n", exiOut.V2G_Message.Body.CurrentDemandRes.EVSEPresentVoltage);
//             // printf("\t EVSEPresentCurrent=%d\n", exiOut.V2G_Message.Body.CurrentDemandRes.EVSEPresentCurrent);
//             printf("\t SAScheduleTupleID=%d\n", exiOut.V2G_Message.Body.CurrentDemandRes.SAScheduleTupleID);
//             /*printACEVSEStatus(&(exiOut.V2G_Message.Body.PowerDeliveryRes.AC_EVSEStatus));*/
//         } else {
//             errn = ERROR_UNEXPECTED_POWER_DELIVERY_RESP_MESSAGE;
//             return errn;
//         }
//     } else {
//         return errn;
//     }
//     /*********************************
//      * ChargeParameterDiscoveryReq *
//      *********************************/
//     init_iso1BodyType(&exiIn.V2G_Message.Body);
//     exiIn.V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed = 1u;

//     init_iso1ChargeParameterDiscoveryReqType(&exiIn.V2G_Message.Body.ChargeParameterDiscoveryReq);
//     printf("\nEV side: call EVSE ChargeParameterDiscoveryReq \n");

//     uint8_t st_buff1[] = {0x01, 0xfe, 0x80, 0x01, 0x00, 0x00, 0x00, 0x18, 0x80, 0x98, 0x02, 0x0C, 0x0C, 0x4C, 0x8C, 0xCD, 0x0D, 0x4D, 0x8D, 0xD0, 0x94, 0x00, 0x64, 0x0C, 0x30, 0x09, 0x01, 0x88, 0x1C, 0xC0, 0x20, 0x61, 0x81, 0x00, 0x18, 0x60, 0x00, 0x00};

//     errn = request_response1(&exiIn, &exiOut, st_buff1, sizeof(st_buff1));
//     /*********************************
//      * CertificatelnstallationReq *
//      *********************************/
//     /*********************************
//      * CertificateUpdateReq *
//      *********************************/
//     /*********************************
//      * supportedAppProtocolReq *
//      *********************************/
//     /*********************************
//      * WeldingDetectionReq *
//      *********************************/
//     return errn;
// }
// TEST(exi, CurrentDemandReq)
// {
//     int erron;
//     XLOG_D("\n------------------------------------------------------------------------------------");
// #if DEPLOY_ISO1_CODEC == SUPPORT_YES
//     printf("+++ Start V2G client / service example for charging (ISO1) +++\n");
//     erron = charging1();
//     printf("\n+++Terminate V2G Client / Service example for charging with errn = %d +++\n", erron);
//     if (erron != 0) {
//         printf("\n\ncharging error %d!\n", erron);
//         // return errn;
//     }
//     XLOG_D("\n------------------------------------------------------------------------------------");
// #endif /* DEPLOY_ISO1_CODEC == SUPPORT_YES */
// }