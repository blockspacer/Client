// testsupportinformation.cpp
//

///// Includes /////

#include <gtest/gtest.h>
#include <onviftypes/onviftypes.hpp>

#include "testtypes.hpp"

///// Namespaces /////

namespace onvif
{

namespace tests
{

///// Tests /////

TEST(TestSupportInformation, Compare)
{
  Compare(SupportInformation(BinaryData({ 'a', 'b', 'c' }, std::string("contenttype")), std::string("string")));
}

}

}
