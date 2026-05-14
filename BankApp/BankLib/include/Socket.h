#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

/* For IPv4 only */
class Socket
{
	public:
		typedef enum
		{
			ok = 200,
			created = 201,
			bad_request = 400,
			not_found = 404,
			internal_server_error = 500
		} HTTPStatus;

		struct HTTPRequest
		{
			std::string method;
			std::string path;
			std::string body;
		};

	public:
		Socket();
		~Socket();

		/* Singleton Enforcement */
		Socket(const Socket&) = delete;
		Socket& operator=(const Socket&) = delete;

		/* References are fine */
		Socket(Socket&& other) noexcept;
		Socket& operator=(Socket&& other) noexcept;

		bool SetReuseAddress(bool enable);

		bool Bind(const std::string& address, uint16_t port);
		bool Listen(int maxQueue = SOMAXCONN);

		Socket Accept();

		bool Send(const std::string& data);
		std::string Receive(int bufferSize = 0x1000);

		void Close();

		bool IsOpen() const;

		static std::string HTTPStatusToString(Socket::HTTPStatus status);
		static std::string HTTPResponse(Socket::HTTPStatus status, const std::string& body, const std::string& contentType = "application/json");
	
		static HTTPRequest ParseHTTPRequest(const std::string& request);
	private:
		void ReleaseReference();
		explicit Socket(SOCKET handle);
	private:
		SOCKET m_socket = INVALID_SOCKET;
		bool m_hasReference = false;

		static uint32_t s_referenceCount;
};