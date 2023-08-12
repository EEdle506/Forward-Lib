#pragma once

#include "fl/net/http/Core.hpp"

namespace Forward::Web {

    class HttpSession 
    {
    private:
        using ExpireTime = std::chrono::steady_clock::duration;

        Core::Beast::ssl_stream<Core::Beast::tcp_stream> stream_;
        ExpireTime exp_run_, exp_read_, exp_close_;
        
        Core::Beast::flat_buffer buffer_;

    protected:
        Http::request<Http::string_body> req_;

    public:
        explicit HttpSession(Core::Tcp::socket socket, Core::Ssl::context& context);
        virtual ~HttpSession();

        void SetRunExpire(ExpireTime exp_time);
        void SetReadExpire(ExpireTime exp_time);
        void SetCloseExpire(ExpireTime exp_time);

        // Start the session
        void Run();
        // Sends message to client
        void Write(Http::message_generator&& msg);
        // Closes connection
        void Close();

    protected:
        /**
         *
         * void HttpSession::OnRead(sys::error_code ec, size_t bytes_transferred)
         * {
         *     boost::ignore_unused(bytes_transferred);
         * 
         *     if(ec == http::error::end_of_stream)
         *         return Close();
         * 
         *     if(ec)
         *         return FL_LOG("OnRead", ec.message());
         * 
         *     ... Your code
         *  
         *  }*/
        virtual void OnRead(Core::Error ec, std::size_t bytes_transferred) = 0;

    private:
        void OnRun();
        void OnHandshake(Core::Error ec);

        void Read();

        void OnWrite(bool keep_alive, Core::Error ec, std::size_t bytes_transferred);
        void OnClose(Core::Error ec);
    };
}