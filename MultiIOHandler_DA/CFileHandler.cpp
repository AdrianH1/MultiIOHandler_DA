#include "stdafx.h"
#include "CFileHandler.h"


CFileHandler::CFileHandler(std::string path)
    : m_Path(path)
{
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
    //open file

    //m_fs.open(m_Path, std::ios::out | std::ios::in);

    //char data[100];

    //std::cout << "write to file: " << std::endl;
    //std::cin.getline(data, 100);
    //m_fs << data << std::endl;
    
    //std::cout << "read from file" << std::endl;
    //m_fs >> data;
    //std::cout << data << std::endl; 
    
    //m_fs.close();
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
    while (writeToListener && std::getline(m_fs, message))
    {
        for (IIOModule* m : listenerTable)
        {
            m->write(message);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    m_fs.close();
}

void CFileHandler::output()
{
    m_fs.open(m_Path, std::ios::in);
    std::string line;
    std::cout << "read from file" << std::endl;
    while (std::getline(m_fs, line))
    {
        std::cout << line << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    m_fs.close();
}

void CFileHandler::connect()
{
    //activate write to listener
    for (IIOModule* m : listenerTable)
    {
        writeToListener = true;
    }
    m_thrRead = std::thread([this]() {read(); });
}

int CFileHandler::getId()
{
    return m_id;
}


void CFileHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | Path: " << m_Path << std::endl;
}