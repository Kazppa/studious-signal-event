//
// Created by mathieu on 15/01/2021.
//

#ifndef ABSTRACTEVENT_H
#define ABSTRACTEVENT_H

#include "Observer.h"

class AbstractEvent {
public:
    virtual void disconnect(Observer* observer) = 0;
};


#endif //ABSTRACTEVENT_H
