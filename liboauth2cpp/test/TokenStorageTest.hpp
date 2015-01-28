#ifndef OAUTH2CPP_TOKENSTORAGETEST_HPP
#define OAUTH2CPP_TOKENSTORAGETEST_HPP

#include "oauth2cpp/TokenStorage.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TokenStorageTest : public CPPUNIT_NS :: TestFixture
{
  CPPUNIT_TEST_SUITE (TokenStorageTest);
  CPPUNIT_TEST (testDefaultStorageCreation);
  CPPUNIT_TEST (testBearerToken);
  CPPUNIT_TEST_SUITE_END ();

public:
  void setUp (void);
  void tearDown (void);

protected:
  void testDefaultStorageCreation (void);
  void testBearerToken (void);

private:
  void setupDefaultStorage(void);

  oauth2::TokenStorage *storage = nullptr;
};

#endif //OAUTH2CPP_TOKENSTORAGETEST_HPP
