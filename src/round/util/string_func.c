/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ctype.h>
#include <string.h>

#include <round/util/strings.h>

/****************************************
* round_strdup
****************************************/

char *round_strdup(const char *str)
{
#if !defined(HAVE_STRDUP)
 char *cpStr;
#endif

  if (!str)
    return NULL;

#if defined(HAVE_STRDUP)
  return strdup(str);
#else
  cpStr = (char *)malloc(strlen(str)+1);
  if (!cpStr)
    return NULL;
  strcpy(cpStr, str);
  return cpStr;
#endif
}

/****************************************
 * round_strloc
 ****************************************/

bool round_strloc(const char *str, char **buf)
{
  if (!buf)
    return false;
    
  if (*buf) {
    free(*buf);
    *buf = NULL;
  }
  
  if (!str)
    return true;
  
  *buf = round_strdup(str);

  return true;
}

/****************************************
* round_strlen
****************************************/

size_t round_strlen(const char *str)
{
  return (str == NULL) ? 0 : strlen(str);
}

/****************************************
* round_strcpy
****************************************/

char *round_strcpy(char *dst, const char *src)
{
  if (!dst || !src)
    return NULL;
  
  return strcpy(dst, src);
}

/****************************************
* round_strcat
****************************************/

char *round_strcat(char *dst, const char *src)
{
  return strcat(dst, src);
}

/****************************************
* round_strcmp
****************************************/

int round_strcmp(const char *str1, const char *str2)
{
  if (str1 == NULL)
    return -1;
  if (str2 == NULL)
    return 1;
  return strcmp(str1, str2);
}

/****************************************
* round_strncmp
****************************************/

int round_strncmp(const char *str1, const char *str2, int nchars)
{
 if (str1 == NULL)
   return -1;
 if (str2 == NULL)
   return 1;

 return strncmp(str1, str2, nchars);
}

/****************************************
* round_strcasecmp
****************************************/

int round_strcasecmp(const char *str1, const char *str2)
{
  if (str1 == NULL || str2 == NULL) return -1;
#if !defined(WIN32)
  return strcasecmp(str1, str2);
#else
  for (; toupper(*str1) == toupper(*str2); str1++, str2++) {
    if (*str1 == '\0')
      return 0;
  }
  return *str1 - *str2;
#endif
}

/****************************************
* round_streq
****************************************/

bool round_streq(const char *str1, const char *str2)
{
  if (str1 == NULL || str2 == NULL)
    return false;
  
  return ((round_strcmp(str1, str2) == 0) ? true : false);
}

/****************************************
* round_strcaseeq
****************************************/

bool round_strcaseeq(const char *str1, const char *str2)
{
  if (str1 == NULL || str2 == NULL)
    return false;
  
  return ((round_strcasecmp(str1, str2) == 0) ? true : false);
}

/****************************************
* round_strstr
****************************************/

ssize_t round_strstr(const char *haystack, const char *needle)
{
  char *strPos;

  if (haystack == NULL || needle == NULL)
    return -1;
  strPos = strstr(haystack, needle);
  if (strPos == NULL)
    return -1;
  return (strPos - haystack);
}

/****************************************
* round_strchr
****************************************/

ssize_t round_strchr(const char *str, const char *chars, size_t nchars)
{
  size_t strLen;
  ssize_t i, j;

  if (str == NULL || chars == NULL)
    return -1;
    
  strLen = round_strlen(str);
  for (i=0; i<strLen; i++) {
    for (j=0; j<nchars; j++) {
      if (str[i] == chars[j])
        return i;
    }    
  }
  
  return -1;
}

/****************************************
* round_strrchr
****************************************/

ssize_t round_strrchr(const char *str, const char *chars, size_t nchars)
{
  size_t strLen;
  ssize_t i, j;
  
  if (str == NULL || chars == NULL)
    return -1;
    
  strLen = round_strlen(str);
  for (i=(strLen-1); 0<=i; i--) {
    for (j=0; j<nchars; j++) {
      if (str[i] == chars[j])
        return i;
    }    
  }
  
  return -1;

}

/****************************************
* round_strtrimwhite
****************************************/

char *round_strtrimwhite(char *str)
{
  size_t strLen;
  ssize_t i;
  strLen = round_strlen(str);
  if (strLen == 0) return str;
  for (i=(strLen-1); 0<=i; i--) {
    if (isspace(str[i])) {
      strLen--;
    } 
  }
  for (i=0 ; i<strLen ; i++) {
    if (!isspace(str[i])) break;
  }

  if (i>0) memmove(str,str+i,strLen-i);

  str[strLen] = 0;
  return str;
}

/****************************************
* round_strtrim
****************************************/

char *round_strtrim(char *str, char *delim, size_t ndelim)
{
  if (str == NULL || delim == NULL) return NULL;

  round_strrtrim(str, delim, ndelim);
  return round_strltrim(str, delim, ndelim);
}

/****************************************
* round_strltrim
****************************************/

char *round_strltrim(char *str, char *delim, size_t ndelim)
{
  size_t strLen;
  ssize_t i, j;
  
  strLen = round_strlen(str);
  for (i=0; i<strLen; i++) {
    bool hasDelim = false;
    for (j=0; j<ndelim; j++) {
      if (str[i] == delim[j]) {
        hasDelim = true;
        break;
      }
    }
    if (hasDelim == false)
      return (str + i);
  }
  
  return (str + strLen);
}

/****************************************
* round_strrtrim
****************************************/

char *round_strrtrim(char *str, char *delim, size_t ndelim)
{
  size_t strLen;
  ssize_t i, j;
  
  strLen = round_strlen(str);
  for (i=(strLen-1); 0<=i; i--) {
    bool hasDelim = false;
    for (j=0; j<ndelim; j++) {
      if (str[i] == delim[j]) {
        hasDelim = true;
        str[i] = '\0';
        break;
      }
    }
    if (hasDelim == false)
      break;
  }
  
  return str;
}

/****************************************
* round_strncpy
****************************************/

char *round_strncpy(char *str1, const char *str2, size_t cnt)
{
  strncpy(str1, str2, cnt);
  return str1;
}

/****************************************
* round_strncat
****************************************/

char *round_strncat(char *str1, const char *str2, size_t cnt)
{
  size_t str1Len;
  str1Len = round_strlen(str1);
  return round_strncpy((str1 + str1Len), str2, cnt);
}

/****************************************
 * round_isnumeric
 ****************************************/

bool round_isnumeric(const char *str)
{
  if (!str)
    return false;
  
  if (*str == '\0')
    return false;
  
  while (*str != '\0') {
    if (*str < '0')
      return false;
    if ('9' < *str)
      return false;
    str++;
  }
  
  return true;
}

/****************************************
* round_int2str
****************************************/

const char *round_int2str(int value, char *buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
 snprintf(buf, bufSize, "%d", value);
#else
 sprintf(buf, "%d", value);
#endif
 return buf;
}

/****************************************
* round_long2str
****************************************/

const char *round_long2str(long value, char *buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
 snprintf(buf, bufSize, "%ld", value);
#else
 sprintf(buf, "%ld", value);
#endif
 return buf;
}

/****************************************
* round_float2str
****************************************/

const char *round_float2str(float value, char *buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
 snprintf(buf, bufSize, "%f", value);
#else
 sprintf(buf, "%f", value);
#endif
 return buf;
}

/****************************************
* round_double2str
****************************************/

const char *round_double2str(double value, char *buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
 snprintf(buf, bufSize, "%lf", value);
#else
 sprintf(buf, "%lf", value);
#endif
 return buf;
}

/****************************************
* round_sizet2str
****************************************/

const char *round_sizet2str(size_t value, char *buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
 snprintf(buf, bufSize, "%zd", value);
#else
 sprintf(buf, "%zd", value);
#endif
 return buf;
}

/****************************************
* round_ssizet2str
****************************************/

const char *round_ssizet2str(ssize_t value, char *buf, size_t bufSize)
{
#if defined(HAVE_SNPRINTF)
 snprintf(buf, bufSize, "%zd", value);
#else
 sprintf(buf, "%zd", value);
#endif
 return buf;
}

/****************************************
 * round_strtok
 ****************************************/

char *round_strtok(char *s1, const char *s2, char **ptr)
{
  return strtok_r(s1, s2, ptr);
}

/****************************************
 * round_strreplace
 ****************************************/

char *round_strreplace(const char *str, const char *orgToken, const char *repToken)
{
  size_t strLen = round_strlen(str);
  if (strLen <= 0) {
    char *repStr = (char *)malloc(1);
    repStr[0] = '\0';
    return repStr;
  }

  char *repStr = (char *)malloc(strLen + 1);
  
  size_t orgTokenLen = round_strlen(orgToken);
  if (orgTokenLen <= 0) {
    memcpy(repStr, str, (strLen + 1));
    return repStr;
  }
  
  size_t repTokenLen = round_strlen(repToken);
  size_t tokenDiffLen = repTokenLen - orgTokenLen;
  ssize_t lastCopiedIdx = 0;
  ssize_t copiedLen = 0;
  size_t repStrLen = strLen;
  ssize_t orgTokenIdx = round_strstr(str, orgToken);
  while (0 <= orgTokenIdx) {
    if (tokenDiffLen != 0) {
      repStrLen += tokenDiffLen;
      repStr = (char *)realloc(repStr, repStrLen + 1);
    }
    
    size_t copyLen = (orgTokenIdx - lastCopiedIdx);
    if (0 < copyLen) {
      memcpy((repStr + copiedLen), (str + lastCopiedIdx), copyLen);
    }
    
    copiedLen += copyLen;
    repStr[copiedLen] = '\0';
    memcpy((repStr + copiedLen), repToken, repTokenLen);
    copiedLen += repTokenLen;
    repStr[copiedLen] = '\0';
    
    lastCopiedIdx = orgTokenIdx + orgTokenLen;
    orgTokenIdx = round_strstr((str + lastCopiedIdx), orgToken);
    if (0 < orgTokenIdx) {
      orgTokenIdx += lastCopiedIdx;
    }
  }
  
  size_t leftStrLen = (strLen - lastCopiedIdx);
  memcpy((repStr + copiedLen), (str + lastCopiedIdx), leftStrLen);
  copiedLen += leftStrLen;
  repStr[copiedLen] = '\0';
  
  return repStr;
}
