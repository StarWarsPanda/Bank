#include "Socket.h"

uint32_t Socket::s_referenceCount = 0;

Socket::Socket()
{
	if (s_referenceCount++ == 0)
	{
		WSAData sockConfig;

		if (WSAStartup(MAKEWORD(2,2), &sockConfig) != 0)
		{
			--s_referenceCount;
			return;
		}
	}

	m_hasReference = true;
	
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_socket == INVALID_SOCKET)
	{
		ReleaseReference();
		m_hasReference = false;
	}
}

Socket::~Socket()
{
	Close();
	ReleaseReference();
}

Socket::Socket(Socket&& other) noexcept
	:m_socket(other.m_socket), m_hasReference(other.m_hasReference)
{
	other.m_socket = INVALID_SOCKET;
	other.m_hasReference = false;
}

Socket& Socket::operator=(Socket&& other) noexcept
{
	if (this != &other)
	{
		Close();
		ReleaseReference();
		m_socket = other.m_socket;
		other.m_socket = INVALID_SOCKET;
		m_hasReference = other.m_hasReference;
		other.m_hasReference = false;
	}

	return *this;
}

bool Socket::SetReuseAddress(bool enable)
{
	return setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (enable ? "\1" : ""), sizeof(int32_t)) == 0;
}

bool Socket::Bind(const std::string& address, uint16_t port)
{
	sockaddr_in sockAddress{};

	sockAddress.sin_family = AF_INET;
	sockAddress.sin_port = htons(port);
	
	if (inet_pton(AF_INET, address.c_str(), &sockAddress.sin_addr) != 1)
	{
		std::cerr << "Error in setting internal socket address" << std::endl;
		return false;
	}

	const int bindOutcome = bind(m_socket, reinterpret_cast<sockaddr*>(&sockAddress), sizeof(sockAddress));

	if (bindOutcome != 0)
	{
		std::cerr << "Binding failed with id " << bindOutcome << std::endl;
	}

	return bindOutcome != SOCKET_ERROR;
}

bool Socket::Listen(int maxQueue)
{
	return listen(m_socket, maxQueue) != SOCKET_ERROR;
}

Socket Socket::Accept()
{
	sockaddr_in client{};
	int clientSize = sizeof(client);
	SOCKET clientSocket = accept(m_socket, reinterpret_cast<sockaddr*>(&client), &clientSize);

	if (clientSocket == INVALID_SOCKET)
	{
		return Socket();
	}

	return Socket(clientSocket);
}

bool Socket::Send(const std::string& data)
{
	return send(m_socket, data.c_str(), data.length(), 0) != SOCKET_ERROR;
}

std::string Socket::Receive(int bufferSize)
{
	std::string buffer(bufferSize, '\0');

	const uint32_t recievedSize = recv(m_socket, &buffer[0], bufferSize - 1, 0);

	if (recievedSize <= 0)
	{
		return "";
	}

	buffer.resize(recievedSize);
	return buffer;
}

void Socket::Close()
{
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
}

bool Socket::IsOpen() const
{
	return m_socket != INVALID_SOCKET;
}

std::string Socket::HTTPStatusToString(Socket::HTTPStatus status)
{
	switch (status)
	{
		case ok:
			return "OK";
		case created:
			return "Created";
		case bad_request:
			return "Bad Request";
		case not_found:
			return "Not Found";
		case internal_server_error:
			return "Internal Server Error";
		default:
			return "Unknown";
	}
}

std::string Socket::HTTPResponse(Socket::HTTPStatus status, const std::string& body, const std::string& contentType)
{
	std::ostringstream response;

	response 
		<< "HTTP/1.1 " << status << " " << HTTPStatusToString(status) << "\r\n"
		<< "Content-Type: " << contentType << "\r\n"
		<< "Content-Length: " << body.length() << "\r\n"
		<< "Connection: close\r\n"
		<< "\r\n"
		<< body;

	return response.str();
}

Socket::HTTPRequest Socket::ParseHTTPRequest(const std::string& request)
{
	HTTPRequest httpRequest = {};

	std::istringstream irequest(request);

	irequest >> httpRequest.method >> httpRequest.path;

	size_t bodyIndex = request.find("\r\n\r\n");

	if (bodyIndex != std::string::npos)
	{
		httpRequest.body = request.substr(bodyIndex + 4); // +4 to get past the newlines
	}

	return httpRequest;
}

void Socket::ReleaseReference()
{
	if (m_hasReference)
	{
		if (--s_referenceCount == 0)
		{
			WSACleanup();
		}

		m_hasReference = false;
	}
}

Socket::Socket(SOCKET handle)
	:m_socket(handle), m_hasReference(true)
{
	++s_referenceCount;
}
