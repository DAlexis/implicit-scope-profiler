#ifndef ISP_HPP_INCLUDED
#define ISP_HPP_INCLUDED

#include <thread>
#include <vector>
#include <chrono>
#include <cstdint>
#include <map>
#include <boost/thread.hpp>

#define ISP_EVENT_ID (event_id(__FILE__, __LINE__))
#define ISP_EVENT_ID (event_id(__FILE__, __LINE__))

#define ISP_COMBINE1(X,Y) X##Y  // helper macro
#define ISP_COMBINE(X,Y) ISP_COMBINE1(X,Y)

#define ISP_SCOPE(name) isp::Scope ISP_COMBINE(s,__LINE__)(default_host, name, ISP_EVENT_ID);
#define ISP_INSTANT(name) isp::default_host.instant(name, ISP_EVENT_ID);

#define ISP_WRITE_TIMELINE(filename) isp::default_host.write_timeline(filename);

namespace isp
{

class Scope;

using EventId = uint32_t;

class Event
{
public:
    enum class Type
    {
        complete,
        instant
    };

    // Instant event
    Event(EventId id,
          const char* name,
          std::chrono::steady_clock::time_point now);

    // Complete event
    Event(EventId id,
          const char* name,
          std::chrono::steady_clock::time_point begin,
          std::chrono::steady_clock::time_point end);


    const EventId id;
    const char* name;
    const Type type;

    const std::chrono::steady_clock::time_point begin;
    const std::chrono::steady_clock::time_point end;
};

class Host
{
public:
    Host();
    void add_event(const Event& event);
    void write_timeline(const char* filename);
    void instant(const char* name, EventId id);
    void reset();

private:
    std::chrono::steady_clock::time_point m_host_creation;
    std::map<std::thread::id, std::vector<Event>> m_events_by_thread;
    boost::shared_mutex m_events_mutex;
};

class Scope
{
public:
    Scope(Host& host, const char* name, EventId id);
    ~Scope();

    void close();
private:
    EventId m_id;
    Host& m_host;
    const char* m_name;
    std::chrono::steady_clock::time_point m_begin;
    bool m_closed = false;
};

constexpr EventId event_id(const char *file, unsigned int line)
{
    constexpr uint32_t c1 = 1664525, c2 = 1013904223;
    uint32_t hash_ly = 0;

    for(; *file; file++)
        hash_ly = (hash_ly * c1) + (unsigned char)(*file) + c2;

    for(; line; line /= 256)
        hash_ly = (hash_ly * c1) + (unsigned char)(line % 256) + c2;
    return hash_ly;
}

extern Host default_host;

}

#endif // ISP_HPP_INCLUDED
