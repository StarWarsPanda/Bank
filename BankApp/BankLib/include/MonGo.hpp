#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include <monGoSDK.h>

class MonGo
{
    public:
        static MonGo& GetInstance(const std::string& uri);

        ~MonGo();

        MonGo(const MonGo&) = delete;
        MonGo& operator=(const MonGo&) = delete;

        nlohmann::json InsertOne(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& data);
        nlohmann::json InsertMany(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& data);
        nlohmann::json FindOne(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter);
        nlohmann::json FindMany(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter);

        nlohmann::json UpdateOne(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter, const nlohmann::json& update);
        nlohmann::json UpdateMany(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter, const nlohmann::json& update);

        nlohmann::json DeleteOne(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter);
        nlohmann::json DeleteMany(const std::string& databaseName, const std::string& collectionName, const nlohmann::json& filter);

        nlohmann::json ListDatabaseNames();
    private:
        explicit MonGo(const std::string& uri);
};
