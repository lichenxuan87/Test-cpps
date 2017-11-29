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

#ifndef _CJSON_DECODER_HPP_
#define _CJSON_DECODER_HPP_

/*-----------------------------------------------------------------------------
 * INCLUDES AND NAMESPACE
 *---------------------------------------------------------------------------*/
#include <string>
#include <glib-object.h>
#include <json-glib/json-glib.h>
#include <enums.hpp>

using std::string;
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

class CJsonDecoder
{

public:


    /*
     *create a json decoder
     *
     */
    CJsonDecoder();

    /*
     *load data from string
     *
     *@iparam string data
     *
     *@oparam errorcode
     */
    eJsonErrorCode loadFromData(const string &data);

    /*
     *destructor of json decoder
     *
     */
    ~CJsonDecoder();

    /*
     *get string key value
     *
     *@iparam key name
     *@iparam referance for store key value
     *
     *@oparam eJsonErrorCode
     */
    eJsonErrorCode getVal(const string &key , string &value);


    /*
     *get int32_t key value
     *
     *@iparam key name
     *@iparam referance for store key value
     *
     *@oparam eJsonErrorCode
     */
    eJsonErrorCode getVal(const string &key, int32_t &value);


    /*
     *get bool key value
     *
     *@iparam key name
     *
     *@oparam key value in bool
     */
    eJsonErrorCode getVal(const string &key, bool &flag);

    /*
     *start read json member key nama
     *
     *@iparam key name
     *
     */
    void startReadMember(const string &key);

    /*
     *end read json member
     *
     *appear with startReadMember in pair
     *
     */
    void stopReadMember(void);

    /*
     *get elements of json member
     *
     *@iparam index of element
     *
     *@oparam element value in string
     *
     */
    eJsonErrorCode getElement(const int32_t n , string &val);

    /*
     *get elements of json member
     *
     *@iparam index of element
     *
     *@oparam element value in int32_t
     *
     */
    eJsonErrorCode getElement(const int32_t n , int32_t &val);

    /*
     *start read json elements
     *
     *@iparam index of element
     *
     */
    void startReadElement(int32_t n);

    /*
     *end read json element
     *
     *appear with startReadElement in pair
     *
     */
    void stopReadElement(void);

    /*
     *judge whether the json string has a key named key name
     *
     *@iparam key name
     *
     *@oparam judge result
     *
     */
    bool hasKey(const string &key);


private:

    /*
     *class members
     */
    JsonParser *mpParser;
    JsonReader *mpReader;

};

}

#endif    //_CJSON_DECODER_HPP_
