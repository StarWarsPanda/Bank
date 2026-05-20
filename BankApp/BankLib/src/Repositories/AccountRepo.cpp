#include <Repositories/AccountRepo.h>

std::optional<std::vector<Account>> AccountRepo::GetAccounts(const nlohmann::json& filter)
{
    nlohmann::json results = m_mongoClient.FindMany("BankDB", "Accounts", filter);

    if (results.contains("response") && results["response"].is_array())
    {
        std::vector<Account> accounts;
        for (const auto& result : results["response"])
        {
            accounts.push_back(result);
        }
        return accounts;
    }

    return {};
}

std::optional<Account> AccountRepo::GetAccount(const nlohmann::json& filter)
{
    nlohmann::json results = m_mongoClient.FindOne("BankDB", "Accounts", filter);

    if (results.contains("response"))
    {
        if (results["response"].contains("_id"))
        {
            return results["response"];
        }
        else
        {
            std::cout << results["response"].dump() << std::endl;
        }
    }

    return {};
}
