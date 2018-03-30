#include "SqlValue.h"


namespace sql
{

Value::Value()
{
    setValue(nullptr, type_undefined);
}

Value::Value(char *value, field_type type)
{
    setValue(value, type);
}

Value::Value(const Value &value)
{
    this->_value = value._value;
    this->_isnullptr = value._isnullptr;
    this->_type = value._type;
}

Value &Value::operator=(const Value &value)
{
    if (this != &value) {
        this->_value = value._value;
        this->_isnullptr = value._isnullptr;
        this->_type = value._type;
    }
    return *this;
}

bool Value::equals(Value &value)
{
    if (isnullptr() && value.isnullptr()) {
        return true;
    }

    switch (_type) {
    case type_int:
        return (asInteger() == value.asInteger());
    case type_text:
        return (asString().compare(value.asString()) == 0);
    case type_float:
        return (asDouble() == value.asDouble());
    case type_bool:
        return (asBool() == value.asBool());
    case type_time:
        return (asTime() == value.asTime());
    default:
        return (asInteger() == value.asInteger());
    }

    return false;
}

void Value::setValue(char *value, field_type type)
{
    _isnullptr = true;
    _value.clear();
    _type = type;

    if (value) {
        _isnullptr = false;
        _value = value;
        _type = type;
    }
}

string Value::toSql(field_type type)
{
    if (isnullptr()) {
        return "null";
    }

    if (type == type_text) {
        return "'" + quoteStr(asString()) + "'";
    }

    if (_type == type_time) {
        return intToStr(asInteger());
    }

    return asString();
}

string Value::toString()
{
    if (isnullptr()) {
        return "null";
    }

    return asString();
}

string Value::asString()
{
    if (_type == type_time) {
        time t(asInteger());
        return t.asString();
    }

    return _value;
}

integer Value::asInteger()
{
    if (isnullptr()) {
        return 0;
    }

    return strtoll(_value.c_str(), nullptr, 10);
}

double Value::asDouble()
{
    if (isnullptr()) {
        return 0.0;
    }

    return atof(_value.c_str());
}

bool Value::asBool()
{
    if (isnullptr()) {
        return false;
    }

    return (_value.compare("1") == 0);
}

time Value::asTime()
{
    time dt(asInteger());
    return dt;
}

void Value::setnullptr()
{
    _isnullptr = true;
    _value.clear();
}

void Value::setString(string value)
{
    _isnullptr = false;
    _value = value;
}

//CRT_SECURE_NO_WARNINGS
//#pragma warning(disable : 4996)

void Value::setInteger(integer value)
{
    char buffer[128];

    sprintf(buffer, "%lld", value);

    _isnullptr = false;
    _value = buffer;
}

void Value::setDouble(double value)
{
    char buffer[128];

    sprintf(buffer, "%0.8f", value);

    _isnullptr = false;
    _value = buffer;
}

//#pragma warning(default : 4996)

void Value::setBool(bool value)
{
    _isnullptr = false;
    _value = (value ? "1" : "0");
}

void Value::setTime(time value)
{
    time t(value);
    _isnullptr = false;
    setInteger(t.asInteger());
}

bool Value::isnullptr()
{
    return _isnullptr;
}


//sql eof
};
