#pragma once
#include "stdafx.h"
#include "IIOModule.h"

/**
 * This class is a handler for all serial modules
 * The IOHandler connects to a serial port
 * It uses the third-party library ASIO
 * It inherits the IIOModule interface an overwrites all virtual functions
 */

class CSerialHandler  : public IIOModule
{
public:

	/**
	 * Constructor used to initialize the ASIO serial socket with the io_context
	 * Sets Id and type for each instance
	 * Prints a summery for the created module
	 *
	 * @params - serial port and baudrate as connection infos for the serial port
	 */
	CSerialHandler(std::string port, int bauderate);
	~CSerialHandler();

	/**
	 * Stops thread and io_context. Closes serial port and clears listener table
	 * Sets state of module to "uninitialized"
	 */
	void stop();

	/**
	 * Initializes modul and tries to open serial port
	 * Runs ASIO io_context, opens serial port and sets baudrate
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
	std::string m_port;
	int m_baudrate;

	/**
	 * Writes message in parameter to it's serial port
	 * Whole Function is locked with mutex
	 * If a filter is active it is applied before writing to device
	 */
	void write(std::string message);

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

	//Buffer for ASIO async_read_some function
	std::vector<char> vBuffer;
	//Buffer for storing already read data
	std::vector <std::string> readBuffer;
	//ASIO context, used to perform ASIO functions
	asio::io_context m_context;
	//ASIO serial port, used to read from device
	asio::serial_port m_serial;
	//Thread to run m_context separatly from main thread
	std::thread m_thrContext;
};