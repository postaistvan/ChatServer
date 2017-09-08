/*
 * userdb.cpp
 *
 *  Created on: Sep 5, 2017
 *      Author: istvan
 */

#include "ServerConfig.h"
#include "userdb.h"
#include "pugixml/pugixml.hpp"
#include "Logger.h"

#include <iostream>
#include <vector>

namespace userdb {

	/**
	 * users.xml node and attribute names
	 */

	const char* node_users 	= "users";
	const char* attr_user	= "username";
	const char* attr_pass 	= "password";

	/**
	 * Tag for logging on the console
	 */

	const std::string log_tag = "userdb";

	/**
	 * Typedefs
	 */

	typedef struct {
		std::string username;
		std::string password;
	} User;

	typedef std::vector<User> Users;

	/**
	 * Fields used by the userdb
	 */

	pugi::xml_document 		doc;
	pugi::xml_parse_result	result;

	bool 		db_loaded = false;
	Users		users;
	std::string users_xml(USERS_DB_XML_FILE);

	/**
	 * Methods
	 */

	void log_info(const std::string& msg) {
		Logger::console_info(log_tag, msg);
	}

	void log_success(const std::string& msg) {
		Logger::console_success(log_tag, msg);
	}

	void log_warning(const std::string& msg) {
		Logger::console_warning(log_tag, msg);
	}

	void log_error(const std::string& msg) {
		Logger::console_error(log_tag, msg);
	}

	bool load_xml() {
		result = doc.load_file(users_xml.c_str());
		if (result.status != pugi::status_ok) return false;

		users.clear();

		pugi::xml_node users_node = doc.child(node_users);

		for (pugi::xml_node user_node : users_node.children()) {
			User user;

			user.username = user_node.attribute(attr_user).value();
			user.password = user_node.attribute(attr_pass).value();

			users.push_back(user);
		}

		return true;
	}

	bool init_db() {
		db_loaded = load_xml();

		if (db_loaded) 	log_success(users_xml + " loaded successfully");
		else 			log_error("Couldn't load " + users_xml);

		return db_loaded;
	}

	bool existing_user(std::string username, std::string password) {
		if (!db_loaded) init_db();

		for (User user : users) {
			if (user.username == username && user.password == password) return true;
		}

		return false;
	}

	void print_users() {
		if (!db_loaded) init_db();

		for (User user : users) {
			log_info("username: " + user.username + " password: " + user.password);
		}
	}
}
