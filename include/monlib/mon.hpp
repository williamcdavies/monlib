#ifndef MON_HPP
#define MON_HPP

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>


namespace monlib {


    class mon {
        private:
            nlohmann::json data_;

        public:
            /* mon::mon */
            mon() = default;
            mon(const nlohmann::json& root, const std::string& primary_key);
    };


} // namespace monlib


#endif // MON_HPP