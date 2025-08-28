/***********************************************************************
 * (c) Copyright 2022-2023 Micro Focus or one of its affiliates.       *
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
 * Header File: velog.h
 *
 *   Include this header file in C source code files in which you will
 *   be using the Simple API logging functions, such as to register
 *   logging callback functions or set the logging level. This header
 *   file defines the logging callback type definitions, including the
 *   function type VeLogCallBack, the three logging functions
 *   VeSetLogCallBack, VeSetLogLevel, and VeLogLevelName, and their
 *   related constants.
 ***********************************************************************
 */
#ifndef VELOG_H
#define VELOG_H

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "veapi.h"

#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************************
 *
 * Logging Constants:
 *
 *   Defined in the header file velog.h, the Simple API provides the
 *   following constants for use with the logLevel parameter of the
 *   function VeSetLogLevel.
 *
 *   VE_LOG_LEVEL_NONE
 *
 *     Specifies that no logging action be performed, regardless of
 *     whether logging has been enabled by calling function
 *     VeSetLogCallBack.
 *
 *   VE_LOG_LEVEL_CRITICAL
 *
 *     Specifies that a logging action be performed only when the
 *     logging call is at the CRITICAL level. Logging calls at the
 *     CRITICAL level indicate a catastrophic failure and require
 *     immediate attention.
 *
 *   VE_LOG_LEVEL_ERROR
 *
 *     Specifies that a logging action be performed only when the
 *     logging call is at the ERROR or CRITICAL level. Logging calls at
 *     the ERROR level indicate an operational failure that requires
 *     attention.
 *
 *   VE_LOG_LEVEL_WARNING
 *
 *     Specifies that a logging action be performed only when the
 *     logging call is at the WARNING, ERROR, or CRITICAL level.
 *     Logging calls at the WARNING level indicate an unexpected
 *     situation that should be looked into.
 *
 *   VE_LOG_LEVEL_INFO
 *
 *     Specifies that a logging action be performed only when the
 *     logging call is at the INFO, WARNING, ERROR, or CRITICAL level.
 *     Logging calls at the INFO level provide high-level information
 *     about the cryptographic operations being performed. Calls at
 *     this level will not significantly impact performance because
 *     they will not be made at the level of individual cryptographic
 *     operations. In other words, individual protect and access
 *     operations will not generate INFO level logging calls.
 *
 *   VE_LOG_LEVEL_DEBUG
 *
 *     Specifies that a logging action be performed only when the
 *     logging call is at the DEBUG, INFO, WARNING, ERROR, or CRITICAL
 *     level. Logging calls at the DEBUG level provide detailed
 *     information useful when debugging cryptographic operations.
 *     Expect a large volume of log messages that can adversely affect
 *     performance.
 *
 *   VE_LOG_LEVEL_TRACE
 *
 *     Specifies that a logging action be performed only when the
 *     logging call is at the TRACE, DEBUG, INFO, WARNING, ERROR, or
 *     CRITICAL level (all levels). Logging calls at the TRACE level
 *     provide the most detailed information available the
 *     cryptographic operations being performed and may not be
 *     appropriate in production environments. Expect a large volume of
 *     log messages that can adversely affect performance.
 *
 *   For more information about the Simple API's logging functionality,
 *   see the topics "Logging Functions" and "Logging" in the Voltage
 *   SecureData Simple API Developer Guide.
 */
#define VE_LOG_LEVEL_NONE        0
#define VE_LOG_LEVEL_CRITICAL    1
#define VE_LOG_LEVEL_ERROR       2
#define VE_LOG_LEVEL_WARNING     3
#define VE_LOG_LEVEL_INFO        4
#define VE_LOG_LEVEL_DEBUG       5
#define VE_LOG_LEVEL_TRACE       6

/***********************************************************************
 *
 * Function Type Definition: VeLogCallBack
 *
 *   This function typedef provides the expected signature of the
 *   callback function provided in the Simple API application, a
 *   pointer to which is specified as the callbackFunction parameter to
 *   function VeSetLogCallBack. After that function has been called
 *   (with a non-null function pointer), the Simple API will use this
 *   function pointer to call back out to the Simple API application
 *   whenever a logging call with a level less than or equal to the
 *   currently set logging level is executed.
 *
 *   Parameters:
 *
 *     userCtx
 *
 *       A generic pointer of type void*, provided to the Simple API as
 *       the userCtx parameter to function VeSetLogCallBack and
 *       returned as context to the Simple API application in this
 *       parameter. The Simple API stores but never dereferences this
 *       pointer. If you provide a NULL pointer for the userCtx
 *       parameter to function VeSetLogCallback, a NULL pointer will be
 *       returned in this parameter.
 *
 *     logLevel
 *
 *       An integer that reports the level of the logging call in the
 *       Simple API that resulted in this invocation of the callback
 *       function. It will be a value that corresponds to one of the
 *       logging constants for the logging levels CRITICAL, ERROR,
 *       WARNING, INFO, DEBUG, and TRACE (but not NONE). For more
 *       information, see the topic "Logging Constants" in the Voltage
 *       SecureData Simple API Developer Guide.
 *
 *     sdkName
 *
 *       A pointer to the null-terminated string "Simple API C",
 *       indicating that the C language version of the Simple API is
 *       being used.
 *
 *     sdkVersion
 *
 *       A pointer to a null-terminated string providing the version of
 *       the Simple API being used, such as 6.22.0.0.
 *
 *     time
 *
 *       A time_t value that reports the time at which the logging call
 *       was made, represented as the number of seconds since the start
 *       of the Unix epoch: midnight UTC of January 1, 1970 (not
 *       counting leap seconds).
 *
 *     nanoSeconds
 *
 *       An integer that reports the nanosecond within the reported
 *       second at which the logging call was made.
 *
 *     processId
 *
 *       An integer that reports the numeric identifier of the process
 *       in which the Simple API application is running.
 *
 *     threadId
 *
 *       A pointer to a null-terminated string that reports a unique
 *       identifier for the thread in which the logging call within the
 *       Simple API application was made.
 *
 *     sourceFile
 *
 *       A pointer to a null-terminated string that reports the name of
 *       the source file in which the corresponding logging call
 *       originated.
 *
 *     functionName
 *
 *       A pointer to a null-terminated string that reports the name of
 *       the function in which the corresponding logging call
 *       originated.
 *
 *     sourceLine
 *
 *       An integer that reports the line number of the corresponding
 *       logging call in the reported source file.
 *
 *     message
 *
 *       A pointer to a null-terminated string that reports a custom
 *       message associated with the corresponding logging call,
 *       providing information appropriate to the reported log level.
 *
 *   Return Value:
 *
 *     Write this function such that it does not return any value.
 *
 *   Remarks:
 *
 *     All of the string pointer parameters to this function must not
 *     be dereferenced after the callback function returns to the
 *     Simple API. Doing so will have unpredictable results.
 *
 *     What you do with the logging information reported to this
 *     callback function is up to you. Keep in mind that it is a
 *     blocking call in the Simple API code so that whatever processing
 *     you do should be as efficient as possible. Note, however, that
 *     logging at the INFO level and lower (CRITICAL, ERROR, and
 *     WARNING), is sparse enough in the Simple API code so that
 *     performance will not be significantly impacted. For example,
 *     individual protect and access operations will not include INFO
 *     level logging.
 *
 *     To prevent this logging callback function from being called
 *     after having set it using a call to function VeSetLogCallBack,
 *     either:
 *
 *       - Call function VeSetLogCallback again with its
 *         callbackFunction parameter set to NULL, causing the Simple
 *         API to abandon your logging callback function, and/or,
 *
 *       - Call function VeSetLogLevel to set the logging level to
 *         VE_LOG_LEVEL_NONE. This works because no logging calls in
 *         the Simple API code have their level set this low (0).
 *
 *     Note, however, that any in-progress logging calls in another
 *     thread may still call your logging callback function.
 *
 *     For more information about the Simple API's logging
 *     functionality, including the parameters passed the formatted
 *     logging callback function, see the topics "Logging" and "Logging
 *     in C" in the Voltage SecureData Simple API Developer Guide.
 */
typedef void (*VeLogCallBack)(
    void*           userCtx,
    int             logLevel,
    const char*     sdkName,
    const char*     sdkVersion,
    time_t          seconds,
    int             nanoSeconds,
    int             processId,
    const char*     threadId,
    const char*     sourceFile,
    const char*     functionName,
    int             sourceLine,
    const char*     logMessage
);

/***********************************************************************
 *
 * Function: VeSetLogLevel
 *
 *   Use this function to set logging to a particular level from the
 *   following choices, in increasing order of verbosity: NONE,
 *   CRITICAL, ERROR, WARNING, INFO, DEBUG, and TRACE. For example,
 *   when the Simple API is set to log level INFO, log message action
 *   at levels INFO, WARNING, ERROR, and CRITICAL will occur and log
 *   messages at levels DEBUG and TRACE will not.
 *
 *   Parameters:
 *
 *     logLevel
 *
 *       An integer that specifies the logging level. Use one of the
 *       following constants:
 *
 *         VE_LOG_LEVEL_NONE
 *
 *         VE_LOG_LEVEL_CRITICAL
 *
 *         VE_LOG_LEVEL_ERROR
 *
 *         VE_LOG_LEVEL_WARNING
 *
 *         VE_LOG_LEVEL_INFO
 *
 *         VE_LOG_LEVEL_DEBUG
 *
 *         VE_LOG_LEVEL_TRACE
 *
 *       For more information about these constants and their meaning,
 *       see the topic "Logging Constants" in the Voltage SecureData
 *       Simple API Developer Guide.
 *
 *   Return Value:
 *
 *     This function cannot fail and does not have a return value
 *     (void).
 *
 *   Remarks:
 *
 *     When your Simple API application starts, the logging level is
 *     set to INFO. Thereafter, use this function to change the logging
 *     level to one of its other choices. To disable logging, even when
 *     a logging callback function has been set using function
 *     VeSetLogCallBack, set the logging level to NONE
 *     (VE_LOG_LEVEL_NONE). Doing so effectively disables logging
 *     because no logging calls in the Simple API code have their level
 *     set that low (0). Note, however, that any in-progress logging
 *     calls in another thread may still call your logging callback
 *     function.
 *
 *     The amount of logging at various levels that is available to
 *     your logging callback function is dependent on the number of
 *     logging calls that have been added to the Simple API source code.
 *
 *   For more information about the Simple API's logging functionality,
 *   see the topics "Logging" and "Logging in C" in the Voltage
 *   SecureData Simple API Developer Guide.
 */
VE_DLL_DEF void VE_CALLING_CONV VeSetLogLevel(
    int logLevel
);

/***********************************************************************
 *
 * Function: VeGetLogLevel
 *
 *   Use this function to get the currently set logging level (one of
 *   NONE, CRITICAL, ERROR, WARNING, INFO, DEBUG, or TRACE).
 *
 *   Parameters:
 *
 *     None.
 *
 *   Return Value:
 *
 *     This function returns the current logging level.
 *
 *   Remarks:
 *
 *     When your Simple API application starts, the logging level is
 *     set to INFO.
 *
 *     To change the logging level, use function VeSetLogLevel.
 *
 *   For more information about the Simple API's logging functionality,
 *   see the topics "Logging" and "Logging in C" in the Voltage
 *   SecureData Simple API Developer Guide.
 */
VE_DLL_DEF int VE_CALLING_CONV VeGetLogLevel();

/***********************************************************************
 *
 * Function: VeLogLevelName
 *
 *   Use this function to get one of the following strings,
 *   corresponding to the specified log level: NONE, CRITICAL, ERROR,
 *   WARNING, INFO, DEBUG, and TRACE.
 *
 *   If a log level outside the range zero (0) to six (6) is passed,
 *   the "error" string Unrecognized will be returned instead.
 *
 *   For more information about the Simple API's logging functionality,
 *   see the topics "Logging" and "Logging in C" in the Voltage
 *   SecureData Simple API Developer Guide.
 *
 *   Parameters:
 *
 *     logLevel
 *
 *       An integer in the range 0 to 6, generally expected to be value
 *       reported as the logLevel parameter to the callback function
 *       registered by calling function VeSetLogCallBack.
 *
 *       For more information about the log levels and their meaning,
 *       see the topic "Logging Constants" in the Voltage SecureData
 *       Simple API Developer Guide.
 *
 *   Return Value:
 *
 *     One of the NULL-terminated strings NONE, CRITICAL, ERROR,
 *     WARNING, INFO, DEBUG, or TRACE, corresponding to the logLevel
 *     parameter values 0 to 6, respectively, or Unrecognized for any
 *     other value.
 *
 *   Remarks:
 *
 *     The purpose of this function is to make it easier to translate
 *     the numeric value of the logLevel parameter to your callback
 *     function into a human-readable string for use in log messages.
*/
VE_DLL_DEF const char* VE_CALLING_CONV VeLogLevelName(
    int logLevel
);

/***********************************************************************
 *
 * Function: VeSetLogCallBack
 *
 *   Use this function to register a logging callback function of type
 *   VeLogCallBack. If the specified callbackFunction function pointer
 *   is not NULL, the Simple API will call the specified function
 *   pointer whenever a logging call with a level less than or equal to
 *   the currently set logging level is executed.
 *
 *   For example, when the Simple API is set to logging level INFO, log
 *   message action at levels INFO, WARNING, ERROR, and CRITICAL will
 *   occur and log message action at levels DEBUG and TRACE will not.
 *
 *   NOTE: When your Simple API application starts, the logging level
 *         is set to INFO. Thereafter, use function VeSetLogLevel to
 *         change the logging level to one of its other choices.
 *
 *   Parameters:
 *
 *     userCtx
 *
 *       A generic pointer of type void* that the Simple API will store
 *       and include as the userCtx parameter in every call to the
 *       logging callback function specified by the callbackFunction
 *       parameter. It is for the sole use of the calling application;
 *       the Simple API never dereferences this pointer, and so it can
 *       be NULL if the Simple API application has no need for private
 *       context.
 *
 *     callbackFunction
 *
 *       A pointer to a function of type VeLogCallBack. The Simple API
 *       will call this function when a logging call in the
 *       cryptographic code at a level less than or equal to the
 *       currently set logging level is encountered. If you specify
 *       NULL for this parameter, any previous set logging callback
 *       function is abandoned and logging is effectively disabled.
 *       Note, however, that any in-progress logging calls in another
 *       thread may still call your logging callback function.
 *
 *   Return Value:
 *
 *     This function cannot fail and does not have a return value
 *     (void).
 *
 *   Remarks:
 *
 *     The logging callback function will be called when all of the
 *     following criteria are met:
 *
 *       - This function has already been called with a non-NULL
 *         callback function pointer (callbackFunction parameter), and,
 *
 *       - The currently set logging level is not set to
 *         VE_LOG_LEVEL_NONE, and,
 *
 *       - A logging call is made during Simple API processing, and
 *
 *       - The level of the logging call is less than or equal to the
 *         current set logging level. For example, the logging call has
 *         a level of VE_LOG_LEVEL_ERROR and the currently set logging
 *         level is VE_LOG_LEVEL_WARNING, then this criterion is met
 *         because errors have a lower value (2) than warnings (3).
 *
 *     To disable logging callback functionality after calling this
 *     function, either:
 *
 *       - Call this function again with its callbackFunction parameter
 *         set to NULL, and/or,
 *
 *       - Call function VeSetLogLevel to set the logging level to
 *         VE_LOG_LEVEL_NONE.
 *
 *     The amount of logging at various levels that is available to
 *     your logging callback function is dependent on the number of
 *     logging calls that have been added to the Simple API source code.
 *
 *     For more information about the Simple API's logging
 *     functionality, including the parameters passed the logging
 *     callback function, see the topics "Logging" and "Logging in C"
 *     in the Voltage SecureData Simple API Developer Guide.
 */
VE_DLL_DEF void VE_CALLING_CONV VeSetLogCallBack(
    void* userCtx, VeLogCallBack callbackFunction
);


#ifdef __cplusplus
}
#endif

#endif/* VELOG_H */
