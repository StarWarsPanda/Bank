#pragma once

#include <optional>

#include <nlohmann/json.hpp>
#include <MonGo.hpp>

#include "Models/AccountModel.h"

class AccountRepo
{
    public:
        explicit AccountRepo(MonGo& mongoClient) : m_mongoClient(mongoClient) {}
        ~AccountRepo() {}

        std::optional<std::vector<Account>> GetAccounts(const nlohmann::json& filter);
        std::optional<Account> GetAccount(const nlohmann::json& filter);
    private:
        MonGo& m_mongoClient;
};