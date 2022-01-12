#Includes
SFML = /home/mihai/Visual\ Studio\ Code/Git/Car_Rental/Car_Rental/Libraries/SFML-2.5.1/include
MYSQL = /home/mihai/Visual\ Studio\ Code/Git/Car_Rental/Car_Rental/Libraries/mysql-Linux/include
CURL = /home/mihai/Visual\ Studio\ Code/Git/Car_Rental/Car_Rental/Libraries/curl-Linux/include
JSON = /home/mihai/Visual\ Studio\ Code/Git/Car_Rental/Car_Rental/Libraries/Json

#WorkingDirectory
WORKINGDIR = /home/mihai/Visual\ Studio\ Code/Git/Car_Rental/Car_Rental/

#Libs
SFML_L = /home/mihai/Visual\ Studio\ Code/Git/Car_Rental/Car_Rental/Libraries/SFML-2.5.1/lib
MYSQL_L = /home/mihai/Visual\ Studio\ Code/Git/Car_Rental/Car_Rental/Libraries/mysql-Linux/lib
CURL_L = /home/mihai/Visual\ Studio\ Code/Git/Car_Rental/Car_Rental/Libraries/curl-Linux/lib

#Others
CC = g++
INCLUDES = -I$(MYSQL) -I$(CURL) -I$(JSON) -I$(SFML) -I$(WORKINGDIR)

build_and_run:
	make build
	make link
	make run

build:
	$(CC) -c *.cpp $(INCLUDES)

link:
	$(CC) *.o -o Car_Rental.exe -L$(MYSQL_L) -lsfml-graphics -lsfml-window -lsfml-system -lmysqlclient -lcurl

run:
	./Car_Rental.exe

clean:
	rm -f *.o
	rm -f Car_Rental.exe