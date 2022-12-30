#ifndef MONGODBCREATOR_H
#define MONGODBCREATOR_H

#include <string>
#include <vector>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

const std::string mongoDBUri = "mongodb://localhost:27017/";
//constexpr char mongoDBUri[] = "mongodb://localhost:27017/";

class MongoDBCreator
{
public:
    MongoDBCreator(std::string dbName, std::string collectionName) :
        _uri(mongocxx::uri(mongoDBUri)),
        _client(mongocxx::client(_uri)),
        _database_name(dbName),
        _collection_name(collectionName),
        _db(_client[_database_name]) {
        _coll = _db[_collection_name];
    }

    MongoDBCreator(std::string collName);

    void initialiseDB();
    bool findRecord();
    bool setCollection(std::string collectionName);
    bool insertPassword(std::string url, std::string username,
                        std::string password);
    bool insertManyPasswords(std::vector<std::string> url, std::vector<std::string> username,
        std::vector<std::string> password);
    bool removePasswordRecord(std::string url);
    bool updatePasswordRecord(std::string url, std::string new_url,
        std::string username, std::string new_username, std::string password,
        std::string new_password);
    bool updatePasswordRecord(const std::string& pword_id);

private:
    std::string getDateTimeNow();

    std::string _collection_name;
    std::string _database_name;

    mongocxx::uri _uri;
    mongocxx::client _client;
    mongocxx::database _db;
    mongocxx::collection _coll;
};

#endif // MONGODBCREATOR_H
