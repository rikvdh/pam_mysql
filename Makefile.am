
AUTOMAKE_OPTIONS = subdir-objects foreign

libdir=@PAM_MODS_DIR@
lib_LTLIBRARIES=pam_mysql.la
noinst_FILES=pam_mysql.la pam_mysql.a
pam_mysql_la_SOURCES=src/pam_mysql.c
pam_mysql_la_LDFLAGS=-module -avoid-version

#AM_CPPFLAGS = -std=gnu99 -Wall -Wextra -Wshadow -D_FORTIFY_SOURCE=2 -fstrict-aliasing -Wformat -Wformat-security -Wmaybe-uninitialized -Wimplicit-function-declaration -Wredundant-decls -Wundef -Werror -O2 -Wl,-z,relro -Wl,-z,now -fPIC
AM_CPPFLAGS = -std=gnu99 -Wall -Wextra -D_FORTIFY_SOURCE=2 -fstrict-aliasing -Wformat -Wformat-security -Wmaybe-uninitialized -Wimplicit-function-declaration -Wundef -Werror -O2 -Wl,-z,relro -Wl,-z,now -fPIC
EXTRA_DIST = COPYING NEWS README.md CREDITS ChangeLog INSTALL pam_mysql.spec.in pam_mysql.spec
