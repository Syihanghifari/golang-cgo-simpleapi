/***********************************************************************
 * (c) Copyright 2021-2023 Micro Focus or one of its affiliates.       *
 *                                                                     *
 * The only warranties for products and services of Micro Focus and    *
 * its affiliates and licensors ("Micro Focus") are as may be set      *
 * forth in the express warranty statements accompanying such products *
 * and services. Nothing herein should be construed as constituting an *
 * additional warranty. Micro Focus shall not be liable for technical  *
 * or editorial errors or omissions contained herein. The information  *
 * contained herein is subject to change without notice.               *
 *                                                                     *
 * Except as specifically indicated otherwise, this document contains  *
 * confidential information and a valid license is required for        *
 * possession, use or copying. If this work is provided to the U.S.    *
 * Government, consistent with FAR 12.211 and 12.212, Commercial       *
 * Computer Software, Computer Software Documentation, and Technical   *
 * Data for Commercial Items are licensed to the U.S. Government under *
 * vendor's standard commercial license.                               *
 ***********************************************************************
 *
 * Header File: veaes.h
 *
 *   This header contains the Deprecated "AES" definitions that
 *   were superseded by equivalent IBSE definitions in veibse.h.
 *   All new code should use only veibse.h, and existing code
 *   should migrate to veibse.h when practical. This header will
 *   be removed in some future release.
 ***********************************************************************
 */
#ifndef VEAES_H
#define VEAES_H

#include "veibse.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VeIBSE_st *VeAES;

/* veibse.h defines VE_IBSE_AES_EMES */
/* veibse.h defines VE_IBSE_AES_CBC */

typedef struct VeAESParams_v2
{
    int             private1;
    int             private2;
    int             protect;
    int             access;
    const char     *identity;
    const char     *sharedSecret;
    const char     *username;
    const char     *password;
    const char     *clientCertificatePath;
    const char     *clientCertificatePassword;
    int             aesMode;
 
} VeAESParams;

extern VE_DLL_DEF struct VeAESParams_v2 VeAESParamsDefaults_v2;

#define VeAESParamsDefaults VeAESParamsDefaults_v2

VE_DLL_DEF int VE_CALLING_CONV VeCreateAES(
    VeLibCtx     ctx,
    VeAESParams *params,
    VeAES       *aes
);

/* veibse.h defines VeDestroyIBSE(VeIBSE *ibse) */
#define VeDestroyAES(obj) VeDestroyIBSE(obj) 

#ifdef __cplusplus
}
#endif

#endif /* VEAES_H */
