#pragma once

#include <optional>

#include "Models/CustomerModel.h"
#include "AccountRepo.h" 

extern Customer customers[];;

class CustomerRepo
{
public:
	CustomerRepo() {}
	~CustomerRepo() {}

	std::optional<std::vector<Customer>> GetCustomers(const std::string& sql);
	std::optional<Customer> GetCustomer(const std::string& sql, int id); // int id is temporary for right now; parse SQL later
private:

};