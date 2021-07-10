#include <iostream>
#include <string>
#include <filesystem>
#include <functional>

#include <Windows.h>

#include "plugin.hpp"


template<typename T>
using shared_obj_ptr = std::unique_ptr<T, std::function<void(T*)>>;
using entry_point    = pe::plugin* (*)();
namespace fs         = std::filesystem;


constexpr auto dll_extension { ".dll" };
constexpr auto usage         { "Usage: application path_to_directory" };


inline bool is_path_valid(const char* path, std::error_code& ec) noexcept {
    return fs::exists(path, ec);
}


int main(int argc, char **argv) {
    if(std::error_code ec;
       argc != 2 || !is_path_valid(argv[1], ec)) {
        std::wcerr << "Invalid parameters\n" 
                   << usage << '\n';
        return ec.value();
    }

    fs::path dll_path { argv[1] };
    for (const auto& library : fs::directory_iterator(dll_path)) {
        if(!library.is_regular_file() ||
            dll_extension != library.path().extension()) {
            continue;
        }

        auto dll_handle { ::LoadLibrary(TEXT(library.path().string().c_str())) };
        if (!dll_handle) {
            std::wcerr << "Unable to load DLL: "
                       << library.path() << '\n';
            continue;
        }

        auto create_object {
            reinterpret_cast<entry_point>(::GetProcAddress(dll_handle, "create_object"))
        };

        if (!create_object) {
            std::wcerr << "Unable to load create_object from DLL!\n";
            ::FreeLibrary(dll_handle);
            continue;
        }

        shared_obj_ptr<pe::plugin> plugin {
            create_object(),
            [dll_handle] (pe::plugin* p) {
                p->release();
                ::FreeLibrary(dll_handle);
            }
        };
        plugin->execute();
    }

    return EXIT_SUCCESS;
}
