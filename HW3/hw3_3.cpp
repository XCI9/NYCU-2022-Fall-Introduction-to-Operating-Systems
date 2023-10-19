#include <algorithm>
#include <iostream>
#include <queue>

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
        if (m_isIdle && m_waitingQueue.empty()) {
            m_executionRecord.push_back(0);
            return false;
        } else if (m_isIdle) {
            m_currentProcess = m_waitingQueue.front();
            m_waitingQueue.pop();
            m_isIdle = false;
        }

        m_currentProcess.timeLeft -= 1;
        m_currentTimeQuantum--;

        m_executionRecord.push_back(m_currentProcess.id + 1);

        // current process finish
        if (m_currentProcess.timeLeft == 0) {
            m_currentProcess.finishTime = currentTime + 1;
            finishedProcess.push_back(m_currentProcess);
            m_isIdle = true;
            m_currentTimeQuantum = m_timeQuantum;
            return true;
        }

        // current process run out of time quantum
        if (m_currentTimeQuantum == 0) {
            finishedProcess.push_back(m_currentProcess);
            m_currentTimeQuantum = m_timeQuantum;
            m_isIdle = true;
        }

        return true;
    }

    // print queue status for debug
    void visualization() {
        printf("%.*s\n", m_executionRecord.size() * 2 + 1, "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");
        printf("|%d", m_executionRecord[0]);
        for (int i{ 1 }; i < m_executionRecord.size(); i++) {
            if (m_executionRecord[i] != m_executionRecord[i - 1])
                if (m_executionRecord[i] != 0)
                    printf("|%d", m_executionRecord[i]);
                else
                    printf("| ");
            else
                printf("  ");
        }
        printf("|\n");
        printf("%.*s\n", m_executionRecord.size() * 2 + 1, "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");
    }
};

class FirstComeFirstServe {
    std::queue<Process> m_waitingQueue;
    Process m_currentProcess{};
    bool m_isIdle{ true };

    std::vector<int> m_executionRecord;

  public:
    FirstComeFirstServe() {}

    void newProcessArrived(Process process) {
        m_waitingQueue.push(process);
    }

    // return is show if there are process running
    bool loop(std::vector<Process>& finishedProcess, const int currentTime) {
        if (m_isIdle && m_waitingQueue.empty()) {
            m_executionRecord.push_back(0);
            return false;
        } else if (m_isIdle) {
            m_currentProcess = m_waitingQueue.front();
            m_waitingQueue.pop();
            m_isIdle = false;
        }

        m_currentProcess.timeLeft -= 1;
        m_executionRecord.push_back(m_currentProcess.id + 1);

        // current process finish
        if (m_currentProcess.timeLeft == 0) {
            m_currentProcess.finishTime = currentTime + 1;
            finishedProcess.push_back(m_currentProcess);
            m_isIdle = true;
            return true;
        }

        return true;
    }

    void preemptive() {
        if (!m_isIdle) {
            m_isIdle = true;
            m_waitingQueue.push(m_currentProcess);
        }
        m_executionRecord.push_back(0);
    }

    // print queue status for debug
    void visualization() {
        printf("%.*s\n", m_executionRecord.size() * 2 + 1, "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");
        if (m_executionRecord[0] != 0)
            printf("|%d", m_executionRecord[0]);
        else
            printf("| ");
        for (int i{ 1 }; i < m_executionRecord.size(); i++) {
            if (m_executionRecord[i] != m_executionRecord[i - 1])
                if (m_executionRecord[i] != 0)
                    printf("|%d", m_executionRecord[i]);
                else
                    printf("| ");
            else
                printf("  ");
        }
        printf("|\n");
        printf("%.*s\n", m_executionRecord.size() * 2 + 1, "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-");
    }
};

class MultiLevelFeedbackQueue {
    bool m_isIdle{ true };
    RoundRobin m_scheduler1;
    FirstComeFirstServe m_scheduler2;

  public:
    MultiLevelFeedbackQueue(int timeQuantum) : m_scheduler1{ timeQuantum },
                                               m_scheduler2{} {}

    void newProcessArrived(Process process) {
        m_scheduler1.newProcessArrived(process);
    }

    // return is show if there are process running
    bool loop(std::vector<Process>& finishedProcess, const int currentTime) {
        bool isScheduler1Running{};
        bool isScheduler2Running{};

        isScheduler1Running = m_scheduler1.loop(finishedProcess, currentTime);

        if (!finishedProcess.empty() && finishedProcess.back().timeLeft > 0) {
            m_scheduler2.newProcessArrived(finishedProcess.back());
            finishedProcess.pop_back();
        }

        // run if scheduler1 is idle
        if (!isScheduler1Running)
            isScheduler2Running = m_scheduler2.loop(finishedProcess, currentTime);
        else
            m_scheduler2.preemptive();

        return isScheduler1Running || isScheduler2Running;
    }

    void visualization() {
        m_scheduler1.visualization();
        m_scheduler2.visualization();
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

    MultiLevelFeedbackQueue scheduler{ timeQuantum };

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

    // show queue for debug
    // scheduler.visualization();

    std::sort(finishProcess.begin(), finishProcess.end(), [](const Process& p1, const Process& p2) { return p1.id < p2.id; });

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