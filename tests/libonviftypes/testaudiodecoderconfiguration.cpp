// testaudiodecoderconfiguration.cpp
//

///// Includes /////

#include <onviftypes/onviftypes.hpp>
#include <gtest/gtest.h>

#include "testtypes.hpp"

///// Namespaces /////

namespace onvif
{

namespace tests
{

///// Tests /////

TEST(TestAudioDecoderConfiguration, Compare)
{
  Compare(AudioDecoderConfiguration(std::string("name"), 5, std::string("token")));
}

}

}
