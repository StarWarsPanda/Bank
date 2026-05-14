#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <optional>
#include <vector>

#include <nlohmann/json.hpp>

#include <Account.h>
#include <Customer.h>

#pragma region AccountTesting

TEST(Accounts, PremiumAccounts) {
	AccountRepo accountRepo = AccountRepo();
	AccountService accountService = AccountService(accountRepo);

	std::vector<Account> expected = {
		{0, Account::Type::checking, Currency(12345.67)}
	};

	auto premiumAccounts = accountService.getPremiumAccounts();
	bool hasValue = premiumAccounts.has_value();
	
	EXPECT_TRUE(hasValue);
	EXPECT_EQ(expected, *premiumAccounts);
}

TEST(Accounts, AllAccounts) {
	AccountRepo accountRepo = AccountRepo();
	AccountService accountService = AccountService(accountRepo);

	std::vector<Account> expected = {
		{0, Account::Type::checking, Currency(12345.67)},
		{1, Account::Type::saving, Currency(1007.23)},
		{2, Account::Type::checking, Currency(19.71)}
	};

	auto allAccounts = accountService.getAllAccounts();
	bool hasValue = allAccounts.has_value();

	EXPECT_TRUE(hasValue);
	EXPECT_EQ(expected, *allAccounts);
}

TEST(Accounts, AccountById) {
	AccountRepo accountRepo = AccountRepo();
	AccountService accountService = AccountService(accountRepo);

	Account expectedAccountById[] = {
		{0, Account::Type::checking, Currency(12345.67)},
		{1, Account::Type::saving, Currency(1007.23)},
		{2, Account::Type::checking, Currency(19.71)},
		{}
	};

	for (size_t i = 0; i < 4; i++)
	{
		Account expected = expectedAccountById[i];
		auto actual = accountService.getAccountById(i);

		EXPECT_EQ(expected, actual.value_or({}));
	}
}

#pragma endregion

#pragma region CustomerTesting

TEST(Customers, AllCustomers) {
	CustomerRepo customerRepo = CustomerRepo();
	CustomerService customerService = CustomerService(customerRepo);

	std::vector<Customer> expected = {
		{0, "Alice", std::vector<Account>(accounts + 1, accounts + 3)},
		{1, "Bob", std::vector<Account>(accounts + 0, accounts + 1)},
		{2, "Charlie", std::vector<Account>()}
	};

	auto allCustomers = customerService.getAllCustomers();
	bool hasValue = allCustomers.has_value();

	EXPECT_TRUE(hasValue);
	EXPECT_EQ(expected, *allCustomers);
}

TEST(Customers, CustomerById) {
	CustomerRepo customerRepo = CustomerRepo();
	CustomerService customerService = CustomerService(customerRepo);

	Customer expectedCustomerById[] = {
		{0, "Alice", std::vector<Account>(accounts + 1, accounts + 3)},
		{1, "Bob", std::vector<Account>(accounts + 0, accounts + 1)},
		{2, "Charlie", std::vector<Account>()},
		{}
	};

	for (size_t i = 0; i < 4; i++)
	{
		Customer expected = expectedCustomerById[i];
		auto actual = customerService.getCustomerById(i);

		EXPECT_EQ(expected, actual.value_or({}));
	}
}

#pragma endregion