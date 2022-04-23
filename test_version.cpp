#include "ip_address.h"

#include <gtest/gtest.h>

class TestVersion : public ::testing::Test
{
protected:
	void SetUp()
	{
		vs = version();
	}
	void TearDown() {}
	int vs;
};

TEST_F(TestVersion, test1)
{
	ASSERT_GE(vs, 0);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}