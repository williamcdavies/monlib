#include <gtest/gtest.h>
#include <monlib/mon.hpp>

#include <stdexcept>
#include <string>
#include <unordered_map>


class MonFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            mon = monlib::mon(std::unordered_map<std::string, std::string>{{"valid_key", "valid_value"}});
        }

        void TearDown() override {

        }

        monlib::mon mon;
};


TEST(MonTest, CanConstructMonObject) {
    monlib::mon mon;
}


TEST(MonTest, CanConstructMonObjectFromData) {
    monlib::mon mon(std::unordered_map<std::string, std::string>{{"valid_key", "valid_value"}});
    ASSERT_EQ(mon.get("valid_key"), "valid_value");
}


TEST(MonTest, CanConstructMonObjectFromMonObject) {
    monlib::mon mon(monlib::mon(std::unordered_map<std::string, std::string>{{"valid_key", "valid_value"}}));
    ASSERT_EQ(mon.get("valid_key"), "valid_value");
}


TEST_F(MonFixture, GetValidKeyReturnsValidValue) {
    ASSERT_EQ(mon.get("valid_key"), "valid_value");
}


TEST_F(MonFixture, GetInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get("invalid_key"), std::out_of_range);
}