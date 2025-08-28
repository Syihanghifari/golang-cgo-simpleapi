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
 * Header File: veerror.h
 *
 *   This header file defines the constants for the various error codes
 *   that might be returned by the functions of the C language
 *   interface to the Simple API. It is included indirectly by the
 *   header file veapi.h, which itself is included indirectly when you
 *   include one or more of the header files for specific Simple API
 *   functionality, described above.
 *
 *   For more information about the meaning of each individual error
 *   code, see the topic "Error Constants" in the Voltage SecureData
 *   Simple API Developer Guide.
 ***********************************************************************
 */
#ifndef VEERROR_H
#define VEERROR_H

#define VE_ERROR_GENERAL                                   1
#define VE_ERROR_UNIMPLEMENTED                             2
#define VE_ERROR_MEMORY                                    3
#define VE_ERROR_NULL_ARG                                  8
#define VE_ERROR_NON_NULL_ARG                              9
#define VE_ERROR_INVALID_INPUT                            17
#define VE_ERROR_INVALID_INPUT_LENGTH                     18
#define VE_ERROR_BUFFER_TOO_SMALL                         22
#define VE_ERROR_INVALID_PARAMS                           31
#define VE_ERROR_FPE_INPUT_LENGTH_ZERO                    76
#define VE_ERROR_FPE_INPUT_LENGTH_TOO_SHORT               77
#define VE_ERROR_FPE_INPUT_LENGTH_TOO_LONG                78
#define VE_ERROR_TOO_SHORT_FOR_EFPE_KEYNUM                79
#define VE_ERROR_AUTHORIZATION_DENIED                    566
#define VE_ERROR_INVALID_ALGORITHM                       557
#define VE_ERROR_CANNOT_VERIFY_CERT                      571
#define VE_ERROR_NETWORK_CONNECT                         572
#define VE_ERROR_TIMEOUT                                 590
#define VE_ERROR_INPUT_DOES_NOT_MATCH_FORMAT             679
#define VE_ERROR_INPUT_OUT_OF_RANGE                      680
#define VE_ERROR_CENTRALIZED_FORMAT_NOT_FOUND            684
#define VE_ERROR_AUTHORIZATION_EXPIRED                   726

#define VE_ERROR_LOGIC                                  1500 
#define VE_ERROR_INVALID_ARG                            1600
#define VE_ERROR_NO_POLICY                              1601
#define VE_ERROR_INVALID_ENCODING                       1602
#define VE_ERROR_INVALID_BOOLEAN_ARG                    1603
#define VE_ERROR_INVALID_KEYNUM                         1604
#define VE_ERROR_INVALID_BUFFER_SIZE                    1605
#define VE_ERROR_INSUFFICIENT_BUFFER_SIZE               1606
#define VE_ERROR_NULL_LIB_CTX_ARG_IN_CREATE             1607
#define VE_ERROR_INVALID_AUTH_ARGS                      1608

#define VE_ERROR_CLIENTCERT_INVALID_RESOURCE            1650
#define VE_ERROR_CLIENTCERT_STORE_NOT_FOUND             1651
#define VE_ERROR_CLIENTCERT_NO_MATCHING_CERT            1652
#define VE_ERROR_CLIENTCERT_TIME_INVALID                1653

#define VE_ERROR_USAGE                                  1700
#define VE_ERROR_MISSING_DEFAULTS                       1701
#define VE_ERROR_UNEXPECTED_PARAMS_VERSION              1702
#define VE_ERROR_UNEXPECTED_OP_PHASE                    1703
#define VE_ERROR_INVALID_FPE_MODE                       1704
#define VE_ERROR_INVALID_IBSE_MODE                      1705
#define VE_ERROR_UNSUPPORTED_FOR_ACCESS_OBJ             1706
#define VE_ERROR_UNEXPECTED_OBJECT_TYPE                 1707
#define VE_ERROR_UNSUPPORTED_FOR_LIB_CTX                1708
#define VE_ERROR_UNSUPPORTED_FOR_IBSE                   1709
#define VE_ERROR_INVALID_SECUREFILE_VERSION             1710
#define VE_ERROR_EFPE_FORMAT_REQUIRED                   1711
#define VE_ERROR_UNSUPPORTED_FOR_EFPE                   1712
#define VE_ERROR_INVALID_KEYNUM_ZERO                    1713
#define VE_ERROR_BAD_DATA                               1714
#define VE_ERROR_FULL_IDENTITY_NOT_SUPPORTED_FOR_EFPE   1715
#define VE_ERROR_INVALID_IDENTITY                       1716
#define VE_ERROR_FPH_ACCESS_NOT_SUPPORTED               1717
#define VE_ERROR_UNSUPPORTED_FOR_SST                    1718
#define VE_ERROR_INPUT_VALUE_TOO_SMALL                  1719
#define VE_ERROR_INPUT_VALUE_TOO_LARGE                  1720
#define VE_ERROR_UNSUPPORTED_FOR_FPE                    1721
#define VE_ERROR_ONLY_APPLICABLE_FOR_EFPE               1722


#define VE_ERROR_KCW_FAILED_TO_START                    1750
#define VE_ERROR_KCW_FAILED_TO_ADD_FPE                  1751
#define VE_ERROR_KCW_NO_FPE_TO_PROCESS                  1752
#define VE_ERROR_MASKING_NOT_CONFIGURED                 1753
#define VE_ERROR_REGEX_MASKING_NOT_SUPPORTED            1754


#define VE_ERROR_TELEMETRY_FAILED_TO_START                   1760

#define VE_ERROR_TELEMETRY_FAILED_TO_SEND                    1761


#define VE_ERROR_INIT_FAILED                            1850
#define VE_ERROR_CREATE_FAILED                          1851
#define VE_ERROR_PROTECT_FAILED                         1852
#define VE_ERROR_ACCESS_FAILED                          1853
#define VE_ERROR_UNSUPPORTED_CODEPOINT                  1854
#define VE_ERROR_INVALID_ALPHABET                       1855
#define VE_ERROR_INVALID_DATE_FORMAT                    1856
#define VE_ERROR_NET_EMPTY                              1857
#define VE_ERROR_INVALID_CODEPOINT                      1858
#define VE_ERROR_UNRECOGNIZED_PREDEFINED_FORMAT         1859
#define VE_ERROR_CORRUPTED_DATA                         1860

#define VE_ERROR_NO_IDENTITY_OBJECT                     1900

#define VE_ERROR_TOKENIZATION_IDENTITY_MISMATCH         1901
#define VE_ERROR_TOKENIZATION_FORMAT_NOT_MULTIPLEXED    1902
#define VE_ERROR_TOKENIZATION_FORMAT_MULTIPLEXED        1903

#define VE_ERROR_TWEAK_DISABLED                         1904
#define VE_ERROR_TWEAK_STRING_OUT_OF_RANGE              1905
#define VE_ERROR_TWEAK_NOT_SUPPORTED_FOR_FORMAT         1906
#define VE_ERROR_INVALID_PRIMARY_NAMESPACE              1907
#define VE_ERROR_INVALID_SECONDARY_NAMESPACE            1908
#define VE_ERROR_PRIMARY_NAMESPACE_REQUIRED             1909



#define VE_ERROR_HV_INIT_FAILED                 /*(DEPRECATED)*/ \
        VE_ERROR_INIT_FAILED

#define VE_ERROR_HV_CREATE_FAILED               /*(DEPRECATED)*/ \
        VE_ERROR_CREATE_FAILED

#define VE_ERROR_HV_PROTECT_FAILED              /*(DEPRECATED)*/ \
        VE_ERROR_PROTECT_FAILED

#define VE_ERROR_HV_ACCESS_FAILED               /*(DEPRECATED)*/ \
        VE_ERROR_ACCESS_FAILED

#define VE_ERROR_HV_UNSUPPORTED_CODEPOINT       /*(DEPRECATED)*/ \
        VE_ERROR_UNSUPPORTED_CODEPOINT

#define VE_ERROR_HV_INVALID_ALPHABET            /*(DEPRECATED)*/ \
        VE_ERROR_INVALID_ALPHABET

#define VE_ERROR_HV_INVALID_DATE_FORMAT         /*(DEPRECATED)*/ \
        VE_ERROR_INVALID_DATE_FORMAT

#define VE_ERROR_HV_NET_EMPTY                   /*(DEPRECATED)*/ \
        VE_ERROR_NET_EMPTY

#define VE_ERROR_UNSUPPORTED_FOR_AES            /*(DEPRECATED)*/ \
        VE_ERROR_UNSUPPORTED_FOR_IBSE

#define VE_ERROR_INVALID_AES_MODE               /*(DEPRECATED)*/ \
        VE_ERROR_INVALID_IBSE_MODE

#endif /* VEERROR_H */
