#pragma once

#include "AccountModel.h"

class Customer
{
	public:
		Customer() {}
		Customer(uint32_t id, std::string name, std::vector<Account> accounts) :id(id), name(name), accounts(accounts) {}
		~Customer() {}

		bool operator==(const Customer& other) const
		{
			return id == other.id && name == other.name && accounts == other.accounts;
		}
	public:
		uint32_t id = 0;
		std::string name = "";
		std::vector<Account> accounts;
};