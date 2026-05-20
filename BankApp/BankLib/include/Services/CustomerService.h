#pragma once

#include <Repositories/CustomerRepo.h>

class CustomerService
{
	public:
		CustomerService(CustomerRepo& repo) : m_repo(repo) {}
		~CustomerService() {}

		std::optional<std::vector<Customer>> getAllCustomers();
		std::optional<Customer> getCustomerById(int id);

	private:
		CustomerRepo& m_repo;
};