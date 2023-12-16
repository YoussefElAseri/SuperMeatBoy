#ifndef SUPERMEATBOY_SUBJECT_H
#define SUPERMEATBOY_SUBJECT_H


#include <vector>
#include <memory>

class Observer;

class Subject {
protected:
    std::vector<std::shared_ptr<Observer>> mObservers;

public:
    void subscribe(const std::shared_ptr<Observer>& newObserver);

    void unsubscribe(const std::shared_ptr<Observer>& oldObserver);
};


#endif //SUPERMEATBOY_SUBJECT_H
