#include <monlib/mon.hpp>

#include <stdexcept>
#include <string>
#include <unordered_map>


namespace monlib {


    mon::mon(std::unordered_map<std::string, std::string> data) { this->data = data; }


    std::string mon::get(std::string key) { 
        auto it = this->data.find(key);
        if (it == this->data.end()) throw std::out_of_range("Key '" + key + "' not found");

        return it->second;
    }
    

} // namespace monlib
