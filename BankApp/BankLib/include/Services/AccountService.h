#pragma once

#include "Repositories/AccountRepo.h"

class AccountService
{
	public:
		AccountService(AccountRepo& repo) : m_repo(repo) {}
		~AccountService() {}

		std::optional<std::vector<Account>> getAllAccounts();
		std::optional<std::vector<Account>> getPremiumAccounts();
		std::optional<Account> getAccountById(int id);

	private:
		AccountRepo& m_repo;
};