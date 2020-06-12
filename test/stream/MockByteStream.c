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


/**
 * The implementation of the Parent methods.
 * @{
 */
/** @} */


void MockByteStream_init(MockByteStream me)
{
    // initialize interface
    me.parent.handle = &me;

    me.parent.write = &mockWrite;

    // initialize private variables
    memset(me.stringBuffer,0,STRING_BUFFER_SIZE);
}

IByteStream* MockByteStream_getBytestreamInterface(MockByteStream me)
{
    assert(&me != NULL);
    assert(&me.parent != NULL);
    //TODO return the actual IByteStream instead of NULL
    //return me.parent.handle;
    return NULL;
}

//TODO finish implementation of mockWrite
bool mockWrite(IByteStreamHandle handle, const uint8_t data, const size_t length)
{
    bool success = false;
    MockByteStream* me = (MockByteStream*)handle;
    assert(me != NULL);
    strcpy(me->stringBuffer, data); // write the data in the stringBuffer
    return success;
}