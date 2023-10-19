#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>

class FirstInFirstOut {
    int m_frameCount;
    std::deque<int> m_frameQueue;
    std::set<int> m_frame;

  public:
    FirstInFirstOut(int frameCount) : m_frameCount{ frameCount } {}

    int stimulate(const int reference) {
        if (m_frame.find(reference) != m_frame.end())
            return 0;

        if (m_frameQueue.size() >= m_frameCount) {
            m_frame.erase(m_frameQueue.front());
            m_frameQueue.pop_front();
        }

        m_frame.insert(reference);
        m_frameQueue.push_back(reference);

        return 1;
    }
};

class LeastRecentUse {
    int m_frameCount;
    std::map<int, int> m_frameQueue;       // lastUseTime, referenceId
    std::map<int, int> m_frameLastUseTime; // referenceId, lastUseTime
    int m_time{ 0 };

  public:
    LeastRecentUse(int frameCount) : m_frameCount{ frameCount } {}

    int stimulate(const int reference) {
        m_time++;

        if (m_frameLastUseTime.find(reference) != m_frameLastUseTime.end()) {
            // refresh use time
            int referenceLastUseTime{ m_frameLastUseTime[reference] };
            m_frameQueue.erase(referenceLastUseTime);
            m_frameLastUseTime[reference] = m_time;
            m_frameQueue[m_time] = reference;
            return 0;
        }

        if (m_frameQueue.size() >= m_frameCount) {
            int replaceReference{ m_frameQueue.begin()->second };
            m_frameLastUseTime.erase(replaceReference);
            m_frameQueue.erase(m_frameQueue.begin());
        }

        m_frameQueue[m_time] = reference;
        m_frameLastUseTime[reference] = m_time;

        return 1;
    }
};

class LeastFrequencyUse {
    struct CompareInfo {
        int arrivalTime;
        int useCount;

        bool operator<(const CompareInfo& c) const {
            if (useCount != c.useCount)
                return useCount < c.useCount;
            else
                return arrivalTime < c.arrivalTime;
        }
    };

    int m_frameCount;
    std::map<CompareInfo, int> m_frameQueue; // lastUseTime, referenceId
    std::map<int, CompareInfo> m_frameInfo;  // referenceId, lastUseTime
    int m_time{ 0 };

  public:
    LeastFrequencyUse(int frameCount) : m_frameCount{ frameCount } {}

    int stimulate(const int reference) {
        m_time++;

        if (m_frameInfo.find(reference) != m_frameInfo.end()) {
            // refresh use time
            CompareInfo information{ m_frameInfo[reference] };
            m_frameQueue.erase(information);
            m_frameInfo[reference].useCount++;
            information.useCount++;
            m_frameQueue[information] = reference;
            return 0;
        }

        if (m_frameQueue.size() >= m_frameCount) {
            int replaceReference{ m_frameQueue.begin()->second };
            m_frameInfo.erase(replaceReference);
            m_frameQueue.erase(m_frameQueue.begin());
        }

        CompareInfo information{ m_time, 1 };
        m_frameQueue[information] = reference;
        m_frameInfo[reference] = information;

        return 1;
    }
};

int main() {

    int frameCount;
    std::cin >> frameCount;

    FirstInFirstOut schedulerFIFO{ frameCount };
    LeastRecentUse schedulerLRU{ frameCount };
    LeastFrequencyUse schedulerLFU{ frameCount };

    int referenceCount;
    std::cin >> referenceCount;

    int FIFOFaultCount{ 0 };
    int LRUFaultCount{ 0 };
    int LFUFaultCount{ 0 };
    for (int i{ 0 }; i < referenceCount; i++) {
        int reference;
        std::cin >> reference;
        FIFOFaultCount += schedulerFIFO.stimulate(reference);
        LRUFaultCount += schedulerLRU.stimulate(reference);
        LFUFaultCount += schedulerLFU.stimulate(reference);
    }

    std::cout << FIFOFaultCount << "\n";
    std::cout << LRUFaultCount << "\n";
    std::cout << LFUFaultCount << "\n";
    return 0;
}