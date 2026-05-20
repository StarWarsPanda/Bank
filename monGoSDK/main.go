package main

// #include <stdlib.h>
// #include <stdint.h>
import "C"

import (
	"fmt"
	"unsafe"

	"monGoSDK/sdk"

	"go.mongodb.org/mongo-driver/v2/bson"
)

func sanitizeBson(v any) any {
	switch val := v.(type) {
	case bson.ObjectID:
		return val.Hex()
	case bson.M:
		for k, inner := range val {
			val[k] = sanitizeBson(inner)
		}
		return val
	case map[string]any:
		for k, inner := range val {
			val[k] = sanitizeBson(inner)
		}
		return val
	case bson.A:
		for i, inner := range val {
			val[i] = sanitizeBson(inner)
		}
		return val
	case bson.D:
		for i := range val {
			val[i].Value = sanitizeBson(val[i].Value)
		}
		return val
	case []any:
		for i, inner := range val {
			val[i] = sanitizeBson(inner)
		}
		return val
	default:
		return val
	}
}

func bsonBytesToC(value any, outLen *C.int) *C.uchar {
	bsonData, err := bson.Marshal(sanitizeBson(value))
	if err != nil {
		if outLen != nil {
			*outLen = 0
		}

		return nil
	}

	if outLen != nil {
		*outLen = C.int(len(bsonData))
	}

	return (*C.uchar)(C.CBytes(bsonData))
}

func bsonErrorToC(message string, outLen *C.int) *C.uchar {
	return bsonBytesToC(bson.M{"error": message}, outLen)
}

func bsonBytesFromC(data *C.uchar, dataLen C.int) ([]byte, error) {
	if data == nil || dataLen <= 0 {
		return nil, fmt.Errorf("input empty")
	}

	return C.GoBytes(unsafe.Pointer(data), dataLen), nil
}

func toBsonM(value any) (bson.M, error) {
	switch v := value.(type) {
	case bson.M:
		return v, nil
	case map[string]any:
		return bson.M(v), nil
	default:
		return nil, fmt.Errorf("value is not a BSON object")
	}
}

func BytesToBsonM(data *C.uchar, dataLen C.int) (bson.M, error) {
	bsonData, err := bsonBytesFromC(data, dataLen)
	if err != nil {
		return nil, err
	}

	var document bson.M
	if err := bson.Unmarshal(bsonData, &document); err == nil {
		return document, nil
	}

	var documents []bson.M
	if err := bson.Unmarshal(bsonData, &documents); err == nil {
		if len(documents) == 0 {
			return nil, fmt.Errorf("BSON array is empty; expected at least one object")
		}

		return documents[0], nil
	}

	return nil, fmt.Errorf("BSON must decode to an object or an array of objects")
}

//export ConnectMongoDB
func ConnectMongoDB(uri *C.char, errorOut **C.char) C.bool {
	if error := sdk.Connect(C.GoString(uri)); error != nil {
		if errorOut != nil {
			*errorOut = C.CString(error.Error())
		}

		return false
	}

	return true
}

//export DisconnectMongoDB
func DisconnectMongoDB() {
	sdk.Disconnect()
}

//export InsertOneMongoDB
func InsertOneMongoDB(databaseName *C.char, collectionName *C.char, data *C.uchar, dataLen C.int, outLen *C.int) *C.uchar {
	bsonData, err := BytesToBsonM(data, dataLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	result := sdk.InsertOne(C.GoString(databaseName), C.GoString(collectionName), bsonData)
	return bsonBytesToC(result.Data, outLen)
}

//export InsertManyMongoDB
func InsertManyMongoDB(databaseName *C.char, collectionName *C.char, data *C.uchar, dataLen C.int, outLen *C.int) *C.uchar {
	bsonData, err := BytesToBsonM(data, dataLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	result := sdk.InsertMany(C.GoString(databaseName), C.GoString(collectionName), bsonData)
	return bsonBytesToC(bson.M{
		"request":  bsonData,
		"response": result.Data,
	}, outLen)
}

//export FindOneMongoDB
func FindOneMongoDB(databaseName *C.char, collectionName *C.char, filter *C.uchar, filterLen C.int, outLen *C.int) *C.uchar {
	bsonFilter, err := BytesToBsonM(filter, filterLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	result := sdk.FindOne(C.GoString(databaseName), C.GoString(collectionName), bsonFilter)
	return bsonBytesToC(bson.M{
		"request":  bsonFilter,
		"response": result.Data,
	}, outLen)
}

//export FindManyMongoDB
func FindManyMongoDB(databaseName *C.char, collectionName *C.char, filter *C.uchar, filterLen C.int, outLen *C.int) *C.uchar {
	bsonFilter, err := BytesToBsonM(filter, filterLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	results := sdk.FindMany(C.GoString(databaseName), C.GoString(collectionName), bsonFilter)

	var resultsData []any
	for _, result := range results {
		if result.Success {
			resultsData = append(resultsData, sanitizeBson(result.Data))
		}
	}

	return bsonBytesToC(bson.M{
		"request":  bsonFilter,
		"response": resultsData,
	}, outLen)
}

//export UpdateOneMongoDB
func UpdateOneMongoDB(databaseName *C.char, collectionName *C.char, filter *C.uchar, filterLen C.int, update *C.uchar, updateLen C.int, outLen *C.int) *C.uchar {
	bsonFilter, err := BytesToBsonM(filter, filterLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	bsonUpdate, err := BytesToBsonM(update, updateLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	result := sdk.UpdateOne(C.GoString(databaseName), C.GoString(collectionName), bsonFilter, bsonUpdate)
	return bsonBytesToC(result.Data, outLen)
}

//export UpdateManyMongoDB
func UpdateManyMongoDB(databaseName *C.char, collectionName *C.char, filter *C.uchar, filterLen C.int, update *C.uchar, updateLen C.int, outLen *C.int) *C.uchar {
	bsonFilter, err := BytesToBsonM(filter, filterLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	bsonUpdate, err := BytesToBsonM(update, updateLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	result := sdk.UpdateMany(C.GoString(databaseName), C.GoString(collectionName), bsonFilter, bsonUpdate)
	return bsonBytesToC(result.Data, outLen)
}

//export DeleteOneMongoDB
func DeleteOneMongoDB(databaseName *C.char, collectionName *C.char, filter *C.uchar, filterLen C.int, outLen *C.int) *C.uchar {
	bsonFilter, err := BytesToBsonM(filter, filterLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	result := sdk.DeleteOne(C.GoString(databaseName), C.GoString(collectionName), bsonFilter)
	return bsonBytesToC(result.Data, outLen)
}

//export DeleteManyMongoDB
func DeleteManyMongoDB(databaseName *C.char, collectionName *C.char, filter *C.uchar, filterLen C.int, outLen *C.int) *C.uchar {
	bsonFilter, err := BytesToBsonM(filter, filterLen)
	if err != nil {
		return bsonErrorToC(err.Error(), outLen)
	}

	result := sdk.DeleteMany(C.GoString(databaseName), C.GoString(collectionName), bsonFilter)
	return bsonBytesToC(result.Data, outLen)
}

//export ListDatabaseNamesMongoDB
func ListDatabaseNamesMongoDB(outLen *C.int) *C.uchar {
	result := sdk.ListDatabaseNames()
	return bsonBytesToC(result.Data, outLen)
}

//export FreeGoBytes
func FreeGoBytes(ptr unsafe.Pointer) {
	C.free(ptr)
}

func main() {}
