#include <iostream>
#include "ip_address.h"


std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}
std::string current_ip;

int main(int, char**)
{

    try
    {
        std::vector<ip_address> ip_pool;
        ip_pool.reserve(max_elements);
        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            current_ip = v.at(0);
            ip_pool.emplace_back(current_ip, '.');
        }
        std::sort (ip_pool.rbegin(), ip_pool.rend());
        for (auto ip : ip_pool) std::cout << ip << std::endl;
                
        auto filtered_pool_1 = filter(ip_pool, 1);
        for (auto ip : filtered_pool_1) std::cout << ip << std::endl;
        
        auto filtered_pool_2 = filter(ip_pool, 46, 70);
        for (auto ip : filtered_pool_2) std::cout << ip << std::endl;

        auto filtered_pool_3 = filter_any(ip_pool, 46);
        for (auto ip : filtered_pool_3) std::cout << ip << std::endl;

    }
    catch(const std::exception &e)
    {
        std::cerr << current_ip << "  is not valid ip address" << std::endl;
        std::cerr << e.what() << std::endl;

    }

    return 0;
}