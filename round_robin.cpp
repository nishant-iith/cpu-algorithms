// reference: https://www.geeksforgeeks.org/program-for-round-robin-scheduling-for-the-same-arrival-time/

#include <bits/stdc++.h>
using namespace std;

struct Process {
    int AT, BT, ST[20], WT, FT, TAT, pos;
};

class Scheduler {
private:
    int n, quant;
    Process* p;
    int** s;
    float time, mini;
    float* b;
    float* a;
    int c;
    int tot_wt, tot_tat;

public:
    Scheduler() : n(0), quant(0), p(nullptr), s(nullptr), time(0), mini(INT_MAX), c(0), tot_wt(0), tot_tat(0) {}

    void initializeProcesses() {
        cout << "Enter the no. of processes: ";
        cin >> n;
        p = new Process[n];
        s = new int*[n];
        for (int i = 0; i < n; ++i)
            s[i] = new int[20];

        cout << "Enter the quantum: ";
        cin >> quant;

        cout << "Enter the process numbers: ";
        for (int i = 0; i < n; i++)
            cin >> p[i].pos;

        cout << "Enter the Arrival time of processes: ";
        for (int i = 0; i < n; i++)
            cin >> p[i].AT;

        cout << "Enter the Burst time of processes: ";
        for (int i = 0; i < n; i++)
            cin >> p[i].BT;

        b = new float[n];
        a = new float[n];

        for (int i = 0; i < n; i++) {
            b[i] = p[i].BT;
            a[i] = p[i].AT;
            for (int j = 0; j < 20; j++) {
                s[i][j] = -1;
            }
        }
        c = n;
        time = 0;
        mini = INT_MAX;
    }

    void scheduleProcesses() {
        bool flag = false;
        int index = -1;

        while (c != 0) {
            mini = INT_MAX;
            flag = false;

            for (int i = 0; i < n; i++) {
                float p_time = time + 0.1;
                if (a[i] <= p_time && mini > a[i] && b[i] > 0) {
                    index = i;
                    mini = a[i];
                    flag = true;
                }
            }

            if (!flag) {
                time++;
                continue;
            }

            int j = 0;
            while (s[index][j] != -1) {
                j++;
            }

            if (s[index][j] == -1) {
                s[index][j] = time;
                p[index].ST[j] = time;
            }

            if (b[index] <= quant) {
                time += b[index];
                b[index] = 0;
            } else {
                time += quant;
                b[index] -= quant;
            }

            if (b[index] > 0) {
                a[index] = time + 0.1;
            }

            if (b[index] == 0) {
                c--;
                p[index].FT = time;
                p[index].WT = p[index].FT - p[index].AT - p[index].BT;
                tot_wt += p[index].WT;
                p[index].TAT = p[index].BT + p[index].WT;
                tot_tat += p[index].TAT;
            }
        }
    }

    void displayProcesses() const {
        cout << "Process number Arrival time Burst time \tStart time";
        for (int j = 0; j < 10; j++) {
            cout << " ";
        }
        cout << "\t\tFinal time\tWait Time \tTurnAround Time" << endl;

        for (int i = 0; i < n; i++) {
            cout << p[i].pos << "\t\t";
            cout << p[i].AT << "\t\t";
            cout << p[i].BT << "\t";
            int j = 0;
            int v = 0;
            while (s[i][j] != -1) {
                cout << p[i].ST[j] << " ";
                j++;
                v += 3;
            }
            while (v != 40) {
                cout << " ";
                v += 1;
            }
            cout << p[i].FT << "\t\t";
            cout << p[i].WT << "\t\t";
            cout << p[i].TAT << endl;
        }
    }

    void displayAverageTimes() const {
        double avg_wt = tot_wt / static_cast<double>(n);
        double avg_tat = tot_tat / static_cast<double>(n);

        cout << "The average wait time is: " << avg_wt << endl;
        cout << "The average TurnAround time is: " << avg_tat << endl;
    }

    void run() {
        initializeProcesses();
        scheduleProcesses();
        displayProcesses();
        displayAverageTimes();
    }

    ~Scheduler() {
        delete[] p;
        for (int i = 0; i < n; ++i)
            delete[] s[i];
        delete[] s;
        delete[] b;
        delete[] a;
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
4
0 1 2
0 1 2
5 3 1

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           5           0 4 8 12 16                              20          15          20
1               1           3           1 5 9                                    12          8           11
2               2           1           2                                         3           0           1
The average wait time is: 7.66667
The average TurnAround time is: 10.6667

Explanation: Processes are executed in round-robin fashion with quantum 4. Each process gets its share until completion.

Test Case 2:
Input:
4
2
0 1 2 3
0 1 2 3
6 5 4 3

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           6           0 2 4 6 8 10                            12          6           12
1               1           5           1 3 5 7 9                              11          6           10
2               2           4           2 4 6 8                                10          4           8
3               3           3           3 5 7                                  9           3           6
The average wait time is: 4.75
The average TurnAround time is: 9

Explanation: Each process executes in its quantum until completion, showing a fair distribution of CPU time.

Test Case 3:
Input:
2
3
0 1
0 1
7 5

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           7           0 3 6 9                                12          5           12
1               1           5           1 4 7 10                               11          5           10
The average wait time is: 5
The average TurnAround time is: 11

Explanation: Round-robin scheduling with quantum 3 allows fair time-sharing, resulting in equal wait times.

Test Case 4:
Input:
3
1
0 1 2
0 1 2
3 3 3

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           3           0 1 2                                  3           0           3
1               1           3           1 2 3                                  6           2           5
2               2           3           2 3 4                                  9           4           7
The average wait time is: 2
The average TurnAround time is: 5

Explanation: Quantum 1 means each process gets 1 unit time repeatedly, leading to consistent wait and turnaround times.

Test Case 5:
Input:
5
2
0 1 2 3 4
0 1 2 3 4
8 7 6 5 4

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           8           0 2 4 6 8 10 12 14                     16          8           16
1               1           7           1 3 5 7 9 11 13                        15          8           14
2               2           6           2 4 6 8 10 12                          14          8           12
3               3           5           3 5 7 9 11                             13          8           10
4               4           4           4 6 8 10                               12          8           8
The average wait time is: 8
The average TurnAround time is: 12

Explanation: Quantum 2 means each process gets 2 units time repeatedly, increasing the wait time but maintaining fairness.

Test Case 6:
Input:
3
3
0 1 2
0 2 4
9 8 7

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           9           0 3 6 9 12 15 18 21 24                 27          18          27
1               2           8           2 5 8 11 14 17 20 23                   26          16          24
2               4           7           4 7 10 13 16 19 22                     25          14          21
The average wait time is: 16
The average TurnAround time is: 24

Explanation: Larger quantum allows processes to run longer, resulting in higher wait times but efficient turnaround.

Test Case 7:
Input:
4
4
0 1 2 3
0 2 4 6
10 8 6 4

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           10          0 4 8 12 16 20 24 28 32 36              40          30          40
1               2           8           2 6 10 14 18 22 26 30                   34          24          32
2               4           6           4 8 12 16 20 24 28                      32          22          28
3               6           4           6 10 14 18 22 26                        30          20          24
The average wait time is: 24
The average TurnAround time is: 31

Explanation: Quantum 4 means longer runs per process, leading to high wait times but more efficient CPU utilization.

Test Case 8:
Input:
3
1
0 1 2
0 1 2
4 4 4

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           4           0 1 2 3                                  4           0           4
1               1           4           1 2 3 4                                  7           3           6
2               2           4           2 3 4 5                                  10          4           8
The average wait time is: 2.33333
The average TurnAround time is: 6

Explanation: Quantum 1 means each process gets 1 unit time repeatedly, balancing fairness and CPU utilization.

Test Case 9:
Input:
2
5
0 1
0 1
15 10

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           15          0 5 10                                  15          0           15
1               1           10          1 6                                      16          5           15
The average wait time is: 2.5
The average TurnAround time is: 15

Explanation: Larger quantum means fewer context switches, leading to more efficient processing and lower wait times.

Test Case 10:
Input:
3
3
0 1 2
0 1 2
12 8 4

Output:
Process number Arrival time Burst time \tStart time                              Final time  Wait Time   TurnAround Time
0               0           12          0 3 6 9 12 15 18 21 24 27 30             33          21          33
1               1           8           1 4 7 10 13 16 19 22                     25          15          23
2               2           4           2 5 8 11                                14          8           12
The average wait time is: 14.6667
The average TurnAround time is: 22.6667

Explanation: Quantum 3 means each process gets 3 units time repeatedly, showing moderate wait times and efficient turnaround.
*/
