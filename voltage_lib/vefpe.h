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
 * Header File: vefpe.h
 *
 *   Include this header file in C source code files in which you will
 *   be protecting plaintext and/or accessing ciphertext using
 *   Format-Preserving Encryption (FPE). This header file defines the
 *   VeFPE object and the functions used to create and destroy this
 *   type of object. It also defines the FPE-specific utility function
 *   VeGetKeyNumbers.
 ***********************************************************************
 */
#ifndef VEFPE_H
#define VEFPE_H

#include "veapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 *
 * Object: VeFPE
 *
 *   The structure pointer VeFPE, defined in the header file vefpe.h,
 *   serves as the equivalent of the FPE class and its instantiated
 *   objects in object-oriented implementations of the Simple API. This
 *   object establishes and stores characteristics for a set of similar
 *   FPE cryptographic operations to be performed using this object.
 *   These characteristics include whether protect or access operations
 *   will be performed, the name of the FPE format to be used,
 *   authentication credentials for accessing the Voltage SecureData
 *   Key Server during cryptographic operations, etc.
 *
 *   Create this "object" by calling the function VeCreateFPE and
 *   destroy it by calling the function VeDestroyFPE. When you create a
 *   VeFPE object, you initialize it using a parameters structure, the
 *   address of which gets passed to the function VeCreateFPE (for
 *   additional information, see the documentation for this function).
 *   Thereafter, you do not directly access the information stored by
 *   this object.
 */
typedef struct VeFPE_st *VeFPE;
 
/***********************************************************************
 *
 * Function: VeCreateFPE
 *
 *   Use this function and its associated parameters structure to
 *   create and initialize an FPE object to manage a particular type of
 *   FPE operation. After these operations are complete, the FPE object
 *   created by this function should be destroyed using the function
 *   VeDestroyFPE.
 *
 *   FPE objects created using the C language interface to the Simple
 *   API are thread-safe and can safely be shared for similar FPE
 *   operations in different threads. For more information, see the
 *   topic "Building Multi-Threaded Applications" in the Voltage
 *   SecureData Simple API Developer Guide.
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
 *       Pass the address of a properly initialized VeFPEParams
 *       parameters structure. The members of this structure specify
 *       various characteristics of the FPE object being created, such
 *       as whether it will be used for protect or access operations,
 *       the identity from which the cryptographic key will be derived,
 *       the name of the FPE format according to which protect or
 *       access operations will be performed, etc.
 *
 *       To properly initialize this parameters structure, use
 *       structure assignment with the pre-initialized static version
 *       of this structure intended for this purpose:
 *
 *         VeFPEParams fpeParams = VeFPEParamsDefaults;
 *
 *       In general, this structure assignment sets members to zero (0
 *       or NULL). For required and conditionally required settings,
 *       the corresponding structure members must be set appropriately
 *       before calling function VeCreateFPE. For optional settings,
 *       the corresponding structure members may be set.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.protect
 *         params.access
 *
 *           Set one or the other of these integer members to 1 to
 *           specify that this FPE object is going to be used to
 *           protect plaintext by encrypting it, or access ciphertext
 *           by decrypting it, respectively.
 *
 *           Set one but not both of these structure members.
 *
 *         params.allowNetEmpty
 *
 *           Set this integer member to 0 to change the default
 *           Net-Empty input behavior for this FPE object. By default,
 *           when protect or access input is found to be Net-Empty, the
 *           Simple API will return the input value, unchanged, as the
 *           output value of the protect or access operation (this is
 *           the behavior when this structure member is properly set to
 *           its default value of 1). Setting this structure member to
 *           0 will change this default behavior, causing the Simple
 *           API to return an error when the input value to a protect
 *           or access operation is found to be Net-Empty.
 *
 *           NOTE: A plaintext is Net-Empty when it does not contain
 *                 any characters in the (implicit or explicit)
 *                 plaintext alphabet. Likewise, a ciphertext is
 *                 Net-Empty when it does not contain any characters in
 *                 the (implicit or explicit) ciphertext alphabet. For
 *                 example, given that the alphabet for an FPE credit
 *                 card format consists of the digits 0 to 9, the
 *                 credit card plaintext aaaa-bbbb-cccc-dddd is
 *                 Net-Empty.
 *
 *           For more information about protect and access behavior
 *           with respect to Net-Empty input values, see the topic
 *           "Net-Empty Input Values to FPE Protect and Access
 *           Operations" in the Voltage SecureData Simple API Developer
 *           Guide.
 *
 *         params.format
 *
 *           Set this character pointer member to the address of a
 *           null-terminated string that contains the name of the data
 *           protection format to use for the cryptographic operations
 *           associated with this FPE object.
 *
 *           NOTE: If you set a Format-Preserving Hash (FPH) format,
 *                 subsequent protect operations using this object will
 *                 create FPH values and access operations will not be
 *                 allowed. For more information about this capability,
 *                 see the topic "Data Protection Using FPH" in the
 *                 Voltage SecureData Simple API Developer Guide.
 *
 *         params.identity
 *
 *           Set this character pointer member to the address of a
 *           null-terminated string that contains the identity you want
 *           to use for the FPE cryptographic key derivation.
 *
 *           If you are using this FPE object to protect plaintext
 *           using an eFPE format, and your SecureData administrator
 *           has associated an identity with that eFPE format, you can
 *           leave this character pointer set to NULL. The identity
 *           associated with the eFPE format will be used for
 *           cryptographic key derivation. If you do provide an
 *           identity when the eFPE format has an associated identity,
 *           they must be the same identity or an error will result.
 *
 *           NOTE: Key numbers also play a role in the derivation of
 *                 cryptographic keys for eFPE formats. Generally, the
 *                 current key number is automatically used. However,
 *                 you can override this behavior by specifying an
 *                 alternative key number that is valid for the eFPE
 *                 format being used when you call the function
 *                 VeProtect. To do so, set the keyNumber member of the
 *                 parameters structure VeProtectParams to a valid
 *                 alternative key number when you are preparing to
 *                 call the function VeProtect. For more information
 *                 about key numbers and eFPE formats, see the topic
 *                 "Retrieving Key Numbers Used for eFPE" in the
 *                 Voltage SecureData Simple API Developer Guide.
 *
 *           If you are using this FPE object to access ciphertext
 *           using an eFPE format, and that eFPE format has an identity
 *           associated with it, there is no need to set this member.
 *           The key number embedded in the ciphertext, combined with
 *           the identity associated with the eFPE format, allows the
 *           proper cryptographic key to be re-derived. If you do set
 *           this member when an identity is associated with the eFPE
 *           format, they must be the same identity or an error will
 *           result.
 *
 *           If your SecureData administrator has not associated an
 *           identity with the eFPE format, you must specify the
 *           correct identity using this member in order to access the
 *           ciphertext successfully.
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
 *         params.encoding
 *
 *           Optionally set this integer member to one of the following
 *           character encoding constants to establish the character
 *           encoding for FPE plaintext and ciphertext associated with
 *           this FPE object:
 *
 *             - VE_ENCODING_ASCII7
 *
 *             - VE_ENCODING_UTF8
 *
 *           A third setting, the default, for this structure member is
 *           VE_ENCODING_DEFAULT. This setting specifies that the
 *           character encoding established for the associated
 *           LibraryContext object be used for this FPE object.
 *
 *           NOTE: The constant VE_ENCODING_ASCII, one of three
 *                 character encoding constants available in previous
 *                 versions of the Simple API, has been deprecated. Use
 *                 the new constant VE_ENCODING_ASCII7 instead. It is
 *                 the functional equivalent of the deprecated constant
 *                 VE_ENCODING_ASCII.
 *
 *           For more information about the character encoding for the
 *           FPE object, see the topic "Character Encoding" in the
 *           Voltage SecureData Simple API Developer Guide.
 *
 *     fpe
 *
 *       Pass the address of a variable of type VeFPE into which this
 *       function will write the address of the FPE object that it
 *       creates and initializes on your behalf.
 *
 *       NOTE: Set this (pointer) variable to NULL before passing its
 *             address to this function.
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
 *     When an error occurs, no FPE object is returned. Use the
 *     LibraryContext object passed in the ctx parameter to call the
 *     function VeGetErrorDetails.
 *
 *   Remarks:
 *
 *     You will pass the address of the FPE object returned by this
 *     function to several other functions in this interface, including
 *     calls to protect plaintext or access ciphertext, and ending with
 *     a call to the function VeDestroyFPE.
 *
 *     The following functions expect a pointer to an FPE object as a
 *     parameter:
 *
 *       - VeDestroyFPE
 *
 *       - VeProtect
 *
 *       - VeAccess
 *
 *       - VeGetFullIdentity
 *
 *       - VeGetKeyNumbers
 *
 *     An FPE object created using this function can be used for more
 *     than one FPE operation when those operations share certain
 *     characteristics. These characteristics include:
 *
 *       - They use the same LibraryContext object.
 *
 *       - They either protect plaintext or access ciphertext (but not
 *         both).
 *
 *       - They use the same data protection format.
 *
 *       - They use a single identity for key derivation.
 *
 *       - They use the same set of authentication credentials.
 *
 *     Use the parameters structure VeFPEParams to provide the
 *     initialization values for the FPE object when you call the
 *     function VeCreateFPE. To do so, follow these steps:
 *
 *       1. Declare an instance of this structure and assign the
 *          default values to its members using structure assignment
 *          with the static structure VeFPEParamsDefaults:
 *
 *            VeFPEParams fpeArgs = VeFPEParamsDefaults;
 *
 *       2. Explicitly assign values to required members and optionally
 *          to other members to override their default settings. For
 *          example:
 *
 *            fpeArgs.protect = 1;
 *
 *       3. Call the function VeCreateFPE using a previous created
 *          LibraryContext object, the address of this structure, and
 *          the handle used to return the FPE object's address. Make
 *          sure to check the return value.
 */
typedef struct VeFPEParams_v3
{
    int             private1;
    int             private2;
    const char     *private3;
    const char     *private4;
    const char     *private5;
    int             protect;
    int             access;
    int             allowNetEmpty;
    const char     *format;
    const char     *identity;
    const char     *sharedSecret;
    const char     *username;
    const char     *password;
    const char     *clientCertificatePath;
    const char     *clientCertificatePassword;
    int             encoding;
 
} VeFPEParams;

extern VE_DLL_DEF struct VeFPEParams_v3 VeFPEParamsDefaults_v3;

#define VeFPEParamsDefaults VeFPEParamsDefaults_v3

VE_DLL_DEF int VE_CALLING_CONV VeCreateFPE(
    VeLibCtx     ctx,
    VeFPEParams *params,
    VeFPE       *fpe
);
 
/***********************************************************************
 *
 * Function: VeDestroyFPE
 *
 *   Use this function to destroy an FPE object created using the
 *   function VeCreateFPE. This function frees memory and other
 *   resources created internally for the FPE object, but not the
 *   memory or resources used by the LibraryContext object associated
 *   with the FPE object.
 *
 *   Parameters:
 *
 *     fpe
 *
 *       Pass the address of a variable of type VeFPE that contains the
 *       address of the FPE object created by calling the function
 *       VeCreateFPE, and which specifies the FPE object to be
 *       destroyed. After making this call, you can no longer use this
 *       FPE object for making calls to the other functions in this
 *       interface.
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
 *     This function also sets the (pointer) variable specified using
 *     the fpe parameter to NULL before returning. If that variable is
 *     already set to NULL when this function is called, no processing
 *     is performed and the function returns successfully.
 */
VE_DLL_DEF int VE_CALLING_CONV VeDestroyFPE(
    VeFPE *fpe
);

/***********************************************************************
 *
 * Function: VeGetKeyNumbers
 *
 *   Use this function and its associated parameters structure to
 *   retrieve the set of key numbers associated with an embedded FPE
 *   (eFPE) format used by an FPE object that has been initialized for
 *   protect operations.
 *
 *   NOTE: The output memory passed to this function using
 *         params.keyNumbers is an array of integers, not characters or
 *         bytes. Make sure that you allocate this memory accordingly.
 *
 *   Parameters:
 *
 *     fpe
 *
 *       Pass the address of an FPE object created by calling the
 *       function VeCreateFPE. This FPE object must have been
 *       initialized for protect operations, not access operations.
 *       Further, the format specified when the FPE object was created
 *       must be an eFPE format.
 *
 *     params
 *
 *       Pass the address of a properly initialized
 *       VeGetKeyNumbersParams parameters structure. The members of
 *       this structure specify the output buffer for the key numbers
 *       to be returned, the number of keys actually returned, and the
 *       current key number.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.keyNumbers
 *         params.keyNumbersBufferSize
 *
 *           Set this integer pointer and integer to the address of the
 *           start of the output integer array and the length (integer
 *           count) of that array, respectively. This function will use
 *           the length value to avoid writing past the end of the
 *           array. Your goal is to make sure that the output array is
 *           large enough to contain the returned key numbers.
 *
 *           For information about how large the passed keyNumbers
 *           buffer should be, see the topic "Determining Output Buffer
 *           Sizes" in the Voltage SecureData Simple API Developer
 *           Guide.
 *
 *         params.keyNumbersSize
 *
 *           Examine this integer after this function returns in order
 *           to retrieve the number of key numbers written to the array
 *           specified by the keyNumbers member.
 *
 *         params.currentKeyNumber
 *
 *           Examine this integer after this function returns in order
 *           to retrieve the current key number of the eFPE format
 *           associated with this FPE object. This key number will also
 *           be in the set of key numbers returned in the keyNumbers
 *           member.
 *
 *   Return Value:
 *
 *     This function returns zero (0) to indicate successful
 *     completion. To indicate an error, this function returns an
 *     appropriate error code. For information about the meaning of
 *     these codes and their corresponding constants, see the topic
 *     "Error Constants" in the Voltage SecureData Simple API Developer
 *     Guide. This includes the error code that indicates that the
 *     output array was not large enough to contain the set of key
 *     numbers that otherwise would have been returned.
 *
 *     NOTE: The parameters structure members keyNumbers and
 *           keyNumbersSize are also, effectively, return values from
 *           this function in that they are used to return the
 *           resulting array of key numbers to the caller. For more
 *           information, see their descriptions in the Parameters
 *           section above.
 *
 *   Remarks:
 *
 *     The FPE object passed to this function must have been
 *     initialized for protect operations and with the name of an eFPE
 *     format.
 *
 *     Before calling this function to retrieve key numbers, you must
 *     declare an instance of the parameters structure
 *     VeGetKeyNumbersParams and assign the default values to its
 *     members using structure assignment with the static structure
 *     VeGetKeyNumbersParamsDefaults:
 *
 *       VeGetKeyNumbersParams keyNumArgs =
 *                                  VeGetKeyNumbersParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeGetKeyNumbers, passing the address of this structure.
 */
typedef struct VeGetKeyNumbersParams_v1
{
    int                  private1;
    int                  private2;
    unsigned int        *keyNumbers;
    unsigned int         keyNumbersBufferSize;
    unsigned int         keyNumbersSize;
    unsigned int         currentKeyNumber;
} VeGetKeyNumbersParams;

extern VE_DLL_DEF struct VeGetKeyNumbersParams_v1 \
                        VeGetKeyNumbersParamsDefaults_v1;

#define VeGetKeyNumbersParamsDefaults VeGetKeyNumbersParamsDefaults_v1

VE_DLL_DEF int VE_CALLING_CONV VeGetKeyNumbers(
    VeFPE                  fpe,
    VeGetKeyNumbersParams *params
);

#ifdef __cplusplus
}
#endif

#endif /* VEFPE_H */
