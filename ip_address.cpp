#include "ip_address.h"

#include "version.h"

int version() {
	return PROJECT_VERSION_PATCH;
}


ip_address::ip_address(std::initializer_list<std::uint8_t> il)
{
    uint32_t ipv4 = 0;
    auto max = std::min(il.size(),this->_ip4_data.size()); 
    assert(max == 4);
    std::copy_n(il.begin(), max, this->_ip4_data.begin());
    for(int i = 0; i < 4; ++i) {
        ipv4 |= this->_ip4_data[i] << ( 8 * ( 3 - i ) );
    }
    this->_hash_value = ipv4;
}


ip_address::ip_address(std::uint8_t oct_1, std::uint8_t oct_2, 
                    std::uint8_t oct_3, std::uint8_t oct_4)
{
    uint32_t ipv4 = 0;
    this->_ip4_data = {oct_1, oct_2, oct_3, oct_4};
    for(int i = 0; i < 4; ++i) {
        ipv4 |= this->_ip4_data[i] << ( 8 * ( 3 - i ) );
    }
    this->_hash_value = ipv4;
}

ip_address::ip_address(const std::string &ipv4Str, char d)
{
  
	std::istringstream iss( ipv4Str );

	uint32_t ipv4 = 0;

	for(int i = 0; i < 4; ++i ) {
	    uint32_t part;
	    iss >> part;
	    if ( iss.fail() || part > 255 ) {
	        throw std::runtime_error( "Invalid IP address - Expected [0, 255]" );
	    }
	    this->_ip4_data[i] = part;
	    // LSHIFT and OR all parts together with the first part as the MSB
	    ipv4 |= part << ( 8 * ( 3 - i ) );

	    // Check for delimiter except on last iteration
	    if ( i != 3 ) {
	        char delimiter;
	        iss >> delimiter;
	        if ( iss.fail() || delimiter != d ) {
	            throw std::runtime_error( "Invalid IP address - Expected another delimiter" );
	        }
	    }
	}
	_hash_value = ipv4;
            
}


auto& ip_address::data() const { return this->_ip4_data; }
auto& ip_address::data() { return this->_ip4_data; }
auto& ip_address::hash() const { return this->_hash_value; }

const uint8_t& ip_address::operator[](std::size_t i) const {
    return _ip4_data[i];
}

auto operator<<(std::ostream& os, ip_address &ip) -> std::ostream& { 
    return os << ip._to_string();
}


bool operator<(const ip_address& lhs, const ip_address& rhs) {
    return  lhs.hash() < rhs.hash();
}
bool operator>(const ip_address& lhs, const ip_address& rhs){
    return  lhs.hash() > rhs.hash();
}
bool operator<=(const ip_address& lhs, const ip_address& rhs){
    return  lhs.hash() <= rhs.hash();
}
bool operator>=(const ip_address& lhs, const ip_address& rhs){
    return  lhs.hash() >= rhs.hash();
}
bool operator==(const ip_address& lhs, const ip_address& rhs){
    return  lhs.hash() == rhs.hash();
}
/*
bool operator==(const ip_address& lhs, const ip_address& rhs){
    return  lhs.hash() == rhs.hash();
}
*/

std::string ip_address::_to_string(){
    std::string ipv4_str;
    for(int i = 0; i < 4; ++i ) {
        ipv4_str += std::to_string(this->_ip4_data[i]);
        if ( i != 3 ) ipv4_str += ('.');
    }
    return ipv4_str;
}




std::vector<ip_address> filter(std::vector<ip_address> pool, 
                            int octet_1, int octet_2, 
                            int octet_3, int octet_4) {
    std::vector<ip_address> filtered_pool;
    
    for (auto ip : pool) {
        if ((octet_2 != -1) && (octet_3 != -1) && (octet_4 != -1)) {
            if ((ip[0] == octet_1) && (ip[1] == octet_2) &&
                (ip[2] == octet_3) && (ip[3] == octet_4)){
                filtered_pool.push_back(ip);
            }
        }
        if ((octet_2 != -1) && (octet_3 != -1) && (octet_4 == -1)) {
            if ((ip[0] == octet_1) && (ip[1] == octet_2) && (ip[2] == octet_3)) {
                filtered_pool.push_back(ip);
            }
        }
        if ((octet_2 != -1) && (octet_3 == -1) && (octet_4 == -1)) {
            if ((ip[0] == octet_1) && (ip[1] == octet_2)) {
                filtered_pool.push_back(ip);
            }
        }

        if ((octet_2 == -1) && (octet_3 == -1) && (octet_4 == -1)) {
            if (ip[0] == octet_1) {
                filtered_pool.push_back(ip);
            }
        }
    }
    return filtered_pool;
}

std::vector<ip_address> filter_any(std::vector<ip_address> pool, int octet) {
    std::vector<ip_address> filtered_pool;
    for (auto ip : pool) {
        if ((ip[0] == octet) || (ip[1] == octet) ||
           (ip[2] == octet) || (ip[3] == octet)) {
            filtered_pool.push_back(ip);
           }
    }
    return filtered_pool;

}       
