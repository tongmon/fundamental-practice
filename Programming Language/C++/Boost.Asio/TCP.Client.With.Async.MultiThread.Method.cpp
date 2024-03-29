#pragma region standard header
#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <coroutine>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
#pragma endregion

#ifdef BOOST_OS_WINDOWS
#define _WIN32_WINNT 0x0601
#endif

#include <boost/asio.hpp>

using namespace boost;

using Callback = void (*)(unsigned int request_id, const std::string &response, const system::error_code &ec);

struct Session
{
    Session(asio::io_service &ios,
            const std::string &raw_ip_address,
            unsigned short port_num,
            const std::string &request,
            unsigned int id,
            Callback callback)
        : m_sock(ios),
          m_ep(asio::ip::address::from_string(raw_ip_address), port_num),
          m_request(request),
          m_id(id),
          m_callback(callback),
          m_was_cancelled(false)
    {
    }

    asio::ip::tcp::socket m_sock; // Socket used for communication
    asio::ip::tcp::endpoint m_ep; // Remote endpoint.
    std::string m_request;        // Request string.

    // streambuf where the response will be stored.
    asio::streambuf m_response_buf;
    std::string m_response; // Response represented as a string.

    // Contains the description of an error if one occurs during
    // the request lifecycle.
    system::error_code m_ec;

    unsigned int m_id; // Unique ID assigned to the request.

    // Pointer to the function to be called when the request
    // completes.
    Callback m_callback;

    bool m_was_cancelled;
    std::mutex m_cancel_guard;
};

class AsyncTCPClient // : public boost::noncopyable
{
    asio::io_service m_ios;
    std::map<int, std::shared_ptr<Session>> m_active_sessions;
    std::mutex m_active_sessions_guard;
    std::unique_ptr<boost::asio::io_service::work> m_work;
    std::list<std::unique_ptr<std::thread>> m_threads;

  public:
    AsyncTCPClient(unsigned char num_of_threads)
    {
        m_work.reset(new boost::asio::io_service::work(m_ios));

        for (unsigned char i = 0; i < num_of_threads; i++)
        {
            std::unique_ptr<std::thread> th(
                new std::thread([this]() {
                    m_ios.run();
                }));

            m_threads.push_back(std::move(th));
        }
    }

    void emulateLongComputationOp(
        unsigned int duration_sec,
        const std::string &raw_ip_address,
        unsigned short port_num,
        Callback callback,
        unsigned int request_id)
    {
        // Preparing the request string.
        std::string request = "EMULATE_LONG_CALC_OP " + std::to_string(duration_sec) + "\n";

        std::shared_ptr<Session> session = std::shared_ptr<Session>(new Session(m_ios,
                                                                                raw_ip_address,
                                                                                port_num,
                                                                                request,
                                                                                request_id,
                                                                                callback));

        session->m_sock.open(session->m_ep.protocol());

        // Add new session to the list of active sessions so
        // that we can access it if the user decides to cancel
        // the corresponding request before it completes.
        // Because active sessions list can be accessed from
        // multiple threads, we guard it with a mutex to avoid
        // data corruption.
        std::unique_lock<std::mutex>
            lock(m_active_sessions_guard);
        m_active_sessions[request_id] = session;
        lock.unlock();

        session->m_sock.async_connect(session->m_ep,
                                      [this, session](const system::error_code &ec) {
                                          if (ec != boost::system::errc::success)
                                          {
                                              session->m_ec = ec;
                                              onRequestComplete(session);
                                              return;
                                          }

                                          std::unique_lock<std::mutex>
                                              cancel_lock(session->m_cancel_guard);

                                          if (session->m_was_cancelled)
                                          {
                                              onRequestComplete(session);
                                              return;
                                          }

                                          asio::async_write(session->m_sock,
                                                            asio::buffer(session->m_request),
                                                            [this, session](const boost::system::error_code &ec,
                                                                            std::size_t bytes_transferred) {
                                                                if (ec != boost::system::errc::success)
                                                                {
                                                                    session->m_ec = ec;
                                                                    onRequestComplete(session);
                                                                    return;
                                                                }

                                                                std::unique_lock<std::mutex>
                                                                    cancel_lock(session->m_cancel_guard);

                                                                if (session->m_was_cancelled)
                                                                {
                                                                    onRequestComplete(session);
                                                                    return;
                                                                }

                                                                asio::async_read_until(session->m_sock,
                                                                                       session->m_response_buf,
                                                                                       '\n',
                                                                                       [this, session](const boost::system::error_code &ec,
                                                                                                       std::size_t bytes_transferred) {
                                                                                           if (ec != boost::system::errc::success)
                                                                                           {
                                                                                               session->m_ec = ec;
                                                                                           }
                                                                                           else
                                                                                           {
                                                                                               std::istream strm(&session->m_response_buf);
                                                                                               std::getline(strm, session->m_response);
                                                                                           }

                                                                                           onRequestComplete(session);
                                                                                       });
                                                            });
                                      });
    };

    // Cancels the request.
    void cancelRequest(unsigned int request_id)
    {
        std::unique_lock<std::mutex>
            lock(m_active_sessions_guard);

        auto it = m_active_sessions.find(request_id);
        if (it != m_active_sessions.end())
        {
            std::unique_lock<std::mutex>
                cancel_lock(it->second->m_cancel_guard);

            it->second->m_was_cancelled = true;
            it->second->m_sock.cancel();
        }
    }

    void close()
    {
        // Destroy work object. This allows the I/O threads to
        // exit the event loop when there are no more pending
        // asynchronous operations.
        m_work.reset(NULL);

        // Waiting for the I/O threads to exit.
        for (auto &thread : m_threads)
        {
            thread->join();
        }
    }

  private:
    void onRequestComplete(std::shared_ptr<Session> session)
    {
        // Shutting down the connection. This method may
        // fail in case socket is not connected. We don�t care
        // about the error code if this function fails.
        boost::system::error_code ignored_ec;

        session->m_sock.shutdown(
            asio::ip::tcp::socket::shutdown_both,
            ignored_ec);

        // Remove session form the map of active sessions.
        std::unique_lock<std::mutex>
            lock(m_active_sessions_guard);

        auto it = m_active_sessions.find(session->m_id);
        if (it != m_active_sessions.end())
            m_active_sessions.erase(it);

        lock.unlock();

        boost::system::error_code ec;

        if (session->m_ec == boost::system::errc::success && session->m_was_cancelled)
            ec = asio::error::operation_aborted;
        else
            ec = session->m_ec;

        // Call the callback provided by the user.
        session->m_callback(session->m_id,
                            session->m_response, ec);
    };
};

void handler(unsigned int request_id,
             const std::string &response,
             const system::error_code &ec)
{
    if (ec == boost::system::errc::success)
    {
        std::cout << "Request #" << request_id
                  << " has completed. Response: "
                  << response << std::endl;
    }
    else if (ec == asio::error::operation_aborted)
    {
        std::cout << "Request #" << request_id
                  << " has been cancelled by the user."
                  << std::endl;
    }
    else
    {
        std::cout << "Request #" << request_id
                  << " failed! Error code = " << ec.value()
                  << ". Error message = " << ec.message()
                  << std::endl;
    }

    return;
}

int main()
{
    try
    {
        AsyncTCPClient client(4);

        // Here we emulate the user's behavior.

        // User initiates a request with id 1.
        client.emulateLongComputationOp(10, "127.0.0.1", 3333,
                                        handler, 1);
        // Then does nothing for 5 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(5));
        // Then initiates another request with id 2.
        client.emulateLongComputationOp(11, "127.0.0.1", 3334,
                                        handler, 2);
        // Then decides to cancel the request with id 1.
        client.cancelRequest(1);
        // Does nothing for another 6 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(6));
        // Initiates one more request assigning ID 3 to it.
        client.emulateLongComputationOp(12, "127.0.0.1", 3335,
                                        handler, 3);
        // Does nothing for another 15 seconds.
        std::this_thread::sleep_for(std::chrono::seconds(15));
        // Decides to exit the application.
        client.close();
    }
    catch (system::system_error &e)
    {
        std::cout << "Error occured! Error code = " << e.code()
                  << ". Message: " << e.what();

        return e.code().value();
    }

    return 0;
}