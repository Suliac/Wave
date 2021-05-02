#include "pch.h"
#include "Wave/Transport/Common/Buffer.h"
#include "Wave/Transport/Common/IPEndPoint.h"

#include "Test/UnitTests/Fake/FakeUdpSocket.h"
namespace WaveTest
{
    TEST(Socket, SimpleSendRecv)
    {
        uint16_t currentPort = 65000;
        Wave::IPEndPoint destination(127, 0, 0, 1, 65001);

        //FakeUdpSocket fakeSocket;
        //EXPECT_EQ(fakeSocket.Open(Wave::IPEndPoint(0, currentPort)), Wave::SocketResult::OK);
        //
        //const uint8_t msgTest[] = "Hello from client !";

        // Try to read packet
        //Wave::Datagram recvData(512);
        //fakeSocket.InsertFakeDataRecv(msgTest, sizeof(msgTest));
        //
        //int32_t bytesRead;
        //EXPECT_EQ(fakeSocket.ReceiveFrom(recvData, bytesRead), Wave::SocketResult::OK);
        //EXPECT_TRUE(bytesRead > 0);
        //recvData.Reset();
        //
        //// Then send one
        //Wave::Datagram toSendData(sizeof(msgTest), destination); // TODO : remove the cpy of our endpoint struct
        //toSendData.GetBuffer().Insert(msgTest, sizeof(msgTest));
        //EXPECT_EQ(fakeSocket.SendTo(toSendData, (int32_t)toSendData.BufferSize()), Wave::SocketResult::OK);
        //EXPECT_EQ(fakeSocket.SendTo(toSendData, (int32_t)toSendData.BufferSize() + 10), Wave::SocketResult::SendFailed);
    }

    TEST(Buffer, Basics)
    {
        // 1 - Simple ctor
        Wave::Buffer buf(16);
        EXPECT_EQ(buf.GetIndex(), 0);
        EXPECT_EQ(buf.Size(), 16);

        // 2 - Set index
        EXPECT_TRUE(buf.SetIndex(10));
        EXPECT_FALSE(buf.SetIndex(32));

        // 3 - Reset
        buf.Reset();
        EXPECT_EQ(buf.GetIndex(), 0);
    }

    TEST(Buffer, Insert)
    {
        Wave::Buffer buf(16);

        const uint8_t msgTest[] = "this is a test";
        EXPECT_EQ(sizeof(msgTest), 15);

        // 1 - basic insert
        EXPECT_TRUE(buf.Insert(msgTest, sizeof(msgTest)));
        EXPECT_EQ(buf.GetIndex(), 15);

        // 2 - overflow insert
        EXPECT_FALSE(buf.Insert(msgTest, sizeof(msgTest)));
        EXPECT_EQ(buf.GetIndex(), 15); // index shouldn't have changed

        buf.Reset();

        // 3 - data size not matching with real size - dataSize < realSize
        EXPECT_TRUE(buf.Insert(msgTest, 10));
        EXPECT_EQ(buf.GetIndex(), 10);
        // NB : Giving data size > real size will give undefined behaviour :( use vector of byte instead ?

        // 4 - Insert a buffer inside another one
        Wave::Buffer buf2(13);
        EXPECT_TRUE(buf2.Insert(buf));
        EXPECT_EQ(buf2.GetIndex(), buf.GetIndex());

        // 5 - Try insert buffer into another one but overflow
        EXPECT_FALSE(buf2.Insert(buf));
        EXPECT_EQ(buf2.GetIndex(), 10);
    }

    TEST(Buffer, Copy)
    {
        const uint8_t msgTest[] = "this is a test";

        Wave::Buffer buf1(16);
        buf1.Insert(msgTest, sizeof(msgTest));

        // 1 - Simple copy
        Wave::Buffer buf2(16);
        EXPECT_TRUE(buf2.CopyFrom(buf1));
        EXPECT_EQ(buf1.GetIndex(), buf2.GetIndex());

        // 2 - Simple copy but overflow
        Wave::Buffer buf3(13);
        EXPECT_FALSE(buf3.CopyFrom(buf1));
        EXPECT_EQ(buf3.GetIndex(), 0);

        // 3 - Copy ctor
        Wave::Buffer buf4(buf1);
        EXPECT_EQ(buf1.GetIndex(), buf4.GetIndex());
        EXPECT_EQ(buf1.Size(), buf4.Size());
    }
}