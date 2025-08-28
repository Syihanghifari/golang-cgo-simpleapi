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
 * Header File: vesecfil.h
 *
 *   Include this header file in C source code files in which you will
 *   be using Voltage SecureFile technology to protect and/or access
 *   entire files. This header file defines the three SecureFile
 *   functions VeCreateSecureFile, VeReadSecureFile, and
 *   VeGetSecureFileAccessList.
 ***********************************************************************
 */
#ifndef VESECFIL_H
#define VESECFIL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "veapi.h"

/***********************************************************************
 *
 * SecureFile Version Constants:
 *
 *   Defined in the header file vesecfil.h, the Simple API provides the
 *   following constants for specifying the version of SecureFile
 *   encryption to use:
 *
 *   VE_SECURE_FILE_VERSION_1
 *
 *     Specifies the use of Version 1 of SecureFile encryption.
 *
 *   VE_SECURE_FILE_VERSION_2
 *
 *     Specifies the use of Version 2 of SecureFile encryption. This is
 *     the default value when you initialize any of the parameters
 *     structures for the SecureFile functions.
 *
 *   Use these constants for the value of the version members of the
 *   parameters structures VeCreateSecureFileParams,
 *   VeReadSecureFileParams, and VeGetSecureFileAccessListParams.
 *
 *   For more information, see the descriptions of the SecureFile
 *   functions VeCreateSecureFile, VeReadSecureFile, and
 *   VeGetSecureFileAccessList.
 */
#define VE_SECURE_FILE_VERSION_1  1
#define VE_SECURE_FILE_VERSION_2  2

/***********************************************************************
 *
 * Function: VeCreateSecureFile
 *
 *   Use this function to create an encrypted version of a specified
 *   file. You must specify a list of readers who will be able to
 *   decrypt the file produced by this function. Depending on the
 *   version of SecureFile you choose to use, an accompanying digital
 *   signature is mandatory (Version 1) or optional (Version 2).
 *
 *   Parameters:
 *
 *     ctx
 *
 *       Pass the address of the LibraryContext object created by
 *       calling the function VeCreateLibCtx.
 *
 *     params
 *
 *       Pass the address of a properly initialized
 *       VeCreateSecureFileParams parameters structure. The members of
 *       this structure specify the filenames of input plaintext file
 *       and the output ciphertext file, valid reader identities, a
 *       signer identity, and authentication credentials for
 *       interacting with the Key Server.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.version
 *
 *           Set this integer using the constant
 *           VE_SECURE_FILE_VERSION_1 when you want to create a
 *           protected file using Version 1 of Voltage SecureFile. If
 *           you want to use Version 2 of Voltage SecureFile, the
 *           default value for this member (corresponding to the
 *           constant VE_SECURE_FILE_VERSION_2) was already set during
 *           parameters structure initialization.
 *
 *         params.inPath
 *
 *           Set this character pointer to the address of a
 *           null-terminated string that contains the path and name of
 *           the plaintext input file. The input file can be a text
 *           file or a binary file.
 *
 *         params.outPath
 *
 *           Set this character pointer to the address of a
 *           null-terminated string that contains the path and name of
 *           the ciphertext output file to be created by this function.
 *
 *           NOTE: If the specified output file already exists, it will
 *                 be overwritten without any warning.
 *
 *         params.readers
 *         params.readersSize
 *
 *           Set this array pointer and integer to the address of an
 *           array of character pointers and the number of pointers in
 *           the array, respectively. Each of the character pointers in
 *           the array should be set to the address of a
 *           null-terminated string that contains a reader identity.
 *
 *           When an attempt is made to access a protected output file
 *           created by this function, one of the identities specified
 *           in this array must be provided to the function
 *           VeReadSecureFile. It is specified as the readerIdentity
 *           member of the structure VeReadSecureFileParams, the
 *           address of which is passed as the params parameter to that
 *           function.
 *
 *           For more information about identities, see the Voltage
 *           SecureData Architecture Guide.
 *
 *         params.signerIdentity
 *
 *           If the version member is set to specify Version 1 of
 *           Voltage SecureFile, set this character pointer to the
 *           address of a null-terminated string that contains a signer
 *           identity.
 *
 *           If the version member is set to specify Version 2 of
 *           Voltage SecureFile, optionally set this character pointer
 *           to the address of a null-terminated string that contains a
 *           signer identity.
 *
 *           When present, the signer identity is used to derive the
 *           cryptographic key needed to create a digital signature for
 *           the protected output file. Files protected using Version 1
 *           of Voltage SecureFile always include a digital signature
 *           and therefore require a signer identity to be specified.
 *           In Version 2 of Voltage SecureFile, digital signatures are
 *           optional. The default settings for the version member and
 *           the signerIdentity member of the VeCreateSecureFileParams
 *           structure specify a protected output file created with
 *           Version 2 of Voltage SecureFile without a digital
 *           signature.
 *
 *           If you are creating a Voltage SecureFile Version 2
 *           protected file without a digital signature, leave this
 *           member set to NULL, as established during parameters
 *           structure initialization.
 *
 *           For more information about identities, see the Voltage
 *           SecureData Architecture Guide.
 *
 *         params.sharedSecret
 *         params.username
 *         params.password
 *         params.clientCertificatePath
 *         params.clientCertificatePassword
 *
 *           By setting one and only one of the following sets of
 *           authentication credentials, you are choosing your
 *           authentication method:
 *
 *             - Shared Secret Authentication Method - Set the
 *               sharedSecret member to point at your null-terminated
 *               shared secret string.
 *
 *             - Username and Password Authentication Method - Set the
 *               username and password members to point at your
 *               null-terminated username and password strings,
 *               respectively, subject to LDAP authentication.
 *
 *             - Client Certification Authentication Method - Set the
 *               clientCertificatePath and clientCertificatePassword
 *               members to point at your null-terminated client
 *               certificate path and password strings, respectively.
 *
 *               On Unix, Linux, and macOS platforms, you specify the
 *               client certificate to the Simple API by using the full
 *               file system path of an appropriate P12 client
 *               certificate file along with its accompanying password.
 *
 *               On Windows platforms, you must import an appropriate
 *               PFX or P12 client certificate to your personal
 *               certificate store using its password and then specify
 *               that certificate to the Simple API using a path begins
 *               with the name of the Windows certificate store
 *               followed by pairs of well-defined certificate field or
 *               field and attribute names and their values as set in
 *               the certificate in question:
 *
 *                 /cert_store/name1/value1/.../nameN/valueN
 *
 *               For more information about specifying client
 *               certificates paths and passwords, see the topic
 *               "Specifying the Client Certificate Path and Password"
 *               in the Voltage SecureData Simple API Developer Guide.
 *
 *           For more information about these authentication methods,
 *           see the topic "Authentication Methods of the Simple API"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *           NOTE: If you are creating a SecureFile Version 2 protected
 *                 file without a digital signature, you must still set
 *                 some type of authentication credentials, though they
 *                 need not be valid.
 *
 *   Return Value:
 *
 *     This function returns zero (0) to indicate successful
 *     completion. To indicate an error, this function returns an
 *     appropriate error code. For information about the meaning of
 *     these codes and their corresponding constants, see the topic
 *     "Error Constants" in the Voltage SecureData Simple API Developer
 *     Guide.
 *
 *   Remarks:
 *
 *     The encrypted version of the file produced by this function will
 *     only be able to be decrypted by one of the readers specified
 *     using the readers member of the parameters structure
 *     VeCreateSecureFileParams.
 *
 *     To call this function to create a ciphertext version of a
 *     plaintext file, declare an instance of the parameters structure
 *     VeCreateSecureFileParams and assign the default values to its
 *     members using structure assignment with the static structure
 *     VeCreateSecureFileParamsDefaults:
 *
 *       VeCreateSecureFileParams createSFArgs =
 *                                  VeCreateSecureFileParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeCreateSecureFile, passing the address of this structure.
 */
typedef struct VeCreateSecureFileParams_v2
{
    int             private1;
    int             private2;
    int             version;
    const char     *inPath;
    const char     *outPath;
    const char    **readers;
    unsigned int    readersSize;
    const char     *signerIdentity;
    const char     *sharedSecret;
    const char     *username;
    const char     *password;
    const char     *clientCertificatePath;
    const char     *clientCertificatePassword;
} VeCreateSecureFileParams;

extern VE_DLL_DEF struct VeCreateSecureFileParams_v2 \
                        VeCreateSecureFileParamsDefaults_v2;

#define VeCreateSecureFileParamsDefaults \
        VeCreateSecureFileParamsDefaults_v2



VE_DLL_DEF int VE_CALLING_CONV VeCreateSecureFile(
    VeLibCtx                  ctx,
    VeCreateSecureFileParams *params
);

/***********************************************************************
 *
 * Function: VeReadSecureFile
 *
 *   Use this function to decrypt a file that was previously encrypted
 *   using the function VeCreateSecureFile, or by another compatible
 *   Voltage SecureData product. When you call this function, the
 *   reader identity you specify must be the same as one of the reader
 *   identities specified when the file was created.
 *
 *   This function will also attempt to verify the digital signature of
 *   the encrypted input file, if any, and will report the results of
 *   that attempt.
 *
 *   Parameters:
 *
 *     ctx
 *
 *       Pass the address of the LibraryContext object created by
 *       calling the function VeCreateLibCtx.
 *
 *     params
 *
 *       Pass the address of a properly initialized
 *       VeReadSecureFileParams parameters structure. The members of
 *       this structure specify the filenames of input ciphertext file
 *       and the output plaintext file, a reader identity, a digital
 *       signature verification buffer, and authentication credentials
 *       for interacting with the Key Server.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.inPath
 *
 *           Set this character pointer to the address of a
 *           null-terminated string that contains the path and name of
 *           the ciphertext input file.
 *
 *         params.outPath
 *
 *           Set this character pointer to the address of a
 *           null-terminated string that contains the path and name of
 *           the plaintext output file to be created by this function.
 *
 *           NOTE: If the specified output file already exists, it will
 *                 be overwritten without any warning.
 *
 *         params.readerIdentity
 *
 *           Set this character pointer to the address of a
 *           null-terminated string that contains the identity of the
 *           reader. This identity will be used to derive the
 *           cryptographic key to access the protected file. This
 *           identity must match one of the reader identities
 *           associated with the protected file, such as are specified
 *           when creating a SecureFile protected file using function
 *           VeCreateSecureFile or another compatible Voltage
 *           SecureData product.
 *
 *           For more information about identities, see the Voltage
 *           SecureData Architecture Guide.
 *
 *         params.sharedSecret
 *         params.username
 *         params.password
 *         params.clientCertificatePath
 *         params.clientCertificatePassword
 *
 *           By setting one and only one of the following sets of
 *           authentication credentials, you are choosing your
 *           authentication method:
 *
 *             - Shared Secret Authentication Method - Set the
 *               sharedSecret member to point at your null-terminated
 *               shared secret string.
 *
 *             - Username and Password Authentication Method - Set the
 *               username and password members to point at your
 *               null-terminated username and password strings,
 *               respectively, subject to LDAP authentication.
 *
 *             - Client Certification Authentication Method - Set the
 *               clientCertificatePath and clientCertificatePassword
 *               members to point at your null-terminated client
 *               certificate path and password strings, respectively.
 *
 *               On Unix, Linux, and macOS platforms, you specify the
 *               client certificate to the Simple API by using the full
 *               file system path of an appropriate P12 client
 *               certificate file along with its accompanying password.
 *
 *               On Windows platforms, you must import an appropriate
 *               PFX or P12 client certificate to your personal
 *               certificate store using its password and then specify
 *               that certificate to the Simple API using a path begins
 *               with the name of the Windows certificate store
 *               followed by pairs of well-defined certificate field or
 *               field and attribute names and their values as set in
 *               the certificate in question:
 *
 *                 /cert_store/name1/value1/.../nameN/valueN
 *
 *               For more information about specifying client
 *               certificates paths and passwords, see the topic
 *               "Specifying the Client Certificate Path and Password"
 *               in the Voltage SecureData Simple API Developer Guide.
 *
 *           For more information about these authentication methods,
 *           see the topic "Authentication Methods of the Simple API"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *         params.verified
 *         params.verifiedBufferSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the output digital signature verification
 *           buffer and the length (in bytes) of that buffer,
 *           respectively. This function will use the length value to
 *           avoid writing past the end of the buffer. Your goal is to
 *           make sure that the output buffer is large enough to
 *           contain the returned digital signature verification string.
 *
 *           See the Remarks section for information about the format
 *           of the returned verification string.
 *
 *           For information about how large the passed verified buffer
 *           should be, see the topic "Determining Output Buffer Sizes"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *   Return Value:
 *
 *     This function returns zero (0) to indicate successful
 *     completion. This function may also return a variety of other
 *     non-zero error codes to indicate different error conditions. For
 *     more information, see the topic "Error Constants" in the Voltage
 *     SecureData Simple API Developer Guide.
 *
 *     NOTE: The parameters structure member verified is also,
 *           effectively, a return value from this function in that it
 *           is used to return the resulting verification string to the
 *           caller. For more information, see its descriptions in the
 *           Parameters section above.
 *
 *   Remarks:
 *
 *     When reading a Voltage SecureFile protected file, a version
 *     number is not required because the version can be determined
 *     from the file itself.
 *
 *     There are three possible forms that the digital signature
 *     verification results can take, as follows:
 *
 *       - The empty string (length == 0) indicates that there was no
 *         digital signature associated with the ciphertext file being
 *         accessed. This is legitimate only when using Version 2 of
 *         Voltage SecureFile.
 *
 *       - A string that begins with the character 0 indicates that the
 *         digital signature failed verification. This string may have
 *         other values, such as the signer and district, following a
 *         colon character.
 *
 *       - A string that begins with the character 1 indicates that the
 *         digital signature passed verification. This string may have
 *         other values, such as the signer and district, following a
 *         colon character.
 *
 *     Before calling this function to create a plaintext version of a
 *     ciphertext file, declare an instance of the parameters structure
 *     VeReadSecureFileParams and assign the default values to its
 *     members using structure assignment with the static structure
 *     VeReadSecureFileParamsDefaults:
 *
 *       VeReadSecureFileParams readSFArgs =
 *                           VeReadSecureFileParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeReadSecureFile, passing the address of this structure.
 */
typedef struct VeReadSecureFileParams_v2
{
    int             private1;
    int             private2;
    int             version;    /*deprecated; value is ignored*/
    const char     *inPath;
    const char     *outPath;
    const char     *readerIdentity;
    const char     *sharedSecret;
    const char     *username;
    const char     *password;
    const char     *clientCertificatePath;
    const char     *clientCertificatePassword;
    const char     *verified;
    unsigned int    verifiedBufferSize;
} VeReadSecureFileParams;

extern VE_DLL_DEF struct VeReadSecureFileParams_v2 \
                        VeReadSecureFileParamsDefaults_v2;

#define VeReadSecureFileParamsDefaults \
        VeReadSecureFileParamsDefaults_v2

VE_DLL_DEF int VE_CALLING_CONV VeReadSecureFile(
    VeLibCtx                ctx,
    VeReadSecureFileParams *params
);

/***********************************************************************
 *
 * Function: VeGetSecureFileAccessList
 *
 *   Use this function to retrieve a list of the reader identities
 *   associated with a specified Voltage SecureFile protected file. Any
 *   of the returned reader identities can be used as the reader
 *   identity passed to the function VeReadSecureFile in order to
 *   re-create the plaintext version of the specified Voltage
 *   SecureFile protected file.
 *
 *   Parameters:
 *
 *     ctx
 *
 *       Pass the address of the LibraryContext object created by
 *       calling the function VeCreateLibCtx.
 *
 *     params
 *
 *       Pass the address of a properly initialized
 *       VeGetSecureFileAccessListParams parameters structure. The
 *       members of this structure specify the filename of input
 *       ciphertext file and output buffer information for the returned
 *       valid readers.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.inPath
 *
 *           Set this character pointer to the address of a
 *           null-terminated string that contains the path and name of
 *           the ciphertext input file.
 *
 *         params.readers
 *         params.readersBufferSize
 *         params.readersStringBufferSize
 *
 *           Set these three members as follows:
 *
 *             - Set the readers member to the address of an array of
 *               character pointers. These pointers must point to valid
 *               buffers to contain the returned list of readers.
 *
 *             - Set the readersBufferSize member to the number of
 *               valid character pointers in the array.
 *
 *             - Set the readersStringBufferSize member to the length
 *               of the buffers into which this function will write the
 *               list of reader identity strings, one per buffer.
 *
 *           This function will use the array size to avoid returning
 *           more reader identities than memory has been allocated to
 *           handle, and it will use the string buffer size value to
 *           avoid writing past the end of any of the reader buffers.
 *           Your goal is to make sure that the pointer array is large
 *           enough to contain the number of readers associated with
 *           the input ciphertext file, and that all of the individual
 *           buffers are large enough to hold the longest reader
 *           identity that might be returned, including its
 *           null-terminator.
 *
 *           For more information about the structure of the output
 *           buffers used to return the list of reader identity
 *           strings, see the topic "List of Readers Returned by
 *           VeGetSecureFileAccessList" in the Voltage SecureData
 *           Simple API Developer Guide.
 *
 *           For information about how large the passed readers buffers
 *           should be, see the topic "Determining Output Buffer Sizes"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *         params.readersSize
 *
 *           Examine this integer after this function returns in order
 *           to determine the number of reader buffers (pointed to by
 *           the pointers in the readers pointer array) into which this
 *           function has written reader identities. Individual reader
 *           identity strings are null-terminated.
 *
 *   Return Value:
 *
 *     This function returns zero (0) to indicate successful
 *     completion. This function may also return a variety of other
 *     non-zero error codes to indicate different error conditions. For
 *     more information, see the topic "Error Constants" in the Voltage
 *     SecureData Simple API Developer Guide.
 *
 *     NOTE: The parameters structure members readers and readersSize
 *           are also, effectively, return values from this function in
 *           that they are used to return the resulting reader identity
 *           strings to the caller. For more information, see their
 *           descriptions in the Parameters section above.
 *
 *   Remarks:
 *
 *     When retrieving the access list for a Voltage SecureFile
 *     protected file, a version number is not required because the
 *     version can be determined from the file itself.
 *
 *     Before calling this function to retrieve the allowed readers of
 *     an encrypted file, you must declare an instance of the
 *     parameters structure VeGetSecureFileAccessListParams and assign
 *     the default values to its members using structure assignment
 *     with the static structure
 *     VeGetSecureFileAccessListParamsDefaults:
 *
 *       VeGetSecureFileAccessListParams getReadersArgs =
 *                       VeGetSecureFileAccessListParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeGetSecureFileAccessList, passing the address of this structure.
 */
typedef struct VeGetSecureFileAccessListParams_v1
{
    int             private1;
    int             private2;
    int             version;    /*deprecated; value is ignored*/
    const char     *inPath;
    char          **readers;
    unsigned int    readersBufferSize;
    unsigned int    readersStringBufferSize;
    unsigned int    readersSize;
} VeGetSecureFileAccessListParams;

extern VE_DLL_DEF struct VeGetSecureFileAccessListParams_v1 \
                        VeGetSecureFileAccessListParamsDefaults_v1;

#define VeGetSecureFileAccessListParamsDefaults \
        VeGetSecureFileAccessListParamsDefaults_v1


VE_DLL_DEF int VE_CALLING_CONV VeGetSecureFileAccessList(
    VeLibCtx                ctx,
    VeGetSecureFileAccessListParams *params
);

#ifdef __cplusplus
}
#endif

#endif /* VESECFIL_H */
