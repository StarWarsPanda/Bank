#include "Services/CustomerService.h"

std::optional<std::vector<Customer>> CustomerService::getAllCustomers()
{
	return m_repo.GetCustomers("");
}

std::optional<Customer> CustomerService::getCustomerById(int id)
{
	return m_repo.GetCustomer("", id);
}
