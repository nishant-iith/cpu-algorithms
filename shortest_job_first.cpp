// reference - https://www.geeksforgeeks.org/program-for-shortest-job-first-or-sjf-cpu-scheduling-set-1-non-preemptive/

#include <bits/stdc++.h>
using namespace std;

class Scheduler {
private:
    int A[100][4];
    int n;
    float avg_wt, avg_tat;

public:
    Scheduler() : n(0), avg_wt(0.0), avg_tat(0.0) {}

    void initializeProcesses() {
        cout << "Enter number of processes: ";
        cin >> n;

        cout << "Enter Burst Time:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "P" << i + 1 << ": ";
            cin >> A[i][1];
            A[i][0] = i + 1;
        }

        // Sorting process according to their Burst Time.
        for (int i = 0; i < n; i++) {
            int index = i;
            for (int j = i + 1; j < n; j++) {
                if (A[j][1] < A[index][1]) {
                    index = j;
                }
            }
            swap(A[i][1], A[index][1]);
            swap(A[i][0], A[index][0]);
        }
    }

    void calculateMetrics() {
        int total = 0;

        A[0][2] = 0;
        for (int i = 1; i < n; i++) {
            A[i][2] = 0;
            for (int j = 0; j < i; j++) {
                A[i][2] += A[j][1];
            }
            total += A[i][2];
        }

        avg_wt = static_cast<float>(total) / n;
        total = 0;

        for (int i = 0; i < n; i++) {
            A[i][3] = A[i][1] + A[i][2];
            total += A[i][3];
        }

        avg_tat = static_cast<float>(total) / n;
    }

    void displayProcesses() const {
        cout << "P\tBT\tWT\tTAT" << endl;
        for (int i = 0; i < n; i++) {
            cout << "P" << A[i][0] << "\t" << A[i][1] << "\t" << A[i][2] << "\t" << A[i][3] << endl;
        }
        cout << "Average Waiting Time= " << avg_wt << endl;
        cout << "Average Turnaround Time= " << avg_tat << endl;
    }

    void run() {
        initializeProcesses();
        calculateMetrics();
        displayProcesses();
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
4
7
P1: 6
P2: 8
P3: 7
P4: 3

Output:
P	BT	WT	TAT
P4	3	0	3
P1	6	3	9
P3	7	9	16
P2	8	16	24
Average Waiting Time= 7
Average Turnaround Time= 13

Explanation: Processes are sorted by burst time, with WT and TAT calculated accordingly.

Test Case 2:
Input:
5
5
P1: 2
P2: 4
P3: 1
P4: 3
P5: 5

Output:
P	BT	WT	TAT
P3	1	0	1
P1	2	1	3
P4	3	3	6
P2	4	6	10
P5	5	10	15
Average Waiting Time= 4
Average Turnaround Time= 7

Explanation: Shortest job first scheduling minimizes average wait time and turnaround time.

Test Case 3:
Input:
3
4
P1: 10
P2: 5
P3: 8

Output:
P	BT	WT	TAT
P2	5	0	5
P3	8	5	13
P1	10	13	23
Average Waiting Time= 6
Average Turnaround Time= 13.6667

Explanation: Processes are scheduled by burst time, leading to reduced average wait and turnaround times.

Test Case 4:
Input:
4
6
P1: 4
P2: 3
P3: 2
P4: 1

Output:
P	BT	WT	TAT
P4	1	0	1
P3	2	1	3
P2	3	3	6
P1	4	6	10
Average Waiting Time= 2.5
Average Turnaround Time= 5

Explanation: Processes with shortest burst times execute first, optimizing wait and turnaround times.

Test Case 5:
Input:
3
3
P1: 9
P2: 6
P3: 4

Output:
P	BT	WT	TAT
P3	4	0	4
P2	6	4	10
P1	9	10	19
Average Waiting Time= 4.66667
Average Turnaround Time= 11

Explanation: Short burst times are prioritized, lowering the average wait and turnaround times.

Test Case 6:
Input:
5
5
P1: 5
P2: 3
P3: 8
P4: 6
P5: 2

Output:
P	BT	WT	TAT
P5	2	0	2
P2	3	2	5
P1	5	5	10
P4	6	10	16
P3	8	16	24
Average Waiting Time= 6.6
Average Turnaround Time= 11.4

Explanation: Processes are executed based on burst time, leading to minimized average wait and turnaround times.

Test Case 7:
Input:
2
2
P1: 7
P2: 5

Output:
P	BT	WT	TAT
P2	5	0	5
P1	7	5	12
Average Waiting Time= 2.5
Average Turnaround Time= 8.5

Explanation: Shortest job first scheduling results in efficient wait and turnaround times.

Test Case 8:
Input:
3
3
P1: 6
P2: 4
P3: 5

Output:
P	BT	WT	TAT
P2	4	0	4
P3	5	4	9
P1	6	9	15
Average Waiting Time= 4.33333
Average Turnaround Time= 9.33333

Explanation: Processes are scheduled by burst time, reducing the average wait and turnaround times.

Test Case 9:
Input:
4
4
P1: 8
P2: 3
P3: 5
P4: 2

Output:
P	BT	WT	TAT
P4	2	0	2
P2	3	2	5
P3	5	5	10
P1	8	10	18
Average Waiting Time= 4.25
Average Turnaround Time= 8.75

Explanation: Processes with shortest burst times execute first, optimizing wait and turnaround times.

Test Case 10:
Input:
5
5
P1: 2
P2: 1
P3: 4
P4: 6
P5: 8

Output:
P	BT	WT	TAT
P2	1	0	1
P1	2	1	3
P3	4	3	7
P4	6	7	13
P5	8	13	21
Average Waiting Time= 4.8
Average Turnaround Time= 9

Explanation: Short burst times are prioritized, lowering the average wait and turnaround times.
*/
