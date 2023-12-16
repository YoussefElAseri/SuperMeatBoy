#include "Stopwatch.h"

std::shared_ptr<Stopwatch>& Stopwatch::getInstance() {
    std::lock_guard lock(mutex);
    if (mStopWatch == nullptr) {
        mStopWatch = std::shared_ptr<Stopwatch>(new Stopwatch());
    }
    return mStopWatch;
}

Stopwatch::Stopwatch() {
    Reset();
    mDeltaTime = std::chrono::duration<float>(0.0f);
}

void Stopwatch::Reset() {
    mStartTime = std::chrono::system_clock::now();
}

float Stopwatch::DeltaTime() {
    return mDeltaTime.count();
}

void Stopwatch::Tick() {
    mDeltaTime = std::chrono::system_clock::now() - mStartTime;
}
