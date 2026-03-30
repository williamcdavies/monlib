#include <gtest/gtest.h>
#include <monlib/mon.hpp>

#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>


class MonFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            std::ifstream  data_file{ "data/mon_test.json"             };
            nlohmann::json data     { nlohmann::json::parse(data_file) };
            
            mon = monlib::mon{ data, "test_mon" };
        }

        void TearDown() override {

        }

        monlib::mon mon;
};


/* mon::mon */
TEST(MonTest, CanConstructMonObject) {
    monlib::mon mon;
}


TEST(MonTest, CanConstructMonObjectFromParameters) {
    std::ifstream data_file{ "data/mon_test.json"                         };
    monlib::mon   mon      { nlohmann::json::parse(data_file), "test_mon" };
}


TEST(MonTest, CanConstructMonObjectFromReference) {
    std::ifstream data_file{ "data/mon_test.json"                                        };
    monlib::mon   mon      { monlib::mon{ nlohmann::json::parse(data_file), "test_mon" } };
}


/* mon::get */
TEST_F(MonFixture, GetOnValidKeyReturnsValidValue) {
    ASSERT_EQ(mon.get<std::string>("valid_key"), "valid_value");
}


TEST_F(MonFixture, GetOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get<std::string>("invalid_key"), std::out_of_range);
}


/* mon::set */
TEST_F(MonFixture, SetOnValidKeySetsValidValue) {
    mon.set<std::string>("valid_key", "another_valid_value");
    ASSERT_EQ(mon.get<std::string>("valid_key"), "another_valid_value");
}


TEST_F(MonFixture, SetOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.set<std::string>("invalid_key", "another_valid_value"), std::out_of_range);
}