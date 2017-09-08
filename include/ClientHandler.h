/*
 * ClientHandler.h
 *
 *  Created on: Sep 1, 2017
 *      Author: istvan
 */

#ifndef CLIENTHANDLER_H_
#define CLIENTHANDLER_H_

#include <iostream>
#include <dlib/server.h>
#include "JsonHandler.h"

class ClientHandler {

private:
	std::istream& 		in;
	std::ostream& 		out;
	std::string 		foreign_ip;
	std::string 		local_ip;
	unsigned short 		foreign_port;
	unsigned short 		local_port;
	dlib::uint64	 	connection_id;

	std::string			username;
	uint64_t			user_id;

	JsonHandler			json_handler;

	static std::string log_tag;

	void receiver();

public:
	ClientHandler(	std::istream& 		in,
					std::ostream& 		out,
					const std::string& 	foreign_ip,
					const std::string& 	local_ip,
					unsigned short 		foreign_port,
					unsigned short 		local_port,
					uint64_t 			connection_id);

//	ClientHandler();

	void serve();

	const std::string& 	get_username() const;
	const uint64_t&		get_user_id() const;

	void set_username(std::string username);
	void set_user_id(uint64_t user_id);

	bool connection_handshake();

	void start_receiver();

	void log_info(const std::string& msg);
	void log_success(const std::string& msg);
	void log_warning(const std::string& msg);
	void log_error(const std::string& msg);

	~ClientHandler();
};

#endif /* CLIENTHANDLER_H_ */
