#include <iostream>
#include <string>
#include <filesystem>
#include <functional>

#include <Windows.h>

#include "plugin.hpp"


namespace pe {
    
    template<typename T>
    using deleted_unique_ptr = std::unique_ptr<T, std::function<void(T*)>>;
    using entry_point = plugin*(*)();

    constexpr auto usage {
        "Usage: application path_to_directory"
    };

    inline bool is_valid_path(const char* path) {
        return std::filesystem::exists(path);
    }
} // namespace pe


int main(int argc, char **argv) {
    if(argc != 2 || pe::is_valid_path(argv[1])) {
        std::cout << pe::usage << '\n';
        return EXIT_FAILURE;
    }



    auto dll_handle { ::LoadLibrary(TEXT("mylib.dll")) };
    if (!dll_handle) {
        std::cerr << "Unable to load DLL!\n";
        return EXIT_FAILURE;
    }

    auto get_instance {
        reinterpret_cast<pe::entry_point>(::GetProcAddress(dll_handle, "create_object"))
    };

    if (!get_instance) {
        std::cerr << "Unable to load create_object from DLL!\n";
        ::FreeLibrary(dll_handle);
        return EXIT_FAILURE;
    }

    pe::deleted_unique_ptr<pe::plugin> p_plugin {
        get_instance(),
        [dll_handle] (pe::plugin* p) {
            p->release();
            ::FreeLibrary(dll_handle);
        }
    };
    p_plugin->execute();

    return EXIT_SUCCESS;
}