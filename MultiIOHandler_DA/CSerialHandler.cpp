#include "stdafx.h"
#include "cSerialHandler.h"


CSerialHandler::CSerialHandler(std::string port, int bauderate)
    : m_port(port), m_baudrate(bauderate), m_serial(m_context), vBuffer(vBufferSize)
{
    setId(++m_idCounter);
    setModuleType(serial);
    setConnectedState(false);
    std::cout << "Created Serial Module: " << std::endl;
    printInfo();
}

CSerialHandler::~CSerialHandler()
{
    stop();
}

void CSerialHandler::init()
{
    if (m_context.stopped())
    {
        m_context.restart();
    }

    asio::io_context::work idleWork(m_context);

    m_thrContext = std::thread([this]() {m_context.run(); });

    asio::error_code ec;
    m_serial.open(m_port, ec);
    m_serial.set_option(asio::serial_port_base::baud_rate(m_baudrate), ec);

    if (!ec)
    {
        std::cout << "Connected!" << std::endl;
        setConnectedState(true);
        read();
    }
    else
    {
        std::cout << "Failed to connect!" << std::endl;
        m_context.stop();
        if (m_thrContext.joinable()) m_thrContext.join();
    }
}

void CSerialHandler::output()
{
    for (std::string s : readBuffer)
    {
        std::cout << s << std::endl;
    }
    writeToListener = true;
}

void CSerialHandler::read()
{
    if (readBuffer.size() == bufferMax)
    {
        readBuffer.erase(readBuffer.begin());
    }

    m_serial.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [this](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                std::string message = "";
                for (int i = 0; i < length; i++)
                {
                    message += vBuffer[i];
                }
                readBuffer.push_back(message);
                if (writeToListener)
                {
                    for (IIOModule* m : listenerTable)
                    {
                        m->write(message);
                    }
                }
                read();
            }
        });
}

void CSerialHandler::write(std::string message)
{
    const std::lock_guard<std::mutex> lock(writeMutex);
    asio::error_code ec;
    if (filterIsSet())
    {
        std::string filteredMessage = getFilter()->filterData(message);
        m_serial.write_some(asio::buffer(filteredMessage.data(), filteredMessage.size()), ec);
    }
    else
    {
        m_serial.write_some(asio::buffer(message.data(), message.size()), ec);
    }
}

std::vector<std::string> CSerialHandler::getInfo()
{
    std::vector<std::string> info;
    info.push_back(std::to_string(getId()));
    info.push_back(std::to_string(getModuleType()));
    info.push_back(m_port);
    info.push_back(std::to_string(m_baudrate));
    return info;
}

void CSerialHandler::connect()
{
    for (IIOModule* m : listenerTable)
    {
        writeToListener = true;
    }
}

void CSerialHandler::stop()
{
    writeToListener = false;
    setConnectedState(false);
    listenerTable.clear();
    m_serial.close();
    m_context.stop();
    if (m_thrContext.joinable()) m_thrContext.join();
}

void CSerialHandler::printInfo()
{
    std::cout << "ID: " << getId() << " | Type: " << "serial" << " | Port: " << m_port << " | Baudrate: " << m_baudrate << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;
}