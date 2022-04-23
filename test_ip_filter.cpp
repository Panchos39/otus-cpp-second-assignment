#include "ip_address.h"

#include <gtest/gtest.h>

const std::array<std::string, 12> ip_strings = {
			"46.51.22.11",
			"1.1.1.1",
			"127.0.0.1",
			"192.168.5.71",
			"122.53.16.37",
			"66.249.93.2",
			"66.249.92.198",
			"66.183.9.162",
			"66.169.196.128",
			"66.102.6.107",
			"65.208.151.112",
			"65.26.31.140"
		};

class TestIpFilter_1 : public ::testing::Test
{
protected:
	void SetUp()
	{

		for (auto ip_str : ip_strings){
			ip_pool.push_back(ip_address(ip_str, '.'));
		}

		filtered_pool = filter(ip_pool, 66);

	}
	void TearDown() {}
	
	std::vector<ip_address> ip_pool;
	std::vector<ip_address> filtered_pool;
};

class TestIpFilter_2 : public ::testing::Test
{
protected:
	void SetUp()
	{
		for (auto ip_str : ip_strings){
			ip_pool.push_back(ip_address(ip_str, '.'));
		}

		filtered_pool = filter(ip_pool, 66, 249);
	}
	void TearDown() {}
	std::vector<ip_address> ip_pool;
	std::vector<ip_address> filtered_pool;
};


class TestIpFilter_3 : public ::testing::Test
{
protected:
	void SetUp()
	{
		for (auto ip_str : ip_strings){
			ip_pool.push_back(ip_address(ip_str, '.'));
		}

		filtered_pool = filter_any(ip_pool, 1);
	}
	void TearDown() {}
	std::vector<ip_address> ip_pool;
	std::vector<ip_address> filtered_pool;
};



TEST_F(TestIpFilter_1, test_ip_filter_1)
{
	std::vector<ip_address> target = {
		ip_address(66, 249, 93, 2),
		ip_address(66, 249, 92, 198),
		ip_address(66, 183, 9, 162),
		ip_address(66, 169, 196, 128),
		ip_address(66, 102, 6, 107)
	};
	ASSERT_EQ(filtered_pool, target);
}

TEST_F(TestIpFilter_2, test_ip_filter_2)
{
	std::vector<ip_address> target = {
		ip_address(66, 249, 93, 2),
		ip_address(66, 249, 92, 198)
	};
	ASSERT_EQ(filtered_pool, target);
}


TEST_F(TestIpFilter_3, test_ip_filter_3)
{
	std::vector<ip_address> target = {
		ip_address(1, 1, 1, 1),
		ip_address(127, 0, 0, 1)
	};
	ASSERT_EQ(filtered_pool, target);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}