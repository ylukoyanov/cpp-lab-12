#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

struct Event {
    string timestamp;
    string description;
};

class TimeIntervalIterator {
private:
    vector<Event> events_;
    string start_time_;
    string end_time_;
    size_t index_;

    void find_next_event() {
        while (index_ < events_.size()) {
            const string& timestamp = events_[index_].timestamp;
            if (timestamp >= start_time_ && timestamp <= end_time_) {
                break;
            }
            index_++;
        }
    }
public:
    TimeIntervalIterator(const vector<Event>& events, const string& start_time, const string& end_time)
        : events_(events), start_time_(start_time), end_time_(end_time), index_(0) {
        find_next_event();
    }

    bool has_next_event() const {
        return index_ < events_.size();
    }

    Event next_event() {
        if (!has_next_event()) {
            throw out_of_range("No next event");
        }
        Event event = events_[index_];
        index_++;
        find_next_event();
        return event;
    }

};

int main() {
    vector<Event> events = {
        {"10-01-2025 12:00:00", "Event 1"},
        {"11-01-2025 14:30:00", "Event 2"},
        {"12-01-2025 09:15:00", "Event 3"},
        {"13-01-2025 18:45:00", "Event 4"}
    };

    string start_time = "09-01-2025 00:00:00";
    string end_time = "12-01-2025 23:59:59";

    TimeIntervalIterator iterator(events, start_time, end_time);

    while (iterator.has_next_event()) {
        Event event = iterator.next_event();
        cout << event.timestamp << " " << event.description << endl;
    }
}
