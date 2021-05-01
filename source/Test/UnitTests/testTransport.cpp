#include "pch.h"
#include "Wave/Transport/Common/Buffer.h"
namespace WaveTest
{
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