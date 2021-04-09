#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  uint16_t *p16;

  if (len < 16) return 0;

  p16 = (uint16_t *)(buf);
  if (*p16 != 0x1122) return 0;

  p16 = (uint16_t *)(buf + 2);
  if (*p16 != 0x3344) return 0;

  p16 = (uint16_t *)(buf + 4);
  if (*p16 != 0x5566) return 0;

  p16 = (uint16_t *)(buf + 6);
  if (*p16 != 0x7788) return 0;

  p16 = (uint16_t *)(buf + 8);
  if (*p16 != 0xa0a1) return 0;

  p16 = (uint16_t *)(buf + 10);
  if (*p16 != 0xa2a3) return 0;

  p16 = (uint16_t *)(buf + 12);
  if (*p16 != 0x1234) return 0;

  p16 = (uint16_t *)(buf + 14);
  if (*p16 != 0xaabb) return 0;

  abort();

  return 0;

}

#ifdef __AFL_COMPILER
int main(int argc, char **argv) {

  unsigned char buf[16];
  ssize_t       len;
  int           fd = 0;
  if (argc > 1) fd = open(argv[1], O_RDONLY);

  if ((len = read(fd, buf, sizeof(buf))) <= 0) exit(0);

  LLVMFuzzerTestOneInput(buf, len);
  exit(0);

}

#endif

