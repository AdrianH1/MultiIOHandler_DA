#include "stdafx.h"
#include "CFileHandler.h"


CFileHandler::CFileHandler(std::string path)
    : m_Path(path)
{
    m_id = ++m_idCounter;
    std::cout << "Created File: " << std::endl;
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
    //close file
    m_fs.close();
}

void CFileHandler::init()
{
    //open file

    m_fs.open(m_Path, std::ios::out | std::ios::in);

    char data[100];

    std::cout << "write to file: " << std::endl;
    std::cin.getline(data, 100);
    m_fs << data << std::endl;
    
    std::cout << "read from file" << std::endl;
    m_fs >> data;
    std::cout << data << std::endl; 
    


    m_fs.close();
}

void CFileHandler::write(std::string message)
{
    
}

void CFileHandler::read()
{
    //read from file in seconds
}

void CFileHandler::output()
{
    //write to console
}

void CFileHandler::connect()
{
    //activate write to listener
}

int CFileHandler::getId()
{
    return 0;
}

void CFileHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | Path: " << m_Path << std::endl;
}