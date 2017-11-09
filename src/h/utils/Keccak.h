#pragma once

/*
Source: 5b0a851 on Aug 6, 2015	
https://github.com/gvanas/KeccakCodePackage/raw/master/Standalone/CompactFIPS202/Keccak-more-compact.c

License:
http://creativecommons.org/publicdomain/zero/1.0/
*/

#define FOR(i,n) for(i=0; i<n; ++i)
typedef unsigned char u8;
typedef unsigned long long int u64;
typedef unsigned int ui;

void Keccak(ui r, ui c, const u8 *in, u64 inLen, u8 sfx, u8 *out, u64 outLen);
void FIPS202_SHAKE128(const u8 *in, u64 inLen, u8 *out, u64 outLen) { Keccak(1344, 256, in, inLen, 0x1F, out, outLen); }
void FIPS202_SHAKE256(const u8 *in, u64 inLen, u8 *out, u64 outLen) { Keccak(1088, 512, in, inLen, 0x1F, out, outLen); }
void FIPS202_SHA3_224(const u8 *in, u64 inLen, u8 *out) { Keccak(1152, 448, in, inLen, 0x06, out, 28); }
void FIPS202_SHA3_256(const u8 *in, u64 inLen, u8 *out) { Keccak(1088, 512, in, inLen, 0x06, out, 32); }
void FIPS202_SHA3_384(const u8 *in, u64 inLen, u8 *out) { Keccak(832, 768, in, inLen, 0x06, out, 48); }
void FIPS202_SHA3_512(const u8 *in, u64 inLen, u8 *out) { Keccak(576, 1024, in, inLen, 0x06, out, 64); }

int LFSR86540(u8 *R) { (*R) = ((*R) << 1) ^ (((*R) & 0x80) ? 0x71 : 0); return ((*R) & 2) >> 1; }
#define ROL(a,o) ((((u64)a)<<o)^(((u64)a)>>(64-o)))
static u64 load64(const u8 *x) { ui i; u64 u = 0; FOR(i, 8) { u <<= 8; u |= x[7 - i]; } return u; }
static void store64(u8 *x, u64 u) { ui i; FOR(i, 8) { x[i] = u; u >>= 8; } }
static void xor64(u8 *x, u64 u) { ui i; FOR(i, 8) { x[i] ^= u; u >>= 8; } }
#define rL(x,y) load64((u8*)s+8*(x+5*y))
#define wL(x,y,l) store64((u8*)s+8*(x+5*y),l)
#define XL(x,y,l) xor64((u8*)s+8*(x+5*y),l)
void KeccakF1600(void *s)
{
	ui r, x, y, i, j, Y; u8 R = 0x01; u64 C[5], D;
	for (i = 0; i<24; i++) {
		/*θ*/ FOR(x, 5) C[x] = rL(x, 0) ^ rL(x, 1) ^ rL(x, 2) ^ rL(x, 3) ^ rL(x, 4); FOR(x, 5) { D = C[(x + 4) % 5] ^ ROL(C[(x + 1) % 5], 1); FOR(y, 5) XL(x, y, D); }
		/*ρπ*/ x = 1; y = r = 0; D = rL(x, y); FOR(j, 24) { r += j + 1; Y = (2 * x + 3 * y) % 5; x = y; y = Y; C[0] = rL(x, y); wL(x, y, ROL(D, r % 64)); D = C[0]; }
		/*χ*/ FOR(y, 5) { FOR(x, 5) C[x] = rL(x, y); FOR(x, 5) wL(x, y, C[x] ^ ((~C[(x + 1) % 5])&C[(x + 2) % 5])); }
		/*ι*/ FOR(j, 7) if (LFSR86540(&R)) XL(0, 0, (u64)1 << ((1 << j) - 1));
	}
}
void Keccak(ui r, ui c, const u8 *in, u64 inLen, u8 sfx, u8 *out, u64 outLen)
{
	/*initialize*/ u8 s[200]; ui R = r / 8; ui i, b = 0; FOR(i, 200) s[i] = 0;
	/*absorb*/ while (inLen>0) { b = (inLen<R) ? inLen : R; FOR(i, b) s[i] ^= in[i]; in += b; inLen -= b; if (b == R) { KeccakF1600(s); b = 0; } }
	/*pad*/ s[b] ^= sfx; if ((sfx & 0x80) && (b == (R - 1))) KeccakF1600(s); s[R - 1] ^= 0x80; KeccakF1600(s);
	/*squeeze*/ while (outLen>0) { b = (outLen<R) ? outLen : R; FOR(i, b) out[i] = s[i]; out += b; outLen -= b; if (outLen>0) KeccakF1600(s); }
}

/*
Source: KeccakCodePackage
https://raw.githubusercontent.com/gvanas/KeccakCodePackage/d85671d320e762d666db542abedd07c67c4f522b/KeccakSum/KeccakSum.c
License:
http://creativecommons.org/publicdomain/zero/1.0/
git HEAD: 215099f on Jul 2017
*/
int hexencode(const void* data_buf, size_t dataLength, char* result, size_t resultSize) {
	const char hexchars[] = "0123456789abcdef";
	const uint8_t *data = (const uint8_t *)data_buf;
	size_t resultIndex = 0;
	size_t x;

	for (x = 0; x < dataLength; x++) {
		if (resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
		result[resultIndex++] = hexchars[(data[x] / 16) % 16];
		if (resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
		result[resultIndex++] = hexchars[data[x] % 16];
	}
	if (resultIndex >= resultSize) return 1;   /* indicate failure: buffer too small */
	result[resultIndex] = 0;
	return 0;   /* indicate success */
}