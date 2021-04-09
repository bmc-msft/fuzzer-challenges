#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  uint64_t *p64;

  if (len < 32) return 0;

  p64 = (uint64_t *)(buf);
  if (*p64 != 0x1122334455667788) return 0;

  p64 = (uint64_t *)(buf + 8);
  if (*p64 != 0xa0a1a2a3a4a5a6a7) return 0;

  p64 = (uint64_t *)(buf + 16);
  if (*p64 != 0x1234aabbccddeeff) return 0;

  p64 = (uint64_t *)(buf + 24);
  if (*p64 != 0x0f1f2f3f4f5f6f7f) return 0;

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

