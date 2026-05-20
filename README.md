# Bank Application

A comprehensive C++ banking system featuring a modular architecture with account management, customer management, and network communication capabilities.

## Overview

The Bank Application is a production-oriented banking platform built in C++ with a layered architecture. It provides RESTful API operations for customer and account management with robust data persistence and socket-based communication.

## Architecture

### Project Structure

- **BankLib** - Core banking library with business logic and database abstraction
- **BankRun** - Application entry point and runtime environment
- **monGoSDK** - MongoDB integration layer providing database operations
- **Testing** - Comprehensive test suite using Google Test

### Layered Architecture

The system implements a classic layered architecture pattern:

1. **Controllers** - HTTP request handling and routing
   - `AccountController` - Account operations
   - `CustomerController` - Customer operations

2. **Services** - Business logic layer
   - `AccountService` - Account business logic
   - `CustomerService` - Customer business logic

3. **Repositories** - Data access layer
   - `AccountRepo` - Account persistence operations
   - `CustomerRepo` - Customer persistence operations

4. **Models** - Domain entities
   - `AccountModel` - Account entity definition
   - `CustomerModel` - Customer entity definition

5. **Infrastructure**
   - `MonGo` - MongoDB database abstraction layer with CRUD operations
   - `Socket` - Network communication handler
   - `Currency` - Currency conversion utilities

## Technical Details

### Technology Stack

- **Language**: C++ (Visual Studio 2022+) with C++20 Standard
- **Database**: MongoDB with Go integration (monGoSDK)
- **Networking**: Windows Sockets API (Winsock2)
- **Data Format**: JSON (nlohmann/json library)
- **Testing Framework**: Google Test (v1.8.1)
- **Build System**: Visual Studio (MSVC) with Premake5

### Core Components

#### Customer Management
- Create, retrieve, update, and delete customer records
- Maintains customer profile information and transaction history
- Customer validation and business rule enforcement

#### Account Management
- Multi-account support per customer
- Account operations (deposit, withdrawal, balance inquiry)
- Account status tracking and security features

#### Network Communication
- Socket-based client-server communication
- JSON-serialized request/response protocol
- Thread-safe operation handling

##MongoDB integration for scalable persistent storage
- Repository pattern abstraction layer for data access
- JSON-based entity serialization/deserialization
- CRUD operations through MonGo abstraction (InsertOne/Many, FindOne/Many, UpdateOne/Many, DeleteOne/Many)port
- Entity serialization/deserialization

## Project Files

### Core Library (BankLib)

**Headers** (`include/`):
- Controllers and Services for business operations
- Models for entity definitions
- Repository interfaces for data access
- Infrastructure utilities

**Implementation** (`src/`):
- Socket communication logic
- Currency conversion algorithms
- Service implementation and business rules
- Repository data access patterns

### Application (BankRun)

- `BankApp.cpp` - Main application entry point
- Application initialization and request processing

### Testing (Testing)

- `test.cpp` - Test suite with Google Test framework
- Unit and integration tests for core functionality
- Repository and service layer validation

## Build Instructions

### Prerequisites

- Visual Studio 2022 or later
- Windows SDK (included with Visual Studio)
- `nlohmann/json` (included in project)

### Building

1. Ensure MongoDB is installed and accessible (required for monGoSDK integration).
3. From the base directory where you cloned the source (the `premake5.lua` file should be in the current folder), generate the Visual Studio 2022 solution:
   ```sh
   premake5 vs2022
   ```
   This creates the Bank workspace with `BankLib`, `BankApp`, and `Testing` project files in the `BankApp` directory.
4. Open the generated solutionank.sln` along with the `BankLib` and `BankApp` project files.
3. Open `BankApp/Bank.sln` in Visual Studio 2022 and build the solution

### Running Tests

Execute the Testing project to validate all functionality:
- Account operations
- Customer management
- Data persistence
- Network communication

## API Operations

### Customer Operations
- **Create Customer** - Register new customer
- **Retrieve Customer** - Fetch customer details
- **Update Customer** - Modify customer information
- **Delete Customer** - Remove customer record

### Account Operations
- **Create Account** - Open new account
- **Deposit** - Add funds to account
- **Withdraw** - Remove funds from account
- **Check Balance** - Query account balance
- **Transaction History** - View account transactions

## Dependencies
MongoDB** - Database backend (required for data persistence)
- **monGoSDK** - Go-based MongoDB C++ wrapper (included in workspace)
- **nlohmann/json** - JSON library for serialization/deserialization
- **Windows Sockets API** - Network communication
- **Google Test** - Unit testing framework
- **C++20 Standard Library** - STL containers and utilities
- **C++20 Standard Library** - STL containers and utilities (>=20 for `std::optional`)

## Configuration

Configuration parameters are defined in project headers and can be modified for:
- Server port and listening address
- Database connection strings (if persistent storage enabled)
- Currency conversion rates
- Transaction limits and validations

## Development Notes

- Follow the repository pattern for data access
- Implement business logic in service classes
- Maintain separation of concerns across layers
- Add comprehensive tests for new features
- Use JSON format for all network communication

## Future Enhancements

- Database integration for persistent storage
- Enhanced security (authentication/authorization)
- Transaction logging and audit trails
- API rate limiting and throttling
- Comprehensive error handling and logging
