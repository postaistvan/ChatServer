/*
 * ServerService.h
 *
 *  Created on: Sep 1, 2017
 *      Author: istvan
 */

#ifndef SERVERSERVICE_H_
#define SERVERSERVICE_H_

#include <dlib/server.h>
#include <vector>
#include "ClientHandler.h"

typedef std::shared_ptr< ClientHandler > Client;
typedef std::vector< Client > Clients;

class ServerService : public dlib::server_iostream {

private:
	Clients clients;

	static std::string log_tag;

public:
	ServerService();

	void on_connect(std::istream& 		in,
					std::ostream& 		out,
					const std::string& 	foreign_ip,
					const std::string& 	local_ip,
					unsigned short 		foreign_port,
					unsigned short 		local_port,
					dlib::uint64	 	connection_id);

	void createDummyClients();

	void log_info(const std::string& msg);
	void log_success(const std::string& msg);
	void log_warning(const std::string& msg);
	void log_error(const std::string& msg);

	virtual ~ServerService();
};

#endif /* SERVERSERVICE_H_ */
