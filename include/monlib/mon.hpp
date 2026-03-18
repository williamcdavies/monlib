#ifndef MON_HPP
#define MON_HPP

#include <string>
#include <unordered_map>


namespace monlib {


    class mon {
        private:
            std::unordered_map<std::string, std::string> data;
        
        public:
            mon() = default;
            mon(std::unordered_map<std::string, std::string> data);

            std::string get(std::string key);
    };


} // namespace monlib


#endif // MON_HPP