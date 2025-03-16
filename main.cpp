#include <bits/stdc++.h>
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
    bool reverse_;

    void find_next_event() {
	    if (reverse_) {
		    while (index_ < events_.size()) {
			    const string& timestamp = events_[index_].timestamp;
			    if (timestamp >= start_time_ && timestamp <= end_time_) {
				    break;
			    }
			    index_--;
		    }
	    }
	    else {
		    while (index_ < events_.size()) {
			    const string& timestamp = events_[index_].timestamp;
			    if (timestamp >= start_time_ && timestamp <= end_time_) {
				    break;
			    }
			    index_++;
		    }
	    }
    }

public:
    TimeIntervalIterator(const vector<Event>& events, const string& start_time, const string& end_time, bool reverse = false)
        : events_(events), start_time_(start_time), end_time_(end_time), index_(0), reverse_(reverse) {
		if (reverse_) {
			index_ = events_.size() - 1;
		}
		else
		{
			index_ = 0;
		}
		find_next_event();
	}

    bool has_next_event() const {
        if (reverse_) {
		return index_ < events_.size() && index_ >= 0;
	}
	else {
		return index_ < events_.size();
	}
    }


    Event next_event() {
        if (!has_next_event()) {
            throw out_of_range("No next event");
        }
        Event event = events_[index_];
        if (reverse_) {
		index_--;
	}
	else {
		index_++;
	}
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

    cout << "Forward iteration" << endl;
    TimeIntervalIterator forward_iterator(events, start_time, end_time);
    while (forward_iterator.has_next_event()) {
	    Event event = forward_iterator.next_event();
	    cout << event.timestamp << " " << event.description << endl;
    }
    

    cout << "\nReverse iteration" << endl;
    TimeIntervalIterator reverse_iterator(events, start_time, end_time, true);
    while (reverse_iterator.has_next_event()) {
	    Event event = reverse_iterator.next_event();
	    cout << event.timestamp << " " << event.description << endl;
    }
}

