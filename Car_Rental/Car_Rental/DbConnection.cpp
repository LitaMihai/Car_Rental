#include "DbConnection.h"

DbConnection::DbConnection(const char* host, const char* user, const char* pass, const char* db, int port, char* sck, int flags)
{
	this->host = host;
	this->user = user;
	this->pass = pass;
	this->db = db;
	this->port = port;
	this->sck = sck;
	this->flags = flags;
	this->conn = nullptr;
	this->connection = nullptr;
}

DbConnection::~DbConnection()
{
	mysql_close(conn);
}

void DbConnection::initConnection()
{
	std::string stats;
	conn = mysql_init(NULL);
	if (conn == NULL) {
		std::cout << "Error!!\n";
		exit(1);
	}
	connection = mysql_real_connect(conn, host, user, pass, db, port, sck, flags);
	if (connection == NULL)
		stats = "Connection MYSQL None Exist";
	else
		stats = "MYSQL Connected";
	std::cout << "Status: " << stats << "\n\n";
}
