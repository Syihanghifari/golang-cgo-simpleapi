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
 * Header File: veibse.h
 *
 *   Include this header file in C source code files in which you will
 *   be protecting plaintext and/or accessing ciphertext using
 *   Identity-Based Symmetric Encryption (IBSE). This header file
 *   defines the VeIBSE object and the functions used to create and
 *   destroy this type of object. It also defines the constants used to
 *   select which IBSE protection type to use.
 ***********************************************************************
 */

#ifndef VEIBSE_H
#define VEIBSE_H

#include "veapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 *
 * Object: VeIBSE
 *
 *   The structure pointer VeIBSE, defined in the header file veibse.h,
 *   serves as the equivalent of the IBSE class and its instantiated
 *   objects in object-oriented implementations of the Simple API. This
 *   object establishes and stores characteristics for a set of similar
 *   IBSE cryptographic operations to be performed using this object.
 *   These characteristics include whether protect or access operations
 *   will be performed, the identity and IBSE protection type to be
 *   used (for protection), authentication credentials for accessing
 *   the Key Server during cryptographic operations, etc.
 *
 *   Create this "object" by calling the function VeCreateIBSE and
 *   destroy it by calling the function VeDestroyIBSE. When you create
 *   a VeIBSE object, you initialize it using a parameters structure,
 *   the address of which gets passed to the function VeCreateIBSE (for
 *   additional information, see the documentation for this function).
 *   Thereafter, you do not directly access the information stored by
 *   this object.
 */
typedef struct VeIBSE_st *VeIBSE;

/***********************************************************************
 *
 * IBSE Protection Type Constants:
 *
 *   Defined in the header file veibse.h, the Simple API provides the
 *   following constants for use with the protectionType member of the
 *   parameters structure VeIBSEParams:
 *
 *   VE_IBSE_AES_EMES
 *
 *     In the VeIBSEParams parameters structure, this value specifies
 *     the use of the Encrypt-Mix-Encrypt (EME*) mode of the AES
 *     algorithm for the lifetime of the IBSE object being created. You
 *     should never need to use this constant explicitly because it is
 *     the default established when you use structure assignment to
 *     assign default values to the members of the VeIBSEParams
 *     parameters structure immediately after allocating it:
 *
 *       VeIBSEParams myIBSEParams = VeIBSEParamsDefaults;
 *
 *   VE_IBSE_AES_CBC
 *
 *     In the VeIBSEParams parameters structure, this value specifies
 *     the use of the Cipher Block Chaining (CBC) mode of the AES
 *     algorithm for the lifetime of the IBSE object being created. Use
 *     this constant to override the default setting for this
 *     structure, the EME* mode, established when you use structure
 *     assignment to assign default values to the members of the
 *     VeIBSEParams parameters structure immediately after allocating
 *     it:
 *
 *       VeIBSEParams myIBSEParams   = VeIBSEParamsDefaults;
 *       myIBSEParams.protectionType = VE_IBSE_AES_CBC;
 *
 *   VE_IBSE_AES_GCM
 *
 *     In the VeIBSEParams parameters structure, this value specifies
 *     the use of the Galois Counter Mode (GCM) mode of the AES
 *     algorithm for the lifetime of the IBSE object being created. Use
 *     this constant to override the default setting for this
 *     structure, the EME* mode, established when you use structure
 *     assignment to assign default values to the members of the
 *     VeIBSEParams parameters structure immediately after allocating
 *     it:
 *
 *       VeIBSEParams myIBSEParams   = VeIBSEParamsDefaults;
 *       myIBSEParams.protectionType = VE_IBSE_AES_GCM;
 *
 *   For more information, see the description of the function
 *   VeCreateIBSE.
 */
#define VE_IBSE_AES_EMES             1001
#define VE_IBSE_AES_CBC              1002
#define VE_IBSE_AES_GCM              1003

/***********************************************************************
 *
 * Function: VeCreateIBSE
 *
 *   Use this function and its associated parameters structure to
 *   create and initialize an IBSE object to manage a particular type
 *   of IBSE operation. After these operations are complete, the IBSE
 *   object created by this function should be destroyed using the
 *   function VeDestroyIBSE.
 *
 *   IBSE objects created using the C language interface to the Simple
 *   API are thread-safe and can safely be shared for similar IBSE
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
 *       Pass the address of a properly initialized VeIBSEParams
 *       parameters structure. The members of this structure specify
 *       various characteristics of the IBSE object being created, such
 *       as whether it will be used for protect or access operations,
 *       the identity from which the cryptographic key will be derived,
 *       the choice of IBSE protection types to use for encryption and
 *       decryption, etc.
 *
 *       To properly initialize this parameters structure, use
 *       structure assignment with the pre-initialized static version
 *       of this structure intended for this purpose:
 *
 *         VeIBSEParams ibseParams = VeIBSEParamsDefaults;
 *
 *       In general, this structure assignment sets members to zero (0
 *       or NULL). For required and conditionally required settings,
 *       the corresponding structure members must be set appropriately
 *       before calling function VeCreateIBSE. For optional settings,
 *       the corresponding structure members may be set.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.access
 *         params.protect
 *
 *           Set one or the other of these integer members to 1 to
 *           specify that this IBSE object is going to be used to
 *           protect plaintext by encrypting it, or access ciphertext
 *           by decrypting it, respectively.
 *
 *           Set one but not both of these structure members.
 *
 *         params.protectionType
 *
 *           For protect operations, optionally set this integer member
 *           to specify the use of the Galois Counter Mode (GCM) or
 *           Cipher Block Chaining (CBC) modes of the AES algorithm.
 *           Use the constants VE_IBSE_AES_GCM and VE_IBSE_AES_CBC,
 *           respectively, to specify the use of the GCM and CBC modes.
 *
 *           A third setting, the default, for this structure member is
 *           VE_IBSE_AES_EMES. This setting specifies the use of the
 *           Encrypt-Mix-Encrypt (EME*) mode of the AES algorithm for
 *           protecting your plaintext.
 *
 *           Because the protection type does not need to be specified
 *           for IBSE access operations (the protection type used when
 *           protecting the plaintext is stored in the IBSE envelope),
 *           if you set the params.access parameter to 1, any
 *           legitimate value you set for this parameter will be
 *           ignored.
 *
 *           For more information about this choice of protection
 *           types, see the topic "Data Protection Using IBSE" in the
 *           Voltage SecureData Simple API Developer Guide.
 *
 *         params.identity
 *
 *           For protect operations, set this character pointer member
 *           to the address of a null-terminated string that contains
 *           the identity you want to use for the cryptographic key
 *           derivation.
 *
 *           Because no identity is needed for IBSE access operations
 *           (the identity used when protecting the plaintext is stored
 *           in the IBSE envelope), if you set the params.access
 *           parameter to 1, any value you set for this parameter will
 *           be ignored.
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
 *     ibse
 *
 *       Pass the address of a variable of type VeIBSE into which this
 *       function will write the address of the IBSE object that it
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
 *     When an error occurs, no IBSE object is returned. Use the
 *     LibraryContext object passed in the ctx parameter to call the
 *     function VeGetErrorDetails.
 *
 *   Remarks:
 *
 *     You will pass the address of this IBSE object created by this
 *     function to several other functions in this interface, including
 *     calls to protect plaintext or access ciphertext, and ending with
 *     a call to the function VeDestroyIBSE.
 *
 *     The following functions expect a pointer to an IBSE object as a
 *     parameter:
 *
 *       - VeDestroyIBSE
 *
 *       - VeProtect
 *
 *       - VeAccess
 *
 *     An IBSE object created using this function can be used for more
 *     than one IBSE operation when those operations share certain
 *     characteristics. These characteristics include:
 *
 *       - They use the same LibraryContext object.
 *
 *       - They either protect plaintext or access ciphertext (but not
 *         both).
 *
 *       - They use the same IBSE protection type.
 *
 *       - They use a single identity for key derivation.
 *
 *       - They use the same set of authentication credentials.
 *
 *     Use the parameters structure VeIBSEParams to provide the
 *     initialization values for the IBSE object when you call the
 *     function VeCreateIBSE. To do so, follow these steps:
 *
 *       1. Declare an instance of this structure and assign the
 *          default values to its members using structure assignment
 *          with the static structure VeIBSEParamsDefaults:
 *
 *            VeIBSEParams ibseArgs = VeIBSEParamsDefaults;
 *
 *       2. Explicitly assign values to required members and optionally
 *          to other members to override their default settings. For
 *          example:
 *
 *            ibseArgs.access = 1;
 *
 *       3. Call the function VeCreateIBSE using a previous created
 *          LibraryContext object, the address of this structure, and
 *          the handle used to return the IBSE object's address. Make
 *          sure to check the return value.
 */

typedef struct VeIBSEParams_v1
{
    int             private1;
    int             private2;
    int             access;
    int             protect;
    int             protectionType;
    const char     *identity;
    const char     *sharedSecret;
    const char     *username;
    const char     *password;
    const char     *clientCertificatePath;
    const char     *clientCertificatePassword;
 
} VeIBSEParams;

extern VE_DLL_DEF struct VeIBSEParams_v1 VeIBSEParamsDefaults_v1;

#define VeIBSEParamsDefaults VeIBSEParamsDefaults_v1

VE_DLL_DEF int VE_CALLING_CONV VeCreateIBSE(
    VeLibCtx      ctx,
    VeIBSEParams *params,
    VeIBSE       *ibse
);

/***********************************************************************
 *
 * Function: VeDestroyIBSE
 *
 *   Use this function to destroy an IBSE object created using the
 *   function VeCreateIBSE. This function frees memory and other
 *   resources created internally for the IBSE object, but not the
 *   memory or resources used by the LibraryContext object associated
 *   with the IBSE object.
 *
 *   Parameters:
 *
 *     ibse
 *
 *       Pass the address of a variable of type VeIBSE that contains
 *       the address of an IBSE object created by calling the function
 *       VeCreateIBSE. This variable specifies the IBSE object to be
 *       destroyed. After making this call, you can no longer use this
 *       IBSE object as a parameter to another function in this
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
 *     the ibse parameter to NULL before returning. If that variable is
 *     already set to NULL when this function is called, no processing
 *     is performed and the function returns successfully.
 */
VE_DLL_DEF int VE_CALLING_CONV VeDestroyIBSE(
    VeIBSE *ibse
);

#ifdef __cplusplus
}
#endif

#endif /* VEIBSE_H */
