#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  uint8_t *p8;

  if (len < 32) return 0;
  if (memcmp((char *)buf, "0123", 4)) return 0;
  if (memcmp((char *)buf + 4, "87654321", 8)) return 0;
  if (memcmp((char *)buf + 12, "ABCDEFHIKLMNOPQR", 16))
    return 0;
  if (len < 54) return 0;
  if (memcmp((char *)buf + 28, "ZYXWVUTSRQPONMLKJIHGFEDCBA", 26))
    return 0;

  abort();

  return 0;

}

#ifdef __AFL_COMPILER
int main(int argc, char **argv) {

  unsigned char buf[64];
  ssize_t       len;
  int           fd = 0;
  if (argc > 1) fd = open(argv[1], O_RDONLY);

  if ((len = read(fd, buf, sizeof(buf))) <= 0) exit(0);

  LLVMFuzzerTestOneInput(buf, len);
  exit(0);

}

#endif

