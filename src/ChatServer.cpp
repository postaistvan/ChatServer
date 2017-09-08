/*
 * ChatServer.cpp
 *
 *  Created on: Sep 1, 2017
 *      Author: istvan
 */

#include "ChatServer.h"
#include "Logger.h"
#include "userdb.h"
#include "JsonHandler.h"

std::string ChatServer::log_tag("ChatServer");

ChatServer::ChatServer() :
	server()
{
}

void ChatServer::run() {
//	server.createDummyClients();
	try {
		server.set_listening_port(1234);
		server.start_async();

		log_success("Server started");
		log_info("Press any key to close...");

		cin.get();

		log_success("Server closed");
	}
	catch (exception& e) {
		log_error(e.what());
	}
}

void ChatServer::log_info(const std::string& msg) {
	Logger::console_info(log_tag, msg);
}

void ChatServer::log_success(const std::string& msg) {
	Logger::console_success(log_tag, msg);
}

void ChatServer::log_warning(const std::string& msg) {
	Logger::console_warning(log_tag, msg);
}

void ChatServer::log_error(const std::string& msg) {
	Logger::console_error(log_tag, msg);
}

ChatServer::~ChatServer() {
	// TODO Auto-generated destructor stub
}

