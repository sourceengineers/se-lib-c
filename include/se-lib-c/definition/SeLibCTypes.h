/*!****************************************************************************************************************************************
 * @file         SeLibCTypes.h
 *
 * @copyright    Copyright (c) 2018 by Sourceengineers. All Rights Reserved.
 *
 * @license This file is part of "se-scope-target". It is release under a commercial 
 *          license. Refer to the license PDF file received together with this code 
 *          for the exact licensing terms. 
 *
 * @authors      Samuel Schuepbach samuel.schuepbach@sourceengineers.com
 *
 * @brief        Defines the data types that can be used by the se-lib-c.
 *               It specifies the size of addresses by defines which can be controlled by setting
 *               the ARCH_SIZE_32. ARCH_SIZE_32=1 equals a 32 bit architecture and
 *               ARCH_SIZE_32=0, or not setting ARCH_SIZE_32 at all, defined a 64 bit architecture.
 *
 *****************************************************************************************************************************************/

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* Choose the right integer length */
#if (ARCH_SIZE_32)
#define ADDRESS_DATA_TYPE uint32_t
#else
#define ADDRESS_DATA_TYPE uint64_t
#endif

#define GenericReference void*


#endif