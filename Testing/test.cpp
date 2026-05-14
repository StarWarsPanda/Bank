#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <optional>
#include <vector>

#include <nlohmann/json.hpp>

#include <Account.h>
#include <Customer.h>

#pragma region AccountTesting

TEST(Accounts, ServicePremiumAccounts) {
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

TEST(Accounts, ControllerPremiumAccounts) {
	AccountRepo accountRepo = AccountRepo();
	AccountService accountService = AccountService(accountRepo);
	AccountController accountController = AccountController(accountService);

	std::string expected = nlohmann::json(std::vector<Account>{
		{0, Account::Type::checking, Currency(12345.67)}
	}).dump();

	std::string actual = accountController.getPremiumAccounts();
	
	EXPECT_STREQ(expected.c_str(), actual.c_str());
}


TEST(Accounts, ServiceAllAccounts) {
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

TEST(Accounts, ControllerAllAccounts) {
	AccountRepo accountRepo = AccountRepo();
	AccountService accountService = AccountService(accountRepo);
	AccountController accountController = AccountController(accountService);

	std::string expected = nlohmann::json(std::vector<Account>{
		{0, Account::Type::checking, Currency(12345.67)},
		{1, Account::Type::saving, Currency(1007.23)},
		{2, Account::Type::checking, Currency(19.71)}
	}).dump();
	std::string actual = accountController.getAllAccounts();

	EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(Accounts, ServiceAccountById) {
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

	Account expected = Account();
	auto actual = accountService.getAccountById(-1);
	EXPECT_EQ(expected, actual.value_or({}));
}

TEST(Accounts, ControllerAccountById) {
	AccountRepo accountRepo = AccountRepo();
	AccountService accountService = AccountService(accountRepo);
	AccountController accountController = AccountController(accountService);

	Account expectedAccountById[3] = {
		{0, Account::Type::checking, Currency(12345.67)},
		{1, Account::Type::saving, Currency(1007.23)},
		{2, Account::Type::checking, Currency(19.71)}
	};

	for (size_t i = 0; i < 3; i++)
	{
		const Account& account = expectedAccountById[i];
		std::string expected = nlohmann::json(account).dump();
		std::string actual = accountController.getAccountById(i);

		EXPECT_STREQ(expected.c_str(), actual.c_str());
	}

	std::string expected = "null";
	std::string actual = accountController.getAccountById(-1);
	EXPECT_STREQ(expected.c_str(), actual.c_str());

	actual = accountController.getAccountById(3);
	EXPECT_STREQ(expected.c_str(), actual.c_str());
}

#pragma endregion

#pragma region CustomerTesting

TEST(Customers, ServiceAllCustomers) {
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

TEST(Customers, ControllerAllCustomers) {
	CustomerRepo customerRepo = CustomerRepo();
	CustomerService customerService = CustomerService(customerRepo);
	CustomerController customerController = CustomerController(customerService);

	std::string expected = nlohmann::json(std::vector<Customer>{
		{0, "Alice", std::vector<Account>(accounts + 1, accounts + 3)},
		{ 1, "Bob", std::vector<Account>(accounts + 0, accounts + 1) },
		{ 2, "Charlie", std::vector<Account>() }
	}).dump();
	std::string actual = customerController.getAllCustomers();

	EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(Customers, ServiceCustomerById) {
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

TEST(Customers, ControllerCustomerById) {
	CustomerRepo customerRepo = CustomerRepo();
	CustomerService customerService = CustomerService(customerRepo);
	CustomerController customerController = CustomerController(customerService);

	Customer expectedCustomerById[3] = {
		{0, "Alice", std::vector<Account>(accounts + 1, accounts + 3)},
		{1, "Bob", std::vector<Account>(accounts + 0, accounts + 1)},
		{2, "Charlie", std::vector<Account>()}
	};

	for (size_t i = 0; i < 3; i++)
	{
		const Customer& customer = expectedCustomerById[i];
		std::string expected = nlohmann::json(customer).dump();
		std::string actual = customerController.getCustomerById(i);

		EXPECT_STREQ(expected.c_str(), actual.c_str());
	}

	std::string expected = "null";
	std::string actual = customerController.getCustomerById(-1);
	EXPECT_STREQ(expected.c_str(), actual.c_str());

	actual = customerController.getCustomerById(3);
	EXPECT_STREQ(expected.c_str(), actual.c_str());
}

#pragma endregion