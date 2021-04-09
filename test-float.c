#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <math.h>


int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  float *p32, lesser, greater;

  if (len < 16) return 0;

  p32 = (float *)(buf);
  lesser = 1000000.01;
  greater = 1000010.99;
  if (*p32 < lesser || *p32 > greater) return 0;
  if (!isnormal(*p32)) return 0;

  p32 = (float *)(buf + 4);
  lesser = 101.9;
  greater = 109.0;
  if (*p32 < lesser || *p32 > greater) return 0;
  if (!isnormal(*p32)) return 0;

  p32 = (float *)(buf + 8);
  lesser = 22222221.9;
  greater = 22222225.1;
  if (*p32 < lesser || *p32 > greater) return 0;
  if (!isnormal(*p32)) return 0;

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

