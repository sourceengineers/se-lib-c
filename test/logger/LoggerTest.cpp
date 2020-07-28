#include <gtest/gtest.h>

extern "C" {
#include <se-lib-c/logger/Logger.h>
#include <se-lib-c/logger/ILogger.h>
#include <stream/MockByteStream.h>
}

class LoggerTest : public ::testing::Test
{
protected:


    LoggerTest()
            : Test()
    {

    }

    LoggerHandle loggerHandle;
    ILoggerHandle iLoggerHandle;
    severity log_severity;
    size_t buf_size;
    MockByteStream _byteStream;

    void SetUp() override
    {
        MockByteStream_init(&_byteStream);
        log_severity = SC_WARNING;
        buf_size = 100;
        loggerHandle = Logger_create(buf_size, MockByteStream_getBytestreamInterface(&_byteStream));       /* create LoggerHandle */
        iLoggerHandle = Logger_getILogger(loggerHandle);        /* get the interface  */
    }

    void TearDown() override
    {
        LoggerDestroy(loggerHandle);
    }

    virtual ~LoggerTest()
    {

    }
};

TEST_F(LoggerTest, LoggerCreated)
{
    /* check if the logger exists */
    EXPECT_NE(nullptr, &loggerHandle);
    EXPECT_NE(nullptr, &iLoggerHandle);
    EXPECT_NE(nullptr, &_byteStream);
}

TEST_F(LoggerTest, LogFunctionality)
{
    const char logMsg[] = "Hello World!";
    iLoggerHandle->log(iLoggerHandle, log_severity, logMsg);
    EXPECT_STREQ("WARNING: Hello World!", Logger_getBuffer(loggerHandle));
    EXPECT_STREQ("WARNING: Hello World!", _byteStream.stringBuffer);
}

TEST_F(LoggerTest, LongMessage)
{
    //200 char long log message, should be shortened
    const char longLogMsg[] = "Lorem ipsum dolor sit amet, consetetur sadipscing "
                              "elitr, sed diam nonumy eirmod tempor invidunt ut "
                              "labore et dolore magna aliquyam erat, sed diam "
                              "voluptua. At vero eos et accusam et justo duo dolores ";
    iLoggerHandle->log(iLoggerHandle, log_severity, longLogMsg);

    /* Log level will be added, String will be shortened */
    EXPECT_STREQ("WARNING: Lorem ipsum dolor sit amet, consetetur "
                 "sadipscing elitr, sed diam nonumy eirmod tempor invi",
                 Logger_getBuffer(loggerHandle));
}


TEST_F(LoggerTest, BufferOverflow)
{
    const char bufferOverflowMsg[] = "TEST_BUFFER_OVERFLOW_1234567890";
    iLoggerHandle->log(iLoggerHandle, log_severity, bufferOverflowMsg);
    EXPECT_STREQ("SCOPE BUF OVFL;",Logger_getBuffer(loggerHandle));
}


TEST_F(LoggerTest, severities)
{
    severity sev_info = SC_INFO;
    severity sev_debug = SC_DEBUG;
    severity sev_warning = SC_WARNING;
    severity sev_error = SC_ERROR;

    const char logMsg[] = "Log Message";
    iLoggerHandle->log(iLoggerHandle, sev_info, logMsg);
    EXPECT_STREQ("INFO: Log Message",
                 Logger_getBuffer(loggerHandle));
    iLoggerHandle->log(iLoggerHandle, sev_debug, logMsg);
    EXPECT_STREQ("DEBUG: Log Message",
                 Logger_getBuffer(loggerHandle));
    iLoggerHandle->log(iLoggerHandle, sev_warning, logMsg);
    EXPECT_STREQ("WARNING: Log Message",
                 Logger_getBuffer(loggerHandle));
    iLoggerHandle->log(iLoggerHandle, sev_error, logMsg);
    EXPECT_STREQ("ERROR: Log Message",
                 Logger_getBuffer(loggerHandle));
}

TEST_F(LoggerTest, multiple_instances)
{
    MockByteStream _byteStream1;
    MockByteStream _byteStream2;

    MockByteStream_init(&_byteStream1);
    MockByteStream_init(&_byteStream2);

    LoggerHandle loggerHandle1 = Logger_create(buf_size, MockByteStream_getBytestreamInterface(&_byteStream1));
    LoggerHandle loggerHandle2 = Logger_create(buf_size, MockByteStream_getBytestreamInterface(&_byteStream2));

    ILoggerHandle iLoggerHandle1 = Logger_getILogger(loggerHandle1);
    ILoggerHandle iLoggerHandle2 = Logger_getILogger(loggerHandle2);


    iLoggerHandle1->log(iLoggerHandle1, log_severity, "Test 1");
    iLoggerHandle2->log(iLoggerHandle2, log_severity, "Test 2");

    EXPECT_STREQ("WARNING: Test 1",
                 Logger_getBuffer(loggerHandle1));

    EXPECT_STREQ("WARNING: Test 2",
                 Logger_getBuffer(loggerHandle2));
}
