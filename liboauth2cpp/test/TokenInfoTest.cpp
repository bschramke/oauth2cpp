#include "TokenInfoTest.hpp"
#include "oauth2cpp/BearerToken.hpp"
#include "TestConstants.h"

CPPUNIT_TEST_SUITE_REGISTRATION (TokenInfoTest);

void TokenInfoTest::setUp()
{
}

void TokenInfoTest::tearDown()
{
}

void TokenInfoTest::testBearerToken()
{
  oauth2::TokenInfo *token = new oauth2::BearerToken();

  CPPUNIT_ASSERT_EQUAL(TOKEN_TYPE_BEARER,token->getType());
  CPPUNIT_ASSERT_EQUAL(false,token->hasAccessToken());
  CPPUNIT_ASSERT_EQUAL(false,token->hasRefreshToken());

  token->setAccessToken(TOKEN_ACCESS);
  token->setRefreshToken(TOKEN_REFRESH);
  token->expiresIn(TOKEN_EXPIRES_IN);

  CPPUNIT_ASSERT_EQUAL(true,token->hasAccessToken());
  CPPUNIT_ASSERT_EQUAL(true,token->hasRefreshToken());
  CPPUNIT_ASSERT_EQUAL(TOKEN_ACCESS,token->getAccessToken());
  CPPUNIT_ASSERT_EQUAL(TOKEN_REFRESH,token->getRefreshToken());
  CPPUNIT_ASSERT_EQUAL(TOKEN_EXPIRES_IN,token->expiresIn());

  delete token;
}
