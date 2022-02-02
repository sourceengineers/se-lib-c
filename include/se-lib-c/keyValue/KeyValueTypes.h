/*!****************************************************************************************************************************************
 * @file         KeyValueTypes.h
 *
 * @copyright    Copyright (c) 2021 by Source Engineers GmbH. All Rights Reserved.
 *
 * @license {    This file is part of se-lib-c.
 *
 *               se-lib-c is free software; you can redistribute it and/or
 *               modify it under the terms of the GPLv3 General Public License Version 3
 *               as published by the Free Software Foundation.
 *
 *               se-lib-c is distributed in the hope that it will be useful,
 *               but WITHOUT ANY WARRANTY; without even the implied warranty of
 *               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *               GNU General Public License for more details.
 *
 *               You should have received a copy of the GPLv3 General Public License Version 3
 *               along with se-lib-c.  If not, see <http://www.gnu.org/licenses/>.
 *
 *               In closed source or commercial projects, GPLv3 General Public License Version 3
 *               is not valid. In these cases the purchased commercial license is applied.
 *               Please contact us at scope@sourceengineers.com for a commercial license.
 * }
 *
 * @authors      Tobias Jäggi <tobias.jaeggi@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/


#ifndef KEYVALUETYPES_H_
#define KEYVALUETYPES_H_

#include <stdint.h>

typedef enum __KeyValue_KeyType
{
    KEY_TYPE_NONE = 0,
    KEY_TYPE_INT16,
    KEY_TYPE_INT32,
    KEY_TYPE_UINT16,
    KEY_TYPE_UINT32,
    KEY_TYPE_FLOAT
}KeyValue_KeyType;

typedef union __KeyValue_Data
{
    int16_t i16;
    int32_t i32;
    uint16_t ui16;
    uint32_t ui32;
    float  f; //TODO: define how big
}KeyValue_Data;

typedef struct _KeyValue_Value
{
    KeyValue_KeyType type;
    KeyValue_Data data;
}KeyValue_Value;


typedef struct __KeyValuePair
{
    uint16_t key;
    KeyValue_Value value;
}KeyValue_Pair;

#endif //KEYVALUETYPES_H_
