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

int main(int, char**)
{
    try
    {
        std::vector<ip_address> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(ip_address(v.at(0), '.'));
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
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
