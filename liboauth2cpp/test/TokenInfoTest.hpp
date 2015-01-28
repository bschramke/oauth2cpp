#ifndef OAUTH2CPP_TOKENINFOTEST_HPP
#define OAUTH2CPP_TOKENINFOTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TokenInfoTest : public CPPUNIT_NS :: TestFixture
{
  CPPUNIT_TEST_SUITE (TokenInfoTest);
  CPPUNIT_TEST (testBearerToken);
  CPPUNIT_TEST_SUITE_END ();

public:
  void setUp (void);
  void tearDown (void);

protected:
  void testBearerToken (void);
};

#endif //OAUTH2CPP_TOKENINFOTEST_HPP
