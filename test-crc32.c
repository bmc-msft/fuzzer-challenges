#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t crc32(uint8_t *s, size_t n) {
  uint32_t crc = 0xFFFFFFFF;

  for (size_t i = 0; i < n; i++) {

    char ch = s[i];

    for (size_t j = 0; j < 8; j++) {

      uint32_t b = (ch ^ crc) & 1;

      crc >>= 1;
      if (b) crc = crc ^ 0xEDB88320;
      ch >>= 1;

    }

  }

  return ~crc;
}

int LLVMFuzzerTestOneInput(uint8_t *buf, size_t len) {

  uint32_t *p32, crc, i;
  uint8_t   buff[40];

  if (len < 36) return 0;

  // libfuzzer workaround
  memcpy(buff, buf, 36);
  buff[36] = 0;

  if (buff[0] != 'B') return 0;
  if (buff[1] != 'A') return 0;
  if (buff[2] != 'R') return 0;
  if (buff[3] != 'F') return 0;
  for (i = 1; i < 4; i++) {

    buff[i * 4 - 1] = 'E' + i;  // no duplicate crc
    crc = crc32(buff, i * 4);
    p32 = (uint32_t *)(buff + i * 4);
    if (*p32 != crc) return 0;
  }

  abort();

  return 0;
}
