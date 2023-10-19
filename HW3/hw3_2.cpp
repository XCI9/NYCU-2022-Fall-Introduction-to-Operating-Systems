#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Process {
    int id{ 0 };
    int arrivalTime{ 0 };
    int timeLeft{ 0 };

    int finishTime{ 0 };
    int burstTime{ 0 };

    bool operator<(const Process& p) const {
        return timeLeft > p.timeLeft;
    }
};

class RoundRobin {
    const int m_timeQuantum;
    int m_currentTimeQuantum;
    std::queue<Process> m_waitingQueue;
    Process m_currentProcess{};
    bool m_isIdle{ true };

    std::vector<int> m_executionRecord;

  public:
    RoundRobin(int timeQuantum) : m_currentTimeQuantum{ timeQuantum },
                                  m_timeQuantum{ timeQuantum } {}

    void newProcessArrived(Process process) {
        m_waitingQueue.push(process);
    }

    // return is show if there are process running
    bool loop(std::vector<Process>& finishedProcess, const int currentTime) {
        // current process run out of time quantum
        if (m_currentTimeQuantum == 0) {
            m_waitingQueue.push(m_currentProcess);
            m_currentTimeQuantum = m_timeQuantum;
            m_isIdle = true;
        }

        if (m_isIdle && m_waitingQueue.empty())
            return false;
        else if (m_isIdle) {
            m_currentProcess = m_waitingQueue.front();
            m_waitingQueue.pop();
            m_isIdle = false;
        }

        m_executionRecord.push_back(m_currentProcess.id + 1);
        m_currentProcess.timeLeft -= 1;
        m_currentTimeQuantum--;

        // current process finish
        if (m_currentProcess.timeLeft == 0) {
            m_currentProcess.finishTime = currentTime + 1;
            finishedProcess.push_back(m_currentProcess);
            m_isIdle = true;
            m_currentTimeQuantum = m_timeQuantum;
            return true;
        }

        return true;
    }

    // print the queue status for debug
    void visualization() {
        printf("%.*s\n", m_executionRecord.size() * 2 + 1, "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");
        printf("|%d", m_executionRecord[0]);
        for (int i{ 1 }; i < m_executionRecord.size(); i++) {
            if (m_executionRecord[i] != m_executionRecord[i - 1])
                printf("|%d", m_executionRecord[i]);
            else
                printf("  ");
        }
        printf("|\n");
        printf("%.*s\n", m_executionRecord.size() * 2 + 1, "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");
    }
};

int main() {
    int processCount;

    std::cin >> processCount;
    std::vector<Process> process(processCount);

    for (int i{ 0 }; i < processCount; i++) {
        std::cin >> process[i].arrivalTime;
        process[i].id = i;
    }

    for (int i{ 0 }; i < processCount; i++) {
        std::cin >> process[i].timeLeft;
        process[i].burstTime = process[i].timeLeft;
    }

    int timeQuantum;
    std::cin >> timeQuantum;

    RoundRobin scheduler{ timeQuantum };

    std::sort(process.begin(), process.end(), [](const Process& p1, const Process& p2) { return p1.arrivalTime > p2.arrivalTime; });

    std::vector<Process> finishProcess;
    finishProcess.reserve(processCount);

    int currentTime{ 0 };
    bool isRunning{ false };
    // stimulation
    while (1) {
        if (!process.empty() && process.back().arrivalTime == currentTime) {
            scheduler.newProcessArrived(process.back());
            process.pop_back();
        }

        isRunning = scheduler.loop(finishProcess, currentTime);

        currentTime++;
        if (!isRunning && process.empty())
            break;
    }

    std::sort(finishProcess.begin(), finishProcess.end(), [](const Process& p1, const Process& p2) { return p1.id < p2.id; });

    // show queue for debug
    // scheduler.visualization();

    int totalWaitingTime{ 0 }, totalTurnaroundTime{ 0 };
    for (const auto& p : finishProcess) {
        int waitingTime{ p.finishTime - p.arrivalTime - p.burstTime };
        int turnaroundTime{ p.finishTime - p.arrivalTime };
        totalWaitingTime += waitingTime;
        totalTurnaroundTime += turnaroundTime;
        std::cout << waitingTime << " " << turnaroundTime << "\n";
    }
    std::cout << totalWaitingTime << "\n";
    std::cout << totalTurnaroundTime << "\n";

    return 0;
}