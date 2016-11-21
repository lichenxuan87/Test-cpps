/*
 * clientMain.cpp
 *
 *  Created on: Sep 29, 2016
 *      Author: saic
 */


#include <dbus/DMessage.h>
#include <dbus/DProxy.h>
#include <iostream>

#include "DbusClientExample.h"

using namespace yunos;
using namespace std;

void handleTestMethodCallReply(void* data, const SharedPtr<DMessage>& msg)
{

//    SharedPtr<DProxy>* proxy = static_cast<SharedPtr<DProxy>*>(data);
//
//    cout << "Test method call returned from: service: "<< (*proxy)->service()
//            << endl << "objectPath: " << (*proxy)->objectPath()
//            << endl << "interface: " << (*proxy)->interface()
//            << endl;
//    delete proxy;

    /* Message type:
     * enum {
     *     MESSAGE_TYPE_INVALID = 0, MESSAGE_TYPE_METHOD_CALL, MESSAGE_TYPE_METHOD_RETURN, MESSAGE_TYPE_ERROR,
     *     MESSAGE_TYPE_SIGNAL
     * }
     */
    if (msg->getReplyType() == DMessage::MESSAGE_TYPE_METHOD_RETURN)
    {
        int a = msg->readInt32();
        cout << "reply: " << a << endl;
    }
    else if (msg->getReplyType() == DMessage::MESSAGE_TYPE_ERROR)
    {
        cout << "Reply erorr: error type: " << msg->getReplyErrorType()
             << endl << "error name: " << msg->getReplyError() << endl;
    }
}

void testSendMessage(DbusClientExample& example)
{
    // Send a message, note: this message can only be used once.
    SharedPtr<DMessage> msg = example.getProxy()->obtainMethodCallMessage(String("FireInTheHole"));
    msg->writeInt32(666);


    // Send message without reply
    if (example.getProxy()->sendMessage(msg))
    {
        cout << "Send message without reply success" << endl;
    }
    else
    {
        cout << "Send message failed" << endl;
    }

    // Recommended: Send message with reply
    msg = example.getProxy()->obtainMethodCallMessage(String("FireInTheHole"));
    msg->writeInt32(777);

    if (example.getProxy()->sendMessageWithReply(msg,
            ReplyHandler(handleTestMethodCallReply, new SharedPtr<DProxy>(example.getProxy())),
            5000))
    {
        cout << "Send message with reply success" << endl;
    }
    else
    {
        cout << "Send message failed" << endl;
    }

    // Send message with reply block (synchronized method call)
    // WARNING: this is not recommended in yunos 4.0
    msg = example.getProxy()->obtainMethodCallMessage(String("FireInTheHole"));
    msg->writeInt32(888);

    DError error;
    SharedPtr<DMessage> reply = example.getProxy()->sendMessageWithReplyBlocking(msg, 5000, &error);

    if (error.type() == DError::BUS_ERROR_NO_ERROR)
    {
        cout << "Send message with reply blocking success: reply: " << reply->readInt32() << endl;
    }
    else
    {
        cout << "Send message failed: error type: " << error.type()
             << endl << "error name: " << error.name()
             << endl << "error message: " << error.message() << endl;
    }


    // Send an unsupported message to server
    msg = example.getProxy()->obtainMethodCallMessage(String("WTF"));
    msg->writeInt32(999);

    if (example.getProxy()->sendMessageWithReply(msg,
            ReplyHandler(handleTestMethodCallReply, new SharedPtr<DProxy>(example.getProxy())),
            5000))
    {
        cout << "Send message with reply success" << endl;
    }
    else
    {
        cout << "Send message failed" << endl;
    }

}

int main()
{
    DbusClientExample example;

    if (!example.init())
    {
        cout << "Initialization failed" << endl;
        return 1;
    }

    testSendMessage(example);


    // Run a loop in DProxy
    example.run();

    return 0;
}

