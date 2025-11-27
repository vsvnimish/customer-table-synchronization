# 🍽️ Multi-Threaded Customer–Table Synchronization System  
### Using POSIX Threads, Mutex Locks & Semaphores

This project simulates a dining-hall environment where multiple customer threads compete for a limited number of tables. It demonstrates real-world concurrency challenges such as synchronization, queueing, fairness, and resource sharing.

---

## ⭐ Features
- Dynamic customer-thread creation using random batch sizes  
- Random delay between thread batches to simulate real arrivals  
- Mutex + semaphore-based synchronization  
- Controlled table allocation (limited resources)  
- Analysis of waiting-time trends under different parameters  
- Fully multi-threaded design using pthreads  
- Output logs for debugging and performance analysis  

---

## 🛠️ Tech Stack

| Component | Technology |
|----------|------------|
| Programming Language | C++ |
| Threading | POSIX Threads (pthreads) |
| Synchronization | Semaphores (`sem_t`), Mutex |
| Compiler | g++ |
| Required Flags | `-pthread`, `-lrt` |
| OS Compatibility | Linux / Unix |
| Input/Output | `input.txt`, `output-log.txt` |

---

## 🔧 Execution Instructions

### **Compile**
```
g++ SrcAssgn4-CS19B1026.cpp -pthread -lrt -o a
```

### **Run**
```
./a < input.txt > output-log.txt
```

### **Output**
- `output-log.txt` → contains the full execution log  
  (waiting times, table availability, thread events)

---

## 📌 System Modeling Overview

- Customers arrive in **randomly sized groups**.
- A **random delay** is inserted before creating the next group.
- Every customer thread tries to get a table:
  - It checks if tables are available.
  - If the dining hall is full *or* other customers are waiting:
    - The thread waits using `sem_wait(&x_sem)`.
  - Otherwise:
    - The thread enters, eats, and leaves.

- After eating:
  - If the table becomes empty:
    - Waiting threads are signaled (either up to the number of tables or all).
  - Mutex is unlocked so new customers can enter.

- A global array tracks individual thread waiting times:
  - Thread-safe because each thread accesses only its own index.

---

## 📊 Analysis of Graph 1  
### Effect of Number of Customers on Average Waiting Time

- **General Trend:**  
  More customers → Higher waiting time  

- **Case 1:** More customers ⇒ more wait  
- **Case 2:** More delay between customer batches ⇒ *less* wait  

**Observations:**
- From **15 to 25 customers**: waiting time increases (Case 1 dominates).  
- From **25 to 30 customers**: waiting time decreases  
  - Because customers at 25 may have been created *much earlier* and waited longer.

---

## 📉 Analysis of Graph 2  
### Effect of Number of Tables on Waiting Time

- **General Trend:**  
  More tables → Less waiting time  

- **Case 1:** More tables ⇒ customers wait less  
- **Case 2:** Larger delay ⇒ customers wait less  

**Observations:**
- From **4 → 5 tables**: waiting time increases  
  - The batch for 5 tables may have been created earlier → more waiting.  
- From **5 → 6 tables**: sharp drop  
  - Benefit from both Case 1 and Case 2.  
- From **6 → 8 tables**: slow decrease  
  - Delay differences become negligible.

---

## 🧠 Key Concepts Demonstrated

- Mutual exclusion with mutex  
- Semaphore-based blocking and signaling  
- Fair resource allocation  
- Thread scheduling impact on waiting time  
- Real-world concurrency simulation model  

---

## 📁 File Description

| File | Description |
|------|-------------|
| `SrcAssgn4-CS19B1026.cpp` | Main implementation file |
| `input.txt` | Input parameters for simulation |
| `output-log.txt` | Generated output log |

---

## 🚀 Future Enhancements

- Priority scheduling (VIP customers)  
- Automatic graph plotting using Python  
- Grouped seating system (families, teams, etc.)  
- Real-time visualization of table usage  

---
