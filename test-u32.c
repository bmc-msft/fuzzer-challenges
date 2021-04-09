#include <string.h>
#include <stdint.h>
#include <stdlib.h>


int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  uint32_t *p32;

  if (len < 24) return 0;

  p32 = (uint32_t *)(buf);
  if (*p32 != 0x11223344) return 0;

  p32 = (uint32_t *)(buf + 4);
  if (*p32 != 0x55667788) return 0;

  p32 = (uint32_t *)(buf + 8);
  if (*p32 != 0xa0a1a2a3) return 0;

  p32 = (uint32_t *)(buf + 12);
  if (*p32 != 0xa4a5a6a7) return 0;

  p32 = (uint32_t *)(buf + 16);
  if (*p32 != 0x1234aabb) return 0;

  abort();

  return 0;

}

#ifdef __AFL_COMPILER
int main(int argc, char **argv) {

  unsigned char buf[32];
  ssize_t       len;
  int           fd = 0;
  if (argc > 1) fd = open(argv[1], O_RDONLY);

  if ((len = read(fd, buf, sizeof(buf))) <= 0) exit(0);

  LLVMFuzzerTestOneInput(buf, len);
  exit(0);

}

#endif

