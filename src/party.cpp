#include <monlib/party.hpp>

#include <monlib/mon.hpp>
#include <vector>


namespace monlib {


    /* party::party */
    party::party(const std::vector<monlib::mon>& mons) { this->mons_ = mons; }


} // namespace monlib