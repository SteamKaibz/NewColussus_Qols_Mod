#pragma once

#include <string>

struct addrName {
	std::string name = "";
	uint64_t rva_address = 0; // relative virtual address, meaning the address of the var - the module addr.
};
