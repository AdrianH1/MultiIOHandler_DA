#include "CSerialHandler.h"

static const std::string sType = "serial";

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
    //Make sure ASIO io_context is running
    if (m_context.stopped())
    {
        m_context.restart();
    }

    //Give the ASIO io_context fake work to keep it running
    asio::io_context::work idleWork(m_context);

    //Run ASIO io_context in separate thread so that reading can be done parallel to main thread
    m_thrContext = std::thread([this]() {m_context.run(); });

    asio::error_code ec;
    m_serial.open(m_port, ec);
    m_serial.set_option(asio::serial_port_base::baud_rate(m_baudrate), ec);

    //m_serial.set_option(asio::serial_port_base::baud_rate(115200), ec);
    //m_serial.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none), ec);
    //m_serial.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::even), ec);
    //m_serial.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one), ec);
    //m_serial.set_option(asio::serial_port_base::character_size(8), ec);
   
    //auto test = static_cast<asio::serial_port_base::stop_bits::type>(0);

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
    for (std::vector<char> v : readBuffer)
    {
        for (char c : v)
        {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    setWriteToListener(true);
}

void CSerialHandler::read()
{
    //Keep readBuffer size in check
    if (readBuffer.size() == bufferMax)
    {
        readBuffer.erase(readBuffer.begin());
    }

    //Async read function from ASIO
    m_serial.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [this](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                readBuffer.push_back(vBuffer);
                //Call write method of all listener in listener table with read data
                if (getWriteToListener())
                {
                    for (IIOModule* m : listenerTable)
                    {
                        m->write(vBuffer);
                    }
                }
                //This is no endless recursion because async_read_some is only running if data is recieved
                read();
            }
        });
}

void CSerialHandler::write(std::vector<char> message)
{
    //lock_guard to prevent simultaneous writing. Lock is released when block ends.
    const std::lock_guard<std::mutex> lock(writeMutex);
    asio::error_code ec;
    if (filterIsSet())
    {
        std::vector<char> filteredMessage = getFilter()->filterData(message);
        m_serial.write_some(asio::buffer(filteredMessage.data(), filteredMessage.size()), ec);
    }
    else
    {
        m_serial.write_some(asio::buffer(message.data(), message.size()), ec);
    }
}

std::vector<std::vector<std::string>> CSerialHandler::getInfo()
{
    std::vector<std::vector<std::string>> info;
    std::vector<std::string> parameter;

    parameter.push_back("Type");
    //Use string instead of enum, otherwise there is an int for type in json export
    parameter.push_back(sType);
    info.push_back(parameter);
    parameter.clear();

    parameter.push_back("Port");
    parameter.push_back(m_port);
    info.push_back(parameter);
    parameter.clear();

    parameter.push_back("Baudrate");
    parameter.push_back(std::to_string(m_baudrate));
    info.push_back(parameter);
    parameter.clear();

    return info;
}

void CSerialHandler::connect()
{
    setWriteToListener(true);
}

void CSerialHandler::stop()
{
    setWriteToListener(false);
    setConnectedState(false);
    listenerTable.clear();
    removeFilter();
    m_serial.close();
    m_context.stop();
    if (m_thrContext.joinable()) m_thrContext.join();
}

void CSerialHandler::printInfo()
{
    std::cout << "ID: " << getId() << " | Type: " << sType << " | Port: " << m_port << " | Baudrate: " << m_baudrate << " | Connected: " << (getConnectedState() ? "true" : "false") << std::endl;
}