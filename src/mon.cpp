#include <monlib/mon.hpp>

#include <stdexcept>
#include <string>
#include <unordered_map>


namespace monlib {


    /* mon::mon */
    mon::mon(const std::unordered_map<std::string, std::string>& data) { this->data = data; }

    
    /* mon::get */
    template<>
    std::string mon::get<std::string>(const std::string& key) const {
        if (!this->has(key)) throw std::out_of_range("Key '" + key + "' does not exist");

        return this->data.at(key);
    }


    /* mon::set */
    template<>
    void mon::set<std::string>(const std::string& key, const std::string& value) {
        if (!this->has(key)) throw std::out_of_range("Key '" + key + "' does not exist");

        this->data.at(key) = value;
    }


    /* mon::has */
    bool mon::has(const std::string& key) const {
        if(this->data.find(key) == this->data.end()) {
            return false;
        }

        return true;
    }


} // namespace monlib