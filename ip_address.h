#pragma once

#include <vector>
#include <sstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <array>
#include <algorithm>
#include <fstream>

class ip_address
{
    public:
        ip_address()=delete;
        ip_address(std::initializer_list<std::uint8_t> il);
        ip_address(std::uint8_t oct_1, std::uint8_t oct_2, std::uint8_t oct_3, std::uint8_t oct_4);
        ip_address(const std::string &ipv4Str, char d);
        
        auto& data() const;
        auto& data();
        auto& hash() const;

        const uint8_t& operator[](std::size_t i) const;

        friend auto operator<<(std::ostream& os, ip_address &ip) -> std::ostream&;

        friend bool operator<(const ip_address& lhs, const ip_address& rhs);
        friend bool operator>(const ip_address& lhs, const ip_address& rhs);
        friend bool operator<=(const ip_address& lhs, const ip_address& rhs);
        friend bool operator>=(const ip_address& lhs, const ip_address& rhs);
        friend bool operator==(const ip_address& lhs, const ip_address& rhs);
    private:

        std::array<std::uint8_t, 4> _ip4_data;
        uint32_t _hash_value;

        std::string _to_string();       
};

std::vector<ip_address> filter(const std::vector<ip_address>& pool,
                            int octet_1, int octet_2=-1, 
                            int octet_3=-1, int octet_4=-1);

std::vector<ip_address> filter_any(const std::vector<ip_address>& pool, int octet);