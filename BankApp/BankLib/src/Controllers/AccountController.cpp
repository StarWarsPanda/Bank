#include <Controllers/AccountController.h>

std::string AccountController::getAllAccounts()
{
	auto serviceAccounts = m_service.getAllAccounts();
	nlohmann::json accountsJson = serviceAccounts;
	return accountsJson.dump();
}

std::string AccountController::getPremiumAccounts()
{
	auto serviceAccounts = m_service.getPremiumAccounts();
	nlohmann::json accountsJson = serviceAccounts;
	return accountsJson.dump();
}

std::string AccountController::getAccountById(int id)
{
	auto serviceAccount = m_service.getAccountById(id);
	nlohmann::json accountJson = serviceAccount;
	return accountJson.dump();
}