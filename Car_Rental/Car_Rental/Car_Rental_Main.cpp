#include "DbConnection.h"

int main() {

	DbConnection dataBase("localhost","root","","car_rental",3306,NULL,0);
	dataBase.initConnection();


	
	/*
	MYSQL_RES* result;
	MYSQL_ROW row;
	int query_rez;
	query_rez = mysql_query(connection, "SELECT * FROM users");

	result = mysql_store_result(connection);

	while ((row = mysql_fetch_row(result)) != NULL) 
		cout << row[0] <<" "<<row[1]<<" "<<row[2]<<endl;

	//cout << result << "\n";
	*/

	system("pause");
	
	return EXIT_SUCCESS;
}