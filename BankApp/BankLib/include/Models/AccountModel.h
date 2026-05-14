#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <optional>

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