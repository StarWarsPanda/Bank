#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <optional>

#include <nlohmann/json.hpp>

#include <Currency.h>

class Account
{
	public:
		typedef enum
		{
			checking,
			saving
		}Type;

	public:
		Account() {}
		Account(uint32_t id, Type type, Currency balance):id(id), type(type), balance(balance) {}
		~Account() {}

		bool operator==(const Account& other) const
		{
			return id == other.id && type == other.type && balance == other.balance;
		}

	public:
		uint32_t id = 0;
		Type type = checking;
		Currency balance = 0.0;
};

inline void to_json(nlohmann::json& j, const Account& p)
{
	j = nlohmann::json{
		{"id", p.id},
		{"type", p.type},
		{"balance", p.balance.ToDouble()},
	};
}

inline void from_json(const nlohmann::json& j, Account& p)
{
	p.id = j.value("id", 0);
	p.type = j.value("type", Account::Type::checking);
	p.balance = j.value("balance", 0.0);
}