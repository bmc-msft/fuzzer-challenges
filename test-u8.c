#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  if (len < 12) return 0;

  if (buf[0] != 'A') return 0;
  if (buf[1] != 'C') return 0;
  if (buf[2] != 'E') return 0;
  if (buf[3] != 'G') return 0;
  if (buf[4] != 'I') return 0;
  if (buf[5] != 'K') return 0;
  if (buf[6] != 'M') return 0;
  if (buf[7] != 'Z') return 0;
  if (buf[8] != 'Y') return 0;
  if (buf[9] != 0) return 0;
  if (buf[10] != 1) return 0;
  if (buf[11] != 128) return 0;

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

