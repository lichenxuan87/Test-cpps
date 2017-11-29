/******************************************************************************
 * Project ZXQ Internet Car
 * (c) copyright 2015
 * Company SAIC Motor
 * All rights reserved
 * Secrecy Level STRICTLY CONFIDENTIAL
 *****************************************************************************/
/*
 * @file CJsonDecoder.hpp
 * @group NewTrack
 * @author wangjq
 * Decode json string and get value
 */

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/

#include <cassert>
#include <CJsonDecoder.hpp>
#include <util.hpp>
#include <sstream>
#include <macros.hpp>

using std::stringstream;

namespace NNewTrack
{

/*-----------------------------------------------------------------------------
 * CLASS IMPLEMENTATIONS
 *----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * MACROS AND CONSTANTS
 *---------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
 * ENUMS, TYPEDEFS, STRUCTS
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * LOCAL AND GLOBAL VARIABLES
 *---------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
 * CLASS IMPLEMENTATIONS
 *---------------------------------------------------------------------------*/

CJsonDecoder::CJsonDecoder(): mpReader(nullptr)
{
    mpParser = json_parser_new ();
}

eJsonErrorCode CJsonDecoder::loadFromData(const string &data)
{
    assert(mpParser != nullptr);

    if (data.empty())
    {
        return eJsonErrorCode::JEC_DATA_EMPTY;
    }

    try
    {
        if (json_parser_load_from_data (mpParser, data.c_str(), -1, nullptr))
        {
            mpReader = json_reader_new (json_parser_get_root (mpParser));
        }
        else
        {
            return eJsonErrorCode::JEC_LOAD_FAIL;
        }
    }
    catch (...)
    {
        LOG_D("loadFromData fail!\n");
        return eJsonErrorCode::JEC_LOAD_FAIL;
    }
    return eJsonErrorCode::JEC_OK;
}


CJsonDecoder::~CJsonDecoder()
{
    if (mpParser != nullptr)
    {
        g_object_unref(mpParser);
        mpParser = nullptr;
    }
    if (mpReader != nullptr)
    {
        g_object_unref(mpReader);
        mpReader = nullptr;
    }
}

eJsonErrorCode CJsonDecoder::getVal(const string &key , string &value)
{
    assert(mpReader != nullptr);

    if (key.empty())
    {
        return eJsonErrorCode::JEC_KEY_EMPTY;
    }
    try
    {
        if (!hasKey(key))
        {
            return eJsonErrorCode::JEC_NO_KEY;
        }
        if (json_reader_read_member(mpReader , key.c_str()))
        {
            const char *str = json_reader_get_string_value(mpReader);
            json_reader_end_member(mpReader);
            if (nullptr != str)
            {
                value = str;
            }
            else
            {
                return eJsonErrorCode::JEC_WRONG_TYPE;
            }
        }
    }
    catch (...)
    {
        LOG_E("getVal error\n");
        return eJsonErrorCode::JEC_READ_FAIL;
    }
    return eJsonErrorCode::JEC_OK;
}

eJsonErrorCode CJsonDecoder::getVal(const string &key , int32_t &value)
{
    assert(mpReader != nullptr);

    if (key.empty())
    {
        return eJsonErrorCode::JEC_KEY_EMPTY;
    }
    try
    {
        if (!hasKey(key))
        {
            return eJsonErrorCode::JEC_NO_KEY;
        }
        if (json_reader_read_member(mpReader , key.c_str()))
        {
            int32_t val_tmp = json_reader_get_int_value(mpReader);
            if (val_tmp == 0)
            {
                const char *cstr = json_reader_get_string_value(mpReader);
                if (nullptr != cstr)
                {
                    return eJsonErrorCode::JEC_WRONG_TYPE;
                }
            }
            json_reader_end_member(mpReader);
            value = val_tmp;
        }
    }
    catch (...)
    {
        LOG_E("getVal error\n");
        return eJsonErrorCode::JEC_READ_FAIL;
    }
    return eJsonErrorCode::JEC_OK;
}


eJsonErrorCode CJsonDecoder::getVal(const string &key, bool &flag)
{
    assert(mpReader != nullptr);

    if (key.empty())
    {
        return eJsonErrorCode::JEC_KEY_EMPTY;
    }
    try
    {
        if (!hasKey(key))
        {
            return eJsonErrorCode::JEC_NO_KEY;
        }
        if (json_reader_read_member (mpReader, key.c_str()))
        {
            bool val_tmp = json_reader_get_boolean_value (mpReader);
            if (!flag)
            {
                const char *cstr = json_reader_get_string_value(mpReader);
                if (nullptr != cstr)
                {
                    return eJsonErrorCode::JEC_WRONG_TYPE;
                }
            }
            json_reader_end_member (mpReader);
            flag = val_tmp;
        }
    }
    catch (...)
    {
        LOG_E("getVal error\n");
        return eJsonErrorCode::JEC_READ_FAIL;
    }
    return eJsonErrorCode::JEC_OK;
}

void CJsonDecoder::startReadMember(const string &key)
{
    assert(mpReader != nullptr);

    if (key.empty())
    {
        return;
    }
    try
    {
        json_reader_read_member (mpReader, key.c_str());
    }
    COMMON_CATCH();
}

void CJsonDecoder::stopReadMember(void)
{
    assert(mpReader != nullptr);

    try
    {
        json_reader_end_member (mpReader);
    }
    COMMON_CATCH();
}

eJsonErrorCode CJsonDecoder::getElement(const int32_t n , string &val)
{
    assert(mpReader != nullptr);

    if (n < 0)
    {
        return eJsonErrorCode::JEC_NO_KEY;
    }
    try
    {
        if (json_reader_read_element (mpReader, n))
        {
            val = json_reader_get_string_value (mpReader);
            json_reader_end_element (mpReader);
        }
        else
        {
            return eJsonErrorCode::JEC_READ_FAIL;
        }
    }
    COMMON_CATCH();

    return eJsonErrorCode::JEC_OK;
}

eJsonErrorCode CJsonDecoder::getElement(const int32_t n , int32_t &val)
{
    assert(mpReader != nullptr);

    if (n < 0)
    {
        return eJsonErrorCode::JEC_NO_KEY;
    }
    try
    {
        if (json_reader_read_element (mpReader, n))
        {
            val = json_reader_get_int_value (mpReader);
            json_reader_end_element (mpReader);

        }
        else
        {
            return eJsonErrorCode::JEC_READ_FAIL;
        }
    }
    COMMON_CATCH();

    return eJsonErrorCode::JEC_OK;
}

void CJsonDecoder::startReadElement(int32_t n)
{
    assert(mpReader != nullptr);

    if (n < 0)
    {
        return;
    }
    try
    {
        json_reader_read_element (mpReader, n);
    }
    COMMON_CATCH();
}

void CJsonDecoder::stopReadElement(void)
{
    assert(mpReader != nullptr);
    try
    {
        json_reader_end_element (mpReader);
    }
    COMMON_CATCH();
}

bool CJsonDecoder::hasKey(const string &key)
{
    assert(mpReader != nullptr);

    bool ret = false;
    if (!key.empty())
    {
        try
        {
            if (json_reader_read_member (mpReader, key.c_str()))
            {
                ret = true;
            }
            json_reader_end_member(mpReader);
        }
        COMMON_CATCH();
    }

    return ret;
}

}



