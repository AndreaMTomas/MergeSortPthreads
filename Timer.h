#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

class Timer {
    public:
        void start() {time_start = std::chrono::high_resolution_clock::now();}
        void stop()  {time_stop = std::chrono::high_resolution_clock::now();}
        auto elapsed() { std::chrono::duration<double> diff =  time_stop - time_start; return diff.count();}
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> time_start;
        std::chrono::time_point<std::chrono::high_resolution_clock> time_stop;

};

#endif