/* See LICENSE file for copyright and license details. */

#include <stdlib.h>

// clang-format off
#define MAX(A, B)	   	 ((A) > (B) ? (A) : (B))
#define MIN(A, B)	  	 ((A) < (B) ? (A) : (B))
#define CLAMP(X, A, B) 	 ((X) < (A) ? (A) : (X) > (B) ? (B) : (X))
#define BETWEEN(X, A, B) ((A) <= (X) && (X) <= (B))
// clang-format on

void  die(const char *fmt, ...);
void *ecalloc(size_t nmemb, size_t size);
