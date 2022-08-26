#include "stdafx.h"
#include "CFileHandler.h"


CFileHandler::CFileHandler(std::string path)
    : m_Path(path)
{
    m_type = file;
    m_id = ++m_idCounter;
    std::cout << "Created File Module: " << std::endl;
    printInfo();
}

CFileHandler::~CFileHandler()
{
    stop();
}

//void CFileHandler::run()
//{
//
//}

void CFileHandler::stop()
{
    writeToListener = false;
    m_fs.close();
}

void CFileHandler::init()
{
    m_thrRead = std::thread([this]() {read(); });
}

void CFileHandler::write(std::string message)
{
    std::cout << "Writing to file" << std::endl;
    m_fs.open(m_Path, std::ios::app);
    m_fs << message << std::endl;
    m_fs.close();
}

void CFileHandler::read()
{
    m_fs.open(m_Path, std::ios::in);
    std::string message;
    while (true)
    {
        if (std::getline(m_fs, message))
        {
            if (outputToConsole)
            {
                std::cout << message << std::endl;
            }
            if (writeToListener)
            {
                for (IIOModule* m : listenerTable)
                {
                    m->write(message);
                }
            }
        }
        else
        {
            //Set file pointer to the start of the file
            m_fs.clear();
            m_fs.seekg(0);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    m_fs.close();
}

void CFileHandler::output()
{
    outputToConsole = true;
}

void CFileHandler::connect()
{
    //activate write to listener
    for (IIOModule* m : listenerTable)
    {
        writeToListener = true;
    }
}

std::vector<std::string> CFileHandler::getInfo()
{
    std::vector<std::string> info;
    info.push_back(std::to_string(m_id));
    info.push_back(std::to_string(m_type));
    info.push_back(m_Path);
    return info;
}

int CFileHandler::getId()
{
    return m_id;
}


void CFileHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | Path: " << m_Path << std::endl;
}