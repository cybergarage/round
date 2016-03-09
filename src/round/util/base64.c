/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/base64.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#include <round/util/strings.h>

/****************************************
 * round_base64_encode
 ****************************************/

ssize_t round_base64_encode(const byte *rawBytes, size_t rawByteLen, char **encodedStr)
{
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  BIO *bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, rawBytes, (int)rawByteLen);
  BIO_flush(b64);

  BUF_MEM *bufMem;
  BIO_get_mem_ptr(b64, &bufMem);
  size_t encodedSize = bufMem->length;
  
  *encodedStr = (char *)malloc(encodedSize+1);
  if (!(*encodedStr))
    return -1;
  
  memcpy(*encodedStr, bufMem->data, encodedSize);
  (*encodedStr)[encodedSize] = '\0';
 
  BIO_free_all(b64);

  return encodedSize;
}

/****************************************
 * round_base64_decode
 ****************************************/

ssize_t round_base64_decode(const char *encodedStr, byte **decordedBytes)
{
 size_t encodedStrSize = round_strlen(encodedStr);

 size_t decordedSize = (double)(encodedStrSize) * (3.0/4.0);
 if ((1 <= encodedStrSize) && (encodedStr[encodedStrSize-1] == '=')) {
   decordedSize--;
   if ((2 <= encodedStrSize) && (encodedStr[encodedStrSize-2] == '=')) {
     decordedSize--;
   }
 }

 *decordedBytes = (byte *)malloc(decordedSize + 1);
 if (!(*decordedBytes))
   return -1;

 BIO *b64 = BIO_new(BIO_f_base64());
 BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
 BIO *bmem = BIO_new_mem_buf((void *)encodedStr, (int)encodedStrSize);
 b64 = BIO_push(b64, bmem);
 size_t readLen = BIO_read(b64, *decordedBytes, (int)decordedSize);
 (*decordedBytes)[readLen] = '\0';
 BIO_free_all(b64);

 return readLen;
}
