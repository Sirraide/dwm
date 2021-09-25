/* See LICENSE file for copyright and license details. */
#include "util.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__attribute__((malloc)) //
void *
	ecalloc(size_t nmemb, size_t size) {
	void *p;

	if (!(p = calloc(nmemb, size))) die("calloc:");
	return p;
}

__attribute__((noreturn))
__attribute__((format(printf, 1, 2))) //
void die(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);

	if (fmt[0] && fmt[strlen(fmt) - 1] == ':') fprintf(stderr, "\033[31m %s\033[0m\n", strerror(errno));
	else fputc('\n', stderr);

	exit(1);
}
