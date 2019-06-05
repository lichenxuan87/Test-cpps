/*
 * ParameterSerializer.cpp
 *
 *  Created on: Sep 4, 2018
 *      Author: peter
 */

#include "KeyValueSerializer.h"
#include <iostream>

using namespace std;

bool KeyValueSerializer::openFile(const char* fileName, KeyValueSerializer::ACCESS_TYPE type)
{
    if (type == READ)
    {
        m_fileStream.open(fileName, ios::in | ios::binary);

    }
    else
    {
        m_fileStream.open(fileName, ios::out | ios::binary);
    }

    if (!m_fileStream.is_open())
    {
        cout << "Failed to open file " << fileName << endl;
        return false;
    }
    else
    {
        if (type == READ)
        {
            string line;
            size_t pos;
            while(getline(m_fileStream, line))
            {
                pos = line.find(":");
                m_keyValuePairs.insert(std::make_pair<string, string>(line.substr(0, pos), line.substr(pos+1)));
            }
        }
        return true;
    }
}

void KeyValueSerializer::closeFile()
{
    m_fileStream.close();
}

bool KeyValueSerializer::writeKeyValuePair(const char* key, const char* value)
{
    m_fileStream << key << ":" << value << "\n";

    return true;
}

bool KeyValueSerializer::getValue(string key, string& value)
{
    unordered_map<string, string>::const_iterator got = m_keyValuePairs.find (key);

    if ( got == m_keyValuePairs.end() )
    {
        std::cout << "not found";
        return false;
    }
    else
    {
        value = got->second;
        return true;
    }
}

