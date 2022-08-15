#include "CJSONHandler.h"

using json = nlohmann::json;

void CJSONHandler::test()
{
	json jsonFile;
	std::ofstream file("C:\\Users\\Adrian\\source\\repos\\AdrianH1\\key.json");

	int id = 12;
	std::string type = "socket";
	std::string ip = "192.168.1.1";
	int unsigned port = 65123;

	jsonFile["Module1"] = { {"ID", id}, {"type", type}, {"ip", ip}, {"port", port} };

	id = 13;
	type = "socket";
	ip = "193.168.1.1";
	port = 65133;

	jsonFile["Module2"]["ID"] = id;
	jsonFile["Module2"]["type"] = type;
	jsonFile["Module2"]["ip"] = ip;
	jsonFile["Module2"]["port"] = port;

	file << std::setw(4) << jsonFile << std::endl;

	file.close();

	std::cout << "writing done" << std::endl;

	try
	{
		std::fstream f("C:\\Users\\Adrian\\source\\repos\\AdrianH1\\key.json");
		json data = json::parse(f);
		std::cout << data;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}

	std::cout << "reading done" << std::endl;
}
