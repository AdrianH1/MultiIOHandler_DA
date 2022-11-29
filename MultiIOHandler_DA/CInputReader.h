#include "stdafx.h"

/**
 * Valid commands, module types and parameter used for validation
 */
static const std::vector<std::string> openCmd = { "open" };
static const std::string typeParam = "type";
static const std::vector<std::string> moduleTypes = { "clientsocket", "serversocket", "clientsocketudp", "serversocketudp", "file", "serial", "multicast" };
static const std::vector<std::string> socketParam = {"ip", "port"};
static const std::vector<std::string> fileParam = {"path"};
static const std::vector<std::string> serialParam = {"speed", "datab", "stopb", "parity", "flow"};
static const std::vector<std::string> multicastParam = {"ip", "port", "multicast"};
static const std::unordered_map <std::string, std::vector<std::string>> typeToParamsMap = {
	{"clientsocket", socketParam},
	{"serversocket", socketParam},
	{"clientsocketudp", socketParam},
	{"serversocketudp", socketParam},
	{"file", fileParam},
	{"serial", serialParam},
	{"multicast", multicastParam}
};

static const std::vector<std::string> connectCmd = { "connect" };
static const std::vector<std::string> connectParam = { "sendModule", "recvModul" };

static const std::vector<std::string> moduleCmd = {"init", "output", "input", "stop", "remove", "filter" };
static const std::vector<std::string> moduleParam = { "id" };

static const std::vector<std::string> jsonCmd = { "save", "load" };
static const std::vector<std::string> jsonCmd = { "path"};

static const std::vector<std::string> otherCmd = { "show", "help", "exit" };

class CInputReader
{
public:
	CInputReader() = default;

	/**
	 * Reads a complete line of user input and validates it
	 * Separates the line by space and stores them in a vector
	 *
	 * @return - A string vector of every input separated by a space
	 */
	std::vector<std::string> readInput();

private:

	bool inputValid(std::vector<std::string>* input);

	bool isCmdValid(std::string* cmd);

	bool isTypeValid(std::string* type);

	std::vector<std::string> setCmdParameter(std::vector<std::string>* input);

	/**
	 * Separates a line of input by space for further usage
	 *
	 * @params - Whole line of input as one string
	 * @return - A string vector with the separated string given in the parameters
	 */
	std::vector<std::string> separateInput(std::string* inputLine);
	std::unordered_map<std::string, std::string> mapInputToParam(std::vector<std::string>* input);

	/**
	 * Check if a string is an integer
	 */
	bool isInteger(const std::string s);

	/**
	 * Converts all input into lowercase to support lower and uppercase user input
	 */
	std::string lowerCase(std::string inputline);

	/**
	 * Function to output an error.
	 * This is used so that all error outputs look the same.
	 */
	void displayError(std::string ec);

	/**
	 * Displays the full help text in the console
	 */
	void displayHelp();

};