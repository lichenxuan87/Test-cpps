/******************************************************************************
 * Project ZXQ Internet Car
 * (c) copyright 2015
 * Company SAIC Motor
 * All rights reserved
 * Secrecy Level STRICTLY CONFIDENTIAL
 *****************************************************************************/
/*
 * @file CJsonAdapter.cpp
 * @group NewTrack
 * @author wangjq
 * Generate json string
 */

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include <CJsonAdapter.hpp>
#include <cassert>
#include <util.hpp>
#include <macros.hpp>
#include <string.h>


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

CJsonAdapter::CJsonAdapter()
    : mpBuilder(nullptr)
{
    mpBuilder = json_builder_new();
    json_builder_begin_object(mpBuilder);

}

CJsonAdapter::~CJsonAdapter()
{
    if (nullptr != mpBuilder)
    {
        g_object_unref(mpBuilder);
        mpBuilder = nullptr;
    }
}

void CJsonAdapter::addKey(const string &key, const string &val)
{
    assert(mpBuilder != nullptr);

    if (key.empty() || val.empty())
    {
        return;
    }
    try
    {
        json_builder_set_member_name(mpBuilder, key.c_str());
        json_builder_add_string_value(mpBuilder, val.c_str());
    }
    COMMON_CATCH();
}

void CJsonAdapter::addKey(const string &key, int32_t val)
{
    assert(mpBuilder != nullptr);

    if (key.empty())
    {
        return;
    }
    try
    {
        json_builder_set_member_name(mpBuilder, key.c_str());
        json_builder_add_int_value(mpBuilder, val);
    }
    COMMON_CATCH();
}

void CJsonAdapter::addKey(const string &key, double val)
{
    assert(mpBuilder != nullptr);

    if (key.empty())
    {
        return;
    }
    try
    {
        json_builder_set_member_name(mpBuilder, key.c_str());
        json_builder_add_double_value(mpBuilder, val);
    }
    COMMON_CATCH();
}

void CJsonAdapter::addKey(const string &key, bool val)
{
    assert(mpBuilder != nullptr);

    if (key.empty())
    {
        return;
    }
    try
    {
        json_builder_set_member_name(mpBuilder, key.c_str());
        json_builder_add_boolean_value(mpBuilder, val);
    }
    COMMON_CATCH();
}

string CJsonAdapter::stringify()
{
    assert(mpBuilder != nullptr);

    string ret_str;
    try
    {
        json_builder_end_object (mpBuilder);
        auto root = json_builder_get_root(mpBuilder);
        auto gen = json_generator_new();
        if (root == nullptr || gen == nullptr)
        {
            throw "json_builder_get_root or json_generator_new failed.";
        }
        json_generator_set_root(gen, root);
        char *data = json_generator_to_data(gen, NULL);
        ret_str = data;
        g_free(data);
        json_node_free(root);
        g_object_unref(gen);
    }
    COMMON_CATCH();
    return ret_str;
}

bool CJsonAdapter::stringify(const map<string , bool> &map , string &ret)
{
    assert(mpBuilder != nullptr);

    try
    {
        JsonBuilder *sub_builder = json_builder_new();
        if(nullptr == sub_builder)
        {
        	return false;
        }

        JsonNode *node = nullptr;
        //JsonNode *sub_node = nullptr;

        json_builder_set_member_name(mpBuilder , "count");
        json_builder_add_int_value(mpBuilder , map.size());
        json_builder_set_member_name(mpBuilder , "list");

        json_builder_begin_array(sub_builder);

        for (auto ite = map.begin(); ite != map.end() ; ite++)
        {
            //LOG_D("<%s,%d>\n",ite->first.c_str(),ite->second);
            JsonBuilder *sub_sub_builder = json_builder_new();
            if(nullptr == sub_sub_builder)
            {
            	return false;
            }
            json_builder_begin_object(sub_sub_builder);

            json_builder_set_member_name(sub_sub_builder, "id");
            json_builder_add_string_value(sub_sub_builder, ite->first.c_str());

            json_builder_set_member_name(sub_sub_builder, "flag");
            json_builder_add_boolean_value(sub_sub_builder, ite->second);

            json_builder_end_object(sub_sub_builder);
            JsonNode *sub_node = json_builder_get_root(sub_sub_builder);
            if(nullptr == sub_node)
            {
            	return false;
            }

            json_builder_add_value(sub_builder , sub_node);
            g_object_unref(sub_sub_builder);
            //json_node_unref(sub_node);
        }

        json_builder_end_array(sub_builder);
        node = json_builder_get_root(sub_builder);          //memory leak 12 bytes every time
        if(nullptr == node)
        {
        	return false;
        }

        json_builder_add_value(mpBuilder , node);

        json_builder_end_object(mpBuilder);

        auto root = json_builder_get_root(mpBuilder);
        auto gen = json_generator_new();

        try
        {
            if (root == nullptr || gen == nullptr)
            {
            	g_object_unref(sub_builder);
            	json_node_free(node);
                throw "json_builder_get_root or json_generator_new failed.";
            }
        }
        catch (const char *exception)
        {
            LOG_E("exception %s\n", exception);
        	g_object_unref(sub_builder);
        	json_node_free(node);
            return false;
        }

        json_generator_set_root(gen, root);
        char *data = json_generator_to_data(gen, nullptr);
        //LOG_D("data:%s\tsize:%d\n", data, (int32_t)strlen(data));
        ret = data;
        g_free(data);
/*      JsonArray *arr = json_node_get_array(node);
		guint len = json_array_get_length(arr);
		LOG_D("len:%d", len);
		for(uint32_t i = 0; i < len ; i++)
		{
			json_node_free(json_array_get_element(arr, i));
		}*/
    	json_node_free(node);
    	g_object_unref(root);
        g_object_unref(gen);
        g_object_unref(sub_builder);
        //LOG_D("data:%s\tsize:%d\n", data, (int32_t)strlen(data));
        //LOG_D("ret:%s\tsize:%d\n", ret.c_str(), (int32_t)ret.length());
    }
    COMMON_CATCH();

    return true;
}


bool CJsonAdapter::stringify(const string &data , map<string , bool> &cfm)
{
    //LOG_D("stringify\n");
    try
    {
        string jstr(data);
        JsonParser *parser = json_parser_new ();
        GError *error = nullptr;
        json_parser_load_from_data (parser, jstr.c_str(), jstr.length(), &error);
        if (error)
        {
            LOG_I("Unable to parse %s: %s\n", jstr.c_str(), error->message);
            g_error_free (error);
            g_object_unref (parser);
            return false;
        }
        JsonReader *reader = json_reader_new (json_parser_get_root (parser));
        int32_t count = 0;
        string id;
        bool flag = true;

        if (json_reader_read_member(reader, "count"))
        {
            count = json_reader_get_int_value(reader);
            //LOG_D("count:%d\n",count);

        }
        json_reader_end_member(reader);

        if (count > 0 )
        {
            if (json_reader_read_member(reader, "list"))
            {
                //util::msControlFlagMap.clear();

                for (int32_t i = 0; i < count ; i++ )
                {
                    json_reader_read_element(reader , i);

                    if (json_reader_read_member(reader, "id"))
                    {
                        id = json_reader_get_string_value(reader);
                        //LOG_D("id:%s\n",id.c_str());
                    }
                    json_reader_end_member(reader);

                    if (json_reader_read_member(reader , "flag"))
                    {
                        flag = json_reader_get_boolean_value(reader);
                        //LOG_D("flag:%d\n",flag);
                    }
                    json_reader_end_member(reader);

                    json_reader_end_element(reader);

                    std::map<string, bool>::iterator itor = cfm.find(id);
                    if (itor != cfm.end())
                    {
                        itor->second = flag;
                    }
                    else
                    {
                        cfm.insert(map<string , bool>::value_type(id , flag));
                    }
                }
            }
            json_reader_end_member(reader);
        }
        else
        {
            g_object_unref(reader);
            g_object_unref(parser);
            return false;
        }

        g_object_unref(reader);
        g_object_unref(parser);

    }
    COMMON_CATCH();

    return true;
}

}


