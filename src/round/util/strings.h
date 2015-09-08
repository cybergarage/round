/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _ROUNDC_STRING_H_
#define _ROUNDC_STRING_H_

#include <round/typedef.h>
#include <stdlib.h>

#ifdef  __cplusplus
extern "C" {
#endif

/****************************************
* Define
****************************************/

#define ROUNDC_STRING_MEMORY_ALLOCATION_UNIT 64
 
/* UINT_MAX : 4294967295U */
#define ROUNDC_STRING_INTEGER_BUFLEN 16
 
 /* ULONG_MAX : 4294967295UL */
#define ROUNDC_STRING_LONG_BUFLEN 32

 /*  ULLONG_MAX : 18446744073709551615ULL */
#define ROUNDC_STRING_LONGLONG_BUFLEN 32

#define ROUNDC_STRING_FLOAT_BUFLEN 64
#define ROUNDC_STRING_DOUBLE_BUFLEN 64
  
/****************************************
* Function 
****************************************/
  
char *round_strdup(const char *str);
size_t round_strlen(const char *str);
char *round_strcpy(char *dst, const char *src);
char *round_strcat(char *dst, const char *src);
int round_strcmp(const char *str1, const char *str2);
int round_strncmp(const char *str1, const char *str2, int nchars);
int round_strcasecmp(const char *str1, const char *str2);
bool round_streq(const char *str1, const char *str2);
bool round_strcaseeq(const char *str1, const char *str2);
ssize_t round_strchr(const char *str, const char *chars, size_t nchars);
ssize_t round_strrchr(const char *str, const char *chars, size_t nchars);
ssize_t round_strstr(const char *haystack, const char *needle);
char *round_strtrimwhite(char *str);
char *round_strtrim(char *str, char *delim, size_t ndelim);
char *round_strltrim(char *str, char *delim, size_t ndelim);
char *round_strrtrim(char *str, char *delim, size_t ndelim);
char *round_strncpy(char *str1, const char *str2, size_t cnt);
char *round_strncat(char *str1, const char *str2, size_t cnt);
bool round_strloc(const char *str, char **buf);
  
const char *round_int2str(int value, char *buf, size_t bufSize);
const char *round_long2str(long value, char *buf, size_t bufSize);
const char *round_float2str(float value, char *buf, size_t bufSize);
const char *round_double2str(double value, char *buf, size_t bufSize);
const char *round_sizet2str(size_t value, char *buf, size_t bufSize);
const char *round_ssizet2str(ssize_t value, char *buf, size_t bufSize);

#define round_str2int(value) (value ? atoi(value) : 0)
#define round_str2long(value) (value ? atol(value) : 0)
#define round_strhex2long(value) (value ? strtol(value, NULL, 16) : 0)
#define round_strhex2ulong(value) (value ? strtoul(value, NULL, 16) : 0)
#define round_str2float(value) ((float)(value ? atof(value) : 0.0))
#define round_str2double(value) (value ? atof(value) : 0.0)
#define round_str2sizet(value) ((size_t)(value ? atol(value) : 0))
#define round_str2ssizet(value) ((ssize_t)(value ? atol(value) : 0))

/****************************************
* Data Type
****************************************/
	
typedef struct {
	char *value;
	size_t memSize;
	size_t valueSize;
} RoundString;
	
/****************************************
* Function (String)
****************************************/

RoundString *round_string_new();
void round_string_delete(RoundString *str);
void round_string_clear(RoundString *str);

void round_string_setvalue(RoundString *str, const char *value);
void round_string_setintvalue(RoundString *str, int value);
void round_string_setlongvalue(RoundString *str, long value);
void round_string_setfloatvalue(RoundString *str, float value);
void round_string_setdoublevalue(RoundString *str, double value);
void round_string_setnvalue(RoundString *str, const char *value, size_t len);
void round_string_setpointervalue(RoundString *str, char *value, size_t len);

char *round_string_getvalue(RoundString *str);
#define round_string_getintvalue(str) mupnp_str2int(round_string_getvalue(str))
#define round_string_getlongvalue(str) mupnp_str2long(round_string_getvalue(str))
#define round_string_getfloatvalue(str) mupnp_str2float(round_string_getvalue(str))
#define round_string_getdoublevalue(str) mupnp_str2double(round_string_getvalue(str))
	
size_t round_string_length(RoundString *str);

char *round_string_addvalue(RoundString *str, const char *value);
char *round_string_naddvalue(RoundString *str, const char *value, size_t valueLen);
char *round_string_addrepvalue(RoundString *str, const char *value, size_t repeatCnt);
char *round_string_naddrepvalue(RoundString *str, const char *value, size_t valueLen, size_t repeatCnt);

char *round_string_replace(RoundString *str, char *fromStr[], char *toStr[], size_t fromStrCnt);

size_t round_string_getmemorysize(RoundString *str);
                                                                                                                                             
#ifdef  __cplusplus
}
#endif

#endif
