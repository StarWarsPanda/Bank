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

inline void to_json(nlohmann::json& j, const Customer& p)
{
	j = nlohmann::json{
		{"id", p.id},
		{"name", p.name},
		{"accounts", p.accounts},
	};
}

inline void from_json(const nlohmann::json& j, Customer& p)
{
	std::cout << j.dump(4) << std::endl;

	p.id = j.value("id", 0);
	p.name = j.value("name", "");
	p.accounts = j.value("accounts", std::vector<Account>());
}