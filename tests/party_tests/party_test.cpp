#include <gtest/gtest.h>
#include <monlib/party.hpp>

#include <monlib/mon.hpp>
#include <vector>


class PartyFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            party = monlib::party{};
        }

        void TearDown() override {

        }

        monlib::party party;
};


/* party::party */
TEST(PartyTest, CanConstructPartyObject) {
    monlib::party party;
}


TEST(PartyTest, CanConstructPartyObjectFromParameters) {
    std::vector<monlib::mon> mons;
    monlib::party party{mons};
}


TEST(PartyTest, CanConstructPartyObjectFromReference) {
    std::vector<monlib::mon> mons;
    monlib::party(monlib::party{mons});
}