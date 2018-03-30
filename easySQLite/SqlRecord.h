//
// Copyright (C) 2010 Piotr Zagawa
//
// Released under BSD License
//

#pragma once

#include <vector>

#include "SqlValue.h"
#include "SqlCommon.h"
#include "SqlFieldSet.h"


namespace sql
{

class Record
{
private:
	FieldSet* _fields;
	std::vector<Value> _values;

public:
	Record(FieldSet* fields);
	Record(Record* record);
	Record(const Record& record);

private:
	friend class RecordSet;

	void initColumnCount(int columns);
	void initColumnValue(int column_index, char* value, field_type type);

public:
	int columnCount();
	Value* getValue(int column_index);
	Value* getValue(string fieldName);
	Value* getKeyIdValue();
	Field* fieldByName(string fieldName);
	FieldSet* fields();
	string toString();
	string toSql();
	bool equalsColumnValue(Record* record, string fieldName);
	bool equalsValues(Record* record);

public:
	string toSqlInsert(string tableName);
	string toSqlUpdate(string tableName, unsigned int updateKeyIndex = 0);

public:
	void setnullptr(int index);
	void setString(int index, string value);
	void setInteger(int index, integer value);
	void setDouble(int index, double value);
	void setBool(int index, bool value);
	void setTime(int index, time value);

public:
	void setnullptr(string fieldName);
	void setString(string fieldName, string value);
	void setInteger(string fieldName, integer value);
	void setDouble(string fieldName, double value);
	void setBool(string fieldName, bool value);
	void setTime(string fieldName, time value);

};


//sql eof
};
