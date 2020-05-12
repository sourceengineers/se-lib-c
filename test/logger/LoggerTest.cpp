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

    LoggerHandle loggerHandle;
    ILoggerHandle iLoggerHandle;
    severity log_severity;
    size_t buf_size;

    void SetUp() override
    {
        log_severity = WARNING;
        buf_size = 100;
        loggerHandle = Logger_create(buf_size);                 /* create LoggerHandle */
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

TEST_F(LoggerTest, severities)
{
    severity sev_info = INFO;
    severity sev_debug = DEBUG;
    severity sev_warning = WARNING;
    severity sev_error = ERROR;

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
    LoggerHandle h1 = Logger_create(100);
    LoggerHandle h2 = Logger_create(200);

    ILoggerHandle ih1 = Logger_getILogger(h1);
    ILoggerHandle ih2 = Logger_getILogger(h2);

    ih1->log(ih1, log_severity, "Test 1");
    ih2->log(ih2, log_severity, "Test 2");

    EXPECT_STREQ("WARNING: Test 1",
                 Logger_getBuffer(h1));

    EXPECT_STREQ("WARNING: Test 2",
                 Logger_getBuffer(h2));
}
