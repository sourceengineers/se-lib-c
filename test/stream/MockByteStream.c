/*!****************************************************************************************************************************************
 * @file         MockByteStream.c
 *
 * @copyright    © by Source Engineers GmbH, 2020
 *
 * @authors      Flurin Bühler <flurin.buehler@sourceengineers.com>
 *
 * @brief        TODO
 *
 *****************************************************************************************************************************************/
#include "MockByteStream.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


bool mockWrite(IByteStreamHandle handle, const uint8_t* data, const size_t length)
{
    MockByteStream* me = (MockByteStream*)handle;
    assert(me != NULL);
    strcpy(me->stringBuffer, data);
    return true;
}

/**
 * The implementation of the Parent methods.
 * @{
 */
/** @} */


//NOTE so muss es sein, mit Pointer auf MockByteStream, nicht das Objekt.
void MockByteStream_init(MockByteStream* me)
{
    // initialize interface
    me->parent.handle = &me;

    me->parent.byteIsReady = NULL;
    me->parent.readByte = NULL;
    me->parent.length = NULL;
    me->parent.read = NULL;
    me->parent.writeByte = NULL;
    me->parent.write = &mockWrite;
    me->parent.flush = NULL;
    me->parent.capacity = NULL;

    // initialize private variables
    memset(me->stringBuffer,0,STRING_BUFFER_SIZE);
}


IByteStream* MockByteStream_getBytestreamInterface(MockByteStream* me)
{
    assert(&me->parent != NULL);
    return &me->parent;
}

