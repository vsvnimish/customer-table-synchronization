# 🍽️ Multi-Threaded Customer--Table Synchronization System

### Using POSIX Threads, Mutex Locks & Semaphores

This project simulates a dining-hall environment where multiple customer
threads compete for a limited number of tables. It demonstrates
real-world concurrency challenges such as synchronization, queueing,
fairness, and resource sharing.

## ⭐ Features

-   Dynamic customer-thread creation using random batch sizes
-   Random delay between thread batches to simulate real arrivals
-   Mutex + semaphore-based synchronization
-   Controlled table allocation
-   Analysis of waiting-time trends under different parameters
-   Fully multi-threaded architecture
-   Output logs for detailed study

## 🛠️ Tech Stack

  Component              Technology
  ---------------------- -----------------------------
  Programming Language   C++
  Threading              POSIX Threads (pthreads)
  Synchronization        Semaphores (`sem_t`), Mutex
  Compiler               g++
  Required Flags         -pthread, -lrt
  OS Compatibility       Linux / Unix
  Input/Output           input.txt, output-log.txt

## 🔧 Execution Instructions

### Compile

    g++ SrcAssgn4-CS19B1026.cpp -pthread -lrt -o a

### Run

    ./a < input.txt > output-log.txt

### Output

-   output-log.txt → contains the full execution log

## 📌 System Modeling Overview

-   Random customer-thread batch creation
-   Random delays between thread groups
-   Semaphore-based blocking/waiting
-   Table allocation and signaling after eating
-   Global arrays safely indexed by thread ID

## 📊 Graph Analysis Summary

### Graph 1 -- Customers vs Waiting Time

-   More customers → more waiting (generally)
-   Exceptions due to creation-time delays

### Graph 2 -- Tables vs Waiting Time

-   More tables → less waiting
-   Minor fluctuations when delay dominates

## 🧠 Key Concepts

-   Semaphore blocking/signaling
-   Mutex-based critical sections
-   Fair resource allocation
-   Multi-threaded system modeling

## 📁 Files

  File                      Description
  ------------------------- -------------------------
  SrcAssgn4-CS19B1026.cpp   Source program
  input.txt                 Simulation parameters
  output-log.txt            Complete program output

## 🚀 Future Enhancements

-   Priority scheduling
-   Auto graph generation
-   VIP table policies
