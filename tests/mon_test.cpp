#include <gtest/gtest.h>
#include <monlib/mon.hpp>

#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>


class MonFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            mon = monlib::mon(std::unordered_map<std::string, std::string>{
                {"valid_key", "valid_value"},
                {"valid_unsigned_short_key",     std::to_string(std::numeric_limits<unsigned short>::max())    },
                {"valid_unsigned_int_key",       std::to_string(std::numeric_limits<unsigned int>::max())      },
                {"valid_long_key",               std::to_string(std::numeric_limits<long>::min())              },
                {"valid_unsigned_long_key",      std::to_string(std::numeric_limits<unsigned long>::max())     },
                {"valid_long_long_key",          std::to_string(std::numeric_limits<long long>::min())         },
                {"valid_unsigned_long_long_key", std::to_string(std::numeric_limits<unsigned long long>::max())},
                {"valid_float_key",              std::to_string(3.14f)                                         },
                {"valid_double_key",             std::to_string(3.14)                                          },
                {"valid_long_double_key",        std::to_string(3.14L)                                         },
                {"valid_bool_key",               std::to_string(true)                                          },
                {"valid_void_ptr_key",           std::to_string(0x00000000)                                    },
                {"valid_short_key",              std::to_string(std::numeric_limits<short>::min())             },
                {"valid_int_key",                std::to_string(std::numeric_limits<int>::min())               }
            });
        }

        void TearDown() override {

        }

        monlib::mon mon;
};


TEST(MonTest, CanConstructMonObject) {
    monlib::mon mon;
}


TEST(MonTest, CanConstructMonObjectFromParameters) {
    monlib::mon mon(std::unordered_map<std::string, std::string>{{"valid_key", "valid_value"}});
    ASSERT_EQ(mon.get<std::string>("valid_key"), "valid_value");
}


TEST(MonTest, CanConstructMonObjectFromReference) {
    monlib::mon mon(monlib::mon(std::unordered_map<std::string, std::string>{{"valid_key", "valid_value"}}));
    ASSERT_EQ(mon.get<std::string>("valid_key"), "valid_value");
}


TEST_F(MonFixture, GetValidKeyReturnsValidValue) {
    ASSERT_EQ(mon.get<std::string>("valid_key"), "valid_value");
}


TEST_F(MonFixture, GetInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get<std::string>("invalid_key"), std::out_of_range);
}


TEST_F(MonFixture, GetUnsignedShortReturnsValidValue) {
    ASSERT_EQ(mon.get<unsigned short>("valid_unsigned_short_key"), std::numeric_limits<unsigned short>::max());
}


TEST_F(MonFixture, GetUnsignedShortOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<unsigned short>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetUnsignedIntReturnsValidValue) {
    ASSERT_EQ(mon.get<unsigned int>("valid_unsigned_int_key"), std::numeric_limits<unsigned int>::max());
}


TEST_F(MonFixture, GetUnsignedIntOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<unsigned int>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetLongReturnsValidValue) {
    ASSERT_EQ(mon.get<long>("valid_long_key"), std::numeric_limits<long>::min());
}


TEST_F(MonFixture, GetLongOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<long>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetUnsignedLongReturnsValidValue) {
    ASSERT_EQ(mon.get<unsigned long>("valid_unsigned_long_key"), std::numeric_limits<unsigned long>::max());
}


TEST_F(MonFixture, GetUnsignedLongOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<unsigned long>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetLongLongReturnsValidValue) {
    ASSERT_EQ(mon.get<long long>("valid_long_long_key"), std::numeric_limits<long long>::min());
}


TEST_F(MonFixture, GetLongLongOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<long long>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetUnsignedLongLongReturnsValidValue) {
    ASSERT_EQ(mon.get<unsigned long long>("valid_unsigned_long_long_key"), std::numeric_limits<unsigned long long>::max());
}


TEST_F(MonFixture, GetUnsignedLongLongOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<unsigned long long>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetFloatReturnsValidValue) {
    ASSERT_NEAR(mon.get<float>("valid_float_key"), 3.14f, std::numeric_limits<float>::epsilon());
}


TEST_F(MonFixture, GetFloatOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<float>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetDoubleReturnsValidValue) {
    ASSERT_NEAR(mon.get<double>("valid_double_key"), 3.14, std::numeric_limits<double>::epsilon());
}


TEST_F(MonFixture, GetDoubleOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<double>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetLongDoubleReturnsValidValue) {
    ASSERT_NEAR(mon.get<long double>("valid_long_double_key"), 3.14L, std::numeric_limits<long double>::epsilon());
}


TEST_F(MonFixture, GetLongDoubleOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<long double>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetBoolReturnsValidValue) {
    ASSERT_EQ(mon.get<bool>("valid_bool_key"), true);
}


TEST_F(MonFixture, GetBoolOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<bool>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetVoidPtrReturnsValidValue) {
    ASSERT_EQ(mon.get<void*>("valid_void_ptr_key"), nullptr);
}


TEST_F(MonFixture, GetVoidPtrOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<void*>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetShortReturnsValidValue) {
    ASSERT_EQ(mon.get<short>("valid_short_key"), std::numeric_limits<short>::min());
}


TEST_F(MonFixture, GetShortOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<short>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetIntReturnsValidValue) {
    ASSERT_EQ(mon.get<int>("valid_int_key"), std::numeric_limits<int>::min());
}


TEST_F(MonFixture, GetIntOnInvalidValueThrowsInvalidArgument) {
    ASSERT_THROW(mon.get<int>("valid_key"), std::invalid_argument);
}


TEST_F(MonFixture, GetOrValidKeyReturnsValidValue) {
    ASSERT_EQ(mon.get_or<std::string>("valid_key", "valid_fallback"), "valid_value");
}


TEST_F(MonFixture, GetOrInvalidKeyReturnsValidFallback) {
    ASSERT_EQ(mon.get_or<std::string>("invalid_key", "valid_fallback"), "valid_fallback");
}


TEST_F(MonFixture, HasValidKeyReturnsTrue) {
    ASSERT_EQ(mon.has("valid_key"), true);
}


TEST_F(MonFixture, HasInvalidKeyReturnsFalse) {
    ASSERT_EQ(mon.has("invalid_key"), false);
}