#include <gtest/gtest.h>
#include <monlib/mon.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>

#include "filesystem.hpp"


class MonFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            std::ifstream ifs{ "data/mon_test.json" };
            
            mon = monlib::mon{ ifs, "Bulbasaur" };
        }

        void TearDown() override {

        }

        monlib::mon mon;
};


/* mon::mon */
TEST(MonTest, CanConstructMonObject) {
    monlib::mon mon;
}


TEST(MonTest, CanConstructMonObjectFromJSON) {
    std::ifstream ifs{ "data/mon_test.json"                    };
    monlib::mon   mon{ nlohmann::json::parse(ifs), "Bulbasaur" };
}


TEST(MonTest, CanConstructMonObjectFromInputFileStream) {
    std::ifstream ifs{ "data/mon_test.json" };
    monlib::mon   mon{ ifs, "Bulbasaur"     };
}


TEST(MonTest, CanConstructMonObjectFromReference) {
    std::ifstream ifs{ "data/mon_test.json"                                   };
    monlib::mon   mon{ monlib::mon{ nlohmann::json::parse(ifs), "Bulbasaur" } };
}


/* mon::get */
TEST_F(MonFixture, GetOnValidKeyReturnsExpectedValue) {
    ASSERT_EQ(mon.get<uint64_t>("id"), 1);
}


TEST_F(MonFixture, GetOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get<uint64_t>("invalid_key"), std::out_of_range);
}


/* mon::get_ptr */
TEST_F(MonFixture, GetPtrOnValidKeyReturnsExpectedValue) {
    ASSERT_EQ(*mon.get_ptr<uint64_t>("id"), 1);
}


TEST_F(MonFixture, GetPtrOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get_ptr<uint64_t>("invalid_key"), std::out_of_range);
}


/* mon::get_ref */
TEST_F(MonFixture, GetRefOnValidKeyReturnsExpectedValue) {
    ASSERT_EQ(mon.get_ref<uint64_t>("id"), 1);
}


TEST_F(MonFixture, GetRefOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get_ref<uint64_t>("invalid_key"), std::out_of_range);
}


/* mon::get_pkey */
TEST_F(MonFixture, GetPkeyReturnsExpectedValue) {
    ASSERT_EQ(mon.get_pkey(), "Bulbasaur");
}


/* mon::set */
TEST_F(MonFixture, SetOnValidKeySetsValidValue) {
    mon.set<uint64_t>("id", 0);
    ASSERT_EQ(mon.get<uint64_t>("id"), 0);
}


TEST_F(MonFixture, SetOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.set<uint64_t>("invalid_key", 0), std::out_of_range);
}


/* mon::write_to */
TEST(MonTest, WriteToUpdatesTargetValue) {
    std::filesystem::path tmp_file{ make_temporary("data/mon_test.json") };
    
    {
        std::ifstream ifs{ tmp_file         };
        monlib::mon   mon{ ifs, "Bulbasaur" };

        mon.set<uint64_t>("id", 0);
        mon.write_to(tmp_file);
    }

    std::ifstream ifs{ tmp_file         };
    monlib::mon   mon{ ifs, "Bulbasaur" };

    ASSERT_EQ(mon.get<uint64_t>("id"), 0);

    std::filesystem::remove(tmp_file);
}