#pragma once

#include "fl/net/Endpoint.hpp"

namespace Forward {

    class AsyncListener : public std::enable_shared_from_this<AsyncListener>
    {
    private:
        using AsyncAcceptFunc = std::function<void(beast::error_code, tcp::socket&&)>;

        Endpoint endpoint_;

        net::io_context& io_context_;
        tcp::acceptor acceptor_;

        AsyncAcceptFunc call_back_;

    public:
        AsyncListener(net::io_context& ioc, 
            Endpoint const& endpoint, 
            AsyncAcceptFunc const& call_back);

        bool Listen();
        bool Listen(beast::error_code& ec);
        
        void Accept();
    };
} // namespace Forward