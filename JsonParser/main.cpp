/*
 * main.cpp
 *
 *  Created on: Dec 7, 2017
 *      Author: knowyou
 */



#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define AMBIENTLIGHT_STATUS                 0
#define AMBIENTLIGHT_WELCOME_STATUS         1
#define AMBIENTLIGHT_WELCOME_MODE           2
#define AMBIENTLIGHT_STARTUP_STATUS         3
#define AMBIENTLIGHT_STARTUP_MODE           4
#define AMBIENTLIGHT_SPEECH_FOLLOWUP_STATUS 5
#define AMBIENTLIGHT_MUSIC_FOLLOWUP_STATUS  6
#define AMBIENTLIGHT_DRIVE_MODE             7
#define AMBIENTLIGHT_DEFAULT_STATUS         8
#define AMBIENTLIGHT_DEFAULT_VALUE          9

#define VEHICLE_VALUE_TYPE_BOOL             0
#define VEHICLE_VALUE_TYPE_BOOL_VEC         1
#define VEHICLE_VALUE_TYPE_INT32            2
#define VEHICLE_VALUE_TYPE_INT32_VEC        3


const char* valueTypeToString(int valueType);
const char* propertyIdToString(int propertyId);


int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << "Usage: jsonParser <json file name>" << endl;
    }

    Json::Value root;
    Json::Reader reader;

    ifstream is;
    is.open(argv[1], std::ios::binary);

    if (reader.parse(is, root))
    {
        if (!root["properties"].isNull())
        {
            int numOfProperties = root["properties"].size();

            for (int i = 0; i < numOfProperties; i++)
            {
                Json::Value property = root["properties"][i];
                int propertyId = property["property"].asInt();

                int valueType = property["value_type"].asInt();

                cout << "Property: " << propertyIdToString(propertyId)
                     << ", value type: " << valueTypeToString(valueType) << ", value: ";

                switch (valueType)
                {
                case 0: // VEHICLE_VALUE_TYPE_BOOL
                    cout << property["value"].asInt() << endl;
                    break;
                case 1: // VEHICLE_VALUE_TYPE_BOOL_VEC
                    cout << "[ ";

                    for (int j = 0; j < property["value"].size(); j++)
                    {
                        Json::Value boolValue = property["value"][j];
                        cout << boolValue.asInt() << ", ";
                    }
                    cout << " ]" << endl;
                    break;
                case 2:
                    break;
                case 3: // VEHICLE_VALUE_TYPE_INT32_VEC
                    cout << "[ ";

                    for (int j = 0; j < property["value"].size(); j++)
                    {
                        Json::Value intValue = property["value"][j];
                        cout << intValue.asInt() << ", ";
                    }

                    cout << " ]" << endl;

                    break;

                default:
                    break;
                }
            }
        }
        else
        {
            cout << "No key named properties" << endl;
        }
    }
    else
    {
        cout << "Parse error" << endl;
    }
    is.close();

    return 0;
}


const char* propertyIdToString(int propertyId)
{
    switch (propertyId)
    {
    case 0:
        return "AMBIENTLIGHT_STATUS";
        break;
    case 1:
        return "AMBIENTLIGHT_WELCOME_STATUS";
        break;
    case 9:
        return "AMBIENTLIGHT_DEFAULT_VALUE";
        break;
    default:
        return "Default";
        break;
    }
}

const char* valueTypeToString(int valueType)
{
    switch (valueType)
    {
    case 0:
        return "VEHICLE_VALUE_TYPE_BOOL";
        break;
    case 1:
        return "VEHICLE_VALUE_TYPE_BOOL_VEC";
        break;
    case 3:
        return "VEHICLE_VALUE_TYPE_INT32_VEC";
        break;
    default:
        return "Default";
        break;
    }
}
