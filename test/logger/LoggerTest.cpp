#include <gtest/gtest.h>

extern "C" {
#include <se-lib-c/logger/Logger.h>
}

class LoggerTest : public ::testing::Test
{
protected:
    LoggerTest()
            : Test()
    {
    }

    void SetUp() override
    {
        buf_size = 100;
        log_severity = WARNING;
        loggerHandle = Logger_create(buf_size);              /* create LoggerHandle */
        iLoggerHandle = Logger_getILogger(loggerHandle);        /* get the interface  */
    }

    void TearDown() override
    {
        LoggerDestroy(loggerHandle);
    }

    virtual ~LoggerTest()
    {

    }

    LoggerHandle loggerHandle;
    ILoggerHandle iLoggerHandle;
    severity log_severity;
    size_t buf_size;
};

TEST_F(LoggerTest, LoggerCreated)
{
    /* check if the logger exists */
    EXPECT_NE(nullptr, loggerHandle);
    EXPECT_NE(nullptr, iLoggerHandle);
}

TEST_F(LoggerTest, LogFunctionality)
{
    const char logMsg[] = "Hello World!";
    iLoggerHandle->log(iLoggerHandle, log_severity, logMsg);
    EXPECT_STREQ("WARNING: Hello World!", Logger_getBuffer(loggerHandle));
}

TEST_F(LoggerTest, LongMessage)
{
    //200 char long log message
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

TEST_F(LoggerTest, severities)
{
    //TODO check the various severities
}

TEST_F(LoggerTest, multiple_logs)
{
    //TODO log multiple logs one after another, see if this works
}

