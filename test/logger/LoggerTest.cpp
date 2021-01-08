#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <se-lib-c/logger/Logger.h>
#include <se-lib-c/logger/ILogger.h>
#include <se-lib-c/logger/LoggerBuilder.h>
#include <stream/MockByteStream.h>
}

class LoggerTest : public ::testing::Test
{
protected:


    LoggerTest()
            : Test()
    {

    }

    size_t _logBufferSize = 300;		// size of the buffer. equals max number of buffered messages
    size_t _logMessageSize = 300;
    ILoggerHandle _logHandle;
    IByteStreamHandle _logByteStream;


    void SetUp() override
    {
        LoggerBuilder_create();
        LoggerBuilder_build(_logMessageSize, _logBufferSize);
        _logHandle = LoggerBuilder_getILoggerHandle();
        _logByteStream = LoggerBuilder_getILoggerBufferHandle();
    }

    void TearDown() override
    {

    }

    virtual ~LoggerTest()
    {

    }
};

/*
 * create the logger
 */
TEST_F(LoggerTest, LoggerCreated)
{
    /* check if the logger exists */
    EXPECT_NE(nullptr, &_logHandle);
    EXPECT_NE(nullptr, &_logByteStream);
}

/*
 * log one message
 */
TEST_F(LoggerTest, LogFunctionality)
{
    const char logMsg[] = "Hello";     //strlen = 5
    _logHandle->log(_logHandle, logMsg);
    char logBufferContents[300];
    size_t log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, strlen(logMsg));
    _logByteStream->read(_logByteStream, (uint8_t *) logBufferContents, log_size);
    for(int i = 0; i<log_size; i++){
        EXPECT_EQ(logMsg[i], logBufferContents[i]);
    }
    log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, 0);
}


/*
 * Log the same message twice
 */
TEST_F(LoggerTest, TwoLogMsg)
{
    const char logMsg[] = "TestString\n\r";
    _logHandle->log(_logHandle, logMsg);
    _logHandle->log(_logHandle, logMsg);
    char logBufferContents[300];

    size_t log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, 2*(strlen(logMsg)));

    char expectedValue[300];
    sprintf(expectedValue, "%s%s", logMsg, logMsg);
    _logByteStream->read(_logByteStream, (uint8_t *) logBufferContents, log_size);
    for(int i = 0; i<log_size; i++){
        EXPECT_EQ(expectedValue[i], logBufferContents[i]);
    }
}

/*
 *  Try to write two 200 Byte Log messages in a 300 Byte buffer. Should lead to the firs message being logged
 *  as expected and the second message being replaced by "SCOPE BUF OVFL\n"
 */
TEST_F(LoggerTest, OvflMsg)
{
    size_t log_size;
    char logBufferContents[300];
    //200 char long log message, should lead to Buffer Overflow
    const char longLogMsg[] = "Lorem ipsum dolor sit amet, consetetur sadipscing "
                              "elitr, sed diam nonumy eirmod tempor invidunt ut "
                              "labore et dolore magna aliquyam erat, sed diam "
                              "voluptua. At vero eos et accusam et justo duo dolores ";
    const char bufOvflMsg[] = "LOG BUF OVFL\n";
    char expectedBufferValues[300];
    sprintf(expectedBufferValues, "%s%s", longLogMsg, bufOvflMsg);

    // write 200 Bytes, expected to work regularly
    _logHandle->log(_logHandle, longLogMsg);
    log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, strlen(longLogMsg));

    // try to write 200 Bytes again. This would lead to a Buffer overflow, thus the ovfl msg should be appended instead
    // of the message
    _logHandle->log(_logHandle, longLogMsg);
    log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, strlen(expectedBufferValues));


    _logByteStream->read(_logByteStream, (uint8_t *) logBufferContents, log_size);
    for(int i = 0; i<log_size; i++){
        EXPECT_EQ(expectedBufferValues[i], logBufferContents[i]);
    }
    // Buffer should be empty now
    log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, 0);
}



/*
 *  Try to log two 290-Byte Log messages in a 300 Byte buffer. The first message should be logged as intednded.
 *  The second message will not fit in the buffer and the overflow-message will also not fit in the buffer,
 *  instead the buffer will be flushed and only the overflow-message will be written.
 */
TEST_F(LoggerTest, OvflMsgEmptyBuf)
{
    size_t log_size;
    char logBufferContents[300];
    //290 char long log message
    const char longLogMsg[] = "Lorem ipsum dolor sit amet, consectetur "
                              "adipiscing elit. Nulla porta non augue vel pharetra. "
                              "Pellentesque quam orci, gravida at lorem eget, viverra "
                              "condimentum massa. Integer a sapien a dolor elementum "
                              "suscipit. In sit amet mi non mauris varius semper non "
                              "eu justo. Vestibulum semper proin.";
    const char bufOvflMsg[] = "LOG BUF OVFL\n";
    char expectedBufferValues[300];
    sprintf(expectedBufferValues, "%s", bufOvflMsg);

    // write 290 Bytes, expected to work regularly
    _logHandle->log(_logHandle, longLogMsg);
    log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, strlen(longLogMsg));
    EXPECT_EQ(_logByteStream->numOfFreeBytes(_logByteStream), _logBufferSize - strlen(longLogMsg));

    // try to write 290 Bytes again. This would lead to a Buffer overflow. The bufOfvlMsg can also not be appended, as this
    // would also lead to a buffer overflow. Instead, the buffer is flushed and only the overflow message is written
    _logHandle->log(_logHandle, longLogMsg);
    log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, strlen(expectedBufferValues));

    _logByteStream->read(_logByteStream, (uint8_t *) logBufferContents, log_size);
    for(int i = 0; i<log_size; i++){
        EXPECT_EQ(expectedBufferValues[i], logBufferContents[i]);
    }
    // Buffer should be empty now
    log_size = (_logByteStream->length(_logByteStream));
    EXPECT_EQ(log_size, 0);
}
