// MD5. Adapted from LibTomCrypt. This code is Public Domain
#include "md5.hpp"

#include <cstring>

typedef std::uint32_t u32;
typedef std::uint64_t u64;

static const unsigned char Worder[64] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,1,6,11,0,5,10,15,4,9,14,3,8,13,2,7,12,
  5,8,11,14,1,4,7,10,13,0,3,6,9,12,15,2,0,7,14,5,12,3,10,1,8,15,6,13,4,11,2,9
};

static const unsigned char Rorder[64] = {
  7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
  4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

static const u32 Korder[64] = {
  0xd76aa478UL, 0xe8c7b756UL, 0x242070dbUL, 0xc1bdceeeUL, 0xf57c0fafUL, 0x4787c62aUL, 0xa8304613UL, 0xfd469501UL,
  0x698098d8UL, 0x8b44f7afUL, 0xffff5bb1UL, 0x895cd7beUL, 0x6b901122UL, 0xfd987193UL, 0xa679438eUL, 0x49b40821UL,
  0xf61e2562UL, 0xc040b340UL, 0x265e5a51UL, 0xe9b6c7aaUL, 0xd62f105dUL, 0x02441453UL, 0xd8a1e681UL, 0xe7d3fbc8UL,
  0x21e1cde6UL, 0xc33707d6UL, 0xf4d50d87UL, 0x455a14edUL, 0xa9e3e905UL, 0xfcefa3f8UL, 0x676f02d9UL, 0x8d2a4c8aUL,
  0xfffa3942UL, 0x8771f681UL, 0x6d9d6122UL, 0xfde5380cUL, 0xa4beea44UL, 0x4bdecfa9UL, 0xf6bb4b60UL, 0xbebfbc70UL,
  0x289b7ec6UL, 0xeaa127faUL, 0xd4ef3085UL, 0x04881d05UL, 0xd9d4d039UL, 0xe6db99e5UL, 0x1fa27cf8UL, 0xc4ac5665UL,
  0xf4292244UL, 0x432aff97UL, 0xab9423a7UL, 0xfc93a039UL, 0x655b59c3UL, 0x8f0ccc92UL, 0xffeff47dUL, 0x85845dd1UL,
  0x6fa87e4fUL, 0xfe2ce6e0UL, 0xa3014314UL, 0x4e0811a1UL, 0xf7537e82UL, 0xbd3af235UL, 0x2ad7d2bbUL, 0xeb86d391UL
};

static u32 rol(u32 x, u32 n) {
  return (x << (n & 31)) | (x >> (32 - (n & 31)));
}

static u32 min(u32 x, u32 y) {
  return x < y ? x : y;
}

static u32 load32(const unsigned char* y) {
  return (u32(y[3]) << 24) | (u32(y[2]) << 16) | (u32(y[1]) << 8) | (u32(y[0]) << 0);
}

static void store64(u64 x, unsigned char* y) {
  for(int i = 0; i != 8; ++i) {
    y[i] = (x >> (i * 8)) & 255;
  }
}

static void store32(u32 x, unsigned char* y) {
  for(int i = 0; i != 4; ++i) {
    y[i] = (x >> (i * 8)) & 255;
  }
}

template<class Fun>
static void Round(Fun f, u32& a, u32 b, u32 c, u32 d, u32 M, u32 s, u32 t) {
  a = (a + f(b,c,d) + M + t);
  a = rol(a, s) + b;
}

static void md5_compress(md5_state &md, const unsigned char* buf) {
  u32 W[16], a, b, c, d, t;

  // Copy the state into 512-bits into W[0..15]
  for(int i = 0; i < 16; i++) {
    W[i] = load32(buf + (4*i));
  }
 
  // Copy state
  a = md.state[0];
  b = md.state[1];
  c = md.state[2];
  d = md.state[3];

  auto F = [](u32 x, u32 y, u32 z) { return z ^ (x & (y ^ z)); };
  auto G = [](u32 x, u32 y, u32 z) { return y ^ (z & (y ^ x)); };
  auto H = [](u32 x, u32 y, u32 z) { return x ^ y ^ z; };
  auto I = [](u32 x, u32 y, u32 z) { return y ^ (x | ~z); };

  for (int i = 0; i < 16; ++i) {
    Round(F, a, b, c, d, W[Worder[i]], Rorder[i], Korder[i]);
    t = d; d = c; c = b; b = a; a = t;
  }

  for (int i = 16; i < 32; ++i) {
    Round(G, a, b, c, d, W[Worder[i]], Rorder[i], Korder[i]);
    t = d; d = c; c = b; b = a; a = t;
  }

  for (int i = 32; i < 48; ++i) {
    Round(H, a, b, c, d, W[Worder[i]], Rorder[i], Korder[i]);
    t = d; d = c; c = b; b = a; a = t;
  }

  for (int i = 48; i < 64; ++i) {
    Round(I, a, b, c, d, W[Worder[i]], Rorder[i], Korder[i]);
    t = d; d = c; c = b; b = a; a = t;
  }

  md.state[0] += a;
  md.state[1] += b;
  md.state[2] += c;
  md.state[3] += d;
}

void md5_init(md5_state& md) {
  md.curlen = 0;
  md.length = 0;
  md.state[0] = 0x67452301UL;
  md.state[1] = 0xefcdab89UL;
  md.state[2] = 0x98badcfeUL;
  md.state[3] = 0x10325476UL;
}

void md5_process(md5_state& md, const void* src, std::uint32_t inlen) {
  const u32 block_size = sizeof(md5_state::buf);
  auto in = static_cast<const unsigned char*>(src);

  while(inlen > 0) {
    if(md.curlen == 0 && inlen >= block_size) {
      md5_compress(md, in);
      md.length += block_size * 8;
      in        += block_size;
      inlen     -= block_size;
    } else {
      u32 n = min(inlen, (block_size - md.curlen));
      std::memcpy(md.buf + md.curlen, in, n);
      md.curlen += n;
      in        += n;
      inlen     -= n;

      if(md.curlen == block_size) {
        md5_compress(md, md.buf);
        md.length += 8*block_size;
        md.curlen = 0;
      }
    }
  }
}

void md5_done(md5_state& md, void* out) {
  // Increase the length of the message.
  md.length += md.curlen * 8;

  // Append the '1' bit.
  md.buf[md.curlen++] = static_cast<unsigned char>(0x80);

  // If the length is currently above 56 bytes we append zeros then compress.
  // Then we can fall back to padding zeros and length encoding like normal.
  if(md.curlen > 56) {
    while (md.curlen < 64) {
      md.buf[md.curlen++] = 0;
    }
    md5_compress(md, md.buf);
    md.curlen = 0;
  }

  // Pad up to 56 bytes of zeroes.
  while(md.curlen < 56) {
    md.buf[md.curlen++] = 0;
  }

  // Store length.
  store64(md.length, md.buf+56);
  md5_compress(md, md.buf);

  // Copy output.
  for(int i = 0; i < 4; i++) {
    store32(md.state[i], static_cast<unsigned char*>(out)+(4*i));
  }
}
