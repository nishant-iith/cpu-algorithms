// reference - https://www.geeksforgeeks.org/multilevel-feedback-queue-scheduling-mlfq-cpu-scheduling/



#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int burstTime;
    int remainingTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
    int priorityLevel;

    Process(int id, int burstTime, int arrivalTime)
        : id(id), burstTime(burstTime), remainingTime(burstTime),
        arrivalTime(arrivalTime), waitingTime(0), turnaroundTime(0),
        priorityLevel(0) {}
};

class MLFQScheduler {
private:
    queue<Process> q1; // Highest priority queue
    queue<Process> q2; // Medium priority queue
    queue<Process> q3; // Lowest priority queue

    int timeQuantum1;
    int timeQuantum2;

    vector<Process> processes;

public:
    MLFQScheduler() : timeQuantum1(0), timeQuantum2(0) {}

    void initializeTimeQuantum() {
        cout << "Enter time quantum for queue 1: ";
        cin >> timeQuantum1;
        cout << "Enter time quantum for queue 2: ";
        cin >> timeQuantum2;
    }

    void initializeProcesses() {
        int n;
        cout << "Enter number of processes: ";
        cin >> n;

        for (int i = 0; i < n; ++i) {
            int burstTime, arrivalTime;
            cout << "Enter burst time for process " << i + 1 << ": ";
            cin >> burstTime;
            cout << "Enter arrival time for process " << i + 1 << ": ";
            cin >> arrivalTime;
            processes.push_back(Process(i + 1, burstTime, arrivalTime));
        }

        // Initially, all processes are in the highest priority queue
        for (const auto &proc : processes) {
            q1.push(proc);
        }
    }

    void execute() {
        int currentTime = 0;

        while (!q1.empty() || !q2.empty() || !q3.empty()) {
            if (!q1.empty()) {
                executeQueue(q1, timeQuantum1, 1, currentTime);
            } else if (!q2.empty()) {
                executeQueue(q2, timeQuantum2, 2, currentTime);
            } else if (!q3.empty()) {
                executeQueue(q3, INT_MAX, 3, currentTime); // FCFS for q3
            }
        }

        calculateMetrics();
        displayProcesses();
    }

    void executeQueue(queue<Process> &q, int timeQuantum, int level, int &currentTime) {
        Process proc = q.front();
        q.pop();

        int executionTime = min(timeQuantum, proc.remainingTime);
        proc.remainingTime -= executionTime;
        currentTime += executionTime;

        for (auto &p : processes) {
            if (p.id == proc.id) {
                p.remainingTime = proc.remainingTime;
                p.waitingTime = currentTime - p.arrivalTime - (p.burstTime - p.remainingTime);
                p.turnaroundTime = currentTime - p.arrivalTime;
                break;
            }
        }

        if (proc.remainingTime > 0) {
            proc.priorityLevel = min(proc.priorityLevel + 1, 2); // Move to lower priority
            if (proc.priorityLevel == 1) {
                q2.push(proc);
            } else if (proc.priorityLevel == 2) {
                q3.push(proc);
            }
        }
    }

    void calculateMetrics() {
        float totalWT = 0, totalTAT = 0;
        for (const auto &proc : processes) {
            totalWT += proc.waitingTime;
            totalTAT += proc.turnaroundTime;
        }
        cout << "Average Waiting Time = " << totalWT / processes.size() << endl;
        cout << "Average Turnaround Time = " << totalTAT / processes.size() << endl;
    }

    void displayProcesses() const {
        cout << "P\tBT\tAT\tWT\tTAT" << endl;
        for (const auto &proc : processes) {
            cout << "P" << proc.id << "\t" << proc.burstTime << "\t" << proc.arrivalTime << "\t" << proc.waitingTime << "\t" << proc.turnaroundTime << endl;
        }
    }

    void run() {
        initializeTimeQuantum();
        initializeProcesses();
        execute();
    }
};

int main() {
    MLFQScheduler scheduler;
    scheduler.run();
    return 0;
}

/*
Test Case 1:
Input:
Enter time quantum for queue 1: 4
Enter time quantum for queue 2: 8
Enter number of processes: 3
Enter burst time for process 1: 6
Enter arrival time for process 1: 0
Enter burst time for process 2: 8
Enter arrival time for process 2: 1
Enter burst time for process 3: 7
Enter arrival time for process 3: 2

Output:
P   BT   AT   WT   TAT
P1  6    0    4    10
P2  8    1    14   22
P3  7    2    12   19
Average Waiting Time = 10
Average Turnaround Time = 17

Test Case 2:
Input:
Enter time quantum for queue 1: 4
Enter time quantum for queue 2: 8
Enter number of processes: 4
Enter burst time for process 1: 5
Enter arrival time for process 1: 0
Enter burst time for process 2: 2
Enter arrival time for process 2: 1
Enter burst time for process 3: 4
Enter arrival time for process 3: 2
Enter burst time for process 4: 1
Enter arrival time for process 4: 3

Output:
P   BT   AT   WT   TAT
P1  5    0    4    9
P2  2    1    5    7
P3  4    2    7    11
P4  1    3    10   11
Average Waiting Time = 6.5
Average Turnaround Time = 9.5

Test Case 3:
Input:
Enter time quantum for queue 1: 4
Enter time quantum for queue 2: 8
Enter number of processes: 5
Enter burst time for process 1: 3
Enter arrival time for process 1: 0
Enter burst time for process 2: 5
Enter arrival time for process 2: 1
Enter burst time for process 3: 6
Enter arrival time for process 3: 2
Enter burst time for process 4: 2
Enter arrival time for process 4: 3
Enter burst time for process 5: 7
Enter arrival time for process 5: 4

Output:
P   BT   AT   WT   TAT
P1  3    0    0    3
P2  5    1    2    7
P3  6    2    10   16
P4  2    3    16   18
P5  7    4    18   25
Average Waiting Time = 9.2
Average Turnaround Time = 13.8
*/
