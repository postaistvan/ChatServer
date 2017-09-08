/*
 * ChatServer.h
 *
 *  Created on: Sep 1, 2017
 *      Author: istvan
 */

#ifndef CHATSERVER_H_
#define CHATSERVER_H_

#include "ServerService.h"

class ChatServer {

private:
	ServerService server;

	static std::string log_tag;

public:
	ChatServer();

	void run();

	void log_info(const std::string& msg);
	void log_success(const std::string& msg);
	void log_warning(const std::string& msg);
	void log_error(const std::string& msg);

	virtual ~ChatServer();
};

#endif /* CHATSERVER_H_ */
