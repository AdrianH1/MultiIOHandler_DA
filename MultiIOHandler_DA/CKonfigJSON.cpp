#include "CKonfigJSON.h"
#include "CClientSocketHandler.h"
#include "CServerSocketHandler.h"
#include "CFileHandler.h"
#include "CSerialHandler.h"

using json = nlohmann::json;

void CKonfigJSON::save(std::string path, std::vector<IIOModule*> &modules)
{
	std::vector<std::string> info;
	//json object to store all data in 
	std::ofstream file(path);
	if (file)
	{
		json json;
		std::cout << "Saving..." << std::endl;
		for (int i = 0; i < modules.size(); i++)
		{
			//Connection infos are different for each module type
			switch (modules.at(i)->getModuleType())
			{
			//Add alle infos recieved from getInfo() to the json object
			case IIOModule::tModule::clientSocket:
				info = modules.at(i)->getInfo();
				json["Module" + std::to_string(i)] = { {"id", stoi(info.at(0))}, {"type", stoi(info.at(1))}, {"ip", info.at(2)}, {"port", stoi(info.at(3))}};
				break;
			case IIOModule::tModule::serverSocket:
				info = modules.at(i)->getInfo();
				json["Module" + std::to_string(i)] = { {"id", stoi(info.at(0))}, {"type", stoi(info.at(1))}, {"ip", info.at(2)}, {"port", stoi(info.at(3))} };
				break;
			case IIOModule::tModule::file:
				info = modules.at(i)->getInfo();
				json["Module" + std::to_string(i)] = { {"id", stoi(info.at(0))}, {"type", stoi(info.at(1))}, {"path", info.at(2)} };
				break;
			case IIOModule::tModule::serial:
				info = modules.at(i)->getInfo();
				json["Module" + std::to_string(i)] = { {"id", stoi(info.at(0))}, {"type", stoi(info.at(1))}, {"port", info.at(2)}, {"baudrate", stoi(info.at(3))} };
			default:
				break;
			}
		}
		//Write json object to file
		file << std::setw(4) << json << std::endl;
		file.close();
		std::cout << "Saving finished!" << std::endl;
	}
	else
	{
		std::cout << "File not found!" << std::endl;
	}

}


void CKonfigJSON::load(std::string path, std::vector<IIOModule*>& modules)
{
	std::fstream file(path);
	//json object to load data into from file
	if (file)
	{
		json data = json::parse(file);
		std::cout << "Loading..." << std::endl;
		for (int i = 0; i < data.size(); i++)
		{
			//Connection infos are different for each module type
			//Read module type from json format and compare to enum module type
			if (data["Module" + std::to_string(i)]["type"] == IIOModule::tModule::serverSocket)
			{
				//Convert json data to needed type for module consturctor
				std::string ip = data["Module" + std::to_string(i)]["ip"].get<std::string>();
				int port = data["Module" + std::to_string(i)]["port"].get<int>();
				//Create module, initialize and add it to the modules list of the IOHandler 
				CServerSocketHandler* socket = new CServerSocketHandler(ip, port);
				socket->init();
				modules.push_back(socket);
			}
			else if (data["Module" + std::to_string(i)]["type"] == IIOModule::tModule::clientSocket)
			{
				//Convert json data to needed type for module consturctor
				std::string ip = data["Module" + std::to_string(i)]["ip"].get<std::string>();
				int port = data["Module" + std::to_string(i)]["port"].get<int>();
				//Create module, initialize and add it to the modules list of the IOHandler 
				CClientSocketHandler* socket = new CClientSocketHandler(ip, port);
				socket->init();
				modules.push_back(socket);
			}
			else if (data["Module" + std::to_string(i)]["type"] == IIOModule::tModule::file)
			{
				//Convert json data to needed type for module consturctor
				std::string path = data["Module" + std::to_string(i)]["path"].get<std::string>();
				//Create module, initialize and add it to the modules list of the IOHandler 
				CFileHandler* file = new CFileHandler(path);
				file->init();
				modules.push_back(file);
			}
			else if (data["Module" + std::to_string(i)]["type"] == IIOModule::tModule::serial)
			{
				//Convert json data to needed type for module consturctor
				std::string port = data["Module" + std::to_string(i)]["port"].get<std::string>();
				int baudrate = data["Module" + std::to_string(i)]["baudrate"].get<int>();
				//Create module, initialize and add it to the modules list of the IOHandler 
				CSerialHandler* serial = new CSerialHandler(port, baudrate);
				serial->init();
				modules.push_back(serial);
			}
		}
		std::cout << "Loading finished!" << std::endl;
	}
	else
	{
		std::cout << "File not found!" << std::endl;
	}
}
