#include <monlib/mon.hpp>

#include <stdexcept>
#include <string>
#include <unordered_map>


namespace monlib {


    mon::mon(const std::unordered_map<std::string, std::string>& data) { this->data = data; }

    
    template<>
    std::string mon::get<std::string>(const std::string& key) const {
        return this->data.at(key);
    }


} // namespace monlib
