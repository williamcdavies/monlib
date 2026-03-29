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
            /* mon::mon */
            mon() = default;
            mon(const std::unordered_map<std::string, std::string>& data);


            /* mon::get */
            template<typename T>
            T get(const std::string& key) const {
                if (!this->has(key)) throw std::out_of_range("Key '" + key + "' does not exist");

                T                  value;
                const std::string& value_as_string = this->data.at(key);
                std::stringstream  ss(value_as_string);

                ss >> value;
                if (ss.fail()) throw std::invalid_argument("Value '" + value_as_string + "' bound to key '" + key + "' cannot be resolved as specified type");

                return value;
            }

            template<>
            std::string get<std::string>(const std::string& key) const;


            /* mon::set */
            template<typename T>
            void set(const std::string& key, const std::string& value) {
                
            }

            template<>
            void set<std::string>(const std::string& key, const std::string& value);


            /* mon::has */
            bool has(const std::string& key) const;
    };


} // namespace monlib


#endif // MON_HPP