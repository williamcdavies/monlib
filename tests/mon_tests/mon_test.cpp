#include <gtest/gtest.h>
#include <monlib/mon.hpp>

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
            mon = monlib::mon{ ifs, "Bulbasaur"     };
            ifs.close();
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
    std::ifstream ifs{ "data/mon_test.json"            };
    monlib::mon   mon{ monlib::mon{ ifs, "Bulbasaur" } };
}


/* mon::get_pkey */
TEST_F(MonFixture, GetPkeyReturnsPrimaryKey) {
    ASSERT_EQ(mon.get_pkey(), "Bulbasaur");
}


/* mon::get */
TEST_F(MonFixture, GetOnValidKeyReturnsExpectedValue) {
    ASSERT_EQ(mon.get<int>("id"), 1);
}


TEST_F(MonFixture, GetOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.get<int>("invalid_key"), std::out_of_range);
}


/* mon::set */
TEST_F(MonFixture, SetOnValidKeySetsExpectedValue) {
    mon.set("id", 0);
    ASSERT_EQ(mon.get<int>("id"), 0);
}


TEST_F(MonFixture, SetOnInvalidKeyThrowsOutOfRange) {
    ASSERT_THROW(mon.set("invalid_key", 0), std::out_of_range);
}


/* mon::has */
TEST_F(MonFixture, HasOnValidKeyReturnsTrue) {
    ASSERT_TRUE(mon.has("id"));
}


TEST_F(MonFixture, HasOnInvalidKeyReturnsFalse) {
    ASSERT_FALSE(mon.has("invalid_key"));
}


/* mon::write_to */
TEST_F(MonFixture, WriteToValidPathUpdatesExpectedObject) {
    std::filesystem::path tmp_file{ make_temporary("data/mon_test.json") };
    
    mon.set("id", 0);
    mon.write_to(tmp_file);
    
    std::ifstream ifs{ tmp_file };
    nlohmann::json data = nlohmann::json::parse(ifs).at("Bulbasaur");
    ifs.close();
    
    ASSERT_EQ(data.at("id"), 0);
    
    std::filesystem::remove(tmp_file);
}


TEST_F(MonFixture, WriteToInvalidPathThrowsRuntimeError) {
    ASSERT_THROW(mon.write_to(std::filesystem::temp_directory_path()), std::runtime_error);
}