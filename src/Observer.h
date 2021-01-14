#ifndef OBSERVER_H
#define OBSERVER_H

#include <unordered_set>

class AbstractEvent;

class Observer {
private:
    std::unordered_set<AbstractEvent*> m_Events;

public:
    Observer() = default;

    Observer(const Observer &other); // non default

    Observer(Observer &&other) noexcept; // non default

    ~Observer();

    void addEvent(AbstractEvent* event);

    void removeEvent(AbstractEvent* eventToRemove);

    Observer &operator=(const Observer &other); // non default
    Observer &operator=(Observer &&other) noexcept; // non default
};

#endif //OBSERVER_H
