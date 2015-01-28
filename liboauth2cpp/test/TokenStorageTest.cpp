#include "oauth2cpp/BearerToken.hpp"
#include "oauth2cpp/DefaultStorage.hpp"
#include "TokenStorageTest.hpp"
#include "TestConstants.h"

CPPUNIT_TEST_SUITE_REGISTRATION (TokenStorageTest);

void TokenStorageTest::setUp()
{
}

void TokenStorageTest::tearDown()
{
  if(storage != nullptr)
    {
      delete storage;
      storage = nullptr;
    }
}

void TokenStorageTest::setupDefaultStorage()
{
  storage = new oauth2::DefaultStorage();
  auto token = std::unique_ptr<oauth2::TokenInfo>(new oauth2::BearerToken());

  token->setAccessToken(TOKEN_ACCESS);
  token->setRefreshToken(TOKEN_REFRESH);
  token->expiresIn(TOKEN_EXPIRES_IN);

  storage->writeTokenInfo(CLIENT_ID,std::move(token));
}

void TokenStorageTest::testDefaultStorageCreation()
{
  storage = new oauth2::DefaultStorage();

  CPPUNIT_ASSERT_EQUAL(false, storage->hasTokenInfo(CLIENT_ID));
  CPPUNIT_ASSERT_EQUAL(false, storage->hasAccessToken(CLIENT_ID));
  CPPUNIT_ASSERT_EQUAL(false, storage->hasRefreshToken(CLIENT_ID));
}

void TokenStorageTest::testBearerToken()
{
  setupDefaultStorage();

  CPPUNIT_ASSERT_EQUAL(true, storage->hasTokenInfo(CLIENT_ID));
  CPPUNIT_ASSERT_EQUAL(true, storage->hasAccessToken(CLIENT_ID));
  CPPUNIT_ASSERT_EQUAL(true, storage->hasRefreshToken(CLIENT_ID));

  CPPUNIT_ASSERT_EQUAL(TOKEN_TYPE_BEARER, storage->getTokenInfo(CLIENT_ID)->getType());
  CPPUNIT_ASSERT_EQUAL(TOKEN_EXPIRES_IN, storage->getTokenInfo(CLIENT_ID)->expiresIn());
  CPPUNIT_ASSERT_EQUAL(TOKEN_ACCESS, storage->getAccessToken(CLIENT_ID));
  CPPUNIT_ASSERT_EQUAL(TOKEN_REFRESH, storage->getRefreshToken(CLIENT_ID));

}

