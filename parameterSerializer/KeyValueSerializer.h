/*
 * parameterSerializer.h
 *
 *  Created on: Sep 4, 2018
 *      Author: peter
 */

#ifndef PARAMETERSERIALIZER_KEYVALUESERIALIZER_H_
#define PARAMETERSERIALIZER_KEYVALUESERIALIZER_H_

#include <fstream>
#include <unordered_map>
#include <string>

class KeyValueSerializer
{
public:
    enum ACCESS_TYPE
    {
        READ,
        WRITE
    };

    KeyValueSerializer() {}

    bool openFile(const char* fileName, KeyValueSerializer::ACCESS_TYPE type);
    void closeFile();

    bool writeKeyValuePair(const char* key, const char* value);

    bool getValue(std::string key, std::string& value);

private:
    std::fstream m_fileStream;
    std::unordered_map<std::string, std::string> m_keyValuePairs;
};



#endif /* PARAMETERSERIALIZER_KEYVALUESERIALIZER_H_ */
