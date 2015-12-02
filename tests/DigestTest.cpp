/******************************************************************
 *
 * Round for C
 *
 * Copyright (C) Satoshi Konno 2015
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>

#include <round/util/digest.h>
#include <round/util/strings.h>

BOOST_AUTO_TEST_SUITE(digest)

#if defined(ROUND_SUPPORT_MD_5DIGEST)

BOOST_AUTO_TEST_CASE(MD5Digest) {
  char *digest = NULL;
  BOOST_CHECK(round_md5_digest("a", &digest));
  BOOST_CHECK(digest);
  BOOST_CHECK_EQUAL(round_strlen(digest), ROUND_MD5_DIGEST_STRING_LENGTH);
  free(digest);
}

#endif

BOOST_AUTO_TEST_CASE(SHADigest) {
  char *digest = NULL;
  BOOST_CHECK(round_sha_digest("a", &digest));
  BOOST_CHECK(digest);
  BOOST_CHECK_EQUAL(round_strlen(digest), ROUND_SHA_DIGEST_STRING_LENGTH);
  free(digest);
}

BOOST_AUTO_TEST_CASE(SHA256Digest) {
  char *digest = NULL;
  BOOST_CHECK(round_sha256_digest("a", &digest));
  BOOST_CHECK(digest);
  BOOST_CHECK_EQUAL(round_strlen(digest), ROUND_SHA256_DIGEST_STRING_LENGTH);
  free(digest);
}

BOOST_AUTO_TEST_SUITE_END()
