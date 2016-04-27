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

static void (*happy_flow_cleanup)(pam_handle_t *pamh, void *data, int error_status) = NULL;
static void *happy_flow_data = NULL;
void happy_flow_set_data_cb(pam_handle_t *pamh, const char *module_data_name, void *data,
			    void (*cleanup)(pam_handle_t *pamh, void *data, int error_status)) {
	TEST_ASSERT_EQUAL(NULL, pamh);
	TEST_ASSERT_EQUAL_STRING("pam_mysql", module_data_name);
	happy_flow_cleanup = cleanup;
	happy_flow_data = data;
}

TEST(PamMysqlAuthenticate, happy_flow)
{
	pam_handle_t *pamh = NULL;
	int retval;

	pamstub_set_pam_get_data_retval(PAM_NO_MODULE_DATA);
	pamstub_set_pam_set_data_retval(PAM_SUCCESS);
	pamstub_set_pam_set_data_callback(happy_flow_set_data_cb);
	retval = pam_sm_authenticate(pamh, 0, 0, NULL);
	TEST_ASSERT_EQUAL(PAM_USER_UNKNOWN, retval);
	TEST_ASSERT_EQUAL(1, pamstub_get_pam_get_data_calls());
	TEST_ASSERT_EQUAL(1, pamstub_get_pam_set_data_calls());
	if (happy_flow_cleanup)
		happy_flow_cleanup(pamh, happy_flow_data, retval);
}

static void *happy_flow_data_a = NULL;
void happy_flow_get_data_a_cb(const pam_handle_t *pamh, const char *module_data_name, const void **data) {
	TEST_ASSERT_EQUAL(NULL, pamh);
	TEST_ASSERT_EQUAL_STRING("pam_mysql", module_data_name);
	*data = happy_flow_data_a;
}

TEST(PamMysqlAuthenticate, happy_flow_already_alloc)
{
	pam_handle_t *pamh = NULL;
	int retval;

	pamstub_set_pam_get_data_retval(PAM_SUCCESS);
	pamstub_set_pam_get_data_callback(happy_flow_get_data_a_cb);
	happy_flow_data_a = calloc(1024, sizeof(char));
	retval = pam_sm_authenticate(pamh, 0, 0, NULL);
	free(happy_flow_data_a);
	TEST_ASSERT_EQUAL(PAM_USER_UNKNOWN, retval);
	TEST_ASSERT_EQUAL(1, pamstub_get_pam_get_data_calls());
	TEST_ASSERT_EQUAL(0, pamstub_get_pam_set_data_calls());
}

static void RunAllTests(void)
{
	RUN_TEST_CASE(PamMysqlAuthenticate, invalid_getdatareturn);
	RUN_TEST_CASE(PamMysqlAuthenticate, set_data_fail);
	RUN_TEST_CASE(PamMysqlAuthenticate, happy_flow);
	RUN_TEST_CASE(PamMysqlAuthenticate, happy_flow_already_alloc);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}
