/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h>

#if defined(__APPLE__)
#define COMMON_DIGEST_FOR_OPENSSL
#include <CommonCrypto/CommonDigest.h>
#define SHA1FUNC CC_SHA1
#define SHA256FUNC CC_SHA256
#else
#include <openssl/sha.h>
#define SHA1FUNC SHA1
#define SHA256FUNC SHA256
#endif

#include <round/util/digest.h>
#include <round/util/strings.h>

////////////////////////////////////////
// MD5
////////////////////////////////////////

#if defined(ROUND_SUPPORT_MD_5DIGEST)

bool round_md5_digest(const char* string, char** buf)
{
  char* md5DigestString = (char*)malloc((MD5_DIGEST_LENGTH * 2) + 1);

  unsigned char md5Digest[MD5_DIGEST_LENGTH];
  MD5FUNC(string, (int)round_strlen(string), md5Digest);

  char hexString[3];
  for (int n = 0; n < MD5_DIGEST_LENGTH; n++) {
    snprintf(hexString, sizeof(hexString), "%02X", md5Digest[n]);
    md5DigestString[(n * 2) + 0] = hexString[0];
    md5DigestString[(n * 2) + 1] = hexString[1];
  }
  md5DigestString[(MD5_DIGEST_LENGTH * 2)] = '\0';

  *buf = md5DigestString;

  return true;
}

#endif

////////////////////////////////////////
// SHA1
////////////////////////////////////////

bool round_sha_digest(const char* string, char** buf)
{
  unsigned char shaDigest[SHA_DIGEST_LENGTH];
  char* shaDigestString = (char*)malloc((SHA_DIGEST_LENGTH * 2) + 1);

  SHA1FUNC(string, (int)round_strlen(string), shaDigest);

  char hexString[3];
  int n;
  for (n = 0; n < SHA_DIGEST_LENGTH; n++) {
    snprintf(hexString, sizeof(hexString), "%02X", shaDigest[n]);
    shaDigestString[(n * 2) + 0] = hexString[0];
    shaDigestString[(n * 2) + 1] = hexString[1];
  }
  shaDigestString[(SHA_DIGEST_LENGTH * 2)] = '\0';

  *buf = shaDigestString;

  return true;
}

////////////////////////////////////////
// SHA256
////////////////////////////////////////

bool round_sha256_digest(const char* string, char** buf)
{
  char* shaDigestString = (char*)malloc((SHA256_DIGEST_LENGTH * 2) + 1);

  unsigned char shaDigest[SHA256_DIGEST_LENGTH];
  SHA256FUNC(string, (int)round_strlen(string), shaDigest);

  char hexString[3];
  int n;
  for (n = 0; n < SHA256_DIGEST_LENGTH; n++) {
    snprintf(hexString, sizeof(hexString), "%02X", shaDigest[n]);
    shaDigestString[(n * 2) + 0] = hexString[0];
    shaDigestString[(n * 2) + 1] = hexString[1];
  }
  shaDigestString[(SHA256_DIGEST_LENGTH * 2)] = '\0';

  *buf = shaDigestString;

  return true;
}
