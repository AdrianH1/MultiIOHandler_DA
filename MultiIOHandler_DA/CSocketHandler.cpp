#include "CSocketHandler.h"
#include "Session.h"

size_t bufferMax = 50;
bool outputToConsole = false;

CSocketHandler::CSocketHandler(std::string ip, int unsigned port)
    : m_ip(ip), m_port(port), m_socket(m_context), vBuffer(1*512)
{
    m_id = ++m_idCounter;
    std::cout << "Created Socket: " << std::endl;
    printInfo();


}

CSocketHandler::~CSocketHandler()
{
    stop();
}

void CSocketHandler::run()
{
    asio::io_context::work idleWork(m_context);

    m_thrContext = std::thread([this]() {m_context.run(); });

    init();
}

void CSocketHandler::init()
{
    asio::error_code ec;
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(m_ip, ec), m_port);

    m_socket.connect(endpoint, ec);

    if (!ec)
    {
        std::cout << "Connected!" << std::endl;
        getData();
    }
    else
    {
        std::cout << "Failed to connect!" << std::endl;
    }
}

void CSocketHandler::output()
{
    for (std::string s : readBuffer)
    {
        std::cout << s << std::endl;
    }
    outputToConsole = true;
}

void CSocketHandler::getData()
{
    if (readBuffer.size() == bufferMax)
    {
        readBuffer.erase(readBuffer.begin());
    }

    m_socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                //std::cout << "\n\nRead " << length << " bytes\n\n";
                std::string message = "";
                for (int i = 0; i < length; i++)
                {
                    message += vBuffer[i];
                    //std::cout << vBuffer[i];
                }
                readBuffer.push_back(message);
                if (outputToConsole)
                {
                    std::cout << message << std::endl;
                }
                getData();
            }
        }
    );
}

void CSocketHandler::stop()
{
    m_context.stop();

    if (m_thrContext.joinable()) m_thrContext.join();

    std::cout << "Disconnected!" << std::endl;
}

void CSocketHandler::accept()
{
    
}


void CSocketHandler::read()
{
}

void CSocketHandler::write()
{

}

int CSocketHandler::getId()
{
    return m_id;
}

void CSocketHandler::printInfo()
{
    std::cout << "ID: " << m_id << " | IP: " << m_ip << " | Port: " << m_port << std::endl;
}
