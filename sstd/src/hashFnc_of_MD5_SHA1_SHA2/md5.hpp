// MD5. Adapted from LibTomCrypt. This code is Public Domain
#pragma once

#include <cstdint>

struct md5_state {
  std::uint64_t length;
  std::uint32_t state[4];
  std::uint32_t curlen;
  unsigned char buf[64];
};

void md5_init(md5_state& md);
void md5_process(md5_state& md, const void* in, std::uint32_t inlen);
void md5_done(md5_state& md, void* out);
