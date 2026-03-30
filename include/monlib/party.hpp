#ifndef PARTY_HPP
#define PARTY_HPP

#include <monlib/mon.hpp>
#include <vector>


namespace monlib {


    class party {
        private:
            std::vector<monlib::mon> mons_;

        public:
            /* party::party */
            party() = default;
            party(const std::vector<monlib::mon>& mons);
    };


} // namespace monlib


#endif // PARTY_HPP