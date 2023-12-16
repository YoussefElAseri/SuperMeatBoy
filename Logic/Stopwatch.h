#ifndef SUPERMEATBOY_STOPWATCH_H
#define SUPERMEATBOY_STOPWATCH_H


#include <memory>
#include <mutex>
#include <chrono>

class Stopwatch {
private:
    inline static std::mutex mutex;
    inline static std::shared_ptr<Stopwatch> mStopWatch;
    std::chrono::system_clock::time_point mStartTime;
    std::chrono::duration<float> mDeltaTime{};
    Stopwatch();

public:
    Stopwatch(Stopwatch&) = delete;

    void operator=(const Stopwatch&) = delete;

    static std::shared_ptr<Stopwatch>& getInstance();

    void Reset();

    float DeltaTime();

    void Tick();

    ~Stopwatch() = default;
};


#endif //SUPERMEATBOY_STOPWATCH_H
