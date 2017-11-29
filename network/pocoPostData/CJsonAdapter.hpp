/******************************************************************************
 * Project ZXQ Internet Car
 * (c) copyright 2015
 * Company SAIC Motor
 * All rights reserved
 * Secrecy Level STRICTLY CONFIDENTIAL
 *****************************************************************************/
/*
 * @file CJsonAdapter.hpp
 * @group NewTrack
 * @author wangjq
 * Generate json string
 */

#ifndef _CJSON_ADAPTER_HPP_
#define _CJSON_ADAPTER_HPP_

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include <string>
#include <map>

using std::string;
using std::map;
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


class CJsonAdapter
{
public:

    /*
     *create a json adapter to generate a json string
     *
     */
    CJsonAdapter();

    /*
     *destructor of json adapter
     *
     */
    ~CJsonAdapter();

    /*
     *add a string key-value to json string
     *
     *@iparam key name
     *@iparam key value
     *
     */
    void addKey(const string &key, const string &val);
    /*
     *add a int32_t key-value to json string
     *
     *@iparam key name
     *@iparam key value
     *
     */
    void addKey(const string &key, int32_t val);

    /*
     *add a double key-value to json string
     *
     *@iparam key name
     *@iparam key value
     *
     */
    void addKey(const string &key, double val);

    /*
     *add a bool key-value to json string
     *
     *@iparam key name
     *@iparam key value
     *
     */
    void addKey(const string &key, bool val);

    /*
     *change json object to json string
     *
     *@oparam json string
     */
    string stringify();

    /*
     *change map<string , bool> to string
     *
     *@iparam map<string , bool>
     *@iparam string to save return value
     *
     *@oparam bool
     */
    bool stringify(const map<string , bool> &map , string &data);

    /*
     *change string map<string , bool>
     *
     *@oparam string
     *
     *@oparam map<string , bool>
     *
     */
    bool stringify(const string &data, map<string , bool> &cfm);




private:

    /*
     *class number
     *
     */
    JsonBuilder *mpBuilder;

};
}
#endif    //_CJSON_ADAPTER_HPP_
