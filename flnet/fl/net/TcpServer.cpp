#include "fl/net/TcpServer.hpp"
#include "fl/utils/Log.hpp"

#include <boost/beast/core/bind_handler.hpp>

namespace Forward::Net {

    TcpServer::TcpServer(uint32_t io_count)
        : io_count_(io_count)
        , io_context_(io_count)
        , acceptor_(io_context_)
    {
        io_sessions_.reserve(io_count);
    }

    TcpServer::~TcpServer()
    {
    
    }

    void TcpServer::SetErrorCallback(OnError const& callback) 
    {
        on_error_ = callback;
        is_onerror = true;
    }
    void TcpServer::SetAcceptCallback(OnSocket const& callback)
    {
        on_socket_ = callback;
        is_onsocket = true;
    }

    void TcpServer::Listen()
    {
        Core::Error ec;
        Listen(ec);
    }
    void TcpServer::Listen(Core::Error& ec)
    {
        Listen(Endpoint(), ec);
    }

    void TcpServer::Listen(Endpoint const& endpoint)
    {
        Core::Error ec;
        Listen(endpoint, ec);
    }
    void TcpServer::Listen(Endpoint const& endpoint, Core::Error& ec)
    {
        if (IsListening())
        {
            FL_LOG("Listener", "already listening");
            return;
        }

        // Open the acceptor
        acceptor_.open(endpoint.Protocol(), ec);

        if(ec)
            return;

        // Allow address reuse
        acceptor_.set_option(Core::Asio::socket_base::reuse_address(true));
        acceptor_.bind(endpoint, ec);

        if (ec) 
            return;

        acceptor_.listen(Core::Asio::socket_base::max_listen_connections, ec);

        if(ec)
            return;

        is_listening = true;

        AcceptNextSocket();
        StartIOContext();
    }

    bool TcpServer::IsListening() const
    {
        return is_listening;
    }

    void TcpServer::OnSocketError(Core::Error ec)
    {
        FL_LOG("TcpServer", ec);
    }
    void TcpServer::OnSocketAccept(Core::Tcp::socket socket)
    {
        
    }

    void TcpServer::StartIOContext() 
    {
        for (uint64_t i = 0; i < io_count_; ++i)
        {
            io_sessions_.emplace_back(
            [this]
            {
                io_context_.run();
            });
        }

        io_context_.run();
    }
    void TcpServer::AcceptNextSocket()
    {
        acceptor_.async_accept(
            Core::Asio::make_strand(io_context_),
            boost::beast::bind_front_handler(
                &TcpServer::HandleSocket,
                this));
    }
    void TcpServer::HandleSocket(Core::Error ec, Core::Tcp::socket socket)
    {
        if (ec)
        {
            OnSocketError(ec);

            if (is_onerror)
                on_error_(ec);

            return;
        }

        if (is_onsocket)
            on_socket_(std::move(socket));
        else
            OnSocketAccept(std::move(socket));

        AcceptNextSocket();
    }
     
} // namespace Forward
