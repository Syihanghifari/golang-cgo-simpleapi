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
 * Header File: veapi.h
 *
 *   This header file defines the VeObj and VeLibCtx objects, and for
 *   the latter, the foundational object of the Simple API, the
 *   functions to create and destroy it. Several utility functions, as
 *   well as the primary cryptographic functions VeProtect and
 *   VeAccess, are also defined in this header.
 *
 *   NOTE: The header files for specific Simple API functionality
 *         contain an #include statement for this header file, which
 *         means that it need not be included explicitly.
 ***********************************************************************
 */
#ifndef VEAPI_H
#define VEAPI_H

#include "vedecl.h"
#include "veerror.h"
#include "vsver.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 *
 * Function: VeGetVersion
 *
 *   Use this function to retrieve a string representation of the
 *   Simple API version.
 *
 *   Parameters:
 *
 *     None.
 *
 *   Return Value:
 *
 *     A string representation of the Simple API version. For example:
 *
 *       Simple API 6.20.0
 *
 *     This string remains available for use for the lifetime of your
 *     application.
 *
 *   Remarks:
 *
 *     There is no guarantee regarding the syntax of the returned
 *     string other than that it will be null-terminated.
 *
 *     On Unix and Linux platforms, you can also retrieve a version
 *     string directly from an executable that is statically linked
 *     with the Simple API and from the Simple API dynamic library
 *     libvibesimpledyn.so. For more information, see the topic "Simple
 *     API Version Detection on Unix and Linux" in the Voltage
 *     SecureData Simple API Developer Guide.
 */
VE_DLL_DEF const char* VE_CALLING_CONV VeGetVersion();


/***********************************************************************
 *
 * Function: VeGetVersionNumber
 *
 *   Use this function to retrieve an integer encoding of the Simple
 *   API version number.
 *
 *   Parameters:
 *
 *     None.
 *
 *   Return Value:
 *
 *     An integer that numerically encodes the Simple API version
 *     number. This value allows for client code that performs
 *     differently for older versus newer versions of the Simple API.
 *
 *   Remarks:
 *
 *     The decimal number encoding scheme is:
 *
 *       [1-99][00-99][00-99][00-25]
 *       Major  Minor  Maint  Patch
 *
 *     Using the scheme, version 4.5.0 of the Simple API is numerically
 *     represented as 4050000, and version 6.20.0 of the Simple API is
 *     numerically represented as 6200000 (the lack of a patch
 *     designator is implicitly "a" (4.5.0a), and represented as a pair
 *     of zeros in the least two significant places).
 *
 *     The C language header file vsver.h includes constants for
 *     different versions of the Simple API. For example:
 *
 *       #define VS_SIMPLE_API_VERSION_NUMBER_3_13_0   3130000
 *       #define VS_SIMPLE_API_VERSION_NUMBER_3_13_0b  3130001
 *       #define VS_SIMPLE_API_VERSION_NUMBER_3_13_0c  3130002
 *           .
 *           .
 *           .
 *       #define VE_VERSION_NUMBER_6_0_0               6000000
 *       #define VE_VERSION_NUMBER_6_10_0              6100000
 *       #define VE_VERSION_NUMBER_6_20_0              6200000
 */
VE_DLL_DEF int VE_CALLING_CONV VeGetVersionNumber();

 
/***********************************************************************
 *
 * Object: VeObj
 *
 *   The void pointer VeObj, defined in the header file veapi.h, serves
 *   as the equivalent of a base class for the VeFPE and VeIBSE
 *   objects. This allows these latter two objects to share the
 *   implementation of several functions, such as VeProtect and
 *   VeAccess. There are no functions to create or destroy the object
 *   VeObj.
 */
typedef void *VeObj;

/***********************************************************************
 *
 * Function: VeGetErrorDetails
 *
 *   Use this function to retrieve a descriptive string, including the
 *   error stack, associated with the most recent Simple API error
 *   encountered on the current thread. This string is formatted for
 *   printing.
 *
 *   The Simple API provides the memory for the error string retrieved
 *   by this function.
 *
 *   Parameters:
 *
 *     obj
 *
 *       Pass the address of the LibraryContext, FPE, or IBSE object
 *       created by calling the function VeCreateLibCtx, VeCreateFPE,
 *       or VeCreateIBSE, respectively. Use the object that was passed
 *       to the call that failed, for which you are retrieving error
 *       details.
 *
 *   Return Value:
 *
 *     A character pointer to a null-terminated string that describes
 *     the most recent error, including the error stack, encountered by
 *     the Simple API on the current thread.
 *
 *     Client code can display or copy this string, but the memory
 *     associated with the string is owned by the Simple API.
 *
 *   Remarks:
 *
 *     The error string pointer returned by this function is valid
 *     until the next time you call a Simple API function on the
 *     current thread. After that, dereferencing this pointer has
 *     unpredictable results because the associated memory may have
 *     been freed.
 *
 *     In other words, if you want error details, call this function
 *     immediately after the error has occurred. Further, if you want
 *     to do something with the error details other than immediately
 *     writing them to the console or a log file, make a copy.
 */
VE_DLL_DEF const char* VE_CALLING_CONV VeGetErrorDetails(VeObj obj);


/***********************************************************************
 *
 * Object: VeLibCtx
 *
 *   The structure pointer VeLibCtx, defined in the header file
 *   veapi.h, serves as the equivalent of the LibraryContext class and
 *   objects in object-oriented language implementations of the Simple
 *   API. This object establishes and stores the fundamental context
 *   within which cryptographic operations will be performed. This
 *   includes such configuration settings as the type of caching used,
 *   the location of the Client Policy file provided by the SecureData
 *   Server Infrastructure, information about where trusted root
 *   certificates are stored, etc.
 *
 *   Create this "object" by calling the function VeCreateLibCtx and
 *   destroy it by calling the function VeDestroyLibCtx. When you
 *   create a VeLibCtx object, you initialize it using a parameters
 *   structure, the address of which gets passed to the function
 *   VeCreateLibCtx (for additional information, see the documentation
 *   for this function). Thereafter, you do not directly access the
 *   information stored by this object.
 */
typedef struct VeLibCtx_st *VeLibCtx;

/***********************************************************************
 *
 * Character Set Encoding Constants:
 *
 *   Both the LibraryContext and FPE objects have a setting that
 *   specifies their character encoding for plaintext and ciphertext.
 *   These settings are necessary for the objects to properly interpret
 *   their plaintext and ciphertext input data in the context of the
 *   specified data protection format.
 *
 *   Unless explicitly set to something else, an FPE object character
 *   encoding is set to the special value VE_ENCODING_DEFAULT, which
 *   specifies that the FPE object inherits its character encoding from
 *   its associated LibraryContext object. The default character
 *   encoding for LibraryContext objects is VE_ENCODING_ASCII7, which
 *   specifies 7-bit ASCII characters as potentially subject to
 *   protection, with other characters passing through unchanged.
 *
 *   Defined in the header file veapi.h, the Simple API provides the
 *   following constants for specifying the character set encoding when
 *   creating LibraryContext and FPE objects:
 *
 *   VE_ENCODING_DEFAULT
 *
 *     As the value of the encoding member of the VeFPEParams
 *     parameters structure, this value specifies the use of the
 *     character set encoding already stored in the associated
 *     LibraryContext object. You should never need to use this
 *     constant explicitly because it is the default established when
 *     you use structure assignment to assign default values to the
 *     members of the VeFPEParams parameters structure immediately
 *     after allocating it:
 *
 *       VeFPEParams myFPEParams = VeFPEParamsDefaults;
 *
 *   VE_ENCODING_ASCII
 *
 *     In versions of the Simple API prior to version 5.0, this
 *     character encoding constant was the default value in the
 *     VeLibCtxParams parameters structure. As of version 5.0, it has
 *     been deprecated and replaced by the constant VE_ENCODING_ASCII7,
 *     which has the benefit of being more explicit about its nature.
 *     You should change your code to use the constant
 *     VE_ENCODING_ASCII7 wherever it currently uses the constant
 *     VE_ENCODING_ASCII.
 *
 *   VE_ENCODING_ASCII7
 *
 *     In the VeLibCtxParams parameters structure, this value specifies
 *     the use of the 7-bit ASCII character encoding. You should never
 *     need to use this constant for this structure because it is the
 *     default established when you use structure assignment to assign
 *     default values to the members of the VeLibCtxParams parameters
 *     structure immediately after allocating it:
 *
 *       VeLibCtxParams myLibCtxParams = VeLibCtxParamsDefaults;
 *
 *     In the VeFPEParams parameters structure, this value specifies
 *     the use of the 7-bit ASCII character encoding. You should only
 *     need to use this constant in this structure if you have chosen
 *     to use a different, non-default character encoding for the
 *     associated LibraryContext object and need to override that
 *     choice for this FPE object. For example:
 *
 *       VeLibCtxParams myLibCtxParams = VeLibCtxParamsDefaults;
 *       myLibCtxParams.encoding       = VE_ENCODING_UTF8;
 *           .
 *           .
 *           .
 *       VeFPEParams myFPEParams = VeFPEParamsDefaults;
 *       myFPEParams.encoding    = VE_ENCODING_ASCII7;
 *
 *   VE_ENCODING_UTF8
 *
 *     This character encoding is required when you intend to use a
 *     variable-length string format with extended Unicode code points,
 *     allowing an extended set of characters to be protected when
 *     using such formats, including the following:
 *
 *       - Printable ASCII
 *
 *       - Printable Latin-1 Supplement
 *
 *       - Latin Extended-A
 *
 *       - Euro Sign
 *
 *     For more information, see the topic "FPE2 Support for VLS
 *     Formats with Extended Unicode Code Points" in the Voltage
 *     SecureData Simple API Developer Guide.
 *
 *     In the VeLibCtxParams parameters structure, this value specifies
 *     the use of the UTF-8 character encoding. Use this constant to
 *     override the default setting for this structure, 7-bit ASCII,
 *     established when you use structure assignment to assign default
 *     values to the members of the VeLibCtxParams parameters structure
 *     immediately after allocating it:
 *
 *       VeLibCtxParams myLibCtxParams = VeLibCtxParamsDefaults;
 *       myLibCtxParams.encoding       = VE_ENCODING_UTF8;
 *
 *     In the VeFPEParams parameters structure, this value specifies
 *     the use of the UTF-8 character encoding. As with the
 *     VeLibCtxParams parameters structure, use this constant to
 *     override the default setting for this structure,
 *     VE_ENCODING_DEFAULT, when the associated LibraryContext object
 *     is set to use a different character encoding, such as the
 *     default 7-bit ASCII character encoding:
 *
 *       VeLibCtxParams myLibCtxParams = VeLibCtxParamsDefaults;
 *           .
 *           .
 *           .
 *       VeFPEParams myFPEParams = VeFPEParamsDefaults;
 *       myFPEParams.encoding    = VE_ENCODING_UTF8;
 *
 *   For more information, see the descriptions of the functions
 *   VeCreateLibCtx and VeCreateFPE.
 */
#define VE_ENCODING_DEFAULT             0
#define VE_ENCODING_ASCII7              1
#define VE_ENCODING_EBCDIC_1047         2
#define VE_ENCODING_UTF8                3

/* Deprecated, please use VE_ENCODING_ASCII7 instead. 
 */
#define VE_ENCODING_ASCII               VE_ENCODING_ASCII7

/***********************************************************************
 *
 * Function: VeCreateLibCtx
 *
 *   Use this function and its associated parameters structure to
 *   create and initialize a LibraryContext object for use in
 *   subsequent calls to the Simple API. Typically, you call this
 *   function once at startup.
 *
 *   When you are done with the LibraryContext object, call the
 *   function VeDestroyLibCtx to destroy it.
 *
 *   In general, your application should create and use a single
 *   LibraryContext object. This object is thread-safe and can safely
 *   be shared by multiple FPE and IBSE objects operating in different
 *   threads.
 *
 *   NOTE: Create this object before creating any other Simple API
 *         objects, and destroy it after destroying those other objects.
 *
 *   Parameters:
 *
 *     params
 *
 *       Pass the address of a properly initialized VeLibCtxParams
 *       parameters structure. The members of this structure specify
 *       various characteristics of the LibraryContext object being
 *       created, such as where to find the Client Policy file, caching
 *       choices for cryptographic information, non-default Client
 *       Identifier fields, etc.
 *
 *       To properly initialize this parameters structure, use
 *       structure assignment with the pre-initialized static version
 *       of this structure intended for this purpose:
 *
 *         VeLibCtxParams libCtxParams = VeLibCtxParamsDefaults;
 *
 *       In general, this structure assignment sets members to zero (0
 *       or NULL). For required and conditionally required settings,
 *       the corresponding structure members must be set appropriately
 *       before calling function VeCreateLibCtx. For optional settings,
 *       the corresponding structure members may be set.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.policyURL
 *         params.policyFilePath
 *         params.keyServerHost
 *
 *           Optionally set the keyServerHost character pointer member
 *           to the address of a fully qualified domain name (FQDN) to
 *           be used when requesting cryptographic keys and retrieving
 *           public parameters.
 *
 *           When params.keyServerHost is not set, set either the
 *           policyURL or the policyFilePath character pointer member
 *           (but not both) to the address of the URL string or file
 *           path string, respectively, of the Client Policy file to
 *           use for this LibraryContext object.
 *
 *           When params.keyServerHost is set, optionally set either
 *           the policyURL or the policyFilePath character pointer
 *           member (but not both) to the address of the URL string or
 *           file path string, respectively, of the Client Policy file
 *           to use for this LibraryContext object. If neither the
 *           policyURL member nor the policyFilePath member of this
 *           params structure is set, the FQDN specified by the
 *           keyServerHost member will also be used to construct the
 *           URL for retrieving the Client Policy. For comprehensive
 *           information about valid combinations of these settings,
 *           see the topic "Constructing URLs for the SecureData Server
 *           Infrastructure" in the Voltage SecureData Simple API
 *           Developer Guide.
 *
 *           When provided, these strings must be null-terminated.
 *
 *           Setting the keyServerHost character pointer member to an
 *           empty string ("") is interpreted the same as the default
 *           NULL setting: as though no Key Server hostname is
 *           specified.
 *
 *           For more information about setting an explicit Key Server
 *           hostname and providing the location of the Client Policy,
 *           see the topics "Key Server Hostname" and "Client Policy
 *           Location" in the Voltage SecureData Simple API Developer
 *           Guide.
 *
 *         params.enableMemoryCache
 *         params.fileCachePath
 *
 *           These settings determine whether this LibraryContext
 *           object will cache cryptographic information at all, and if
 *           so, whether caching will be in-memory or file-based. The
 *           default is to use in-memory caching.
 *
 *           To disable all caching, set the enableMemoryCache integer
 *           member to 0. This option is not advised in a production
 *           environment.
 *
 *           To use file-based caching instead of in-memory caching,
 *           set the enableMemoryCache integer member to 0 and set the
 *           fileCachePath character pointer member to the address of a
 *           string containing the path of your chosen cache directory.
 *           Note that the permissions on the specified directory must
 *           be set such that the client application can create
 *           directories and files in it. The directory path string
 *           must be null-terminated.
 *
 *           NOTE: If you specify both file-based caching and in-memory
 *                 caching, file-based caching will be used, with no
 *                 error reported.
 *
 *           For more information about the caching options, see the
 *           topics "Caching Options" and "Type of Caching Used" in the
 *           Voltage SecureData Simple API Developer Guide.
 *
 *         params.trustStorePath
 *
 *           For non-Windows installations, set the trustStorePath
 *           character pointer member to the address of a string that
 *           contains the path to the OpenSSL truststore directory
 *           where your certificates are located. This is generally the
 *           trustStore directory in your installation directory, but
 *           could be a different OpenSSL truststore directory. The
 *           truststore directory path string must be null-terminated.
 *
 *           NOTE: On HPE NonStop OSS and Stratus VOS platforms, the
 *                 Simple API installation includes a single truststore
 *                 file, named TRUSTSTR, that contains the contents of
 *                 all of the .pem files concatenated into this single
 *                 file. On this platform, specify the path to this
 *                 file instead of the path to the trustStore
 *                 directory, and add the prefix "file:" to the
 *                 beginning of the path.
 *
 *           This setting is not relevant to Windows installations.
 *
 *           For more information about the OpenSSL truststore and
 *           trusted root certificates it contains, see the topic
 *           "Truststore Location" in the Voltage SecureData Simple API
 *           Developer Guide.
 *
 *         params.encoding
 *
 *           Optionally set this integer member to character encoding
 *           constant VE_ENCODING_UTF8 to establish an alternative
 *           character encoding for FPE plaintext and ciphertext
 *           associated with this FPE object:
 *
 *             - VE_ENCODING_UTF8
 *
 *           A second setting, the default, for this structure member
 *           is VE_ENCODING_ASCII7.
 *
 *           NOTE: The constant VE_ENCODING_ASCII, one of three
 *                 character encoding constants available in previous
 *                 versions of the Simple API, and the previous default
 *                 value for LibraryContext objects, has been
 *                 deprecated. The new default for LibraryContext
 *                 objects is VE_ENCODING_ASCII7, a functional
 *                 equivalent of VE_ENCODING_ASCII.
 *
 *           For more information about the character encoding for the
 *           LibraryContext object, see the topic "Character Encoding"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *         params.clientIdProduct
 *         params.clientIdProductVersion
 *         params.clientIdOS
 *         params.clientIdOSVersion
 *         params.clientIdDevice
 *         params.clientIdDeviceVersion
 *
 *           Optionally set one or more of these six character pointer
 *           members to the address of non-default strings for the
 *           configurable fields within the Client Identifier. The
 *           Client Identifier is used to identify your application
 *           when requesting cryptographic keys from a Key Server using
 *           this LibraryContext object.
 *
 *           All of these strings, if set, must be null-terminated.
 *
 *           For more information about setting the Client Identifier
 *           fields, including restrictions on the characters that can
 *           be used in each type of field, see the topic "Client
 *           Identifier Fields" in the Voltage SecureData Simple API
 *           Developer Guide.
 *
 *         params.allowShortFPE
 *
 *           Optionally set this integer member to 1 if you want to
 *           allow FPE plaintext associated with this LibraryContext
 *           object to be encrypted, regardless of its bit size.
 *
 *           NOTE: For plaintext shorter than 8 bits, the FPE algorithm
 *                 is not considered cryptographically secure. However,
 *                 in some cases, particularly data masking operations,
 *                 it is better to perform less-than-perfect encryption
 *                 than no encryption at all.
 *
 *           For more information about allowing short FPE plaintext,
 *           see the topic "FPE with Short Plaintext" in the Voltage
 *           SecureData Simple API Developer Guide.
 *
 *         params.allowNonHardwareRNG
 *
 *           Optionally set this integer member to 1 if you want to
 *           allow the use of a non-hardware-based seed value for the
 *           Simple API's pseudo-random number generator (PRNG).
 *
 *           NOTE: Setting this diagnostic parameter to 1 results in
 *                 PRNG seeding with the system time, which is
 *                 generally agreed to be unsuitable for production
 *                 environments.
 *
 *           For more information about PRNG seeding, see the topic
 *           "Random Number Generation" in the Voltage SecureData
 *           Simple API Developer Guide.
 *
 *         params.networkTimeout
 *
 *           Optionally set this integer member to a value between 1
 *           and 300, inclusive, if you want to set a custom network
 *           timeout value, in seconds, for this LibraryContext object.
 *           This timeout value applies to network interactions with
 *           the SecureData Server Infrastructure, including the
 *           download operations for the Client Policy, public
 *           parameters, and cryptographic keys.
 *
 *           The default value is 10 (seconds).
 *
 *           For more information about setting a network timeout
 *           value, see the topic "Network Operation Timeout" in the
 *           Voltage SecureData Simple API Developer Guide.
 *
 *         params.CRLChecking
 *
 *           On Windows, optionally set this integer member to 0 if you
 *           want to disable certificate revocation list (CRL)
 *           checking. This can be important when your Simple API
 *           application on Windows is not able to access the CRL
 *           specified in a trusted root certificate, thereby
 *           preventing communication with your SecureData Server
 *           Infrastructure.
 *
 *           For more information about CRL checking, see the topic
 *           "CRL Checking" in the Voltage SecureData Simple API
 *           Developer Guide.
 *
 *     ctx
 *
 *       Pass the address of a variable of type VeLibCtx that this
 *       function will use to return the address of the LibraryContext
 *       object that it allocates and initializes on your behalf.
 *
 *       NOTE: Set this (pointer) variable to NULL before passing its
 *             address to this function.
 *
 *       You will pass the address of this LibraryContext object to
 *       several other functions in this interface, including calls to
 *       create FPE and IBSE objects, and ending with a call to the
 *       function VeDestroyLibCtx.
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
 *     Even when an error is returned, this function returns the
 *     unsuccessfully created LibraryContext object in the parameter
 *     ctx, which allows you to call the function VeGetErrorDetails
 *     before calling the function VeDestroyLibCtx.
 *
 *   Remarks:
 *
 *     Use the parameters structure VeLibCtxParams to provide the
 *     initialization values for the LibraryContext object when you
 *     call the function VeCreateLibCtx. To do so, follow these steps:
 *
 *       1. Declare an instance of this structure and assign the
 *          default values to its members using structure assignment
 *          with the static structure VeLibCtxParamsDefaults:
 *
 *            VeLibCtxParams libCtxArgs = VeLibCtxParamsDefaults;
 *
 *       2. Explicitly assign values to required members and optionally
 *          to other members to override their default settings. For
 *          example:
 *
 *            libCtxArgs.policyURL = "https://voltage-pp-0000.example...
 *
 *       3. Call the function VeCreateLibCtx using the address of this
 *          structure and the handle used to return the LibraryContext
 *          object's address. Make sure to check the return value.
 */
typedef struct VeLibCtxParams_v3
{
    int             private1;
    int             private2;
    const char     *policyURL;
    const char     *policyFilePath;
    const char     *keyServerHost;
    int             enableMemoryCache;
    const char     *fileCachePath;
    const char     *trustStorePath;
    int             encoding;
    const char     *clientIdProduct;
    const char     *clientIdProductVersion;
    const char     *clientIdOS;
    const char     *clientIdOSVersion;
    const char     *clientIdDevice;
    const char     *clientIdDeviceVersion;
    int             allowShortFPE;
    int             allowNonHardwareRNG;
    int             networkTimeout;
    int             CRLChecking;
    int             diagSSLTrace; /* not implemented */
 
} VeLibCtxParams;

extern VE_DLL_DEF struct VeLibCtxParams_v3 VeLibCtxParamsDefaults_v3;

#define VeLibCtxParamsDefaults VeLibCtxParamsDefaults_v3

VE_DLL_DEF int VE_CALLING_CONV VeCreateLibCtx(
    const VeLibCtxParams *params,
    VeLibCtx             *ctx
);
 
/***********************************************************************
 *
 * Function: VeDestroyLibCtx
 *
 *   Use this function to destroy a LibraryContext object created using
 *   the function VeCreateLibCtx. This function frees memory and other
 *   resources created internally for the LibraryContext object.
 *
 *   Parameters:
 *
 *     ctx
 *
 *       Pass the address of a variable of type VeLibCtx that contains
 *       the address of the LibraryContext object created by calling
 *       the function VeCreateLibCtx, and which specifies the
 *       LibraryContext object to be destroyed. After making this call,
 *       you can no longer use this LibraryContext object for making
 *       calls to the other functions in this interface.
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
 *     the ctx parameter to NULL before returning. If that variable is
 *     already set to NULL when this function is called, no processing
 *     is performed and the function returns successfully.
 */
VE_DLL_DEF int VE_CALLING_CONV VeDestroyLibCtx(VeLibCtx *ctx);
 
/***********************************************************************
 *
 * Function: VeGetFullIdentity
 *
 *   Use this function to retrieve the fully qualified identity from an
 *   FPE object that has been initialized for protect operations and
 *   that does not specify an eFPE format.
 *
 *   Parameters:
 *
 *     obj
 *
 *       Pass the address of an FPE object created by calling the
 *       function VeCreateFPE. This FPE object must have been
 *       initialized for protect operations, not access operations.
 *
 *     identity
 *     identityBufferSize
 *
 *       Pass the address of the start of the output buffer and the
 *       length (in bytes) of that buffer, respectively. This function
 *       will use the length value to avoid writing past the end of the
 *       buffer. Your goal is to make sure that the output buffer is
 *       large enough to contain the full identity to be returned.
 *
 *       The returned full identity will be null-terminated. This
 *       eliminates the need for an identitySize parameter and means
 *       that the output buffer must have room to accommodate this
 *       extra character.
 *
 *       For information about how large the passed identity buffer
 *       should be, see the topic "Determining Output Buffer Sizes" in
 *       the Voltage SecureData Simple API Developer Guide.
 *
 *   Return Value:
 *
 *     This function returns zero (0) to indicate successful
 *     completion. To indicate an error, this function returns an
 *     appropriate error code. For information about the meaning of
 *     these codes and their corresponding constants, see the topic
 *     "Error Constants" in the Voltage SecureData Simple API Developer
 *     Guide. This includes the error code that indicates that the
 *     output buffer was not large enough to contain the
 *     null-terminated full identity that otherwise would have been
 *     returned.
 *
 *     NOTE: The parameters structure member identity is also,
 *           effectively, a return value from this function in that it
 *           is used to return the resulting null-terminated full
 *           identity to the caller. For more information, see its
 *           description in the Parameters section above.
 *
 *   Remarks:
 *
 *     This function is not supported for FPE objects that specify an
 *     eFPE format.
 */
VE_DLL_DEF int VE_CALLING_CONV VeGetFullIdentity(
    VeObj               obj,
    char                *identity,
    unsigned int        identityBufferSize
);

/***********************************************************************
 *
 * Function: VeIsFpeUserDataError
 *
 *   Use this function to determine whether an error condition
 *   encountered by one of the Simple API cryptographic functions when
 *   performing an FPE protect or access operation was due to a problem
 *   with the data itself, such as it not being in the correct format.
 *
 *   Parameters:
 *
 *     status
 *
 *       The integer return value (an error code) from one of the
 *       protect or access functions: VeProtect (FPE only), VeAccess
 *       (FPE only), VeProtectDataRanges, or VeAccessDataRanges.
 *
 *       NOTE: This function is not relevant for IBSE protect and
 *             access operations because any data is acceptable.
 *
 *   Return Value:
 *
 *     An integer that indicates whether the error code passed using
 *     the status parameter is a data error, as follows:
 *
 *       - The value zero (0) indicates that the function that returned
 *         the error code specified by the status parameter failed for
 *         a reason not related to the data to be protected or accessed
 *         (or that the function succeeded).
 *
 *       - The value one (1) indicates that the function that returned
 *         the error code specified by the status parameter failed for
 *         a reason directly related to the data to be protected or
 *         accessed (such as it not being in the correct format).
 *
 *   Remarks:
 *
 *     This function is useful when your application wants to process
 *     bad data in a different way than other errors. Using it instead
 *     of checking for individual error codes returned by the Simple
 *     API allows your code to be more adaptable to any future bad data
 *     error codes that are introduced.
 */
VE_DLL_DEF int VE_CALLING_CONV VeIsFpeUserDataError(
    int status
);


/***********************************************************************
 *
 * Function: VeProtect
 *
 *   Use this function and its associated parameters structure to
 *   protect plaintext according to the encryption parameters
 *   established for the specified FPE or IBSE object and specified in
 *   this function's params structure.
 *
 *   Parameters:
 *
 *     obj
 *
 *       Pass the address of an FPE or IBSE object created by calling
 *       the function VeCreateFPE or VeCreateIBSE, respectively. This
 *       object must have been initialized for protect operations.
 *
 *     params
 *
 *       Pass the address of a structure of type VeProtectParams that
 *       has been initialized appropriately. This includes the address
 *       and length of the plaintext to be protected, output buffer
 *       information for the resulting ciphertext, etc.
 *
 *       To properly initialize this parameters structure, use
 *       structure assignment with the pre-initialized static version
 *       of this structure intended for this purpose:
 *
 *         VeProtectParams protectParams = VeProtectParamsDefaults;
 *
 *       In general, this structure assignment sets members to zero (0
 *       or NULL). For required settings, the corresponding structure
 *       members must be set appropriately before calling function
 *       VeProtect. For optional settings, the corresponding structure
 *       members may be set.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.plaintext
 *         params.plaintextSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the input plaintext buffer and the length of
 *           the plaintext in that buffer, respectively. The length of
 *           the plaintext is interpreted strictly according to the
 *           specified size and not according to any null-termination
 *           otherwise used.
 *
 *           NOTE: Setting the plaintextSize member to 0 is not
 *                 considered an error, and will produce ciphertext of
 *                 length 0. When the plaintextSize member is set to 0
 *                 to indicate no input, the plaintext member must
 *                 still be set to a non-null value.
 *
 *         params.tweak
 *         params.tweakSize
 *
 *           When performing an FPE protect operation, optionally set
 *           this character pointer and integer to the address of the
 *           start of the input tweak buffer and the length of the
 *           tweak string in that buffer, respectively. The length of
 *           the tweak string is interpreted strictly according to the
 *           specified size and not according to any null-termination
 *           otherwise used.
 *
 *           By default, when the params structure is properly
 *           initialized, the tweakSize member is set to 0, indicating
 *           that tweaking should not be performed.
 *
 *           For more information about using tweak values for FPE
 *           operations, see the topic "FPE Support for Tweak Values"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *         params.ciphertext
 *         params.ciphertextBufferSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the output ciphertext buffer and the length
 *           (in bytes) of that buffer, respectively. This function
 *           will use the length value to avoid writing past the end of
 *           the buffer. Your goal is to make sure that the output
 *           buffer is large enough to contain the produced ciphertext.
 *
 *           For information about how large the passed ciphertext
 *           buffer should be, see the topic "Determining Output Buffer
 *           Sizes" in the Voltage SecureData Simple API Developer
 *           Guide.
 *
 *         params.ciphertextSize
 *
 *           Examine this integer after this function returns in order
 *           to retrieve the length (in bytes) of the resulting
 *           ciphertext written to the buffer specified by the
 *           ciphertext member.
 *
 *         params.keyNumber
 *
 *           If you are performing FPE, and your named format is an
 *           eFPE format, you can set this integer to a key number that
 *           will be used to derive the cryptographic key required to
 *           protect the specified plaintext.
 *
 *           For information about how to retrieve the key numbers that
 *           are currently defined for a particular format, see the
 *           topic "Retrieving Key Numbers Used for eFPE" in the
 *           Voltage SecureData Simple API Developer Guide and the
 *           function VeGetKeyNumbers.
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
 *     NOTE: The parameters structure members ciphertext and
 *           ciphertextSize are also, effectively, return values from
 *           this function in that they are used to return the
 *           resulting ciphertext to the caller. For more information,
 *           see their descriptions in the Parameters section above.
 *
 *   Remarks:
 *
 *     Before calling this function to protect plaintext, you must
 *     declare an instance of the parameters structure VeProtectParams
 *     and assign the default values to its members using structure
 *     assignment with the static structure VeProtectParamsDefaults:
 *
 *       VeProtectParams protectArgs = VeProtectParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeProtect, passing the address of this structure.
 *
 *     When the FPE or IBSE object was created, a number of protection
 *     parameters were specified (using the parameters structure
 *     VeFPEParams or VeIBSEParams) that remain static for the lifetime
 *     of that object. This includes information such as:
 *
 *       - The fact that this FPE or IBSE object is being used for
 *         protect operations
 *
 *       - The LibraryContext object that governs these protect
 *         operations
 *
 *       - The identity to be used for cryptographic key derivation
 *
 *       - The name of the format for FPE
 *
 *       - Authentication credentials for communicating with the Key
 *         Server
 *
 *     If you are using the FPE or IBSE object in a loop to protect a
 *     number of similar plaintexts, these are the parameters that do
 *     not vary from one encryption to the next.
 *
 *     On the other hand, the parameters structure VeProtectParams,
 *     specified for each protect operation, is used to specify the
 *     protection parameters that will vary from one protect operation
 *     to the next. This includes the plaintext itself, information
 *     about the ciphertext output buffer you provide, and for eFPE
 *     protect operations, possibly a key number.
 *
 *     Possible pseudo-code for using this function is:
 *
 *       1. Create and initialize the FPE or IBSE object.
 *
 *       2. Allocate and initialize the parameters structure.
 *
 *       3. Start looping.
 *
 *          a. Update the parameters structure with the plaintext for
 *             this iteration, the output buffer for this iteration (if
 *             different), and any other parameters that can vary for
 *             each iteration (such as the tweak value).
 *
 *          b. Call the function VeProtect.
 *
 *          c. Process errors and output from function VeProtect.
 *             Output processing might consist of copying or otherwise
 *             saving the resulting ciphertext to a more permanent
 *             location, etc.
 *
 *          d. If not done, iterate through the loop again.
 *
 *       4. As appropriate, free the parameters structure and destroy
 *          the FPE or IBSE object.
 *
 *     If an FPE object is passed to this function that specifies a
 *     Format-Preserving Hash (FPH) format, this protect operation will
 *     create an FPH value which cannot subsequently be accessed. For
 *     more information about this capability, see the topic "Data
 *     Protection Using FPH" in the Voltage SecureData Simple API
 *     Developer Guide.
 */
 typedef struct VeProtectParams_v3
{
    int                  private1;
    int                  private2;
    void                *private3;
    const char          *private4;
    const char          *private5;
    const unsigned char *plaintext;
    unsigned int         plaintextSize;
    const unsigned char *tweak;
    unsigned int         tweakSize;
    unsigned char       *ciphertext;
    unsigned int         ciphertextBufferSize;
    unsigned int         ciphertextSize;
    int                  keyNumber;
 
} VeProtectParams;

extern VE_DLL_DEF struct VeProtectParams_v3 VeProtectParamsDefaults_v3;

#define VeProtectParamsDefaults VeProtectParamsDefaults_v3

VE_DLL_DEF int VE_CALLING_CONV VeProtect(
    VeObj                obj,
    VeProtectParams     *params
);


/***********************************************************************
 *
 * Function: VeAccess
 *
 *   Use this function and its associated parameters structure to
 *   access ciphertext according to the decryption parameters
 *   established for the specified FPE or IBSE object and specified in
 *   this function's params structure.
 *
 *   Parameters:
 *
 *     obj
 *
 *       Pass the address of an FPE or IBSE object created by calling
 *       the function VeCreateFPE or VeCreateIBSE, respectively. This
 *       object must have been initialized for access operations.
 *
 *     params
 *
 *       Pass the address of a structure of type VeAccessParams that
 *       has been initialized appropriately. This includes the address
 *       and length of the ciphertext to be accessed, output buffer
 *       information for the recovered plaintext, etc.
 *
 *       To properly initialize this parameters structure, use
 *       structure assignment with the pre-initialized static version
 *       of this structure intended for this purpose:
 *
 *         VeAccessParams accessParams = VeAccessParamsDefaults;
 *
 *       In general, this structure assignment sets members to zero (0
 *       or NULL). For required settings, the corresponding structure
 *       members must be set appropriately before calling function
 *       VeAccess. For optional settings, the corresponding structure
 *       members may be set.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.ciphertext
 *         params.ciphertextSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the input buffer and the length of the
 *           ciphertext in that buffer, respectively. The length of the
 *           ciphertext is interpreted strictly according to the
 *           specified size and not according to any null-termination
 *           otherwise used.
 *
 *           NOTE: Setting the ciphertextSize member to 0, indicating
 *                 an empty ciphertext buffer, is not considered an
 *                 error, and will recover plaintext of length 0, as
 *                 expected. When the ciphertextSize member is set to 0
 *                 to indicate no input, the ciphertext member must
 *                 still be set to point at a legitimate, although
 *                 possibly empty, ciphertext buffer.
 *
 *         params.tweak
 *         params.tweakSize
 *
 *           When performing an FPE access operation, optionally set
 *           this character pointer and integer to the address of the
 *           start of the input tweak buffer and the length of the
 *           tweak string in that buffer, respectively. The length of
 *           the tweak string is interpreted strictly according to the
 *           specified size and not according to any null-termination
 *           otherwise used.
 *
 *           By default, when the params structure is properly
 *           initialized, the tweakSize member is set to 0, indicating
 *           that tweaking should not be performed.
 *
 *           NOTE: Tweaking may be used in conjunction with masking.
 *
 *           For more information about using tweak values for FPE
 *           operations, see the topic "FPE Support for Tweak Values"
 *           in the Voltage SecureData Simple API Developer Guide.
 *
 *         params.plaintext
 *         params.plaintextBufferSize
 *
 *           Set this character pointer and integer to the address of
 *           the start of the output plaintext buffer and the length
 *           (in bytes) of that buffer, respectively. This function
 *           will use the length value to avoid writing past the end of
 *           the buffer. Your goal is to make sure that the output
 *           buffer is large enough to contain the recovered plaintext.
 *
 *           When the masked member (see below) is set to 1, the
 *           plaintext output will be masked as appropriate for the
 *           specified format before it is written to this buffer.
 *
 *           For information about how large the passed plaintext
 *           buffer should be, see the topic "Determining Output Buffer
 *           Sizes" in the Voltage SecureData Simple API Developer
 *           Guide.
 *
 *         params.plaintextSize
 *
 *           Examine this integer after this function returns in order
 *           to retrieve the length (in bytes) of the recovered
 *           plaintext written to the buffer specified by the plaintext
 *           member.
 *
 *         params.masked
 *
 *           Set this integer member to 1 to enable the masking of
 *           output plaintext for this FPE object during access
 *           operations. By default, when this structure is properly
 *           initialized, the masked member is set to 0, indicating
 *           that masking should not be performed. When the masked
 *           member is set to 1, before returning the recovered
 *           plaintext, it will be masked according to the masking rule
 *           associated with the specified format.
 *
 *           NOTE: Masking may be used in conjunction with tweaking.
 *
 *           For more information about using masking for FPE access
 *           operations, see the topic "Masking for Accessed FPE
 *           Ciphertext" in the Voltage SecureData Simple API Developer
 *           Guide.
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
 *     NOTE: The parameters structure members plaintext and
 *           plaintextSize are also, effectively, return values from
 *           this function in that they are used to return the
 *           recovered plaintext (masked as appropriate for the
 *           specified format, when specified) to the caller. For more
 *           information, see their descriptions in the Parameters
 *           section above.
 *
 *   Remarks:
 *
 *     Before calling this function to access ciphertext, you must
 *     declare an instance of the parameters structure VeAccessParams
 *     and assign the default values to its members using structure
 *     assignment with the static structure VeAccessParamsDefaults:
 *
 *       VeAccessParams accessArgs = VeAccessParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeAccess, passing the address of this structure.
 *
 *     When the FPE or IBSE object was created, a number of decryption
 *     parameters were specified (using the parameters structure
 *     VeFPEParams or VeIBSEParams) that remain static for the lifetime
 *     of that object. This includes information such as:
 *
 *       - The fact that this FPE or IBSE object is being used for
 *         access operations
 *
 *       - The LibraryContext object that governs these access
 *         operations
 *
 *       - The identity to be used for cryptographic key derivation
 *
 *       - The name of the format for FPE
 *
 *       - Authentication credentials for communicating with the Key
 *         Server
 *
 *       - The Boolean that controls whether the returned plaintext
 *         should be masked
 *
 *     If you are using the FPE or IBSE object in a loop to access a
 *     number of similar ciphertexts, these are the parameters that do
 *     not vary from one decryption to the next.
 *
 *     On the other hand, the parameters structure VeAccessParams is
 *     used to specify the decryption parameters that will vary from
 *     one decryption to the next. This includes the ciphertext itself,
 *     an optional tweak string, and information about the plaintext
 *     output buffer you provide.
 *
 *     Possible pseudo-code for using this function is:
 *
 *       1. Create and initialize the FPE or IBSE object.
 *
 *       2. Allocate and initialize the parameters structure.
 *
 *       3. Start looping.
 *
 *          a. Update the parameters structure with the ciphertext for
 *             this iteration, the output buffer for this iteration (if
 *             different), and any other parameters that can vary for
 *             each iteration (such as the tweak value).
 *
 *          b. Call the function VeAccess.
 *
 *          c. Process errors and output from function VeAccess. Output
 *             processing might consist of copying or otherwise saving
 *             the resulting plaintext to a more permanent location,
 *             etc.
 *
 *          d. If not done, iterate through the loop again.
 *
 *       4. As appropriate, free the parameters structure and destroy
 *          the FPE or IBSE object.
 *
 *     If an FPE object is passed to this function that specifies a
 *     Format-Preserving Hash (FPH) format, any attempt to perform an
 *     access operation will fail. For more information about this
 *     capability, see the topic "Data Protection Using FPH" in the
 *     Voltage SecureData Simple API Developer Guide.
 */

typedef struct VeAccessParams_v3
{
    int                  private1;
    int                  private2;
    void                *private3;
    const char          *private4;
    const char          *private5;
    const unsigned char *ciphertext;
    unsigned int         ciphertextSize;
    const unsigned char *tweak;
    unsigned int         tweakSize;
    unsigned char       *plaintext;
    unsigned int         plaintextBufferSize;
    unsigned int         plaintextSize;
    int                  masked;
 
} VeAccessParams;


extern VE_DLL_DEF struct VeAccessParams_v3 VeAccessParamsDefaults_v3;

#define VeAccessParamsDefaults VeAccessParamsDefaults_v3

VE_DLL_DEF int VE_CALLING_CONV VeAccess(
    VeObj                obj,
    VeAccessParams      *params
);

/***********************************************************************
 * Pointers to arrays of both of the following byte array
 * structures are used by the functions VeProtectDataRanges
 * and VeAccessDataRanges, and specifically, in their parameter
 * structures - see below.
 */
typedef struct VeByteArray_v1 
{
    unsigned char *ptr;
    unsigned int   size;       /* returned size */
    unsigned int   bufferSize; /* "capacity" */
} VeByteArray;

typedef struct VeConstByteArray_v1
{
    const unsigned char *ptr;
    unsigned int         size;
} VeConstByteArray;

/***********************************************************************
 *
 * Function: VeProtectDataRanges
 *
 *   Use this function and its associated parameters structure to
 *   protect a sequence of plaintext datetimes, preserving the deltas
 *   between them, according to the encryption parameters established
 *   for the specified FPE object and specified in the parameters
 *   structure.
 *
 *   NOTE: Use this function to obscure the specifics of a sequence of
 *         datetimes while preserving the time spans between them. An
 *         example of how this might be useful is an analysis of the
 *         time span between medical tests, while protecting the
 *         specific datetimes in client records.
 *
 *         The name of this function is VeProtectDataRanges rather than
 *         VeProtectDateRanges to allow for future extension to other
 *         data types.
 *
 *   Parameters:
 *
 *     fpeProtect
 *
 *       Pass the address of an FPE object created by calling the
 *       function VeCreateFPE. This object must have been initialized
 *       for protect operations using a centrally defined date format
 *       (note that if your date format includes a year field, it must
 *       not be a two-digit year).
 *
 *     params
 *
 *       Pass the address of a structure of type
 *       VeProtectDataRangeParams that has been initialized
 *       appropriately. This includes the address and length of the
 *       plaintexts to be protected, output buffer information for the
 *       resulting ciphertexts, etc.
 *
 *       To properly initialize this parameters structure, use
 *       structure assignment with the pre-initialized static version
 *       of this structure intended for this purpose:
 *
 *         VeProtectDataRangesParams protectArgDates =
 *                                    VeProtectDataRangesParamsDefaults;
 *
 *       In general, this structure assignment sets members to zero (0
 *       or NULL). For required settings, the corresponding structure
 *       members must be set appropriately before calling function
 *       VeProtectDataRanges.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.plaintexts
 *         params.ciphertexts
 *         params.numElements
 *
 *           For a given number of plaintexts, N, to be protected:
 *
 *           Set the params.plaintexts structure pointer to the address
 *           of the first element in an array of exactly N
 *           VeConstByteArray structures.
 *
 *           Set the params.ciphertexts structure pointer to the
 *           address of the first element in an array of exactly N
 *           VeByteArray structures.
 *
 *           Set the integer params.numElements to N.
 *
 *         params.plaintexts[i].ptr
 *         params.plaintexts[i].size
 *
 *           Set these byte pointers and integers to the addresses of
 *           the start of each input plaintext buffer and the length of
 *           the plaintext in each buffer, respectively. The length of
 *           the plaintext is interpreted strictly according to the
 *           specified size and not according to any null-termination
 *           otherwise used.
 *
 *           There are N instances of these input parameters where i
 *           ranges from 0 to N-1.
 *
 *           NOTE: Setting the params.plaintexts[i].size member to 0 is
 *                 not considered an error, and will produce ciphertext
 *                 of length 0, as expected. Although no data at this
 *                 address will be examined, the
 *                 params.plaintexts[i].ptr member must be non-null.
 *
 *         params.ciphertexts[i].ptr
 *         params.ciphertexts[i].bufferSize
 *
 *           Set these byte pointers and integers to the addresses of
 *           the start of each output ciphertext buffer and the length
 *           (in bytes) of each buffer, respectively. This function
 *           will use these length values to avoid writing past the end
 *           of these buffers. Your goal is to make sure that these
 *           output buffers are large enough to contain the produced
 *           ciphertext.
 *
 *           Although it is not strictly required that all of the
 *           output buffers are the same size, there is no good reason
 *           for them not to be. Therefore, this function will return
 *           an error if all of the params.ciphertexts[i].bufferSize
 *           values are not the same, as well as when they specify
 *           buffers not sufficiently large to contain the resulting
 *           ciphertext.
 *
 *           For information about how large the passed ciphertext
 *           buffers should be, see the topic "Determining Output
 *           Buffer Sizes" in the Voltage SecureData Simple API
 *           Developer Guide.
 *
 *         params.ciphertexts[i].size
 *
 *           Examine these integers after this function returns in
 *           order to retrieve the length (in bytes) of the resulting
 *           ciphertexts written to the buffers specified by the
 *           params.ciphertexts[i].ptr members.
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
 *     NOTE: The parameters structure members params.ciphertexts[i].ptr
 *           and params.ciphertexts[i].size are also, effectively,
 *           return values from this function in that they are used to
 *           return the resulting ciphertext to the caller. For more
 *           information, see their descriptions in the Parameters
 *           section above.
 *
 *   Remarks:
 *
 *     For information about the datetime limits that the Simple API
 *     imposes on the plaintext and ciphertext values consumed and
 *     produced by this function, see the topic "FPE Support for Date
 *     Range Protection" in the Voltage SecureData Simple API Developer
 *     Guide.
 *
 *     Before calling this function to protect a sequence of plaintext
 *     datetimes, you must declare an instance of the parameters
 *     structure VeProtectDataRangesParams and assign the default
 *     values to its members using structure assignment with the static
 *     structure VeProtectDataRangesParamsDefaults:
 *
 *       VeProtectDataRangesParams protectDRArgs =
 *                                    VeProtectDataRangesParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeProtectDataRange, passing the address of this structure.
 *
 *     When the FPE object was created, a number of encryption
 *     parameters were established that remain static for the lifetime
 *     of that object. This includes information such as:
 *
 *       - The fact that this FPE object is being used for protect
 *         operations
 *
 *       - The LibraryContext object that governs these protect
 *         operations
 *
 *       - The identity to be used for key derivation
 *
 *       - The name of the centrally defined date format
 *
 *       - Authentication credentials for communicating with the Key
 *         Server
 *
 *     If you are using the FPE object in a loop to protect a number of
 *     similar sequences of plaintext datetimes, these are the
 *     parameters that do not vary from one encryption to the next.
 *
 *     On the other hand, the parameters structure
 *     VeProtectDataRangesParams is used to specify the encryption
 *     parameters that will vary from one encryption to the next. This
 *     includes the plaintext datetime sequence itself and information
 *     about the ciphertext output buffers you provide.
 *
 *     Possible pseudo-code for using this function is:
 *
 *       1. Create and initialize the FPE object.
 *
 *       2. Initialize the parameters structure (typically allocated on
 *          the stack).
 *
 *       3. Start looping.
 *
 *          a. Update the parameters structure with the plaintext
 *             datetime sequence for this iteration and the output
 *             buffers for this iteration (if different).
 *
 *          b. Call the function VeProtectDataRanges.
 *
 *          c. Process errors and output from function
 *             VeProtectDataRanges. Output processing might consist of
 *             copying or otherwise saving the resulting ciphertext
 *             datetimes to a more permanent location, etc.
 *
 *          d. If not done, iterate through the loop again.
 *
 *       4. As appropriate, free any allocated data associated with the
 *          parameters structure and destroy the FPE object.
 */
typedef struct VeProtectDataRangesParams_v1
{
    int                     private1;
    int                     private2;
    const VeConstByteArray *plaintexts;  /* in */
    VeByteArray            *ciphertexts; /* out */
    unsigned int            numElements; /* applies to both arrays */
} VeProtectDataRangesParams;

extern VE_DLL_DEF struct VeProtectDataRangesParams_v1 \
       VeProtectDataRangesParamsDefaults_v1;

#define VeProtectDataRangesParamsDefaults \
        VeProtectDataRangesParamsDefaults_v1

VE_DLL_DEF int VE_CALLING_CONV VeProtectDataRanges(
    VeObj                      fpeProtect,
    VeProtectDataRangesParams *params
);


/***********************************************************************
 *
 * Function: VeAccessDataRanges
 *
 *   Use this function and its associated parameters structure to
 *   recover a sequence of plaintext datetimes according to the
 *   decryption parameters established for the specified FPE object and
 *   specified in the parameters structure.
 *
 *   NOTE: The name of this function is VeAccessDataRanges rather than
 *         VeAccessDateRanges to allow for future extension to other
 *         data types.
 *
 *   Parameters:
 *
 *     fpeAccess
 *
 *       Pass the address of an FPE object created by calling the
 *       function VeCreateFPE. This object must have been initialized
 *       for access operations using a centrally defined date format
 *       (note that if your date format includes a year field, it must
 *       not be a two-digit year).
 *
 *     params
 *
 *       Pass the address of a structure of type
 *       VeAccessDataRangeParams that has been initialized
 *       appropriately. This includes the address and length of the
 *       ciphertexts to be accessed, output buffer information for the
 *       recovered plaintexts, etc.
 *
 *       To properly initialize this parameters structure, use
 *       structure assignment with the pre-initialized static version
 *       of this structure intended for this purpose:
 *
 *         VeAccessDataRangesParams accessArgDates =
 *                                     VeAccessDataRangesParamsDefaults;
 *
 *       In general, this structure assignment sets members to zero (0
 *       or NULL). For required settings, the corresponding structure
 *       members must be set appropriately before calling function
 *       VeAccessDataRanges.
 *
 *       The members of this structure are as follows:
 *
 *         params.privateN
 *
 *           Reserved for internal use. Do not set, or attempt to
 *           interpret, these values.
 *
 *         params.ciphertexts
 *         params.plaintexts
 *         params.numElements
 *
 *           For a given number of ciphertexts, N, to be accessed:
 *
 *           Set the params.ciphertexts structure pointer to the
 *           address of the first element in an array of exactly N
 *           VeConstByteArray structures.
 *
 *           Set the params.plaintexts structure pointer to the address
 *           of the first element in an array of exactly N VeByteArray
 *           structures.
 *
 *           Set the integer params.numElements to N.
 *
 *         params.ciphertexts[i].ptr
 *         params.ciphertexts[i].size
 *
 *           Set these byte pointers and integers to the addresses of
 *           the start of each input ciphertext buffer and the length
 *           of the ciphertext in each buffer, respectively. The length
 *           of the ciphertext is interpreted strictly according to the
 *           specified size and not according to any null-termination
 *           otherwise used.
 *
 *           There are N instances of these input parameters where i
 *           ranges from 0 to N-1.
 *
 *           NOTE: Setting the params.ciphertexts[i].size member to 0
 *                 is not considered an error, and will recover
 *                 plaintext of length 0, as expected. Although no data
 *                 at this address will be examined, the
 *                 params.ciphertexts[i].ptr member must be non-null.
 *
 *         params.plaintexts[i].ptr
 *         params.plaintexts[i].bufferSize
 *
 *           Set these byte pointers and integers to the addresses of
 *           the start of each output plaintext buffer and the length
 *           (in bytes) of each buffer, respectively. This function
 *           will use these length values to avoid writing past the end
 *           of these buffers. Your goal is to make sure that these
 *           output buffers are large enough to contain the recovered
 *           plaintext.
 *
 *           Although it is not strictly required that all of the
 *           output buffers are the same size, there is no good reason
 *           for them not to be. Therefore, this function will return
 *           an error if all of the params.plaintexts[i].bufferSize
 *           values are not the same, as well as when they specify
 *           buffers not sufficiently large to contain the recovered
 *           plaintext.
 *
 *           For information about how large the passed plaintext
 *           buffers should be, see the topic "Determining Output
 *           Buffer Sizes" in the Voltage SecureData Simple API
 *           Developer Guide.
 *
 *         params.ciphertexts[i].size
 *
 *           Examine these integers after this function returns in
 *           order to retrieve the length (in bytes) of the recovered
 *           plaintexts written to the buffers specified by the
 *           params.plaintexts[i].ptr members.
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
 *     NOTE: The parameters structure members params.plaintexts[i].ptr
 *           and params.plaintexts[i].size are also, effectively,
 *           return values from this function in that they are used to
 *           return the recovered plainstext to the caller. For more
 *           information, see their descriptions in the Parameters
 *           section above.
 *
 *   Remarks:
 *
 *     For information about the datetime limits that the Simple API
 *     imposes on the plaintext and ciphertext values consumed and
 *     produced by this function, see the topic "FPE Support for Date
 *     Range Protection" in the Voltage SecureData Simple API Developer
 *     Guide.
 *
 *     Before calling this function to access a sequence of ciphertext
 *     datetimes, you must declare an instance of the parameters
 *     structure VeAccessDataRangeParams and assign the default values
 *     to its members using structure assignment with the static
 *     structure VeAccessDataRangesParamsDefaults:
 *
 *       VeAccessDataRangesParams accessDRArgs =
 *                                     VeAccessDataRangesParamsDefaults;
 *
 *     After initializing the parameters structure with its default
 *     values, explicitly set all required parameters by setting the
 *     appropriate structure member. Set optional structure members
 *     only when you want to use a non-default setting. After the
 *     parameters structure is fully initialized, call the function
 *     VeAccessDataRanges, passing the address of this structure.
 *
 *     When the FPE object was created, a number of encryption
 *     parameters were established that remain static for the lifetime
 *     of that object. This includes information such as:
 *
 *       - The fact that this FPE object is being used for access
 *         operations
 *
 *       - The LibraryContext object that governs these access
 *         operations
 *
 *       - The identity to be used for key derivation
 *
 *       - The name of the centrally defined date format
 *
 *       - Authentication credentials for communicating with the Key
 *         Server
 *
 *     If you are using the FPE object in a loop to access a number of
 *     similar sequences of ciphertext datetimes, these are the
 *     parameters that do not vary from one decryption to the next.
 *
 *     On the other hand, the parameters structure
 *     VeAccessDataRangesParams is used to specify the decryption
 *     parameters that will vary from one decryption to the next. This
 *     includes the ciphertext datetime sequence itself and information
 *     about the plaintext output buffers you provide.
 *
 *     Possible pseudo-code for using this function is:
 *
 *       1. Create and initialize the FPE object.
 *
 *       2. Initialize the parameters structure (typically allocated on
 *          the stack).
 *
 *       3. Start looping.
 *
 *          a. Update the parameters structure with the ciphertext
 *             datetime sequence for this iteration and the output
 *             buffers for this iteration (if different).
 *
 *          b. Call the function VeAccessDataRanges.
 *
 *          c. Process errors and output from function
 *             VeAccessDataRanges. Output processing might consist of
 *             copying or otherwise saving the recovered plaintext
 *             datetimes to a more permanent location, etc.
 *
 *          d. If not done, iterate through the loop again.
 *
 *       4. As appropriate, free any allocated data associated with the
 *          parameters structure and destroy the FPE object.
 */
typedef struct VeAccessDataRangesParams_v1
{
      int                     private1;
      int                     private2;
      const VeConstByteArray *ciphertexts; /* in */
      VeByteArray            *plaintexts;  /* out */
      unsigned int            numElements; /* applies to both arrays */
} VeAccessDataRangesParams;

extern VE_DLL_DEF struct VeAccessDataRangesParams_v1
                         VeAccessDataRangesParamsDefaults_v1;

#define VeAccessDataRangesParamsDefaults    \
        VeAccessDataRangesParamsDefaults_v1

VE_DLL_DEF int VE_CALLING_CONV VeAccessDataRanges(
    VeObj                     fpeAccess,
    VeAccessDataRangesParams *params
);

/***********************************************************************
 *
 * Function: VeGetLocalUsage
 *
 *   Use this function to retrieve a buffer containing JSON-formatted
 *   local usage data. This returned usage data includes counts for
 *   protect and access operations for the specified LibraryContext
 *   object since either A) the creation of the LibraryContext object,
 *   or B) the previous call to this function.
 *
 *   These counts are organized according to unique combinations of A)
 *   the data protection format, B) the full identity used when
 *   deriving cryptographic keys, C) the authentication method, and D)
 *   when the authentication method is username and password, the
 *   username.
 *
 *   For conceptual information about retrieving usage data, including
 *   the JSON format in which it is returned, see the topic "Retrieving
 *   Local Usage Data" in the Voltage SecureData Simple API Developer
 *   Guide.
 *
 *   Parameters:
 *
 *     libctx
 *
 *       Pass the address of the LibraryContext object, created by
 *       calling the function VeCreateLibCtx, for which you want to
 *       retrieve usage data.
 *
 *     json
 *
 *       Pass the address of a character pointer, which when
 *       successful, this function will set the address of a character
 *       buffer that contains the JSON-formatted local usage data to be
 *       returned.
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
 *     When you are finished processing the JSON data in the returned
 *     character buffer, deallocate it using function
 *     VeDestroyLocalUsageBuffer.
 */
VE_DLL_DEF int VeGetLocalUsage(VeLibCtx ctx, const char **jsonBuffer);

/***********************************************************************
 *
 * Function: VeDestroyLocalUsageBuffer
 *
 *   Use this function to deallocate the buffer containing
 *   JSON-formatted usage data, returned by function VeGetLocalUsage,
 *   after it is no longer needed.
 *
 *   Parameters:
 *
 *     ctx
 *
 *       Pass the address of the LibraryContext object, created by
 *       calling the function VeCreateLibCtx, associated with a
 *       previously returned buffer containing JSON-formatted usage
 *       data.
 *
 *     jsonBuffer
 *
 *       Pass the address of the character buffer, containing
 *       JSON-formatted usage data, returned by a previous call to the
 *       function VeGetLocalUsage and that you no longer need access
 *       to, so that it can be deallocated.
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
 *     After calling this function, do not attempt to access the
 *     JSON-formatted usage data that the buffer specified by the
 *     jsonBuffer parameter contained prior to this call. The
 *     associated memory may already be reallocated for a different
 *     purpose.
 */
VE_DLL_DEF int VeDestroyLocalUsageBuffer(VeLibCtx ctx,
                                         const char *jsonBuffer);


#ifdef __cplusplus
}
#endif

#endif /* VEAPI_H */
