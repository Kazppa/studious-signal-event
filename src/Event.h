//
// Created by mathieu on 13/01/2021.
//

#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <list>
#include <type_traits>
#include <algorithm>

#include "AbstractEvent.h"
#include "Observer.h"


template<typename ...Args>
class Event : public AbstractEvent {
protected:
    using CallbackFunction = std::function<void(Args...)>;
    template<class C>
    using IsObserver = std::enable_if_t<std::is_base_of_v<Observer, C>>;
    template<typename Class, typename Method>
    using IsClassMethod = std::enable_if_t<std::is_invocable_v<Method, Class, Args...>>;

    struct Callback {
        Observer *m_Observer = nullptr;
        CallbackFunction m_Callback;
    };

    std::list<Callback> m_Callbacks;

public:
    Event() = default;

    Event(const Event &other) = delete;

    Event(Event &&other) noexcept = delete;

    ~Event() {
        for (auto &cb : m_Callbacks) {
            if (cb.m_Observer) {
                cb.m_Observer->removeEvent(this);
            }
        }
    };

    // Register free function/Lambda callback
    void connect(CallbackFunction func) {
        m_Callbacks.push_back({nullptr, func});
    }

    // Register Observer function member
    template<class C, typename Slot, typename = IsObserver<C>, typename = IsClassMethod<C, Slot>>
    void connect(C *receiver, Slot &&slot) {
        Observer *observer = receiver;
        if (!observer || isObserverConnected(observer)) {
            // Avoid nullptr and observer duplication
            return;
        }

        m_Callbacks.push_back({observer, [receiver, slot](Args... args) -> void {
            std::invoke(slot, receiver, args...);
        }});
        observer->addEvent(this);
    }

    void disconnect(Observer *receiver) override {
        m_Callbacks.erase(std::remove_if(std::begin(m_Callbacks), std::end(m_Callbacks), [receiver](const Callback &o) {
            return o.m_Observer == receiver;
        }));
    }

    bool isObserverConnected(Observer *observer) {
        return std::any_of(m_Callbacks.begin(), m_Callbacks.end(), [observer](const Callback &cb) {
            return (cb.m_Observer == observer);
        });
    }

    // Trigger the event and notify every observers
    void operator()(Args &&... args) {
        // In a separated thread, call observers one by one
        std::thread(&Event::notifyObservers, this, args...).detach();
    }

    Event &operator=(const Event &other) = delete;

    Event &operator=(Event &&other) noexcept = delete;

protected:
    void notifyObservers(Args... args) {
        for (auto &obs: m_Callbacks) {
            obs.m_Callback(args...);
        }
    }
};

#endif //EVENT_H
