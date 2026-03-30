#include <gtest/gtest.h>
#include <monlib/mon.hpp>


class MonFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            mon = monlib::mon{};
        }

        void TearDown() override {

        }

        monlib::mon mon;
};


/* mon::mon */
TEST(MonTest, CanConstructMonObject) {
    monlib::mon mon;
}


TEST(PartyTest, CanConstructPartyObjectFromParameters) {
    
}


TEST(PartyTest, CanConstructPartyObjectFromReference) {
    
}