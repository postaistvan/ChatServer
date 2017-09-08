/*
 * ServerService.cpp
 *
 *  Created on: Sep 1, 2017
 *      Author: istvan
 */

#include "ServerService.h"
#include "Logger.h"
#include <memory>

using namespace std;

std::string ServerService::log_tag("ServerService");

ServerService::ServerService() {
	// TODO Auto-generated constructor stub

}

void ServerService::on_connect(	std::istream& in,
								std::ostream& out,
								const std::string& foreign_ip,
								const std::string& local_ip,
								unsigned short foreign_port,
								unsigned short local_port,
								dlib::uint64 connection_id)
{
	Client cl(new ClientHandler(in, out, foreign_ip, local_ip, foreign_port, local_port, connection_id));
	cl->serve();

	clients.push_back(cl);
}

void ServerService::createDummyClients() {
//	for (int i = 0; i < 5; i++) {
//		ClientHandler cl;
//		cl.set_user_id(i);
//
//		clients.push_back(cl);
//	}
//
//	for (Clients::iterator it = clients.begin(); it != clients.end(); it++) {
//		ClientHandler cl = *it;
//
//		cout << cl.get_user_id() << endl;
//		clients.erase(it);
//	}
}

void ServerService::log_info(const std::string& msg) {
	Logger::console_info(log_tag, msg);
}

void ServerService::log_success(const std::string& msg) {
	Logger::console_success(log_tag, msg);
}

void ServerService::log_warning(const std::string& msg) {
	Logger::console_warning(log_tag, msg);
}

void ServerService::log_error(const std::string& msg) {
	Logger::console_error(log_tag, msg);
}

ServerService::~ServerService() {
	// TODO Auto-generated destructor stub
}

