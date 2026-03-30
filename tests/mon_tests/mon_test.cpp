#include <gtest/gtest.h>
#include <monlib/mon.hpp>

#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>


class MonFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            std::ifstream  data_file{ "data/mon_test.json"             };
            nlohmann::json data     { nlohmann::json::parse(data_file) };
            
            mon = monlib::mon{ data, "id" };
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