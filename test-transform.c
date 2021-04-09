#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

static uint8_t hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                          '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
static uint8_t dehex[] = {0, 1, 2, 3,  4,  5,  6,  7,  8,  9,  0,  0,  0, 0,
                          0, 0, 0, 10, 11, 12, 13, 14, 15, 0,  0,  0,  0, 0,
                          0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
                          0, 0, 0, 0,  0,  0,  0,  10, 11, 12, 13, 14, 15};

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  uint8_t * p8;
  uint32_t *p32;
  int       i;
  uint8_t   buff[100], tmp[20];
  size_t    result;

  if (len < 48) return 0;
  if (len > sizeof(buff)) return 0;

  // libfuzzer workaround
  memcpy(buff, buf, len);
  buff[sizeof(buff) - 1] = 0;

  // string to int
  if (atoi((char *)buff) != 66766) return 0;

  // integer arithmetic modification
  p32 = (uint32_t *)(buff + 6);
  *p32 -= 0x100;
  if (*p32 != 0x200) return 0;

  // integer xor modification
  p32 = (uint32_t *)(buff + 10);
  *p32 ^= 0xa50ff05a;
  if (*p32 != 0x11002200) return 0;

  // cesar cipher
  for (i = 0; i < 10; i++)
    buff[i + 14] = buff[i + 14] + 5;
  if (memcmp(buff + 14, "MNOPQRSTUVW", 10)) return 0;

  // must be uppercase, transformed to lowercase
  for (i = 0; i < 5; i++)
    if (isupper(buff[i + 24]))
      buff[i + 24] = tolower(buff[i + 24]);
    else
      return 0;
  if (strncmp((char *)buff + 24, "abcdefghijk", 5)) return 0;

  for (i = 0; i < 8; i++) {

    tmp[i << 1] = hex[buff[i + 30] >> 4];
    tmp[(i << 1) + 1] = hex[buff[i + 30] % 16];

  }

  tmp[16] = 0;
  if (strncmp((char *)tmp, "4142434445464748", 16)) return 0;

  for (i = 0; i < 4; i++) {

    if (((buff[38 + (i << 1)] >= 'a' && buff[38 + (i << 1)] <= 'f') ||
         (buff[38 + (i << 1)] >= '0' && buff[38 + (i << 1)] <= '9')) &&
        ((buff[38 + (i << 1) + 1] >= 'a' && buff[38 + (i << 1) + 1] <= 'f') ||
         (buff[38 + (i << 1) + 1] >= '0' && buff[38 + (i << 1) + 1] <= '9'))) {

      tmp[i] = (uint8_t)(dehex[buff[38 + (i << 1)] - '0'] << 4) +
               (uint8_t)dehex[buff[38 + (i << 1) + 1] - '0'];

    } else

      return 0;

  }

  tmp[4] = 0;
  if (strncmp((char *)tmp, "FOOO", 4)) return 0;

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

