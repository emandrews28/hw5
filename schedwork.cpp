#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedHelper(int day, int shift, std::vector<int>& workers, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched);
bool isValid(int day, int shift, int ID, std::vector<int>& workers, const size_t maxShifts, DailySchedule& sched);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    std::vector<int> workers(avail[0].size(), 0);
    sched.resize(avail.size());
    for(size_t i=0; i < avail.size(); i++) {
        for(size_t j=0; j < dailyNeed; j++) {
            sched[i].push_back(INVALID_ID);
        }
    }
    return schedHelper(0, 0, workers, avail, dailyNeed, maxShifts, sched);
}

bool schedHelper(int day, int shift, std::vector<int>& workers, const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched) {
    if(day == sched.size()) {
      return true;
    }
    if(shift == sched[day].size()) {
      return schedHelper(day+1, 0, workers, avail, dailyNeed, maxShifts, sched);
    } 
    if(sched[day][shift] != INVALID_ID) {
      return schedHelper(day, shift+1, workers, avail, dailyNeed, maxShifts, sched);
    }
    for(size_t i=0; i < avail[day].size(); i++) {
      if(!avail[day][i]) {
        continue;
      }
      sched[day][shift] = i;
      workers[i]++;
      if(isValid(day, shift, i, workers, maxShifts, sched)) {
        if(schedHelper(day, shift+1, workers, avail, dailyNeed, maxShifts, sched)) {
          return true;
        }
      }
      sched[day][shift] = INVALID_ID;
    }
    return false;
}

bool isValid(int day, int shift, int ID, std::vector<int>& workers, const size_t maxShifts, DailySchedule& sched) {
  if(workers[ID] > maxShifts) {
    return false;
  }
  return true;
}

