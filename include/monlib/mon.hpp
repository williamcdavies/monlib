#ifndef MON_HPP
#define MON_HPP

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>


namespace monlib {


    class mon {
        private:
            nlohmann::json data_;

        public:
            /* mon::mon */
            mon() = default;
            mon(const nlohmann::json& root, const std::string& primary_key);

            
            /* mon::get */
            template <typename T>
            T get(const std::string& key) const {
                if (!this->has(key)) throw std::out_of_range("Key " + key + " cannot be found");

                return this->data_.at(key).get<T>();
            }


            /* mon::get_ptr */
            template <typename T>
            T* get_ptr(const std::string& key) {
                if (!this->has(key)) throw std::out_of_range("Key " + key + " cannot be found");

                return this->data_.at(key).get_ptr<T*>();
            }


            /* mon::get_ref */
            template <typename T>
            T& get_ref(const std::string& key) {
                if (!this->has(key)) throw std::out_of_range("Key " + key + " cannot be found");

                return this->data_.at(key).get_ref<T&>();
            }


            /* mon::set */
            template <typename T>
            void set(const std::string& key, const T& value) {
                if (!this->has(key)) throw std::out_of_range("Key " + key + " cannot be found");
                
                this->data_[key] = value;
            }


            /* mon::has */
            bool has(const std::string& key) const;
    };


} // namespace monlib


#endif // MON_HPP