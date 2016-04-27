#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <unity.h>
#include <unity_fixture.h>
#include <pam_stubs.h>

extern int pam_sm_authenticate(pam_handle_t * pamh, int flags, int argc, const char **argv);

TEST_GROUP(PamMysqlAuthenticateArgs);

TEST_SETUP(PamMysqlAuthenticateArgs)
{
}

TEST_TEAR_DOWN(PamMysqlAuthenticateArgs)
{
}

static void *happy_flow_data_a = NULL;
void auth_args_cb(const pam_handle_t *pamh, const char *module_data_name, const void **data) {
	TEST_ASSERT_EQUAL(NULL, pamh);
	TEST_ASSERT_EQUAL_STRING("pam_mysql", module_data_name);
	*data = happy_flow_data_a;
}

TEST(PamMysqlAuthenticateArgs, auth_args)
{
	char *args[] = {
		"host=localhost",
		"db=pamtest",
		"user=root",
		"passwd=root",
		"where=active=1",
		"table=users",
		"update_table=users2",
		"usercolumn=username",
		"passwdcolumn=password",
		"statcolumn=stat",
		"crypt_type=0",
		"md5=1",
		"verbose=1",
		"sqllog=1",
		"logtable=log",
		"logmsgcolumn=msg",
		"logpidcolumn=pid",
		"logusercolumn=user",
		"loghostcolumn=host",
		"logrhostcolumn=rhost",
		"logtimecolumn=time",
		"use_323_passwd=0",
		"disconnect_every_op=0",
		"invalid_option=boem"
	};
	pam_handle_t *pamh = NULL;
	int retval;

	pamstub_set_pam_get_data_retval(PAM_SUCCESS);
	pamstub_set_pam_get_data_callback(auth_args_cb);
	happy_flow_data_a = calloc(1024, sizeof(char));
	retval = pam_sm_authenticate(pamh, 0, 24, (const char **)args);
	free(happy_flow_data_a);
	TEST_ASSERT_EQUAL(PAM_USER_UNKNOWN, retval);
	TEST_ASSERT_EQUAL(1, pamstub_get_pam_get_data_calls());
	TEST_ASSERT_EQUAL(0, pamstub_get_pam_set_data_calls());
}

static void RunAllTests(void)
{
	RUN_TEST_CASE(PamMysqlAuthenticateArgs, auth_args);
}

int main(int argc, const char * argv[])
{
	return UnityMain(argc, argv, RunAllTests);
}
