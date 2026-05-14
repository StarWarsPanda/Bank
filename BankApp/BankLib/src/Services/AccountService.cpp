#include <Services/AccountService.h>
#include <Controllers/AccountController.h>

std::optional<std::vector<Account>> AccountService::getAllAccounts()
{
	return m_repo.GetAccounts("");
}

std::optional<std::vector<Account>> AccountService::getPremiumAccounts()
{
	// SQL should be handeling this
	auto allAccounts = *m_repo.GetAccounts("");

	allAccounts.erase(std::remove_if(allAccounts.begin(), allAccounts.end(),
		[](Account acc) { return acc.balance < 10000.00; }),
		allAccounts.end()
	);
	return std::optional<std::vector<Account>>(allAccounts);
}

std::optional<Account> AccountService::getAccountById(int id)
{
	return m_repo.GetAccount("", id);
}
