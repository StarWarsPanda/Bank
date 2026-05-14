#include <Repositories/CustomerRepo.h>

Customer customers[]{
	{0, "Alice", std::vector<Account>(accounts + 1, accounts + 3)},
	{1, "Bob", std::vector<Account>(accounts + 0, accounts + 1)},
	{2, "Charlie", std::vector<Account>()}
};

std::optional<std::vector<Customer>> CustomerRepo::GetCustomers(const std::string& sql)
{
	// Skip SQL to get database table info right now
	return std::vector<Customer>(customers, customers + 3);
}

std::optional<Customer> CustomerRepo::GetCustomer(const std::string& sql, int id)
{
	// Skip SQL to get database table info right now
	if (0 <= id && id < 3)
	{
		return customers[id];
	}

	return {};
}
