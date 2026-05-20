package sdk

import (
	"context"
	"sync"
	"time"

	"go.mongodb.org/mongo-driver/v2/bson"
	"go.mongodb.org/mongo-driver/v2/mongo"
	"go.mongodb.org/mongo-driver/v2/mongo/options"
	"go.mongodb.org/mongo-driver/v2/mongo/readpref"
)

//export Document
type Document struct {
	Success bool
	Data    bson.M
}

var (
	mongoClient *mongo.Client
	mutex       sync.Mutex
)

func Connect(uri string) error {
	mutex.Lock()
	defer mutex.Unlock()

	context, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	clientOptions := options.Client().ApplyURI(uri)
	client, error := mongo.Connect(clientOptions)

	if error != nil {
		return error
	}

	if error = client.Ping(context, readpref.Primary()); error != nil {
		return error
	}

	mongoClient = client
	return nil
}

func Disconnect() error {
	mutex.Lock()
	defer mutex.Unlock()

	if mongoClient == nil {
		return nil
	}

	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	return mongoClient.Disconnect(context)
}

func InsertOne(databaseName string, collectionName string, document any) Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	result, error := mongoClient.Database(databaseName).Collection(collectionName).InsertOne(context, document)

	if error != nil {
		return Document{Success: false, Data: bson.M{"error": error.Error()}}
	}

	return Document{Success: result != nil, Data: bson.M{"Acknowledged": result.Acknowledged, "InsertedID": result.InsertedID}}
}

func InsertMany(databaseName string, collectionName string, documents any) Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	result, error := mongoClient.Database(databaseName).Collection(collectionName).InsertMany(context, documents)

	if error != nil {
		return Document{Success: false, Data: bson.M{"error": error.Error()}}
	}

	return Document{Success: result != nil, Data: bson.M{"Acknowledged": result.Acknowledged, "InsertedIDs": result.InsertedIDs}}
}

func FindOne(databaseName string, collectionName string, filter bson.M) Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	var result bson.M
	error := mongoClient.Database(databaseName).Collection(collectionName).FindOne(context, filter).Decode(&result)

	if error != nil {
		return Document{Success: false, Data: bson.M{"error": error.Error()}}
	}

	return Document{Success: result != nil, Data: result}
}

func FindMany(databaseName string, collectionName string, filter bson.M) []Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	cursor, error := mongoClient.Database(databaseName).Collection(collectionName).Find(context, filter)

	if error != nil {
		return []Document{{Success: false, Data: bson.M{"error": error.Error()}}}
	}

	defer cursor.Close(context)

	var results []bson.M
	error = cursor.All(context, &results)

	if error != nil {
		return []Document{{Success: false, Data: bson.M{"error": error.Error()}}}
	}

	documents := make([]Document, 0, len(results))

	for i := 0; i < len(results); i++ {
		documents = append(documents, Document{
			Success: results[i] != nil,
			Data:    results[i],
		})
	}

	return documents
}

func UpdateOne(databaseName string, collectionName string, filter bson.M, update bson.M) Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	result, error := mongoClient.Database(databaseName).Collection(collectionName).UpdateOne(context, filter, update)

	if error != nil {
		return Document{Success: false, Data: bson.M{"error": error.Error()}}
	}

	return Document{Success: false, Data: bson.M{
		"Acknowledged":  result.Acknowledged,
		"MatchedCount":  result.MatchedCount,
		"ModifiedCount": result.ModifiedCount,
		"UpsertedCount": result.UpsertedCount,
		"UpsertedID":    result.UpsertedID,
	}}
}

func UpdateMany(databaseName string, collectionName string, filter bson.M, update bson.M) Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	result, error := mongoClient.Database(databaseName).Collection(collectionName).UpdateMany(context, filter, update)

	if error != nil {
		return Document{Success: false, Data: bson.M{"error": error.Error()}}
	}

	return Document{Success: false, Data: bson.M{
		"Acknowledged":  result.Acknowledged,
		"MatchedCount":  result.MatchedCount,
		"ModifiedCount": result.ModifiedCount,
		"UpsertedCount": result.UpsertedCount,
		"UpsertedID":    result.UpsertedID,
	}}
}

func DeleteOne(databaseName string, collectionName string, filter bson.M) Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	result, error := mongoClient.Database(databaseName).Collection(collectionName).DeleteOne(context, filter)

	if error != nil {
		return Document{Success: false, Data: bson.M{"error": error.Error()}}
	}

	return Document{Success: false, Data: bson.M{
		"Acknowledged": result.Acknowledged,
		"DeletedCount": result.DeletedCount,
	}}
}

func DeleteMany(databaseName string, collectionName string, filter bson.M) Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	result, error := mongoClient.Database(databaseName).Collection(collectionName).DeleteMany(context, filter)

	if error != nil {
		return Document{Success: false, Data: bson.M{"error": error.Error()}}
	}

	return Document{Success: false, Data: bson.M{
		"Acknowledged": result.Acknowledged,
		"DeletedCount": result.DeletedCount,
	}}
}

func ListDatabaseNames() Document {
	context, cancel := context.WithTimeout(context.Background(), 5*time.Second)
	defer cancel()

	names, error := mongoClient.ListDatabaseNames(context, bson.M{})

	if error != nil {
		return Document{Success: false, Data: bson.M{"error": error.Error()}}
	}

	return Document{Success: false, Data: bson.M{
		"databases": names,
	}}
}
