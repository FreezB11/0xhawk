/*
 * @author: hsay
 * @file: timer.h
 * @date: Oct27
 */
#include <iostream>
#include <chrono>

class Timer{
    public:
        Timer(){
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }
        ~Timer(){
            stop();
        }
        void stop(){
            auto endTimepoint = std::chrono::high_resolution_clock::now();
            
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count(); 

            auto duration = stop - start;
            double ms = duration * 0.001;

            std::cout <<"\n" << duration << "us (" << ms << ")\n";

        }


    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};
