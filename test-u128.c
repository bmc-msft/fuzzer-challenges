#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef unsigned __int128 uint128_t;

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  uint128_t *p128, v128, i;
  uint8_t *  p = (uint8_t *)&v128;

  if (len < 48) return 0;

  for (i = 0; i < 2; i++) {

    if (len < 16 + i * 16) return 0;
    p128 = (uint128_t *)(buf + i * 16);
    memset((char *)&v128, 'A' + i * 5, sizeof(v128));
    if (*p128 != v128) return 0;

  }

  for (i = 0; i < sizeof(v128); i++)
    p[i] = '0' + i * 2;
  p128 = (uint128_t *)(buf + 32);
  if (*p128 != v128) return 0;

  abort();

  return 0;

}

#ifdef __AFL_COMPILER
int main(int argc, char **argv) {

  unsigned char buf[128];
  ssize_t       len;
  int           fd = 0;
  if (argc > 1) fd = open(argv[1], O_RDONLY);

  if ((len = read(fd, buf, sizeof(buf))) <= 0) exit(0);

  LLVMFuzzerTestOneInput(buf, len);
  exit(0);

}

#endif

