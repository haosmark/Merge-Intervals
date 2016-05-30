// MergeIntervals.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

struct Interval
{
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

using namespace std;

// where is x in relation to the interval?
// returns 0 if is between, -1 if less, 1 if greater than
int getRelativePosition(int x, Interval interval)
{
    if (x > interval.end)
    {
        return 1;
    }
    if (x < interval.start)
    {
        return -1;
    }
    return 0;
}

vector<Interval> insert(vector<Interval> &intervals, Interval newInterval)
{
    // make sure new interval's end is greater than its start
    // if they are not, then swap them
    if (newInterval.start > newInterval.end)
    {
        auto temp = newInterval.start;
        newInterval.start = newInterval.end;
        newInterval.end = temp;
    }

    auto newIntervalStart = -1;
    auto newIntervalEnd = -1;
    vector<Interval> mergeResult;

    // loop through all intervals
    for (auto i = 0; i < intervals.size(); i++)
    {
        // if new interval start is greater than current interval end then it's too early to merge
        // add old interval to returned collection
        if (getRelativePosition(newInterval.start, intervals[i]) == 1)
        {
            mergeResult.push_back(intervals[i]);
        }

        // if new interval start is less than current interval, then define it as the new start
        if ((getRelativePosition(newInterval.start, intervals[i]) == -1) && (newIntervalStart == -1))
        {
            newIntervalStart = newInterval.start;
        }

        // merge the interval start
        if (newIntervalStart == -1)
        {
            // if the new interval start is between the current interval points
            if (getRelativePosition(newInterval.start, intervals[i]) == 0)
            {
                if (intervals[i].start < newInterval.start)
                {
                    newIntervalStart = intervals[i].start;
                    newInterval.start = newIntervalStart;
                }
                else
                {
                    newIntervalStart = newInterval.start;
                }
            }
        }

        // merge the interval end
        if (newIntervalEnd == -1)
        {
            // merge the end if it's between the current interval
            if (getRelativePosition(newInterval.end, intervals[i]) == 0)
            {
                if (intervals[i].end < newInterval.end)
                {
                    newIntervalEnd = newInterval.end;
                }
                else
                {
                    newIntervalEnd = intervals[i].end;
                }

            }
            // merge the end if it's less than the current interval
            else if (getRelativePosition(newInterval.end, intervals[i]) == -1)
            {
                newIntervalEnd = newInterval.end;
            }

            // once the end point is know, append the merging interval
            if (newIntervalEnd != -1)
            {
                mergeResult.push_back(Interval(newIntervalStart, newIntervalEnd));
                if (newIntervalEnd != intervals[i].end)
                {
                    mergeResult.push_back(intervals[i]);
                }
            }
        }
        // if merging process is complete, just append the remaining intervals
        else
        {
            mergeResult.push_back(intervals[i]);
        }
    }

    if (newIntervalEnd == -1)
    {
        mergeResult.push_back(newInterval);
    }
    return mergeResult;
}

int main()
{
    // test cases
    vector<Interval> a { Interval(1, 3), Interval(6, 9) };
    vector<Interval> merged_a = insert(a, Interval(2, 5));

    vector<Interval> b { Interval(1, 2), Interval(3, 5), Interval(6, 7), Interval(8, 10), Interval(12, 16) };
    vector<Interval> merged_b = insert(b, Interval(4, 9));

    vector<Interval> c{ Interval(3, 6), Interval(8, 10) };
    vector<Interval> merged_c = insert(c, Interval(1, 2));

    vector<Interval> d{ Interval(1, 2), Interval(3, 6) };
    vector<Interval> merged_d = insert(d, Interval(8, 10));

    vector<Interval> e{ Interval(1, 2), Interval(8, 10) };
    vector<Interval> merged_e = insert(e, Interval(3, 6));

    vector<Interval> f { Interval(2, 3), Interval(4, 5) };
    vector<Interval> merged_f = insert(f, Interval(1, 10));

    vector<Interval> g { Interval(14648047, 16875188), Interval(99776803, 99818745) };
    vector<Interval> merged_g = insert(g, Interval(108785977, 16197462));
    
    return 0;
}

