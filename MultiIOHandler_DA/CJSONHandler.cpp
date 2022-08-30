#include "CJSONHandler.h"
#include "CClientSocketHandler.h"
#include "CFileHandler.h"

using json = nlohmann::json;

void CJSONHandler::save(std::string path, std::vector<IIOModule*> &modules)
{
	std::vector<std::string> info;
	json json;
	std::ofstream file(path);
	for (int i = 0; i < modules.size(); i++)
	{
		switch (modules.at(i)->m_type)
		{
		case IIOModule::type::clientSocket:
			info = modules.at(i)->getInfo();
			json["Module" + std::to_string(i)] = { {"id", stoi(info.at(0))}, {"type", stoi(info.at(1))}, {"ip", info.at(2)}, {"port", stoi(info.at(3))}};
			break;
		case IIOModule::type::serverSocket:
			info = modules.at(i)->getInfo();
			json["Module" + std::to_string(i)] = { {"id", stoi(info.at(0))}, {"type", stoi(info.at(1))}, {"ip", info.at(2)}, {"port", stoi(info.at(3))} };
			break;
		case IIOModule::type::file:
			info = modules.at(i)->getInfo();
			json["Module" + std::to_string(i)] = { {"id", stoi(info.at(0))}, {"type", stoi(info.at(1))}, {"path", info.at(2)} };
			break;
		case IIOModule::type::serial:
		default:
			break;
		}
	}
	file << std::setw(4) << json << std::endl;
	file.close();
}


void CJSONHandler::load(std::string path, std::vector<IIOModule*>& modules)
{
	std::cout << "Loading..." << std::endl;
	std::fstream f(path);
	json data = json::parse(f);
	for (int i = 0; i < data.size(); i++)
	{
		if (data["Module" + std::to_string(i)]["type"] == IIOModule::type::serverSocket)
		{

		}
		else if (data["Module" + std::to_string(i)]["type"] == IIOModule::type::clientSocket)
		{
			std::string ip = data["Module" + std::to_string(i)]["ip"].get<std::string>();
			int port = data["Module" + std::to_string(i)]["port"].get<int>();
			CClientSocketHandler* socket = new CClientSocketHandler(ip, port);
			socket->init();
			modules.push_back(socket);
		}
		else if (data["Module" + std::to_string(i)]["type"] == IIOModule::type::file)
		{
			std::string path = data["Module" + std::to_string(i)]["path"].get<std::string>();
			CFileHandler* file = new CFileHandler(path);
			file->init();
			modules.push_back(file);
		}
		else if (data["Module" + std::to_string(i)]["type"] == IIOModule::type::serial)
		{

		}
	}
	std::cout << "Loading finished!" << std::endl;
}
