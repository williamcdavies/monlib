#include <gtest/gtest.h>
#include <monlib/mon.hpp>

#include <cstdint>
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
            
            mon = monlib::mon{ data, "Bulbasaur" };
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
    monlib::mon   mon      { nlohmann::json::parse(data_file), "Bulbasaur" };
}


TEST(MonTest, CanConstructMonObjectFromReference) {
    std::ifstream data_file{ "data/mon_test.json"                                        };
    monlib::mon   mon      { monlib::mon{ nlohmann::json::parse(data_file), "Bulbasaur" } };
}


/* mon::get */
TEST_F(MonFixture, GetOnValidKeyReturnsValidValue) {
    ASSERT_EQ(mon.get<uint64_t>("id"), 1);
}


TEST_F(MonFixture, GetOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get<uint64_t>("invalid_key"), std::out_of_range);
}


/* mon::get_ptr */
TEST_F(MonFixture, GetPtrOnValidKeyReturnsValidValue) {
    ASSERT_EQ(*mon.get_ptr<uint64_t>("id"), 1);
}


TEST_F(MonFixture, GetPtrOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get_ptr<uint64_t>("invalid_key"), std::out_of_range);
}


/* mon::get_ref */
TEST_F(MonFixture, GetRefOnValidKeyReturnsValidValue) {
    ASSERT_EQ(mon.get_ref<uint64_t>("id"), 1);
}


TEST_F(MonFixture, GetRefOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get_ref<uint64_t>("invalid_key"), std::out_of_range);
}


/* mon::set */
TEST_F(MonFixture, SetOnValidKeySetsValidValue) {
    mon.set<uint64_t>("id", 0);
    ASSERT_EQ(mon.get<uint64_t>("id"), 0);
}


TEST_F(MonFixture, SetOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.set<uint64_t>("invalid_key", 0), std::out_of_range);
}