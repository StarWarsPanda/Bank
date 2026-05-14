#pragma once

#include "Models/AccountModel.h"

extern Account accounts[];

class AccountRepo
{
public:
    AccountRepo() {}
    ~AccountRepo() {}

    std::optional<std::vector<Account>> GetAccounts(const std::string& sql);
    std::optional<Account> GetAccount(const std::string& sql, int id); // int id is temporary for right now; parse SQL later
private:

};