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
 * Header File: vedecl.h
 *
 *   This header file defines declaration macros to support Windows
 *   linkage requirements. It is included indirectly by the header file
 *   veapi.h, which itself is included indirectly when you include one
 *   or more of the header files for specific Simple API functionality,
 *   described above.
 ***********************************************************************
 */
#ifndef VEDECL_H
#define VEDECL_H

#if defined(_WIN32)
#    define VE_CALLING_CONV __stdcall
#    if defined(VE_STATIC_LINK)
#        define VE_DLL_DEF
#    else
#        if defined(VE_BUILD)
#            define VE_DLL_DEF   __declspec(dllexport) 
#        else
#            define VE_DLL_DEF   __declspec(dllimport) 
#        endif
#    endif
#else
#    define VE_CALLING_CONV
#    define VE_DLL_DEF
#endif

#endif /* VEDECL_H */
