#include "Subject.h"

void Subject::subscribe(const std::shared_ptr<Observer> &newObserver) {
    mObservers.emplace_back(newObserver);
}

void Subject::unsubscribe(const std::shared_ptr<Observer> &oldObserver) {
    for (int i = 0; i < mObservers.size(); ++i) {
        if (mObservers[i] == oldObserver) {
            mObservers.erase(mObservers.begin()+i);
            return;
        }
    }
}
