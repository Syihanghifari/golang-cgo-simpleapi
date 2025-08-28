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
 * Header File: vebase64.h
 *
 *   Include the header file vebase64.h in C source code files in which
 *   you will be using the Simple API to perform Base64 encoding and/or
 *   decoding. This header file defines the two Base64 functions
 *   VeBase64Encode and VeBase64Decode.
 ***********************************************************************
 */
#ifndef VEBASE64_H
#define VEBASE64_H

#include "veapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 *
 * Function: VeBase64Encode
 *
 *   Use this function and its associated parameters structure to
 *   create the Base64-encoded equivalent of the data you provide. The
 *   input data will be treated as binary data by the conversion
 *   process.
 *
 *   Call the function VeBase64Decode to reverse this process.
 *
 *   For more information about this conversion process, see the topic
 *   "Base64 Encoding" in the Voltage SecureData Simple API Developer
 *   Guide.
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
 *       A required pointer to a properly initialized
 *       VeBase64EncodeParams parameters structure.
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
 *           the start of the input buffer and the length of the data
 *           in that buffer, respectively. This buffer should contain
 *           the data to be Base64-encoded. Any NULL characters in the
 *           input buffer, even as the final character, are not treated
 *           in any special way.
 *
 *           Both of these structure members must be set explicitly
 *           before calling this function.
 *
 *           NOTE: Setting the dataSize member to 0 is not considered
 *                 an error, but will not produce any Base64-encoded
 *                 result. Although no data at this address will be
 *                 examined, the data member must be non-null.
 *
 *         params.encoded
 *         params.encodedBufferSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the output buffer and the length (in bytes)
 *           of that buffer, respectively. This function will use the
 *           length value to avoid writing past the end of the buffer.
 *           Your goal is to make sure that the output buffer is large
 *           enough to contain the resulting Base64-encoded data.
 *
 *           Both of these structure members must be set explicitly
 *           before calling this function.
 *
 *           For information about how large the passed encoded buffer
 *           should be, see the topic "Determining Output Buffer Sizes"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *         params.encodedSize
 *
 *           Examine this integer after this function returns in order
 *           to retrieve the length (in bytes) of the resulting
 *           Base64-encoded data written to the buffer specified by the
 *           encoded member.
 *
 *           NOTE: Although the Base64 alphabet would allow the encoded
 *                 output to be returned as a null-terminated string
 *                 rather than with an explicit length value, the
 *                 potentially large size of such encodings makes
 *                 processing based on null-termination less desirable
 *                 than for shorter strings. If it works better for
 *                 your application, adding a null-terminator is simple
 *                 using the length returned in this member, so long as
 *                 you have reserved space for the NULL character in
 *                 your output buffer.
 *
 *         params.wrapLines
 *
 *           Optionally set this integer member to 1 to have the
 *           Base64-encoded data divided into separate lines of
 *           sixty-four Base64 characters each, using the end-of-line
 *           (EOL) character(s) appropriate to the operating system on
 *           which your application is running. For example, linefeed
 *           (LF) on Unix, Linux, and macOS, and a
 *           carriage-return/linefeed pair (CR/LF) on Windows.
 *
 *           Set this integer member to 0 to have the Base64-encoded
 *           data not divided into separate lines. This is the default
 *           value, so setting this member to 0 is generally redundant.
 *
 *   Return Value:
 *
 *     This function returns zero (0) to indicate successful
 *     completion. This function may also return a variety of other
 *     non-zero error codes to indicate different error conditions. For
 *     more information, see the topic "Error Constants" in the Voltage
 *     SecureData Simple API Developer Guide.
 *
 *     NOTE: The parameters structure members encoded and encodedSize
 *           are also, effectively, return values from this function in
 *           that they are used to return the resulting Base64-encoded
 *           data to the caller. For more information, see their
 *           descriptions in the Parameters section above.
 *
 *   Remarks:
 *
 *     To call this function, declare an instance of the parameters
 *     structure VeBase64EncodeParams and assign the default values to
 *     its members using structure assignment with the static structure
 *     VeBase64EncodeParamsDefaults:
 *
 *       VeBase64EncodeParams encodeArgs =
 *                                   VeBase64EncodeParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeBase64Encode, passing the address of this structure.
 */
typedef struct VeBase64EncodeParams_v1
{
    int                  private1;
    int                  private2;
    const unsigned char *data;
    unsigned int         dataSize;
    unsigned char       *encoded;
    unsigned int         encodedBufferSize;
    unsigned int         encodedSize;
    int                  wrapLines;
 
} VeBase64EncodeParams;

extern VE_DLL_DEF struct VeBase64EncodeParams_v1 \
                        VeBase64EncodeParamsDefaults_v1;

#define VeBase64EncodeParamsDefaults VeBase64EncodeParamsDefaults_v1


VE_DLL_DEF int VE_CALLING_CONV VeBase64Encode(
    VeLibCtx              ctx,
    VeBase64EncodeParams *params
);

/***********************************************************************
 *
 * Function: VeBase64Decode
 *
 *   Use this function and its associated parameters structure to
 *   convert a the Base64-encoded character buffer back into its
 *   original form.
 *
 *   This function reverses the Base64 encoding performed by the
 *   function VeBase64Encode.
 *
 *   For more information about this conversion process, see the topic
 *   "Base64 Encoding" in the Voltage SecureData Simple API Developer
 *   Guide.
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
 *       A required pointer to a properly initialized
 *       VeBase64DecodeParams parameters structure.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.encoded
 *         params.encodedSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the input Base64-encoded buffer and the
 *           length of the data in that buffer, respectively. This
 *           buffer should contain the data to be Base64-decoded.
 *
 *           Both of these structure members must be set explicitly
 *           before calling this function.
 *
 *           NOTE: Setting the encodedSize member to 0 is not
 *                 considered an error, but will not produce any
 *                 Base64-decoded result. Although no data at this
 *                 address will be examined, the encoded member must be
 *                 non-null.
 *
 *         params.decoded
 *         params.decodedBufferSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the output buffer and the length (in bytes)
 *           of that buffer, respectively. This function will use the
 *           length value to avoid writing past the end of the buffer.
 *           Your goal is to make sure that the output buffer is large
 *           enough to contain the data resulting from the Base64
 *           decode operation.
 *
 *           Both of these structure members must be set explicitly
 *           before calling this function.
 *
 *           For information about how large the passed decoded buffer
 *           should be, see the topic "Determining Output Buffer Sizes"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *         params.decodedSize
 *
 *           Examine this integer after this function returns in order
 *           to retrieve the length (in bytes) of the data resulting
 *           from the Base64 decode operation and written to the buffer
 *           specified by the decoded member.
 *
 *         params.ignoreInvalidChars
 *
 *           Optionally set this integer member to 1 in order to
 *           specify that any characters in the input buffer encoded
 *           that are outside the Base64 character set will be ignored.
 *           That is, they will not contribute anything to the output
 *           buffer. The default value of this member is 0, which
 *           specifies that any such characters (other than EOL
 *           characters) that are encountered in the input buffer will
 *           result in immediate termination of the decode operation
 *           and an error code being returned by this function.
 *
 *   Return Value:
 *
 *     This function returns zero (0) to indicate successful
 *     completion. This function may also return a variety of other
 *     non-zero error codes to indicate different error conditions. For
 *     more information, see the topic "Error Constants" in the Voltage
 *     SecureData Simple API Developer Guide.
 *
 *     NOTE: The parameters structure members decoded and decodedSize
 *           are also, effectively, return values from this function in
 *           that they are used to return the resulting Base64-decoded
 *           data to the caller. For more information, see their
 *           descriptions in the Parameters section above.
 *
 *   Remarks:
 *
 *     To call this function, declare an instance of the parameters
 *     structure VeBase64DecodeParams and assign the default values to
 *     its members using structure assignment with the static structure
 *     VeBase64DecodeParamsDefaults:
 *
 *       VeBase64DecodeParams decodeArgs =
 *                                   VeBase64DecodeParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeBase64Decode, passing the address of this structure.
 */
typedef struct VeBase64DecodeParams_v1
{
    int                  private1;
    int                  private2;
    const unsigned char *encoded;
    unsigned int         encodedSize;
    unsigned char       *decoded;
    unsigned int         decodedBufferSize;
    unsigned int         decodedSize;
    int                  ignoreInvalidChars;
 
} VeBase64DecodeParams;

extern VE_DLL_DEF struct VeBase64DecodeParams_v1 \
                        VeBase64DecodeParamsDefaults_v1;

#define VeBase64DecodeParamsDefaults VeBase64DecodeParamsDefaults_v1

VE_DLL_DEF int VE_CALLING_CONV VeBase64Decode(
    VeLibCtx              ctx,
    VeBase64DecodeParams *params
);

#ifdef __cplusplus
}
#endif

#endif /* VEBASE64_H */
