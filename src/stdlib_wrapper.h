#ifndef __STDLIB_WRAPPER_H__
#define __STDLIB_WRAPPER_H__

size_t strnncpy(char *dest, size_t dest_size, const char *src, size_t src_len);
void *xcalloc(size_t nmemb, size_t size);
char *xstrdup(const char *ptr);
void xfree(void *ptr);
void xfree_overwrite(char *ptr);
void logmsg(int level, const char *format, ...);

#endif /* __STDLIB_WRAPPER_H__ */
