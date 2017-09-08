/*
 * ClientHandler.cpp
 *
 *  Created on: Sep 1, 2017
 *      Author: istvan
 */

#include <thread>

#include "ClientHandler.h"
#include "Logger.h"
#include "userdb.h"

using namespace std;

std::string ClientHandler::log_tag("ClientHandler");

ClientHandler::ClientHandler(	std::istream& 		in,
								std::ostream& 		out,
								const std::string& 	foreign_ip,
								const std::string& 	local_ip,
								unsigned short 		foreign_port,
								unsigned short 		local_port,
								uint64_t 			connection_id):
	in(in),
	out(out),
	foreign_ip(foreign_ip),
	local_ip(local_ip),
	foreign_port(foreign_port),
	local_port(local_port),
	connection_id(connection_id),
	username(),
	user_id(0)
{
}

void ClientHandler::serve() {
	log_success("Client connected");
	log_info("Connection ID: " 		+ std::to_string(connection_id)
			+ "\nForeign IP: " 		+ foreign_ip
			+ "\nForeign port: " 	+ std::to_string(foreign_port)
			+ "\nLocal IP: " 		+ local_ip
			+ "\nLocal port: " 		+ std::to_string(local_port)
	);

	connection_handshake();
	start_receiver();
}

void ClientHandler::set_username(std::string username) {
	this->username = username;
}

void ClientHandler::set_user_id(uint64_t user_id) {
	this->user_id = user_id;
}

bool ClientHandler::connection_handshake() {
	std::string client_login_msg;
	std::string username;
	std::string password;

	in >> client_login_msg;

	json_handler.construct_json(client_login_msg);
	username = json_handler.get_element_value("username");
	password = json_handler.get_element_value("password");

	json_handler.clear();
	json_handler.add_element("type", "login");
	json_handler.add_element("result", "valid");

	out << json_handler.get_json_string() << endl;

	log_info("Client login:\n\tUsername: " + username + "\n\tPassword: " + password);

	return true;
}

void ClientHandler::receiver() {
	std::string msg;

	std::istream _in = std::move(in)
	while (true) {
		in >> msg;

		json_handler.clear();
		json_handler.construct_json(msg);

		cout << '[' << username << "] " << json_handler.get_element_value("text") << endl;
	}
}

void ClientHandler::start_receiver() {
	std::thread t(&ClientHandler::receiver, this);
	t.detach();
}

ClientHandler::~ClientHandler() {
	// TODO Auto-generated destructor stub
	cout << "~ClientHandler: " << connection_id << endl;
}

void ClientHandler::log_info(const std::string& msg) {
	Logger::console_info(log_tag, msg);
}

void ClientHandler::log_success(const std::string& msg) {
	Logger::console_success(log_tag, msg);
}

void ClientHandler::log_warning(const std::string& msg) {
	Logger::console_warning(log_tag, msg);
}

void ClientHandler::log_error(const std::string& msg) {
	Logger::console_error(log_tag, msg);
}

const std::string& ClientHandler::get_username() const {
	return username;
}

const uint64_t& ClientHandler::get_user_id() const {
	return user_id;
}
