#include "isp/isp.hpp"

#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"

#include <fstream>
#include <iostream>

using namespace isp;

Host isp::default_host;

Event::Event(EventId id, const char* name, std::chrono::steady_clock::time_point now) :
    id(id), name(name), type(Type::instant), begin(now), end(now)
{

}

Event::Event(EventId id, const char* name, std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end) :
    id(id), name(name), type(Type::complete), begin(begin), end(end)
{
}

Host::Host()
{
    reset();
}

void Host::add_event(const Event& event)
{
    std::thread::id this_id = std::this_thread::get_id();
    boost::upgrade_lock<boost::shared_mutex> lock(m_events_mutex);
    auto it = m_events_by_thread.find(this_id);
    if (it == m_events_by_thread.end())
    {
         boost::upgrade_to_unique_lock<boost::shared_mutex> unique_lock(lock);
         m_events_by_thread[this_id].push_back(event);
    } else {
        it->second.push_back(event);
    }
}

void Host::write_timeline(const char* filename)
{
    using namespace rapidjson;
    Document d;
    d.SetObject();
    auto & alloc = d.GetAllocator();

    Value trace_events(kArrayType);

    int thread_numer = 1;
    for (auto it = m_events_by_thread.cbegin(); it != m_events_by_thread.cend(); ++it, ++thread_numer)
    {
        for (auto& event : it->second)
        {
            Value trace_event(kObjectType);

            Value pid(1);
            trace_event.AddMember("pid", pid, alloc);

            Value tid(("Thread " + std::to_string(thread_numer)).c_str(), d.GetAllocator());
            trace_event.AddMember("tid", tid, alloc);

            Value ts;
            ts.SetUint64(std::chrono::duration_cast<std::chrono::microseconds>(event.begin - m_host_creation).count());
            trace_event.AddMember("ts", ts, alloc);

            Value dur;
            dur.SetUint64(std::chrono::duration_cast<std::chrono::microseconds>(event.end - event.begin).count());
            trace_event.AddMember("dur", dur, alloc);

            Value name(StringRef(event.name));
            trace_event.AddMember("name", name, alloc);

            Value ph;
            if (event.type == Event::Type::complete)
            {
                trace_event.AddMember("ph", Value("X"), alloc);
            } else {
                trace_event.AddMember("ph", Value("i"), alloc);
            }

            trace_events.PushBack(trace_event, alloc);
        }
    }

    d.AddMember("traceEvents", trace_events, alloc);

    std::ofstream ofs(filename);
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    d.Accept(writer);
}

void Host::instant(const char* name, EventId id)
{
    auto now = std::chrono::steady_clock::now();
    Event ev(id, name, now);
    add_event(ev);
}

void Host::reset()
{
    m_events_by_thread.clear();
    m_host_creation = std::chrono::steady_clock::now();
}

Scope::Scope(Host& host, const char* name, EventId id) :
    m_id(id), m_host(host), m_name(name), m_begin(std::chrono::steady_clock::now())
{
}

Scope::~Scope()
{
    close();
}

void Scope::close()
{
    if (m_closed)
        return;
    auto end = std::chrono::steady_clock::now();
    Event ev(m_id, m_name, m_begin, end);
    m_host.add_event(ev);
    m_closed = true;
}
