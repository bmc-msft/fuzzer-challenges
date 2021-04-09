#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  uint32_t *p32, lesser, greater;

  if (len < 24) return 0;

  p32 = (uint32_t *)(buf);
  lesser = 100100;
  greater = 100102;
  if (*p32 <= lesser || *p32 >= greater) return 0;

  p32 = (uint32_t *)(buf + 4);
  lesser = 2100;
  greater = 2102;
  if (*p32 <= lesser || *p32 >= greater) return 0;

  p32 = (uint32_t *)(buf + 8);
  lesser = 1234567;
  greater = 1234569;
  if (*p32 <= lesser || *p32 >= greater) return 0;

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

