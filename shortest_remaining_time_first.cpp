// reference - https://www.geeksforgeeks.org/shortest-remaining-time-first-preemptive-sjf-scheduling-algorithm/

#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
    int ct;  // Completion Time
};

class Scheduler {
private:
    vector<Process> processes;
    vector<int> wt, tat;

public:
    void initializeProcesses() {
        int n;
        cout << "Enter number of processes: ";
        cin >> n;
        processes.resize(n);
        wt.resize(n);
        tat.resize(n);

        cout << "Enter Process ID, Burst Time and Arrival Time for each process:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "Process " << i + 1 << ": ";
            cin >> processes[i].pid >> processes[i].bt >> processes[i].art;
            processes[i].ct = 0;
        }
    }

    void findWaitingTime() {
        int n = processes.size();
        vector<int> rt(n);

        for (int i = 0; i < n; i++)
            rt[i] = processes[i].bt;

        int complete = 0, t = 0, minm = INT_MAX;
        int shortest = 0, finish_time;
        bool check = false;

        while (complete != n) {
            minm = INT_MAX;
            check = false;

            for (int j = 0; j < n; j++) {
                if ((processes[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                    minm = rt[j];
                    shortest = j;
                    check = true;
                }
            }

            if (check == false) {
                t++;
                continue;
            }

            rt[shortest]--;
            minm = rt[shortest];
            if (minm == 0)
                minm = INT_MAX;

            if (rt[shortest] == 0) {
                complete++;
                check = false;
                finish_time = t + 1;
                processes[shortest].ct = finish_time;
                wt[shortest] = finish_time - processes[shortest].bt - processes[shortest].art;
                if (wt[shortest] < 0)
                    wt[shortest] = 0;
            }
            t++;
        }
    }

    void findTurnAroundTime() {
        int n = processes.size();
        for (int i = 0; i < n; i++)
            tat[i] = processes[i].bt + wt[i];
    }

    void findavgTime() {
        int n = processes.size();
        int total_wt = 0, total_tat = 0;

        findWaitingTime();
        findTurnAroundTime();

        cout << "P\tBT\tAT\tCT\tWT\tTAT\n";
        for (int i = 0; i < n; i++) {
            total_wt += wt[i];
            total_tat += tat[i];
            cout << processes[i].pid << "\t" << processes[i].bt << "\t" << processes[i].art
                 << "\t" << processes[i].ct << "\t" << wt[i] << "\t" << tat[i] << endl;
        }

        cout << "\nAverage waiting time = " << (float)total_wt / n;
        cout << "\nAverage turn around time = " << (float)total_tat / n << endl;
    }

    void run() {
        initializeProcesses();
        findavgTime();
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
5
1 6 2
2 2 5
3 8 1
4 3 0
5 4 4

Output:
P	BT	AT	CT	WT	TAT
4	3	0	3	0	3
3	8	1	11	2	10
1	6	2	17	9	15
5	4	4	21	13	17
2	2	5	23	16	18

Average waiting time = 8
Average turn around time = 12.6

Explanation: Processes are executed based on the shortest remaining time first (SRTF) scheduling algorithm.

Test Case 2:
Input:
4
1 7 0
2 5 1
3 3 2
4 1 3

Output:
P	BT	AT	CT	WT	TAT
1	7	0	7	0	7
2	5	1	14	6	11
3	3	2	17	12	15
4	1	3	8	4	5

Average waiting time = 5.5
Average turn around time = 9.5

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.

Test Case 3:
Input:
3
1 4 0
2 3 1
3 2 2

Output:
P	BT	AT	CT	WT	TAT
1	4	0	4	0	4
2	3	1	8	4	7
3	2	2	10	6	8

Average waiting time = 3.33333
Average turn around time = 6.33333

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.

Test Case 4:
Input:
2
1 5 0
2 4 2

Output:
P	BT	AT	CT	WT	TAT
1	5	0	5	0	5
2	4	2	9	3	7

Average waiting time = 1.5
Average turn around time = 6

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.

Test Case 5:
Input:
3
1 6 0
2 8 1
3 7 2

Output:
P	BT	AT	CT	WT	TAT
1	6	0	6	0	6
2	8	1	14	5	13
3	7	2	21	12	19

Average waiting time = 5.66667
Average turn around time = 12.6667

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.

Test Case 6:
Input:
4
1 2 0
2 3 1
3 5 2
4 7 3

Output:
P	BT	AT	CT	WT	TAT
1	2	0	2	0	2
2	3	1	5	1	4
3	5	2	10	3	8
4	7	3	17	6	13

Average waiting time = 2.5
Average turn around time = 6.75

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.

Test Case 7:
Input:
5
1 4 0
2 2 2
3 1 3
4 3 5
5 5 6

Output:
P	BT	AT	CT	WT	TAT
1	4	0	4	0	4
2	2	2	6	2	4
3	1	3	7	3	4
4	3	5	10	5	8
5	5	6	15	9	14

Average waiting time = 3.8
Average turn around time = 6.8

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.

Test Case 8:
Input:
3
1 3 1
2 2 2
3 1 3

Output:
P	BT	AT	CT	WT	TAT
1	3	1	4	0	3
2	2	2	6	2	4
3	1	3	7	3	4

Average waiting time = 1.66667
Average turn around time = 3.66667

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.

Test Case 9:
Input:
4
1 6 0
2 5 1
3 4 2
4 3 3

Output:
P	BT	AT	CT	WT	TAT
1	6	0	6	0	6
2	5	1	12	6	11
3	4	2	16	10	14
4	3	3	19	13	16

Average waiting time = 7.25
Average turn around time = 11.75

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.

Test Case 10:
Input:
3
1 5 0
2 6 1
3 7 2

Output:
P	BT	AT	CT	WT	TAT
1	5	0	5	0	5
2	6	1	11	4	10
3	7	2	18	9	16

Average waiting time = 4.33333
Average turn around time = 10.3333

Explanation: SRTF scheduling algorithm is used for determining the order of process execution.
*/
