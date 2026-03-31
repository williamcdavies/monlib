#include <monlib/mon.hpp>

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>


namespace monlib {


    /* mon::mon */
    mon::mon(const nlohmann::json& root,      const std::string& pkey): 
        data_(root.at(pkey)), 
        pkey_(pkey) {}
    mon::mon(      std::ifstream&  data_file, const std::string& pkey): 
        data_(nlohmann::json::parse(data_file).at(pkey)),
        pkey_(pkey) {}


    /* mon::get_pkey */
    std::string mon::get_pkey() const {
        return this->pkey_;
    }


    /* mon::has */
    bool mon::has(const std::string& key) const {
        return this->data_.contains(key);
    }


    /* mon::write_to */
    void mon::write_to(const std::filesystem::path& destination) const {
        if (!std::filesystem::is_regular_file(destination)) throw std::runtime_error("Path '" + destination.string() + "' is not a regular file");

        std::ifstream  ifs { destination                };
        nlohmann::json root{ nlohmann::json::parse(ifs) };
        ifs.close();

        root[this->pkey_] = this->data_;

        std::ofstream ofs{ destination };
        ofs << root.dump(4);
        ofs.close();
    }

} // namespace monlib