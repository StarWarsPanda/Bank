#include <Services/AccountService.h>
#include <Controllers/AccountController.h>

std::optional<std::vector<Account>> AccountService::getAllAccounts()
{
	nlohmann::json j = nlohmann::json::object();
	return m_repo.GetAccounts(j);
}

std::optional<std::vector<Account>> AccountService::getPremiumAccounts()
{
	return m_repo.GetAccounts(nlohmann::json{
		{
			"balance", {
				{"$gt", 10000.0}
			}
		}
	});
}

std::optional<Account> AccountService::getAccountById(int id)
{
	return m_repo.GetAccount(nlohmann::json({ 
		{"id", id}
	}));
}
