cmake_minimum_required(VERSION 3.20)
project(ex6)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(ex6
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        AnomalyDetector.h
        CLI.h
        CLI.cpp
        commands.h
        HybridAnomalyDetector.cpp
        HybridAnomalyDetector.h
        minCircle.cpp
        minCircle.h
        Server.cpp
        Server.h
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        timeseries.cpp
        timeseries.h
        main.cpp)
