/*
 * httpsClient.cpp
 *
 *  Purpose: to test using service ticket in Poco library
 *  Created on: Oct 21, 2016
 *      Author: saic
 */



#include <Poco/Net/Context.h>
#include <Poco/Net/Session.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/StreamCopier.h>
#include <iostream>
#include <sstream>
#include <string>


using namespace Poco::Net;
using namespace Poco;
using namespace std;

Context::Ptr g_context = NULL;
Session::Ptr g_sslsession = NULL;


const string CHECK_VERSION_URL = "https://avn-qa.ebanma.com:20016/app-avn/fota/3.0/checkVersion";
const string CONST_POST_DATA = "{\"token\":\"c71d1868b23465940a84263ef35ad35d\",\"timestamp\":1506768698,\"vin\":\"LS7H15111112222A3\",\"device_sn\":\" 0AP191577778888\",\"software_type\":1,\"hw_part_number\":\"1030763304\",\"hw_version\":\" 1.3.1.1.1\",\"mcu_version\":\"128.4.9.0\",\"app_version\":\"\",\"avn_platform\":\"BM01\",\"system_version\":\"v2.0.208\",\"backup_system_version\":\"v2.0.208\",\"emmc_version\":\"4.5.1\",\"space_list\":[{\"partition_name\":\"/data\",\"free_space\":1787654144},{\"partition_name\":\"/keyinfo\",\"free_space\":46915584},{\"partition_name\":\"/etc/machine-id\",\"free_space\":1787654144},{\"partition_name\":\"/cache\",\"free_space\":2071175168},{\"partition_name\":\"/private\",\"free_space\":6611783680},{\"partition_name\":\"/speech\",\"free_space\":1092497408},{\"partition_name\":\"/map\",\"free_space\":9712570368}]}";

void postAndReceiveData();

int main(int argc, char **argv)
{
    postAndReceiveData();

  return 0;
}


void postAndReceiveData()
{
    // Initialize data and url
    string urlStr = CHECK_VERSION_URL;
    printf("urlStr %s \n", urlStr.c_str());

    string sendata = CONST_POST_DATA;
    printf("sendata %s\n",sendata.c_str());

    Poco::URI url(urlStr);

    Poco::Net::Context* mCurContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE,
                                                              "",
                                                              "",
                                                              "/etc/ssl/certs/",
                                                              Poco::Net::Context::VERIFY_RELAXED, 9, true);
    mCurContext->enableSessionCache();

    // Create HTTPS client session
    Poco::Net::HTTPSClientSession *session = nullptr;
    session = new Poco::Net::HTTPSClientSession(mCurContext);

    session->setHost(url.getHost());
    session->setPort(url.getPort());

    // Compose request
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST,
                                  url.toString(), Poco::Net::HTTPMessage::HTTP_1_1);

    Poco::Net::HTMLForm form;
    form.setEncoding("application/x-www-form-urlencoded");
    form.add("data", sendata);
    form.prepareSubmit(request);

    printf("Session time out: %d\n", session->getTimeout().totalSeconds());
    try
    {
        ostream &os = session->sendRequest(request);
        form.write(os);
    }
    catch (exception e)
    {

        printf("Net work receive exception! code stringty:%s\n", e.what());

        delete session;
        return;
    }

    std::string result;

    // receive response
    Poco::Net::HTTPResponse response;
    istream &rs = session->receiveResponse(response);

    std::ostringstream oss;
    response.write(oss);

    printf("Received response length: %ld, \nContent: %s\n", oss.str().length(), oss.str().c_str());
    printf("Recieved response: %d %s\n", response.getStatus(), response.getReason().c_str());

    StreamCopier::copyToString(rs, result);

//    while (!rs.eof())
//    {
//        rs >> result;
//    }
    printf("Response content length: %ld\n", result.length());
    printf("Response content length: %s\n", result.c_str());

    delete session;
}



