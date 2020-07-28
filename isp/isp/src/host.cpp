#include "isp/isp.hpp"

#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"

#include <fstream>

Event::Event(EventId id, const char* name, std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end) :
    id(id), name(name), begin(begin), end(end)
{
}

Host::Host() :
    m_host_creation(std::chrono::steady_clock::now())
{
}

void Host::add_event(const Event& event)
{
    m_events.push_back(event);
}

void Host::write_timeline(const char* filename)
{
    using namespace rapidjson;
    Document d;
    d.SetObject();
    auto & alloc = d.GetAllocator();

    Value trace_events(kArrayType);

    for (auto& event : m_events)
    {
        Value trace_event(kObjectType);

        Value pid;
        pid.SetInt(1);
        trace_event.AddMember("pid", pid, alloc);

        Value tid;
        tid.SetString("Thread 1");
        trace_event.AddMember("tid", tid, alloc);

        Value ts;
        ts.SetUint64(std::chrono::duration_cast<std::chrono::microseconds>(event.begin - m_host_creation).count());
        trace_event.AddMember("ts", ts, alloc);

        Value dur;
        dur.SetUint64(std::chrono::duration_cast<std::chrono::microseconds>(event.end - event.begin).count());
        trace_event.AddMember("dur", dur, alloc);

        Value name(StringRef(event.name));
        trace_event.AddMember("name", name, alloc);

        trace_event.AddMember("ph", Value("X"), alloc);

        trace_events.PushBack(trace_event, alloc);
    }

    d.AddMember("traceEvents", trace_events, alloc);

    std::ofstream ofs(filename);
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    d.Accept(writer);
}

void Host::write_averaged_events(const char* filename)
{
}

Scope::Scope(Host& host, const char* name, EventId id) :
    m_id(id), m_host(host), m_name(name), m_begin(std::chrono::steady_clock::now())
{
}

Scope::~Scope()
{
    auto end = std::chrono::steady_clock::now();
    Event ev(m_id, m_name, m_begin, end);
    m_host.add_event(ev);
}
