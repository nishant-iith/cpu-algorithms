// refernce: https://www.geeksforgeeks.org/program-for-fcfs-cpu-scheduling-set-1/

#include <bits/stdc++.h>
using namespace std;

class Process {
private:
    int pid, at, bt, ct, tat, wt;

public:
    Process(int id, int arrival, int burst)
        : pid(id), at(arrival), bt(burst), ct(0), tat(0), wt(0) {}

    void calculateCompletionTime(int prev_ct) {
        ct = max(at, prev_ct) + bt;
    }

    void calculateMetrics() {
        tat = ct - at;
        wt = tat - bt;
    }

    void display() const {
        cout << pid << "\t" << at << "\t" << bt << "\t" << ct << "\t" << tat << "\t" << wt << endl;
    }

    static bool compareByArrival(const Process& a, const Process& b) {
        return a.at < b.at;
    }

    int getAT() const { return at; }
    int getCT() const { return ct; }
    int getWT() const { return wt; }
};

class Scheduler {
private:
    vector<Process> processes;

public:
    void initializeProcesses() {
        int n, at, bt;
        cout << "Enter number of processes: ";
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cout << "Enter arrival and burst times for process " << i + 1 << ": ";
            cin >> at >> bt;
            processes.emplace_back(i, at, bt);
        }
    }

    void scheduleProcesses() {
        sort(processes.begin(), processes.end(), Process::compareByArrival);
        if (!processes.empty()) {
            processes[0].calculateCompletionTime(processes[0].getAT());
            processes[0].calculateMetrics();
        }
        for (size_t i = 1; i < processes.size(); ++i) {
            processes[i].calculateCompletionTime(processes[i-1].getCT());
            processes[i].calculateMetrics();
        }
    }

    void displayProcesses() const {
        cout << "pid\tat\tbt\tct\ttat\twt\n";
        for (const auto& p : processes) {
            p.display();
        }
    }

    void displayAverageWaitingTime() const {
        float avg_wt = 0;
        for (const auto& p : processes) {
            avg_wt += p.getWT();
        }
        avg_wt /= processes.size();
        cout << "Average waiting time: " << avg_wt << endl;
    }

    void run() {
        initializeProcesses();
        scheduleProcesses();
        displayProcesses();
        displayAverageWaitingTime();
    }
};

int main() {
    Scheduler scheduler;
    scheduler.run();
    return 0;
}


/*
Test Case 1:
Input:
3
0 5
1 3
2 8

Output:
pid	at	bt	ct	tat	wt
0	0	5	5	5	0
1	1	3	8	7	4
2	2	8	16	14	6
Average waiting time: 3.33333

Explanation: Processes are scheduled in order of their arrival times. Process 0 finishes at time 5, Process 1 finishes at time 8, and Process 2 finishes at time 16.

Test Case 2:
Input:
4
0 4
1 2
2 3
3 1

Output:
pid	at	bt	ct	tat	wt
0	0	4	4	4	0
1	1	2	6	5	3
2	2	3	9	7	4
3	3	1	10	7	6
Average waiting time: 3.25

Explanation: Each process completes in the order of arrival with respective burst times.

Test Case 3:
Input:
5
0 2
2 4
4 6
6 8
8 10

Output:
pid	at	bt	ct	tat	wt
0	0	2	2	2	0
1	2	4	6	4	0
2	4	6	12	8	2
3	6	8	20	14	6
4	8	10	30	22	12
Average waiting time: 4

Explanation: Processes execute sequentially based on their arrival and burst times, resulting in increasing waiting times.

Test Case 4:
Input:
2
0 1
0 2

Output:
pid	at	bt	ct	tat	wt
0	0	1	1	1	0
1	0	2	3	3	1
Average waiting time: 0.5

Explanation: Both processes arrive at the same time. Process 0 executes first, followed by Process 1.

Test Case 5:
Input:
3
0 6
1 4
2 2

Output:
pid	at	bt	ct	tat	wt
0	0	6	6	6	0
1	1	4	10	9	5
2	2	2	12	10	8
Average waiting time: 4.33333

Explanation: Processes execute in arrival order with varying burst times leading to different waiting times.

Test Case 6:
Input:
3
0 3
2 3
4 3

Output:
pid	at	bt	ct	tat	wt
0	0	3	3	3	0
1	2	3	6	4	1
2	4	3	9	5	2
Average waiting time: 1

Explanation: Processes arrive at intervals of 2 and execute sequentially.

Test Case 7:
Input:
4
0 3
0 2
0 1
0 4

Output:
pid	at	bt	ct	tat	wt
0	0	3	3	3	0
1	0	2	5	5	3
2	0	1	6	6	5
3	0	4	10	10	6
Average waiting time: 3.5

Explanation: All processes arrive simultaneously, so they execute based on their position.

Test Case 8:
Input:
4
1 3
2 2
3 1
4 4

Output:
pid	at	bt	ct	tat	wt
0	1	3	4	3	0
1	2	2	6	4	2
2	3	1	7	4	3
3	4	4	11	7	3
Average waiting time: 2

Explanation: Processes arrive sequentially with gaps, resulting in incremental waiting times.

Test Case 9:
Input:
5
0 5
2 3
4 1
6 7
8 2

Output:
pid	at	bt	ct	tat	wt
0	0	5	5	5	0
1	2	3	8	6	3
2	4	1	9	5	4
3	6	7	16	10	3
4	8	2	18	10	8
Average waiting time: 3.6

Explanation: Processes execute based on arrival time with varying burst times.

Test Case 10:
Input:
3
0 10
5 3
9 4

Output:
pid	at	bt	ct	tat	wt
0	0	10	10	10	0
1	5	3	13	8	5
2	9	4	17	8	4
Average waiting time: 3

Explanation: Process 0 occupies the CPU for a long time before the others get a turn.
*/