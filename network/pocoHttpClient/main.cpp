/*
 * main.cpp
 *
 *  Created on: Jan 1, 2018
 *      Author: knowyou
 */

#include <Poco/Net/Context.h>
#include <Poco/Net/Session.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "getTime.h"

using namespace Poco::Net;
using namespace Poco;
using namespace std;

//const char* URL = "http://pocoproject.org/images/front_banner.jpg";
const char* URL = "http://127.0.0.1:9090";

bool doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response)
{
    session.sendRequest(request);
    std::istream& rs = session.receiveResponse(response);
    std::cout << response.getStatus() << " " << response.getReason() << std::endl;
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
    {
        std::ofstream ofs("Poco_banner.jpg",std::fstream::binary);
        StreamCopier::copyStream(rs, ofs);
        return true;
    }
    else
    {
        //it went wrong ?
        return false;
    }
}


int main()
{
    URI uri(URL);
    std::string path(uri.getPathAndQuery());
    if (path.empty()) path = "/";

    HTTPClientSession session(uri.getHost(), uri.getPort());
    HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    HTTPResponse response;

    printCurrentTime();

    try
    {
        if (!doRequest(session, request, response))
        {
            std::cerr << "Invalid username or password" << std::endl;
            return 1;
        }
    }
    catch (Poco::TimeoutException e)
    {
        printf("Network receive exception! code:%s\n", e.what());
    }
    catch (exception e)
    {
        printf("Net work receive exception! code stringty:%s\n", e.what());
    }

    printCurrentTime();
    return 0;

}
