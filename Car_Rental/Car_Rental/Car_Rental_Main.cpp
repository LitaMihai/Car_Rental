#include "DbConnection.h"
#include "AccountUI.h"

/*
To do:
	-make an interface
	-implement the user accounts
	-implement the profile of an user
	-implement the profile of a dealership
	-implement much more...
*/

wxIMPLEMENT_APP(AccountUI);

int main() {

	DbConnection dataBase("localhost","root","","car_rental",3306,NULL,0);
	dataBase.initConnection();
	dataBase.closeConnection(dataBase.getConn());

	

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
