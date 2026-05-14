#include <Repositories/AccountRepo.h>

Account accounts[] = {
	{0, Account::Type::checking, Currency(12345.67)},
	{1, Account::Type::saving, Currency(1007.23)},
	{2, Account::Type::checking, Currency(19.71)}
};

std::optional<std::vector<Account>> AccountRepo::GetAccounts(const std::string& sql)
{
	// Skip SQL to get database table info right now
	return std::vector<Account>(accounts, accounts + 3);
}

std::optional<Account> AccountRepo::GetAccount(const std::string& sql, int id)
{
	// Skip SQL to get database table info right now
	if (0 <= id && id < 3)
	{
		return accounts[id];
	}

	return {};
}
