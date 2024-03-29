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

static size_t length(IByteStreamHandle handle)
{
    assert(handle != NULL);
    MockByteStream* me = (MockByteStream*)handle;
    return strlen(me->stringBuffer);
}

bool mockWrite(IByteStreamHandle handle, const uint8_t* data, const size_t length)
{
    if(strlen(data) > STRING_BUFFER_SIZE)
    {
        return false;
    }
    // Return a buffer overflow when this message is logged
    if(strcmp(data, "WARNING: test_buffer_overflow_OVFL") == 0)
    {
        return false;
    }// Return a buffer overflow when this message is logged
    else if(strcmp(data, "WARNING: ShrtOvfl") == 0)
    {
        return false;
    }
    else
    {
        MockByteStream* me = (MockByteStream*)handle;
        assert(me != NULL);
        strcpy(me->stringBuffer, data);
        return true;
    }
}


bool isByteReay(IByteStreamHandle handle) {
    return length(handle) > 0;
}


void flush(IByteStreamHandle handle) {
    MockByteStream* me = (MockByteStream*)handle;
    strcpy(me->stringBuffer, "");
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
    me->parent.handle = me;

    me->parent.byteIsReady = &isByteReay;
    me->parent.readByte = NULL;
    me->parent.length = length;
    me->parent.read = NULL;
    me->parent.writeByte = NULL;
    me->parent.write = &mockWrite;
    me->parent.flush = &flush;
    me->parent.capacity = NULL;

    // initialize private variables
    memset(me->stringBuffer,0,STRING_BUFFER_SIZE);
}


IByteStream* MockByteStream_getBytestreamInterface(MockByteStream* me)
{
    assert(&me->parent != NULL);
    return &me->parent;
}

