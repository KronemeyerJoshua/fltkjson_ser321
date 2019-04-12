#ifndef MessageServer_H
#define MessageServer_H

#include "abstractstubserver.h"
#include "Message.hpp"
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <vector>

using namespace jsonrpc;
using namespace std;

class MessageServer : public AbstractStubServer {
public:
	Message msg;
	MessageServer(AbstractServerConnector &connector, int port);
	virtual Json::Value getMessageFromHeaders();
	virtual Json::Value getMessage(const std::string& param1);
	virtual bool deleteMessage(const std::string& param1);
	virtual bool sendMessage(const Json::Value& msgDetails, const std::string& header);
	virtual bool login(const std::string& userId);
};
#endif