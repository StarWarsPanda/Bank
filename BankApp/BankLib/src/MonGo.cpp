#include <MonGo.hpp>

#include <stdexcept>

MonGo::MonGo(const std::string& uri)
{
	char* error = nullptr;
	if (!ConnectMongoDB(uri.c_str(), &error))
	{
		std::string msg = error ? error : "Failed to connect to MongoDB";
		throw std::runtime_error(msg);
	}
}

MonGo::~MonGo()
{
	DisconnectMongoDB();
}

MonGo& MonGo::GetInstance(const std::string& uri)
{
	static MonGo instance(uri);
	return instance;
}

nlohmann::json MonGo::InsertOne(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& data)
{
	int outBDataLength;
	std::vector<uint8_t> bdata = nlohmann::json::to_bson(data);
	uint8_t* out = InsertOneMongoDB(databaseName.c_str(), collectionName.c_str(), bdata.data(), bdata.size(), &outBDataLength);
	std::vector<uint8_t> outBData(out, out + outBDataLength);
	nlohmann::json j = nlohmann::json::from_bson(outBData);

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}

nlohmann::json MonGo::InsertMany(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& data)
{
	int outBDataLength;
	std::vector<uint8_t> bdata = nlohmann::json::to_bson(data);
	uint8_t* out = InsertManyMongoDB(databaseName.c_str(), collectionName.c_str(), bdata.data(), bdata.size(), &outBDataLength);
	std::vector<uint8_t> outBData(out, out + outBDataLength);
	nlohmann::json j = nlohmann::json::from_bson(outBData);

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}

nlohmann::json MonGo::FindOne(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter)
{
	int outBDataLength;
	std::vector<uint8_t> bfilter = nlohmann::json::to_bson(filter);
	uint8_t* out = FindOneMongoDB(databaseName.c_str(), collectionName.c_str(), bfilter.data(), bfilter.size(), &outBDataLength);
	
	nlohmann::json j;
	if (out != nullptr && outBDataLength > 0)
	{
		std::vector<uint8_t> outBData(out, out + outBDataLength);
		j = nlohmann::json::from_bson(outBData);
	}
	else
	{
		j = nlohmann::json::object();
	}

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}

nlohmann::json MonGo::FindMany(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter)
{
	std::cout << filter.dump() << std::endl;

	int outBDataLength;
	std::vector<uint8_t> bfilter = nlohmann::json::to_bson(filter);
	uint8_t* out = FindManyMongoDB(databaseName.c_str(), collectionName.c_str(), bfilter.data(), bfilter.size(), &outBDataLength);
	
	nlohmann::json j;
	if (out != nullptr && outBDataLength > 0)
	{
		std::vector<uint8_t> outBData(out, out + outBDataLength);
		FreeGoBytes(out);
		j = nlohmann::json::from_bson(outBData);
	}
	else
	{
		j = nlohmann::json::object();
	}

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}

nlohmann::json MonGo::UpdateOne(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter, const nlohmann::json& update)
{
    int outBDataLength;
	std::vector<uint8_t> bfilter = nlohmann::json::to_bson(filter);
	std::vector<uint8_t> bupdate = nlohmann::json::to_bson(update);
	uint8_t* out = UpdateOneMongoDB(databaseName.c_str(), collectionName.c_str(), bfilter.data(), bfilter.size(), bupdate.data(), bupdate.size(), & outBDataLength);
	std::vector<uint8_t> outBData(out, out + outBDataLength);
	FreeGoBytes(out);
	nlohmann::json j = nlohmann::json::from_bson(outBData);

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}

nlohmann::json MonGo::UpdateMany(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter, const nlohmann::json& update)
{
	int outBDataLength;
	std::vector<uint8_t> bfilter = nlohmann::json::to_bson(filter);
	std::vector<uint8_t> bupdate = nlohmann::json::to_bson(update);
	uint8_t* out = UpdateManyMongoDB(databaseName.c_str(), collectionName.c_str(), bfilter.data(), bfilter.size(), bupdate.data(), bupdate.size(), &outBDataLength);
	std::vector<uint8_t> outBData(out, out + outBDataLength);
	nlohmann::json j = nlohmann::json::from_bson(outBData);

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}

nlohmann::json MonGo::DeleteOne(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter)
{
	int outBDataLength;
	std::vector<uint8_t> bfilter = nlohmann::json::to_bson(filter);
	uint8_t* out = DeleteOneMongoDB(databaseName.c_str(), collectionName.c_str(), bfilter.data(), bfilter.size(), &outBDataLength);
	std::vector<uint8_t> outBData(out, out + outBDataLength);
	nlohmann::json j = nlohmann::json::from_bson(outBData);

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}

nlohmann::json MonGo::DeleteMany(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter)
{
	int outBDataLength;
	std::vector<uint8_t> bfilter = nlohmann::json::to_bson(filter);
	uint8_t* out = DeleteManyMongoDB(databaseName.c_str(), collectionName.c_str(), bfilter.data(), bfilter.size(), &outBDataLength);
	std::vector<uint8_t> outBData(out, out + outBDataLength);
	nlohmann::json j = nlohmann::json::from_bson(outBData);

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}

nlohmann::json MonGo::ListDatabaseNames()
{
	int outBDataLength;
	uint8_t* out = ListDatabaseNamesMongoDB(&outBDataLength);
	std::vector<uint8_t> outBData(out, out + outBDataLength);
	nlohmann::json j = nlohmann::json::from_bson(outBData);

	if (j.is_object() && j.contains("error"))
	{
		std::cout << j["error"] << std::endl;
	}

	return j;
}
