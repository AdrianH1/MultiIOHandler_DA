#include "stdafx.h"
#include "File.h"


File::File(std::string path)
    : m_Path(path)
{
    m_id = ++m_idCounter;
}

File::~File()
{
}

void File::init()
{

}

void File::send()
{

}

void File::recv()
{

}

void File::printInfo()
{
    std::cout << "ID: " << m_id << " | Path: " << m_Path << std::endl;
}