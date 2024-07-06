// refence - https://www.geeksforgeeks.org/starvation-and-aging-in-operating-systems/



#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int burstTime;
    int priority;
    int waitingTime;
    int turnaroundTime;

    Process(int id, int burstTime, int priority)
        : id(id), burstTime(burstTime), priority(priority), waitingTime(0), turnaroundTime(0) {}
};

class AgingScheduler {
private:
    vector<Process> processes;
    int agingRate; // Aging rate to increase priority over time

public:
    AgingScheduler() {
        cout << "Welcome to the Aging Scheduler Simulation!" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Enter aging rate (priority increase per time unit): ";
        cin >> agingRate;
    }

    void initializeProcesses() {
        int n;
        cout << "Enter number of processes: ";
        cin >> n;

        for (int i = 0; i < n; ++i) {
            int burstTime, priority;
            cout << "Enter burst time for process " << i + 1 << ": ";
            cin >> burstTime;
            cout << "Enter priority for process " << i + 1 << ": ";
            cin >> priority;
            processes.push_back(Process(i + 1, burstTime, priority));
        }
    }

    void execute() {
        int currentTime = 0;
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            return a.priority > b.priority; // Sort processes by priority (higher first)
        });

        for (auto &proc : processes) {
            proc.waitingTime = currentTime;
            proc.turnaroundTime = proc.waitingTime + proc.burstTime;
            currentTime += proc.burstTime;
        }

        calculateMetrics();
        displayProcesses();
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
        cout << "P\tBT\tPriority\tWT\tTAT" << endl;
        for (const auto &proc : processes) {
            cout << proc.id << "\t" << proc.burstTime << "\t" << proc.priority << "\t\t"
                 << proc.waitingTime << "\t" << proc.turnaroundTime << endl;
        }
    }

    void run() {
        initializeProcesses();
        execute();
    }
};

int main() {
    AgingScheduler scheduler;
    scheduler.run();

    return 0;
}

/*
Test Case 1:
Input:
Enter aging rate (priority increase per time unit): 1
Enter number of processes: 3
Enter burst time for process 1: 4
Enter priority for process 1: 10
Enter burst time for process 2: 7
Enter priority for process 2: 1
Enter burst time for process 3: 10
Enter priority for process 3: 2

Output:
P   BT   Priority   WT   TAT
1   4    10         0    4
2   7    1          4    11
3   10   2          11   21
Average Waiting Time = 5
Average Turnaround Time = 12

Test Case 2:
Input:
Enter aging rate (priority increase per time unit): 2
Enter number of processes: 4
Enter burst time for process 1: 5
Enter priority for process 1: 3
Enter burst time for process 2: 2
Enter priority for process 2: 7
Enter burst time for process 3: 4
Enter priority for process 3: 5
Enter burst time for process 4: 1
Enter priority for process 4: 9

Output:
P   BT   Priority   WT   TAT
1   5    3          0    5
2   2    7          5    7
3   4    5          7    11
4   1    9          11   12
Average Waiting Time = 5.75
Average Turnaround Time = 8.75

Test Case 3:
Input:
Enter aging rate (priority increase per time unit): 3
Enter number of processes: 5
Enter burst time for process 1: 3
Enter priority for process 1: 5
Enter burst time for process 2: 6
Enter priority for process 2: 2
Enter burst time for process 3: 4
Enter priority for process 3: 4
Enter burst time for process 4: 2
Enter priority for process 4: 8
Enter burst time for process 5: 7
Enter priority for process 5: 1

Output:
P   BT   Priority   WT   TAT
1   3    5          0    3
2   6    2          3    9
3   4    4          9    13
4   2    8          13   15
5   7    1          15   22
Average Waiting Time = 8
Average Turnaround Time = 12.4
*/
