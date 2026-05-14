#pragma once

#pragma once

#include "Services/CustomerService.h"

#include <nlohmann/json.hpp>

class CustomerController
{
public:
	CustomerController(CustomerService& service) : m_service(service) {}
	~CustomerController() {}

	std::string getAllCustomers();
	std::string getCustomerById(int id);
private:
	CustomerService& m_service;


};

void to_json(nlohmann::json& json, const Customer& Customer);