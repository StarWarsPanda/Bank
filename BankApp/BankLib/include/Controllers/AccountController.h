#pragma once

#include "Services/AccountService.h"

#include <nlohmann/json.hpp>

class AccountController
{
public:
	AccountController(AccountService& service) : m_service(service) {}
	~AccountController() {}

	std::string getAllAccounts();
	std::string getPremiumAccounts();
	std::string getAccountById(int id);
private:
	AccountService& m_service;

	
};

void to_json(nlohmann::json& json, const Account& account);