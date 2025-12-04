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
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsUsed,
    size_t day,
    size_t slot
);


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

    // days
    size_t n = avail.size();
    //workers
    size_t k = avail[0].size();

    if(dailyNeed > k){
      return false;
    }

    sched.assign(n, std::vector<Worker_T>(dailyNeed, INVALID_ID));
    std::vector<size_t> shiftsUsed(k, 0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsUsed, 0, 0);







}


bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsUsed,
    size_t day,
    size_t slot
)
{
  //days
  size_t n = avail.size();
  //workers
  size_t k = avail[0].size();

  //filled all
  if(day == n){
    return true;
  }

  //filled all slots in the curr day
  if(slot == dailyNeed){
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsUsed, day+1, 0);
  }

  //try assigning workers
  for(size_t i = 0; i < k; ++i){
    
    //must be avail that day
    if(!avail[day][i]){
      continue;
    }
    
    //must not go over max shifts
    if(shiftsUsed[i] >= maxShifts){
      continue;
    }
    
    //not alr sched that day
    if(std::find(sched[day].begin(), sched[day].end(), i) != sched[day].end()){
      continue;
    }
    
    //choose worker
    sched[day][slot] = static_cast<Worker_T>(i);
    shiftsUsed[i]++;
    
    //recurse
    if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsUsed, day, slot+1)){
      return true;
    }
    
    //backtrack
    shiftsUsed[i]--;
    sched[day][slot] = INVALID_ID;
  }
  return false;

}

