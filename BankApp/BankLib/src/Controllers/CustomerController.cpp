#include <Controllers/CustomerController.h>
#include <Controllers/AccountController.h>

std::string CustomerController::getAllCustomers()
{
	auto serviceCustomers = m_service.getAllCustomers();
	nlohmann::json CustomersJson = serviceCustomers;
	return CustomersJson.dump();
}

std::string CustomerController::getCustomerById(int id)
{
	auto serviceCustomer = m_service.getCustomerById(id);
	nlohmann::json CustomerJson = serviceCustomer;
	return CustomerJson.dump();
}