#include <iostream>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <vector>
#include "../lib/cppcodec/base64_rfc4648.hpp"
#include "../lib/json/json.hpp"

using json = nlohmann::json;
using base64 = cppcodec::base64_rfc4648;

struct content
{
    uint16_t co2;
    uint8_t errCode : 6;
    uint8_t errType : 1;
    uint8_t error : 1;
    uint8_t reserved;
    uint32_t id : 20;
    uint32_t segment : 4;
    uint8_t reserved2;
};

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Input must be 8 byte hex numbers or 8 bytes encoded with base64.\n");
        return 1;
    }

    std::string input(argv[1]);
    std::uint64_t value;
    content *cnt;

    if (input.substr(0, 2) == "0x")
    {
        // hex input
        input = input.substr(2);
        if (input.length() % 2 != 0)
        {
            printf("Error: Invalid hex input\n");
            return 1;
        }
        value = std::strtoull(input.c_str(), nullptr, 16);
    }
    else
    {
        // base64 input
        try
        {
            std::vector<uint8_t> decoded = base64::decode(input);
            if (decoded.size() != sizeof(content))
            {
                printf("Error: Invalid input size\n");
                return 1;
            }
            // convert decoded base64 to hex
            std::stringstream ss;
            ss << std::hex << std::setfill('0');

            for (const auto &byte : decoded)
            {
                ss << std::setw(2) << static_cast<int>(byte);
            }

            std::string hex_value = ss.str();
            const char *hex_cstr = hex_value.c_str();
            value = std::strtoull(hex_cstr, nullptr, 16);
        }
        catch (const std::exception &e)
        {
            printf("Error: Invalid base64 input\n");
            return 1;
        }
    }

    cnt = reinterpret_cast<content *>(&value);

    uint16_t co2 = cnt->co2;
    uint8_t errCode = cnt->errCode;
    uint8_t errType = cnt->errType;
    uint8_t error = cnt->error;
    uint8_t reserved = cnt->reserved;
    uint32_t id = cnt->id;
    uint32_t segment = cnt->segment;
    uint8_t reserved2 = cnt->reserved2;

    json jsonString = {
        {"co2", static_cast<uint16_t>(co2)},
        {"errCode", static_cast<uint8_t>(errCode)},
        {"errType", static_cast<uint8_t>(errType)},
        {"error", static_cast<bool>(error)},
        {"reserved", static_cast<uint8_t>(reserved)},
        {"id", static_cast<uint32_t>(id)},
        {"segment", static_cast<uint32_t>(segment)},
        {"reserved2", static_cast<uint8_t>(reserved2)},
    };

    std::cout << std::setw(4) << jsonString << std::endl;

    return 0;
}