#include <stdio.h>

const char *where_is(void *ptr);

int main()
{
  const char *anso = where_is(&where_is);
  const char *me = where_is(&main);
  const char *libc = where_is(&printf);

  printf("anso: %s\n", anso);
  printf("me: %s\n", me);
  printf("libc: %s\n", libc);
}
