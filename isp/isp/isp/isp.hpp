#ifndef ISP_HPP_INCLUDED
#define ISP_HPP_INCLUDED

#include <vector>
#include <chrono>
#include <cstdint>

#define EVENT_ID (event_id(__FILE__, __LINE__))

class Scope;

using EventId = uint32_t;

struct Event
{
    Event(EventId id, const char* name, std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end);

    EventId id;
    const char* name;

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
};

class Host
{
public:
    Host();
    void add_event(const Event& event);
    void write_timeline(const char* filename);
    void write_averaged_events(const char* filename);

private:
    std::chrono::steady_clock::time_point m_host_creation;
    std::vector<Event> m_events;
};

class Scope
{
public:
    Scope(Host& host, const char* name, EventId id);
    ~Scope();

private:
    EventId m_id;
    Host& m_host;
    const char* m_name;
    std::chrono::steady_clock::time_point m_begin;
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

#endif // ISP_HPP_INCLUDED
