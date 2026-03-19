#ifndef MON_HPP
#define MON_HPP

#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>


namespace monlib {


    class mon {
        private:
            std::unordered_map<std::string, std::string> data;
        
        public:
            mon() = default;
            mon(const std::unordered_map<std::string, std::string>& data);

            template<typename T = std::string>
            T get(const std::string& key) const {
                T                 value;
                std::stringstream ss(this->data.at(key));

                ss >> value;
                if (ss.fail()) throw std::invalid_argument("Value bound to key '" + key + "' cannot be resolved as specified type");

                return value;
            }

            template<>
            std::string get<std::string>(const std::string& key) const;
    };


} // namespace monlib


#endif // MON_HPP