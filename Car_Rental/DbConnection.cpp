#include "DbConnection.h"

//Constructor
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

//Functions
void DbConnection::initConnection()
{
	std::string stats;
	this->conn = mysql_init(NULL);
	if (this->conn == NULL) {
		std::cout << "Error!!\n";
		exit(1);
	}
	this->connection = mysql_real_connect(conn, host, user, pass, db, port, sck, flags);
	if (this->connection == NULL)
		stats = "Connection Failed";
	else
		stats = "MYSQL Connected";
	std::cout << "Status: " << stats << "\n\n";
}

void DbConnection::closeConnection(MYSQL* conn)
{
	mysql_close(conn);
}

MYSQL* DbConnection::getConn()
{
	return this->conn;
}
