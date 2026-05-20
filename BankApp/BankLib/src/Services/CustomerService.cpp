#include "Services/CustomerService.h"

std::optional<std::vector<Customer>> CustomerService::getAllCustomers()
{
	nlohmann::json j = nlohmann::json::object();
	return m_repo.GetCustomers(j);
}

std::optional<Customer> CustomerService::getCustomerById(int id)
{
	nlohmann::json j = nlohmann::json{
		{ "id", id }
	};
	return m_repo.GetCustomer(j);
}
