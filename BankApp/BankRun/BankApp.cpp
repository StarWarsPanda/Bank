#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <nlohmann/json.hpp>
#include <Socket.h>

#include "Account.h"
#include "Customer.h"

bool isNumber(const std::string& str) {
	try {
		size_t pos;

		std::stoi(str, &pos);

		return pos == str.size();
	}
	catch (...) {
		return false;
	}
}

int main()
{
	AccountRepo accountRepo = AccountRepo();
	AccountService accountService = AccountService(accountRepo);
	AccountController accountController = AccountController(accountService);

	CustomerRepo customerRepo = CustomerRepo();
	CustomerService customerService = CustomerService(customerRepo);
	CustomerController customerController = CustomerController(customerService);

	int retValue = 0;

	try
	{
		Socket server;

		if (!server.SetReuseAddress(true))
		{
			retValue = 2;
			throw std::runtime_error("SetReuseAddress failed");
		}

		if (!server.Bind("127.0.0.1", 8080))
		{
			retValue = 3;
			throw std::runtime_error("Binding failed");
		}

		if (!server.Listen())
		{
			retValue = 4;
			throw std::runtime_error("Listen failed");
		}

		std::cout << "Server starting..." << std::endl;

		while (true)
		{
			Socket client = server.Accept();
			std::string request = client.Receive();

			if (!request.empty())
			{
				Socket::HTTPRequest parsedRequest = Socket::ParseHTTPRequest(request);
				std::cout << "---------------------------------\nRequest: "
					<< "Method: " << parsedRequest.method << "\n"
					<< "Path: " << parsedRequest.path << "\n"
					<< "Body: " << parsedRequest.body << "\n"
					<< "\n" << std::endl;

				if (parsedRequest.method == "GET")
				{
					if (parsedRequest.path.starts_with("/api"))
					{
						std::string relativePath = parsedRequest.path.substr(4);

						if (relativePath.starts_with("/customers"))
						{
							relativePath = relativePath.substr(min(11, relativePath.length()));

							if (relativePath.empty())
							{
								client.Send(Socket::HTTPResponse(Socket::HTTPStatus::ok, customerController.getAllCustomers()));
								continue;
							}
							else
							{
								const int id = std::stoi(relativePath);

								client.Send(Socket::HTTPResponse(Socket::HTTPStatus::ok, customerController.getCustomerById(id)));
								continue;
							}
						}
						else if (relativePath.starts_with("/accounts"))
						{
							relativePath = relativePath.substr(min(10, relativePath.length()));

							if (relativePath.empty())
							{
								client.Send(Socket::HTTPResponse(Socket::HTTPStatus::ok, accountController.getAllAccounts()));
								continue;
							}
							else if(isNumber(relativePath))
							{
								const int id = std::stoi(relativePath);

								client.Send(Socket::HTTPResponse(Socket::HTTPStatus::ok, accountController.getAccountById(id)));

								continue;
							}
							else if(relativePath.starts_with("premium"))
							{
								client.Send(Socket::HTTPResponse(Socket::HTTPStatus::ok, accountController.getPremiumAccounts()));
								continue;
							}
						}
					}
					else if(parsedRequest.path == "/")
					{
						client.Send(Socket::HTTPResponse(Socket::HTTPStatus::ok, "<p>Root</p>", "text/html"));
						continue;
					}

					client.Send(Socket::HTTPResponse(Socket::HTTPStatus::not_found, "<p>Unknown path</p>", "text/html"));
					continue;
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		std::cout << "\nPress Enter to exit..." << std::endl;
		std::cin.get();
	}



	return retValue;
}
