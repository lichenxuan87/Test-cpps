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
#include <string>


using namespace Poco::Net;
using namespace Poco;
using namespace std;

Context::Ptr g_context = NULL;
Session::Ptr g_sslsession = NULL;

int main(int argc, char **argv)
{


    if (argc != 2)
    {
    cout << "Usage: " << argv[0] << " <uri>" << endl;
    cout << "       fetches the resource identified by <uri> and print it" << endl;
    return -1;
    }

    // prepare session
    URI uri(argv[1]);


    for (int i = 0; i < 5; i++)
    {
        try
        {
            // send request
            if (g_context == (Context*) NULL)
            {
                cout << "No existing context, create a new one!" << endl;
                g_context = new Context(
                        Context::CLIENT_USE,
                        "",
                        "",
                        "/etc/ssl/certs", // Change: set root CA path
                        Poco::Net::Context::VERIFY_RELAXED, // Change: verify certificate
                        9,
                        true
                       );
                g_context->enableSessionCache();
            }

            cout << "Send request to " << uri.toString() << endl;


            HTTPSClientSession* session = NULL;
            if (g_sslsession == (Session*) NULL)
            {
                cout << "Create new ssl session" << endl;
                session = new HTTPSClientSession(g_context);
            }
            else
            {
                cout << "Use existing ssl session" << endl;
                session = new HTTPSClientSession(g_context, g_sslsession); // Change: Reuse existing SSL session
            }

            session->setHost(uri.getHost());
            session->setPort(uri.getPort());

            HTTPRequest req(HTTPRequest::HTTP_POST, uri.toString(), HTTPMessage::HTTP_1_1);
            session->sendRequest(req);

            if (g_sslsession == (Session*)NULL)
            {
                g_sslsession = session->sslSession(); // Change: get SSL session and store for future use
                cout << "Get ssl session from current HTTPS session" << endl;
            }

            // get response
            HTTPResponse res;

            // print response
            istream &is = session->receiveResponse(res);
            string json_str;
            is >> json_str;

            cout << res.getStatus() << " " << res.getReason() << endl;
            cout << "Response size: " << json_str.length() << endl;

            sleep(5);
        }
        catch (Exception e)
        {
            cout << e.displayText() << endl;
        }
    }
    cout << "Exit main function " << endl;

  return 0;
}



