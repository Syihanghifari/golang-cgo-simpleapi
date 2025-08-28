/***********************************************************************
 * (c) Copyright 2021-2023 Open Text or one of its affiliates.         *
 *                                                                     *
 * The only warranties for products and services of Open Text and      *
 * its affiliates and licensors ("Open Text") are as may be set        *
 * forth in the express warranty statements accompanying such products *
 * and services. Nothing herein should be construed as constituting an *
 * additional warranty. Open Text shall not be liable for technical    *
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
 **********************************************************************
 * Simple API Version constants.
 *
 * These can be used with VeGetVersionNumber() (veapi.h) and
 * VsGetSimpleAPINumericVersion() (vssimple.h) to allow client
 * code to vary its usage based on specific Simple API SDK
 * versions. The version constants are monotonically increasing
 * to allow usage like
 *
 *    if (VeGetVersionNumber() >= VE_VERSION_NUMBER_4_0_0)
 *    {
 *        ...
 *    }
 *
 * For version Major.Minor.Maint[Patch] (Patch is optional letter),
 * the numeric value is given by the sum of:
 *    * Major * 1000000
 *    * Minor *   10000
 *    * Maint *     100
 *    * Patch *       1
 *
 * Where:
 *    * Major is in the set [1,99]
 *    * Minor is in the set [0,99]
 *    * Maint is in the set [0,99]
 *    * Patch is in the set [b,z] with numeric values [1,25], and
 *      omitted patch (essentially patch rev 'a') has numeric value 0.
 *
 * NOTE: The numeric form does not encode if the release is beta
 *       or other pre-release. That can be determined only from the
 *       version string and the svn revision in the package name.
 */

#ifndef VSVER_H
#define VSVER_H

#define VS_SIMPLE_API_VERSION_NUMBER_3_13_0   3130000
#define VS_SIMPLE_API_VERSION_NUMBER_3_13_0b  3130001
#define VS_SIMPLE_API_VERSION_NUMBER_3_13_0c  3130002
#define VS_SIMPLE_API_VERSION_NUMBER_3_13_0d  3130003
#define VS_SIMPLE_API_VERSION_NUMBER_3_13_0e  3130004
#define VS_SIMPLE_API_VERSION_NUMBER_3_13_0f  3130005

#define VS_SIMPLE_API_VERSION_NUMBER_3_14_0   3140000
#define VS_SIMPLE_API_VERSION_NUMBER_3_14_1   3140001 /*3140100*/
#define VS_SIMPLE_API_VERSION_NUMBER_3_14_2   3140200
#define VS_SIMPLE_API_VERSION_NUMBER_3_14_3   3140300
#define VS_SIMPLE_API_VERSION_NUMBER_3_14_4   3140400

#define VE_VERSION_NUMBER_4_0_0               4000000
#define VE_VERSION_NUMBER_4_1_0               4010000
#define VE_VERSION_NUMBER_4_2_0               4020000
#define VE_VERSION_NUMBER_4_2_1               4020100
#define VE_VERSION_NUMBER_4_3_0               4030000
#define VE_VERSION_NUMBER_4_3_1               4030100
#define VE_VERSION_NUMBER_4_3_2               4030200
#define VE_VERSION_NUMBER_4_3_3               4030300
#define VE_VERSION_NUMBER_5_0_0               5000000
#define VE_VERSION_NUMBER_5_10                5100000
#define VE_VERSION_NUMBER_5_11                5110000
#define VE_VERSION_NUMBER_5_12                5120000
#define VE_VERSION_NUMBER_5_20                5200000
#define VE_VERSION_NUMBER_5_30                5300000
#define VE_VERSION_NUMBER_6_0_0               6000000
#define VE_VERSION_NUMBER_6_1_0               6010000
#define VE_VERSION_NUMBER_6_1_0_1             6100001 /*alias*/
#define VE_VERSION_NUMBER_6_10_0_1            6100001
#define VE_VERSION_NUMBER_6_2_0               6200000 /*alias*/
#define VE_VERSION_NUMBER_6_20_0              6200000
#define VE_VERSION_NUMBER_6_20_0_1            6200001
#define VE_VERSION_NUMBER_6_21_0_0            6210000
#define VE_VERSION_NUMBER_6_21_0_1            6210001
#define VE_VERSION_NUMBER_6_21_1_0            6210100
#define VE_VERSION_NUMBER_6_21_1_1            6210101 /* 6.22 pre */
#define VE_VERSION_NUMBER_6_22_0_0            6220000
#define VE_VERSION_NUMBER_6_22_0_2            6220002

#define VS_SIMPLE_API_NAME                    "Simple API C"
#define VS_SIMPLE_API_VERSION                 "6.22.0.2"
#define VS_SIMPLE_API_VERSION_NUMBER          VE_VERSION_NUMBER_6_22_0_2
#define VS_SIMPLE_API_VERSION_STRING          VS_SIMPLE_API_NAME " " \
                                              VS_SIMPLE_API_VERSION

#define VS_SIMPLE_API_CLIENT_ID_NAME          "SimpleAPI-C" /*no space*/

#endif /* VSVER_H */
