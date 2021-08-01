#include <iostream>
#include <chrono>
#include <forward_list>
#include <array>
#include <map>
#include <iomanip>

constexpr size_t PAYLOAD_SIZE { 10 };

template <size_t TSize>
using payload = std::array<char, TSize>;

using plot  = std::map<size_t, long long>;


void print_plot(const plot& pl, unsigned int row_len, const std::string& message) {
    std::cout << message << '\n';

    const auto max_value { pl.rbegin()->second };
    for (const auto& p : pl) {
        std::cout << std::setw(6) 
                  << p.first << " Nodes "  
                  << std::setw(6) 
                  << p.second << " ms ";
        for(auto i = 0; i < row_len / (static_cast<long double>(max_value) / p.second); ++i) {
            std::cout << 'X';
        }
        std::cout << '\n';
    }
}


constexpr size_t INCREASING_STEP { 1000 };
constexpr size_t MIN_SIZE        { INCREASING_STEP };
constexpr size_t MAX_SIZE        { 50 * INCREASING_STEP };


int main() {
    using namespace std::chrono;
    plot unseq_access_plot {};

    for(size_t data_size = MIN_SIZE; data_size < MAX_SIZE; data_size += INCREASING_STEP) {
        std::forward_list<payload<PAYLOAD_SIZE>> unseq_ws { data_size };
        for(auto i = 0; i < data_size; ++i) {
            unseq_ws.push_front(std::array<char, PAYLOAD_SIZE> {'a'});
        }

        auto start { high_resolution_clock::now() };
        for(auto iter_count = 0; iter_count < 3; ++iter_count) {
            for(auto& x : unseq_ws) {
                for(auto& i : x) {
                    i = -i;
                }
            }
        }

        auto stop { high_resolution_clock::now() };
        unseq_access_plot.insert(
            std::make_pair(data_size, duration_cast<microseconds>(stop - start).count()));
    }

    print_plot(unseq_access_plot, 50, "Unsequential access");
    std::cout << std::endl;
    return EXIT_SUCCESS;
}