#ifndef MON_HPP
#define MON_HPP

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>


namespace monlib {


    class mon {
        private:
            std::string    pkey_;
            nlohmann::json data_;

        public:
            /* mon::mon */
            mon() = default;
            mon(const nlohmann::json& root, const std::string& pkey);
            mon(      std::ifstream&  ifs,  const std::string& pkey);


            /* mon::get_pkey */
            std::string get_pkey() const;


            /* mon::get */
            template <typename T>
            T get(const std::string& key) const {
                if (!this->has(key)) throw std::out_of_range("Key " + key + " cannot be found");

                return this->data_[key].get<T>();
            }


            /* mon::set */
            template <typename T>
            void set(const std::string& key, const T& value) {
                if (!this->has(key)) throw std::out_of_range("Key " + key + " cannot be found");
                
                this->data_[key] = value;
            }


            /* mon::has */
            bool has(const std::string& key) const;


            /* mon::write_to */
            void write_to(const std::filesystem::path& destination) const;
    }; // mon


} // namespace monlib


#endif // MON_HPP