
AUTOMAKE_OPTIONS = subdir-objects foreign

libdir=@PAM_MODS_DIR@
lib_LTLIBRARIES=pam_mysql.la
noinst_FILES=pam_mysql.la pam_mysql.a
pam_mysql_la_SOURCES=src/pam_mysql.c
pam_mysql_la_LDFLAGS=-module -avoid-version

EXTRA_DIST = COPYING NEWS README.md CREDITS ChangeLog INSTALL pam_mysql.spec.in install-sh missing mkinstalldirs pam_mysql.spec
