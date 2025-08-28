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
 * Header File: vedigest.h
 *
 *   Include this header file in C source code files in which you will
 *   be using the Simple API to create message digests. This header
 *   file defines the single digest creation function VeDigest.
 ***********************************************************************
 */
#ifndef VEDIGEST_H
#define VEDIGEST_H

#include "veapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 *
 * Digest Algorithm Constants:
 *
 *   Defined in the header file vedigest.h, the Simple API provides the
 *   following constants for use with the algorithm member of the
 *   parameters structure VeDigestParams.
 *
 *   VE_DIGEST_MD5
 *
 *     Specifies the use of the MD5 message digest algorithm. This
 *     algorithm produces a digest of 128 bits (16 bytes). Creation of
 *     this type of digest and this constant are deprecated.
 *
 *   VE_DIGEST_SHA1
 *
 *     Specifies the use of the SHA-1 message digest algorithm. This
 *     algorithm produces a digest of 160 bits (20 bytes).
 *
 *   VE_DIGEST_SHA224
 *
 *     Specifies the use of the SHA-224 message digest algorithm. This
 *     algorithm produces a digest of 224 bits (28 bytes).
 *
 *   VE_DIGEST_SHA256
 *
 *     Specifies the use of the SHA-256 message digest algorithm. This
 *     algorithm produces a digest of 256 bits (32 bytes).
 *
 *   VE_DIGEST_SHA384
 *
 *     Specifies the use of the SHA-384 message digest algorithm. This
 *     algorithm produces a digest of 384bits (48 bytes).
 *
 *   VE_DIGEST_SHA512
 *
 *     Specifies the use of the SHA-512 message digest algorithm. This
 *     algorithm produces a digest of 512 bits (64 bytes).
 *
 *   For more information, see the description of the function VeDigest.
 */
#define VE_DIGEST_MD5     1
#define VE_DIGEST_SHA1    2
#define VE_DIGEST_SHA224  3
#define VE_DIGEST_SHA256  4
#define VE_DIGEST_SHA384  5 
#define VE_DIGEST_SHA512  6

/***********************************************************************
 *
 * Function: VeDigest
 *
 *   Use this function to create a digest of the data in the input
 *   buffer you provide. Several standard digest algorithms are
 *   available from which to choose.
 *
 *   Parameters:
 *
 *     ctx
 *
 *       A required pointer to the LibraryContext object created by
 *       calling the function VeCreateLibCtx.
 *
 *     params
 *
 *       A required pointer to a properly initialized VeDigestParams
 *       parameters structure.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.data
 *         params.dataSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the input data buffer and the length of the
 *           data in that buffer, respectively. This is the input data
 *           from which the digest will be created.
 *
 *           Both of these structure members must be set explicitly
 *           before calling this function.
 *
 *           NOTE: Setting the dataSize member to 0 is not considered
 *                 an error, and a digest will be produced according to
 *                 the chosen algorithm. Although no data at this
 *                 address will be examined, the data member must be
 *                 non-null.
 *
 *         params.digest
 *         params.digestBufferSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the output buffer and the length (in bytes)
 *           of that buffer, respectively. This function will use the
 *           length value to avoid writing past the end of the buffer.
 *           Your goal is to make sure that the output buffer is large
 *           enough to contain the resulting digest.
 *
 *           Both of these structure members must be set explicitly
 *           before calling this function.
 *
 *           The required size of output digest buffer follows directly
 *           from the digest algorithm you choose. For information
 *           about how large the passed digest buffer should be, see
 *           the topic the Remarks section below or "Determining Output
 *           Buffer Sizes" in the Voltage SecureData Simple API
 *           Developer Guide.
 *
 *         params.digestSize
 *
 *           Examine this integer after this function returns in order
 *           to retrieve the length (in bytes) of the digest created by
 *           this function and written to the buffer specified by the
 *           digest member.
 *
 *         params.algorithm
 *
 *           Set this member to the constant that corresponds to the
 *           digest algorithm you want to use. If you want to use the
 *           SHA-256 algorithm, which is the default, you do not need
 *           to set this member explicitly (it was set by the structure
 *           assignment initialization described in the Remarks section
 *           below).
 *
 *           For more information about these constants, see the topic
 *           "Digest Algorithm Constants" in the Voltage SecureData
 *           Simple API Developer Guide.
 *
 *   Return Value:
 *
 *     This function returns zero (0) to indicate successful
 *     completion. This function may also return a variety of other
 *     non-zero error codes to indicate different error conditions. For
 *     more information, see the topic "Error Constants" in the Voltage
 *     SecureData Simple API Developer Guide.
 *
 *     NOTE: The parameters structure members digest and digestSize are
 *           also, effectively, return values from this function in
 *           that they are used to return the resulting digital digest
 *           to the caller. For more information, see their
 *           descriptions in the Parameters section above.
 *
 *   Remarks:
 *
 *     To call this function, declare an instance of the parameters
 *     structure VeDigestParams and assign the default values to its
 *     members using structure assignment with the static structure
 *     VeDigestParamsDefaults:
 *
 *       VeDigestParams digestArgs = VeDigestParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeDigest, passing the address of this structure.
 *
 *     The following digest algorithms are available when using this
 *     function, shown with their corresponding constants, as well as
 *     bit and byte sizes (the byte length is what you should use when
 *     allocating an output buffer and assigning its address and size
 *     to the parameters params.digest and params.digestBufferSize):
 *
 *                                         Bit      Byte
 *       Algorithm       C Constant      Length    Length
 *       ---------    ----------------   ------    ------
 *        MD5         VE_DIGEST_MD5        128       16     (deprecated)
 *        SHA-1       VE_DIGEST_SHA1       160       20
 *        SHA-224     VE_DIGEST_SHA224     224       28
 *        SHA-256     VE_DIGEST_SHA256     256       32
 *        SHA-384     VE_DIGEST_SHA384     384       48
 *        SHA-512     VE_DIGEST_SHA512     512       64
 */
typedef struct VeDigestParams_v1
{
    int                  private1;
    int                  private2;
    const unsigned char *data;
    unsigned int         dataSize;
    unsigned char       *digest;
    unsigned int         digestBufferSize;
    unsigned int         digestSize;
    int                  algorithm;
 
} VeDigestParams;

extern VE_DLL_DEF struct VeDigestParams_v1 VeDigestParamsDefaults_v1;

#define VeDigestParamsDefaults VeDigestParamsDefaults_v1

VE_DLL_DEF int VE_CALLING_CONV VeDigest(
    VeLibCtx            ctx,
    VeDigestParams     *params
);

#ifdef __cplusplus
}
#endif

#endif /* VEDIGEST_H */
