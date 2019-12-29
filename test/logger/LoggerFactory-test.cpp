#include <gtest/gtest.h>

extern "C" {
#include <Logger/Builders/LoggerBuilder.h>
}

using namespace testing;
using namespace std;

TEST(logger_stream, test_setupStreams){
    char* message;
    LoggerBuilderHandle builder = LoggerBuilder_create();
    LoggerBuilder_setBufferSize(builder,10);

    BufferedByteStreamHandle streamer;
    streamer = BufferedByteStream_create(1000);

    LoggerBuilder_setStream(builder,BufferedByteStream_getIByteStream(streamer));
    LoggerObject obj = LoggerBuilder_build(builder);


    obj.logger->log(obj.logger, INFO, "Hello World...");
    obj.logger->log(obj.logger, DEBUG, "Second Message");
    obj.logger->log(obj.logger, WARNING, "Third Message");
    obj.logger->log(obj.logger, ERROR, "Forth Message");

    message = LoggerBuilder_getBufferedByteStream(builder);

    ASSERT_STREQ(message,"INFO_Hello World...\nDEBUG_Second Message\nWARNING_Third Message\nERROR_Forth Message\n");


    LoggerBuilder_destroy(builder);
}


TEST(logger_factory_test, test_create){

    const char* buffer;
    const char* logMessage = "Hello World... and Hello to all the Rest";
    LoggerBuilderHandle builder = LoggerBuilder_create();
    LoggerBuilder_setBufferSize(builder,10);

    LoggerObject obj = LoggerBuilder_build(builder);

    obj.logger->log(obj.logger, INFO, logMessage);
    buffer = LoggerBuilder_getBuffer(builder);
    ASSERT_STREQ(buffer,logMessage);

    LoggerBuilder_destroy(builder);
}