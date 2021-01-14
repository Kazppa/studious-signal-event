#include "Observer.h"
#include "AbstractEvent.h"


Observer::Observer(const Observer &other) {

}

Observer::Observer(Observer &&other) noexcept {

}

Observer::~Observer() {
    for (auto event : m_Events) {
        event->disconnect(this);
    }
}

void Observer::addEvent(AbstractEvent *event) {
    m_Events.insert(event);
}

void Observer::removeEvent(AbstractEvent *eventToRemove) {
    m_Events.erase(eventToRemove);
}

Observer& Observer::operator=(const Observer &other) {
    return *this;
}

Observer& Observer::operator=(Observer &&other) noexcept {
    return *this;
}
