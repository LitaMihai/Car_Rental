#Includes
SFML = ./Libraries/SFML-2.5.1/include/
MYSQL = ./Libraries/mysql-Linux/include
CURL = ./Libraries/curl-Linux/include
JSON = ./Libraries/Json/

#WorkingDirectory
WORKINGDIR = ./

#Libs
SFML_L = ./Libraries/SFML-2.5.1/lib
MYSQL_L = ./Libraries/mysql-Linux/lib
CURL_L = ./Libraries/curl-Linux/lib

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