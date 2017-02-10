/*
 * httpsClient.cpp
 *
 *  Purpose: to test using service ticket saved locally in Poco library
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
#include <fstream>
#include <string>
#include <cstdio>



using namespace Poco::Net;
using namespace Poco;
using namespace std;

Context::Ptr g_context = NULL;

const char* const SESSION_FILE = "/tmp/sslSession";

bool saveSessionTicket(SSL_SESSION* session, const char* path)
{
    bool result = false;
    ofstream file(path, ios::out | ios::binary);

    if (file.is_open())
    {
        file.write((const char*)session, sizeof(SSL_SESSION));

        file.close();
        result = true;

        cout << "Write " << sizeof(SSL_SESSION) << " bytes to file"<< endl;
    }

    return result;
}

bool readSessionTicket(SSL_SESSION* session, const char* path)
{
    bool result = false;
    ifstream file(path, ios::in | ios::binary);

    if (file.is_open())
    {
        // get size of file
        file.seekg (0, file.end);
        long size = file.tellg();
        file.seekg (0);

        cout << "Read session ticket file size: " << size << endl;

        unsigned char* buffer = new unsigned char[size];
        file.read((char*)buffer, size);
        memcpy(session, buffer, size);

        file.close();
        result = true;
    }

    return result;
}

void printSessionTicket(SSL_SESSION& session)
{
    cout << session.ssl_version;
    cout << session.key_arg_length;
    cout <<

}


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

            // Read from file to get existing SSL_SESSION
            SSL_SESSION realSession;
            if (readSessionTicket(&realSession, SESSION_FILE))
            {
                cout << "Use existing ssl session" << endl;
                Session* ssl_session = new Session(&realSession);
                session = new HTTPSClientSession(g_context, Session::Ptr(ssl_session)); // Change: Reuse existing SSL session
            }
            else
            {
                cout << "Create new ssl session" << endl;
                session = new HTTPSClientSession(g_context);
            }

            session->setHost(uri.getHost());
            session->setPort(uri.getPort());

            HTTPRequest req(HTTPRequest::HTTP_POST, uri.toString(), HTTPMessage::HTTP_1_1);
            session->sendRequest(req);

            // Change: get SSL session and store for future use
            realSession = *(session->sslSession()->sslSession());
            saveSessionTicket(&realSession, SESSION_FILE);
            cout << "Get ssl session from current HTTPS session. Session id: " << endl;

            cout << std::hex;
            for (int i = 0; i < realSession.session_id_length; i++)
            {
                printf("%02x ", (int)realSession.session_id[i]);

                if ((i+1)%8 == 0)
                {
                    cout << endl;
                }
            }

            cout << endl;

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



