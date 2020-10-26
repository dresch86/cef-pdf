#ifndef SERVER_UNIXSOCKET_H_
#define SERVER_UNIXSOCKET_H_

#include "../Client.h"
#include "SessionManager.h"

#include "include/cef_base.h"

#include <string>
#include <thread>
#include <system_error> // std::error_code

#include <asio.hpp>

#if !defined(OS_WIN)
namespace cefpdf {
namespace server {

class UnixSocket : public CefBaseRefCounted
{

public:
    UnixSocket(CefRefPtr<cefpdf::Client> client, std::string const&);

    void Start();

private:
    void Run();

    void Listen();

    void OnSignal(std::error_code, int);

    void OnConnection(std::error_code);

    CefRefPtr<cefpdf::Client> m_client;

    std::thread m_thread;

    asio::io_service m_ioService;

    asio::local::stream_protocol::acceptor m_acceptor;

    asio::local::stream_protocol::socket m_socket;

    asio::signal_set m_signals;

    CefRefPtr<SessionManager> m_sessionManager;

    int m_counter;

    // Include the default reference counting implementation.
    IMPLEMENT_REFCOUNTING(UnixSocket);
};

} // namespace server
} // namespace cefpdf
#endif
#endif // SERVER_UNIXSOCKET_H_
