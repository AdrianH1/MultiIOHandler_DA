#include "stdafx.h"
#include "Serial.h"


Serial::Serial(int port, int speed)
    : m_Port(port), m_Speed(speed)
{
    m_id = ++m_idCounter;
}

Serial::~Serial()
{
}

void Serial::init()
{

}

void Serial::send()
{

}

void Serial::recv()
{

}

void Serial::printInfo()
{
    std::cout << "ID: " << m_id << " | Port: " << m_Port << " | Spped: " << m_Speed << std::endl;
}