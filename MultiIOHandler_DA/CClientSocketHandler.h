#pragma once

#include "stdafx.h"
#include "IIOModule.h"

/**
 * This class is a handler for all client socket modules
 * The IOHandler acts as a client to connect to a server listening on a IP/Port
 * It uses the third-party library ASIO
 * It inherits the IIOModule interface an overwrites all virtual functions
 */

class CClientSocketHandler : public IIOModule
{
public:
	CClientSocketHandler() = default;
	/**
	 * Constructor used to initialize the ASIO socket with the io_context
	 * Sets Id and type for each instance
	 * Prints a summery for the created module
	 * 
	 * @params - IP and Port as connection infos for the socket
	 */
	CClientSocketHandler(std::string ip, int unsigned port);
	~CClientSocketHandler();

	/**
	 * Stops thread and io_context. Closes socket and clears listener table
	 * Sets state of module to "uninitialized"
	 */
	void stop();

	/**
	 * Initializes modul and tries to establish a connection to backend device
	 * Runs ASIO io_context and creates an ASIO endpoint with the given IP/Port
	 * Runs read() function if connection is successfull. Otherwise shows error.
	 */
	void init();

	/**
	 * Writes all data in readBuffer to console
	 * Sets WriteToListener bool to true
	 */
	void output();

private:
	//Member variable for connection information
	std::string m_ip;
	int unsigned m_port;


	/**
	 * Writes message in parameter to it's backend device
	 * Whole Function is locked with mutex
	 * If a filter is active it is applied before writing to device
	 */
	void write(std::vector<char> message);

	/**
	 * Function to collect modul information, user by json export
	 * 
	 * @return - A string vector with modul information
	 */
	std::vector<std::string> getInfo();

	/**
	 * Print module information to console
	 */
	void printInfo();

	/**
	 * Read data from device to a buffer and forward to all listener in listenerTable
	 * Reading is done asynchronously with ASIO async_read_some function
	 */
	void read();

	/**
	 * Sets writeToListener boolean to true
	 * Read function will then forward all data to the listeners
	 */
	void connect();

	//Buffer for ASIO async_read_some function
	std::vector<char> vBuffer;
	//Buffer for storing already read data
	std::vector<std::vector<char>> readBuffer;
	//ASIO context, used to perform ASIO functions
	asio::io_context m_context;
	//ASIO socket, used to read from device
	asio::ip::tcp::socket m_socket;
	//Thread to run m_context separatly from main thread
	std::thread m_thrContext;

	
};
