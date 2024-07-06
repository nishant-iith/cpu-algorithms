// reference : https://www.geeksforgeeks.org/highest-response-ratio-next-hrrn-cpu-scheduling/

#include <bits/stdc++.h>
using namespace std;

// Defining process details
struct Process {
    char name;
    int at, bt, ct, wt, tt;
    int completed;
    float ntt;
};

class Scheduler {
private:
    vector<Process> processes;
    int n;
    float avgwt, avgtt;

public:
    Scheduler() : n(0), avgwt(0), avgtt(0) {}

    void initializeProcesses() {
        cout << "Enter number of processes: ";
        cin >> n;
        processes.resize(n);

        cout << "Enter Arrival Time and Burst Time for each process:" << endl;
        for (int i = 0; i < n; i++) {
            processes[i].name = 'A' + i;
            cout << "Process " << processes[i].name << ": ";
            cin >> processes[i].at >> processes[i].bt;
            processes[i].completed = 0;
        }
    }

    void sortByArrival() {
        sort(processes.begin(), processes.end(), [](Process &a, Process &b) {
            return a.at < b.at;
        });
    }

    void scheduleProcesses() {
        sortByArrival();
        int sum_bt = accumulate(processes.begin(), processes.end(), 0, [](int sum, Process &p) {
            return sum + p.bt;
        });

        float t = processes[0].at;

        cout << "PN\tAT\tBT\tWT\tTAT\tNTT\n";
        while (any_of(processes.begin(), processes.end(), [](Process &p) { return p.completed == 0; })) {
            float hrr = -9999;
            int loc = -1;

            for (int i = 0; i < n; i++) {
                if (processes[i].at <= t && processes[i].completed == 0) {
                    float temp = (processes[i].bt + (t - processes[i].at)) / static_cast<float>(processes[i].bt);
                    if (hrr < temp) {
                        hrr = temp;
                        loc = i;
                    }
                }
            }

            if (loc != -1) {
                t += processes[loc].bt;
                processes[loc].ct = t;
                processes[loc].wt = processes[loc].ct - processes[loc].at - processes[loc].bt;
                processes[loc].tt = processes[loc].ct - processes[loc].at;
                processes[loc].ntt = (float)processes[loc].tt / processes[loc].bt;
                processes[loc].completed = 1;
                avgwt += processes[loc].wt;
                avgtt += processes[loc].tt;

                cout << processes[loc].name << "\t" << processes[loc].at << "\t" << processes[loc].bt << "\t"
                     << processes[loc].wt << "\t" << processes[loc].tt << "\t" << processes[loc].ntt << endl;
            } else {
                t++;
            }
        }

        avgwt /= n;
        avgtt /= n;
        cout << "\nAverage waiting time: " << avgwt << endl;
        cout << "Average Turn Around time: " << avgtt << endl;
    }

    void run() {
        initializeProcesses();
        scheduleProcesses();
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
0 3
2 6
4 4
6 5
8 2

Output:
PN	AT	BT	WT	TAT	NTT
A	0	3	0	3	1
B	2	6	3	9	1.5
C	4	4	5	9	2.25
D	6	5	9	14	2.8
E	8	2	14	16	8

Average waiting time: 6.2
Average Turn Around time: 10.2

Explanation: Processes are scheduled based on the highest response ratio next (HRRN) scheduling algorithm.

Test Case 2:
Input:
4
0 7
2 4
4 1
5 4

Output:
PN	AT	BT	WT	TAT	NTT
A	0	7	0	7	1
B	2	4	5	9	2.25
C	4	1	11	12	12
D	5	4	12	16	4

Average waiting time: 7
Average Turn Around time: 11

Explanation: Processes are scheduled based on the highest response ratio next (HRRN) scheduling algorithm.

Test Case 3:
Input:
3
0 4
1 3
2 2

Output:
PN	AT	BT	WT	TAT	NTT
A	0	4	0	4	1
B	1	3	3	6	2
C	2	2	6	8	4

Average waiting time: 3
Average Turn Around time: 6

Explanation: Processes are scheduled based on the highest response ratio next (HRRN) scheduling algorithm.

Test Case 4:
Input:
2
0 5
1 3

Output:
PN	AT	BT	WT	TAT	NTT
A	0	5	0	5	1
B	1	3	4	7	2.33333

Average waiting time: 2
Average Turn Around time: 6

Explanation: Processes are scheduled based on the highest response ratio next (HRRN) scheduling algorithm.

Test Case 5:
Input:
4
0 6
1 5
2 8
3 4

Output:
PN	AT	BT	WT	TAT	NTT
A	0	6	0	6	1
B	1	5	5	10	2
C	2	8	10	18	2.25
D	3	4	17	21	5.25

Average waiting time: 8
Average Turn Around time: 13.75

Explanation: Processes are scheduled based on the highest response ratio next (HRRN) scheduling algorithm.
*/
