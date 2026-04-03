#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <chrono>
#include <filesystem>
#include <stdexcept>
#include <string>


/* make_temporary */
inline std::filesystem::path make_temporary(const std::filesystem::path& source) {
    if (!std::filesystem::is_regular_file(source)) throw std::runtime_error("Path '" + source.string() + "' is not a regular file");

    std::string           tmp_filename{ "tmp_" + 
                                        source.stem().string() + 
                                        "_" + 
                                        std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()) + 
                                        "_" + 
                                        source.extension().string() };
    std::filesystem::path tmp_file    { std::filesystem::temp_directory_path() / tmp_filename                                                                                                            };
    
    std::filesystem::copy_file(source, tmp_file, std::filesystem::copy_options::overwrite_existing);

    return tmp_file;
}


#endif // FILESYSTEM_HPP