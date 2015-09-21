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

/*
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
*/

/****************************************
 * round_base64_encode
 ****************************************/

/*
ssize_t round_base64_encode(const byte *inBytes, size_t rawByteLen, std::string *encodedStr)
{
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  BIO *bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, rawBytes, rawByteLen);
  BIO_flush(b64);
  
  BUF_MEM *bufMem;
  BIO_get_mem_ptr(b64, &bufMem);
  size_t encodedSize = bufMem->length;
  *encodedStr = std::string(bufMem->data, encodedSize);
  
  BIO_free_all(b64);
  
  return encodedSize;
}
*/

/****************************************
 * round_base64_decode
 ****************************************/
 /*
ssize_t round_base64_decode(const std::string &encodedStr, byte **decordedBytes);
ssize_t Round::Base64::Decode(const std::string &encodedStr, byte **decordedBytes) {
  size_t encodedStrSize = encodedStr.length();
  
  size_t decordedSize = (double)(encodedStrSize) * (3.0/4.0);
  if ((1 <= encodedStr.length()) && (encodedStr[encodedStrSize-1] == '=')) {
    decordedSize--;
    if ((2 <= encodedStr.length()) && (encodedStr[encodedStrSize-2] == '=')) {
      decordedSize--;
    }
  }
  
  *decordedBytes = (byte *)malloc(decordedSize + 1);
  if (!*decordedBytes)
    return -1;
  
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
  BIO *bmem = BIO_new_mem_buf((void *)encodedStr.c_str(), (int)encodedStrSize);
  b64 = BIO_push(b64, bmem);
  size_t readLen = BIO_read(b64, *decordedBytes, decordedSize);
  (*decordedBytes)[readLen] = '\0';
  BIO_free_all(b64);
  
  return readLen;
}
*/