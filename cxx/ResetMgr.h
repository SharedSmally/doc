#ifndef RESETMGR_H
#define RESETMGR_H

class Resetable
{

};

class ResetMgr : public Group <Resetable>
{

}

#
# metrics: startUpTime; total; success; lastSuccess; failure; lastFailure; xxxFailure; 
# statMetrics: minValue; maxValue; averageValue;
# count: ++; +=
# gauge: ++; +=; --; -=
#

#endif
