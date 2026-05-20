#pragma once

#include <optional>

#include <nlohmann/json.hpp>
#include <MonGo.hpp>

#include "Models/CustomerModel.h"
#include "Models/AccountModel.h" 

class CustomerRepo
{
	public:
		explicit CustomerRepo(MonGo& mongoClient) : m_mongoClient(mongoClient) {}
		~CustomerRepo() {}

		std::optional<std::vector<Customer>> GetCustomers(const nlohmann::json& filter);
		std::optional<Customer> GetCustomer(const nlohmann::json& filter);

	private:
		MonGo& m_mongoClient;
};