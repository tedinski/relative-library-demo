#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>
#include <stdlib.h>

// The code calling this should compile with -fpic to get offsets
// the the actual symbols, otherwise you risk getting the jump tables

const char *where_is(void *ptr)
{
  Dl_info info;
  int ret;
  
  ret = dladdr(ptr, &info);
  
  if (ret == 0) {
    fprintf(stderr, "Symbol lookup failed\n");
    exit(1);
  }
  
  return info.dli_fname;
}

