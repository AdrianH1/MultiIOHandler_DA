#pragma once
#include "IIOModule.h"

/**
 * This class is a handler for all file modules.
 * The IOHandler reads/writes from a file.
 * It inherits the IIOModule interface an overwrites all virtual functions.
 */

class CFileHandler : public IIOModule
{
public:
	CFileHandler() = default;
	/**
	 * Constructor used to initialize the file path
	 * Sets Id and type for each instance
	 * Prints a summary for the created module
	 * 
	 * @params - Path to a file
	 */
	CFileHandler(std::string path);
	~CFileHandler();

	/**
	 * Stops thread and closes file access
	 * Sets state of module to "uninitialized"
	 */
	void stop();

	/**
	 * Initializes modul and checks if file exists and is accessible
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
	std::string m_path;
	std::fstream m_fs;
	//Boolean to activate reading task
	bool reading = true;

	/**
	 * Writes message in parameter to the file
	 * Whole Function is locked with mutex
	 * If a filter is active it is applied before writing to device
	 */
	void write(std::string message);

	/**
	 * Read data from file and forward to all listener in listenerTable
	 * Reading is done line by line in a one second intervall
	 */
	void read();

	/**
	 * Sets writeToListener boolean to true
	 * Read function will then forward all data to the listeners
	 */
	void connect();

	/**
	 * Function to collect modul information, used by json export
	 *
	 * @return - A string vector with modul information
	 */
	std::vector<std::string> getInfo();

	/**
	 * Print module information to console
	 */
	void printInfo();

	//Thread to run read funciton separatly from main thread
	std::thread m_thrRead;
};