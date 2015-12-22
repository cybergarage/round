/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <round/util/strings.h>

#include <string.h>

/* Define amount of extra characters allocated on each realloc, with this we
 can avoid many small subsequent reallocs, which takes lots of time */
#define ROUND_STRING_REALLOC_EXTRA 16

/****************************************
 * round_string_new
 ****************************************/

RoundString* round_string_new(void)
{
  RoundString* str;

  str = (RoundString*)malloc(sizeof(RoundString));

  if (!str)
    return NULL;

  str->value = NULL;
  str->memSize = 0;
  str->valueSize = 0;

  return str;
}

/****************************************
 * round_string_delete
 ****************************************/

bool round_string_delete(RoundString* str)
{
  if (!str)
    return false;

  round_string_clear(str);

  free(str);

  return true;
}

/****************************************
 * round_string_delete
 ****************************************/

bool round_string_clear(RoundString* str)
{
  if (!str)
    return false;

  if (str->value) {
    free(str->value);
    str->value = NULL;
  }

  str->memSize = 0;
  str->valueSize = 0;

  return true;
}

/****************************************
 * round_string_setvalue
 ****************************************/

bool round_string_setvalue(RoundString* str, const char* value)
{
  if (!str)
    return false;

  if (!value)
    return false;

  return round_string_setnvalue(str, value, round_strlen(value));
}

/****************************************
 * round_string_setintvalue
 ****************************************/

bool round_string_setintvalue(RoundString* str, int value)
{
  char buf[ROUND_STRING_INTEGER_BUFLEN];
  return round_string_setvalue(str, round_int2str(value, buf, sizeof(buf)));
}

/****************************************
 * round_string_setlongvalue
 ****************************************/

bool round_string_setlongvalue(RoundString* str, long value)
{
  char buf[ROUND_STRING_LONG_BUFLEN];
  return round_string_setvalue(str, round_long2str(value, buf, sizeof(buf)));
}

/****************************************
 * round_string_setnvalue
 ****************************************/

bool round_string_setnvalue(RoundString* str, const char* value, size_t len)
{
  if (!str)
    return false;

  if (!round_string_clear(str))
    return false;

  if (!value)
    return true;

  str->valueSize = len;
  str->memSize = str->valueSize + 1;

  str->value = (char*)malloc(str->memSize * sizeof(char));
  if (!str->value)
    return false;

  /* memcpy works better with non-zero-terminated data than strncpy */
  memcpy(str->value, value, len);
  str->value[len] = '\0';

  return true;
}

/****************************************
 * round_string_setpointervalue
 ****************************************/

bool round_string_setpointervalue(RoundString* str, char* value, size_t len)
{
  if (!str)
    return false;

  if (!round_string_clear(str))
    return false;

  str->value = value;
  str->valueSize = len;
  str->memSize = str->valueSize + 1;

  return true;
}

/****************************************
 * round_string_getvalue
 ****************************************/

char* round_string_getvalue(RoundString* str)
{
  if (!str)
    return NULL;
  return str->value;
}

/****************************************
 * round_string_getmemorysize
 ****************************************/

size_t round_string_getmemorysize(RoundString* str)
{
  if (!str)
    return 0;
  return str->memSize;
}

/****************************************
 * round_string_length
 ****************************************/

size_t round_string_length(RoundString* str)
{
  if (!str)
    return 0;

  if (!str->value)
    return 0;

  return str->valueSize;
}

/****************************************
 * round_string_equals
 ****************************************/

bool round_string_equals(RoundString* str1, RoundString* str2)
{
  return (round_strcmp(round_string_getvalue(str1),
                       round_string_getvalue(str2))
          == 0)
             ? true
             : false;
}

/****************************************
 * round_string_add
 ****************************************/

char* round_string_addvalue(RoundString* str, const char* value)
{
  return round_string_naddvalue(str, value, round_strlen(value));
}

/****************************************
 * round_string_add
 ****************************************/

char* round_string_naddvalue(RoundString* str, const char* value, size_t valueLen)
{
  char* newValue = NULL;
  size_t newMemSize = 0;

  if (!str)
    return NULL;

  if (value == NULL || valueLen <= 0) {
    /* Empty string, nothing to add */
    return round_string_getvalue(str);
  }

  /* Check, if we need to allocate memory for the new data */
  newMemSize = str->valueSize + valueLen + 1;
  if (newMemSize > str->memSize || str->value == NULL) {
    /* realloc also some extra in order to avoid multiple reallocs */
    newMemSize += ROUND_STRING_REALLOC_EXTRA;
    newValue = realloc(str->value, newMemSize * sizeof(char));

    if (newValue == NULL) {
      /* Memory allocation failed, bail out */
      return NULL;
    }

    str->memSize = newMemSize;
    str->value = newValue;
  }

  /* memcpy works better with non-zero-terminated data
   than strncpy */
  memcpy(str->value + str->valueSize, value, valueLen);

  str->valueSize += valueLen;

  /* In case this is a string, append a termination character */
  str->value[str->valueSize] = '\0';

  return round_string_getvalue(str);
}

/****************************************
 * round_string_addrep
 ****************************************/

char* round_string_addrepvalue(RoundString* str, const char* value, size_t repeatCnt)
{
  int n;

  for (n = 0; n < repeatCnt; n++)
    round_string_addvalue(str, value);

  return round_string_getvalue(str);
}

/****************************************
 * round_string_naddrep
 ****************************************/

char* round_string_naddrepvalue(RoundString* str, const char* value, size_t valueLen, size_t repeatCnt)
{
  int n;

  for (n = 0; n < repeatCnt; n++)
    round_string_naddvalue(str, value, valueLen);

  return round_string_getvalue(str);
}

/****************************************
 * round_string_replace
 ****************************************/

char* round_string_replace(RoundString* str, char* fromStr[], char* toStr[], size_t fromStrCnt)
{
  char* orgValue = NULL;
  size_t orgValueLen = 0;
  int n = 0;
  int copyPos = 0;
  size_t* fromStrLen = NULL;
  RoundString* repValue = NULL;
  bool isReplaced = false;

  if (!str)
    return NULL;

  repValue = round_string_new();

  fromStrLen = (size_t*)malloc(sizeof(size_t) * fromStrCnt);

  if (NULL == fromStrLen) {
    round_string_delete(repValue);
    return NULL;
  }

  for (n = 0; n < fromStrCnt; n++)
    fromStrLen[n] = round_strlen(fromStr[n]);

  orgValue = round_string_getvalue(str);
  orgValueLen = round_string_length(str);

  copyPos = 0;
  while (copyPos < orgValueLen) {
    isReplaced = false;
    for (n = 0; n < fromStrCnt; n++) {
      if (strncmp(fromStr[n], orgValue + copyPos, fromStrLen[n]) == 0) {
        round_string_addvalue(repValue, toStr[n]);
        copyPos += fromStrLen[n];
        isReplaced = true;
        continue;
      }
    }
    if (isReplaced == true)
      continue;
    round_string_naddvalue(repValue, orgValue + copyPos, 1);
    copyPos++;
  }

  free(fromStrLen);

  round_string_setvalue(str, round_string_getvalue(repValue));

  round_string_delete(repValue);

  return round_string_getvalue(str);
}
