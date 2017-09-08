/*
 * userdb.h
 *
 *  Created on: Sep 5, 2017
 *      Author: istvan
 */

#ifndef USERDB_H_
#define USERDB_H_

#include <string>

namespace userdb {
	bool existing_user(std::string username, std::string password);
	void print_users();
}

#endif /* USERDB_H_ */
