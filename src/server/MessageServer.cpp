#include "abstractstubserver.h"
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <iostream>
#include "Message.cpp"
#include "MessageServer.hpp"
using namespace jsonrpc;
using namespace std;

MessageServer::MessageServer(AbstractServerConnector &connector, int port) : AbstractStubServer(connector), msg() {
}

bool MessageServer::login(const std::string& userId) {
	msg.setUser(userId);
	return true;
}

Json::Value MessageServer::getMessageFromHeaders() {
	std::cout << "User has requested headers" << std::endl;
	return msg.getMessageFromHeaders();
}

Json::Value MessageServer::getMessage(const std::string& header) {
	std::cout << "User has requested message for header " << header << std::endl;
	return msg.getMessage(header);
}

bool MessageServer::deleteMessage(const std::string& header) {
	std::cout << "User has requested to delete messsage " << header << std::endl;
	return msg.deleteMessage(header);
}
bool MessageServer::sendMessage(const Json::Value& msgDetails, const std::string& header) {
	std::cout << "User has requested to send message with header " << header << std::endl;
	return msg.sendMessage(msgDetails, header);
}

int main(int argc, char* argv[]) {
	int port = 8081;
	if (argc > 0) {
		port = atoi(argv[1]);
	}
	HttpServer httpserver(port);
	MessageServer serv(httpserver, port);
	serv.StartListening();
	while (cin.get() != '\n') {};
	serv.StopListening();

	return 0;

}