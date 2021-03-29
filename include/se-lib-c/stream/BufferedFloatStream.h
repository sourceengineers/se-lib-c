/*!*****************************************************************************
 * @file         BufferedFloatStream.h
 *
 * @copyright    Copyright (c) 2018 by Sourceengineers. All Rights Reserved.
 *
 * @license      This file is part of SE-Lib-C.
 *
 *               SE-Lib-C is free software; you can redistribute it and/or
 *               modify it under the terms of the GNU General Public License as
 *               published by the Free Software Foundation.
 *
 *               SE-Lib-C is distributed in the hope that it will be useful,
 *               but WITHOUT ANY WARRANTY; without even the implied warranty of
 *               MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *               GNU General Public License for more details.
 *
 *               You should have received a copy of the GNU General Public License
 *               along with SE-Lib-C.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @authors      Samuel Schuepbach samuel.schuepbach@sourceengineers.com
 *
 * @brief        Implementation of the float stream interface.
 *               The buffered float stream uses a ring buffer as underlying data
 *               structure
 *
 ******************************************************************************/

#ifndef FLOATSTREAM_H_
#define FLOATSTREAM_H_

#include <se-lib-c/definition/SeLibCTypes.h>
#include <se-lib-c/stream/IFloatStream.h>
#include <stdbool.h>
#include <stddef.h>

/******************************************************************************
 Define class handle data
******************************************************************************/
typedef struct __BufferedFloatStreamPrivateData* BufferedFloatStreamHandle;

/******************************************************************************
 Public functions 
******************************************************************************/
/**
 * Constructor
 * @param capacity size of the buffer
 * @return
 */
BufferedFloatStreamHandle BufferedFloatStream_create(size_t capacity);

/**
 * Returns the stream interface
 * @param self
 * @return
 */
IFloatStreamHandle BufferedFloatStream_getIFloatStream(BufferedFloatStreamHandle self);

/**
 * Deconstructor
 * @param self
 */
void BufferedFloatStream_destroy(BufferedFloatStreamHandle self);

#endif
