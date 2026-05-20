#include <Repositories/CustomerRepo.h>

std::optional<std::vector<Customer>> CustomerRepo::GetCustomers(const nlohmann::json& filter)
{
	nlohmann::json results = m_mongoClient.FindMany("BankDB", "Customers", filter);

    if (results.contains("response") && results["response"].is_array())
    {
        std::vector<Customer> customers;

        for (const auto& result : results["response"])
        {
            customers.push_back(result);
        }

        return customers;
    }

	return {};
}

std::optional<Customer> CustomerRepo::GetCustomer(const nlohmann::json& filter)
{
    nlohmann::json results = m_mongoClient.FindOne("BankDB", "Customers", filter);

    if (results.contains("response"))
    {
        if (results["response"].contains("_id"))
        {
            return results["response"];
        }
    }

    return {};
}
