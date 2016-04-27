#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_SYSLOG_H
#include <syslog.h>
#endif
#ifdef HAVE_STDARG_H
#include <stdarg.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include "stdlib_wrapper.h"

/* {{{ strnncpy */
size_t strnncpy(char *dest, size_t dest_size, const char *src, size_t src_len)
{
	size_t cpy_len;
	dest_size--;
	cpy_len = (dest_size < src_len ? dest_size: src_len);

	memcpy(dest, src, cpy_len);

	dest[cpy_len] = '\0';

	return cpy_len;
}
/* }}} */

/* {{{ xcalloc */
void *xcalloc(size_t nmemb, size_t size)
{
	void *retval;
	size_t total = nmemb * size;
	if (!total)
		return NULL;

	retval = calloc(nmemb, size);

	return retval;
}
/* }}} */

/* {{{ xrealloc */
void *xrealloc(void *ptr, size_t nmemb, size_t size)
{
	void *retval;
	size_t total = nmemb * size;

	if (!total)
		return NULL;

	retval = realloc(ptr, total);

	return retval;
}
/* }}} */

/* {{{ xstrdup */
char *xstrdup(const char *ptr)
{
	size_t len = strlen(ptr) + sizeof(char);
	char *retval = xcalloc(sizeof(char), len);

	if (retval == NULL)
		return NULL;

	memcpy(retval, ptr, len);

	return retval;
}
/* }}} */

/* {{{ xfree */
void xfree(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
}
/* }}} */

/* {{{ xfree_overwrite */
void xfree_overwrite(char *ptr)
{
	if (ptr != NULL) {
		char *p;
		for (p = ptr; *p != '\0'; p++)
			*p = '\0';
		free(ptr);
	}
}
/* }}} */

#ifndef LOG_AUTHPRIV
#define LOG_AUTHPRIV LOG_AUTH
#endif

void logmsg(int level, const char *format, ...)
{
	va_list args;
	va_start (args, format);

#ifdef DEBUG_BUILD
	switch (level) {
	case LOG_EMERG:
		printf("[emerg  ] ");
		break;
	case LOG_ALERT:
		printf("[alert  ] ");
		break;
	case LOG_CRIT:
		printf("[crit   ] ");
		break;
	case LOG_ERR:
		printf("[err    ] ");
		break;
	case LOG_WARNING:
		printf("[warning] ");
		break;
	case LOG_NOTICE:
		printf("[notice ] ");
		break;
	case LOG_INFO:
		printf("[info   ] ");
		break;
	case LOG_DEBUG:
		printf("[debug  ] ");
		break;
	default:
		printf("[<unknown>] ");
		break;
	}
	vprintf(format, args);
	printf("\n");
#else
	vsyslog(level | LOG_AUTHPRIV, format, args);
#endif
	va_end(args);
}
