#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <unity.h>
#include <unity_fixture.h>
#include <pam_stubs.h>

extern int pam_sm_authenticate(pam_handle_t * pamh, int flags, int argc, const char **argv);

TEST_GROUP(PamMysqlAuthenticate);

TEST_SETUP(PamMysqlAuthenticate)
{
}

TEST_TEAR_DOWN(PamMysqlAuthenticate)
{
}

TEST(PamMysqlAuthenticate, invalid_getdatareturn)
{
	pam_handle_t *pamh = NULL;
	int retval;

	pamstub_set_pam_get_data_retval(-1);
	retval = pam_sm_authenticate(pamh, 0, 0, NULL);
	TEST_ASSERT_EQUAL(PAM_SERVICE_ERR, retval);
	TEST_ASSERT_EQUAL(1, pamstub_get_pam_get_data_calls());
	TEST_ASSERT_EQUAL(0, pamstub_get_pam_set_data_calls());

}

TEST(PamMysqlAuthenticate, set_data_fail)
{
	pam_handle_t *pamh = NULL;
	int retval;

	pamstub_set_pam_get_data_retval(PAM_NO_MODULE_DATA);
	pamstub_set_pam_set_data_retval(1);
	retval = pam_sm_authenticate(pamh, 0, 0, NULL);
	TEST_ASSERT_EQUAL(PAM_SERVICE_ERR, retval);
	TEST_ASSERT_EQUAL(1, pamstub_get_pam_get_data_calls());
	TEST_ASSERT_EQUAL(1, pamstub_get_pam_set_data_calls());
}

static void RunAllTests(void)
{
	RUN_TEST_CASE(PamMysqlAuthenticate, invalid_getdatareturn);
	RUN_TEST_CASE(PamMysqlAuthenticate, set_data_fail);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}
