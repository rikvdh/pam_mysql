#include <unity.h>
#include <unity_fixture.h>

TEST_GROUP(ProductionCode);

TEST_SETUP(ProductionCode)
{
}

TEST_TEAR_DOWN(ProductionCode)
{
}

TEST(ProductionCode, boembats)
{
  TEST_ASSERT_EQUAL(0, 0);
}

static void RunAllTests(void)
{
	RUN_TEST_CASE(ProductionCode, boembats);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}
