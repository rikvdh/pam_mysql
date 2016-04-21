#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <unity.h>
#include <unity_fixture.h>

extern int pam_sm_authenticate(pam_handle_t * pamh, int flags, int argc, const char **argv);

const struct pam_conv conv = {
	misc_conv,
	NULL
};

TEST_GROUP(ProductionCode);

TEST_SETUP(ProductionCode)
{
}

TEST_TEAR_DOWN(ProductionCode)
{
}

TEST(ProductionCode, boembats)
{
	pam_handle_t *pamh;
	int retval;

	retval = pam_start("check_user", "nobody", &conv, &pamh);

	// Are the credentials correct?
	if (retval == PAM_SUCCESS) {
		printf("Credentials accepted.\n");
		retval = pam_sm_authenticate(pamh, 0, 0, NULL);
	}

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
