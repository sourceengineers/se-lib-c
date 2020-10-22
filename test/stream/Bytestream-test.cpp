#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <se-lib-c/stream/BufferedByteStream.h>
}

using namespace std;

TEST(Bytestream, test_read_write_single){
    IByteStreamHandle stream = BufferedByteStream_getIByteStream(BufferedByteStream_create(4));

    ASSERT_TRUE(stream->writeByte(stream, '\x11'));
    ASSERT_TRUE(stream->writeByte(stream, '\x22'));
    ASSERT_TRUE(stream->writeByte(stream, '\x33'));
    ASSERT_TRUE(stream->writeByte(stream, '\x44'));
    ASSERT_FALSE(stream->writeByte(stream, '\x55'));

    size_t length = stream->length(stream);
    ASSERT_EQ(length, 4);

    bool byteIsReady = stream->byteIsReady(stream);
    ASSERT_EQ(byteIsReady, true);
    char byte = stream->readByte(stream);
    ASSERT_EQ(byte, '\x11');

    byteIsReady = stream->byteIsReady(stream);
    ASSERT_EQ(byteIsReady, true);
    byte = stream->readByte(stream);
    ASSERT_EQ(byte, '\x22');

    byteIsReady = stream->byteIsReady(stream);
    ASSERT_EQ(byteIsReady, true);
    byte = stream->readByte(stream);
    ASSERT_EQ(byte, '\x33');

    byteIsReady = stream->byteIsReady(stream);
    ASSERT_EQ(byteIsReady, true);
    byte = stream->readByte(stream);
    ASSERT_EQ(byte, '\x44');

    byteIsReady = stream->byteIsReady(stream);
    ASSERT_EQ(byteIsReady, false);
}

TEST(Bytestream, test_read_write_packets){
    IByteStreamHandle stream = BufferedByteStream_getIByteStream(BufferedByteStream_create(4));

    ASSERT_TRUE(stream->write(stream, (const uint8_t*) "\x11\x22\x33\x44", 4));

    size_t length = stream->length(stream);
    ASSERT_EQ(length, 4);

    uint8_t data[4];
    stream->read(stream, data, 4);

    ASSERT_THAT(data, testing::ElementsAre('\x11', '\x22', '\x33', '\x44'));
}

TEST(Bytestream, test_flush){
    IByteStreamHandle stream = BufferedByteStream_getIByteStream(BufferedByteStream_create(4));

    ASSERT_TRUE(stream->write(stream, (const uint8_t*) "\x11\x22\x33\x44", 4));
    stream->flush(stream);

    size_t length = stream->length(stream);
    ASSERT_EQ(length, 0);
}

TEST(Bytestream, test_writeByte_overflow){
    IByteStreamHandle stream = BufferedByteStream_getIByteStream(BufferedByteStream_create(4));
    ASSERT_TRUE(stream->writeByte(stream, '\x11'));
    ASSERT_TRUE(stream->writeByte(stream, '\x22'));
    ASSERT_TRUE(stream->writeByte(stream, '\x33'));
    ASSERT_TRUE(stream->writeByte(stream, '\x44'));
    ASSERT_FALSE(stream->writeByte(stream, '\x55'));
}

TEST(Bytestream, test_write_overflow){
    IByteStreamHandle stream = BufferedByteStream_getIByteStream(BufferedByteStream_create(4));
    uint8_t data[] = {1, 2, 3, 4, 5};
    size_t len = 5;
    ASSERT_FALSE(stream->write(stream, data, len));
}