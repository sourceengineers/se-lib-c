/*!****************************************************************************************************************************************
 * @file         MockAdcDriver.h
 *
 * @copyright    © by Source Engineers GmbH, 2019
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/

#ifndef MOCKBYTESTREAM_H_
#define MOCKBYTESTREAM_H_

#include <se-lib-c/stream/IByteStream.h>
#include <stdint.h>

#define STRING_BUFFER_SIZE 256
/**
 * Declaration of the mock object.
 */
typedef struct __MockByteStreamPrivateData
{
	IByteStream parent;
	char stringBuffer[STRING_BUFFER_SIZE];
} MockByteStream;

/**
 * initialize a MockByteStream instance.
 */
void MockByteStream_init(MockByteStream* me);

/**
 * Returns a pointer to the IBytestream.
 */ 
IByteStream* MockByteStream_getBytestreamInterface(MockByteStream* me);

#endif // MOCKBYTESTREAM_H_
