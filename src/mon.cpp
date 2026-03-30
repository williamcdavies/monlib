#include <monlib/mon.hpp>

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>


namespace monlib {


    /* mon::mon */
    mon::mon(const nlohmann::json& root, const std::string& primary_key) { this->data_ = root.at(primary_key); }


    /* mon::has*/
    bool mon::has(const std::string& key) const {
        if (this->data_.find(key) == this->data_.end()) return false;

        return true;
    }


} // namespace monlib