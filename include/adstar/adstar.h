/**
A header file for the AD* planner

Needs to have interfaces for all the important functions in the planner
Use environment and state classes

**/

#ifndef ADSTAR_ADSTAR_
#define ADSTAR_ADSTAR_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "adstar/state.h"
#include "adstar/environment.h"
#include <set>
#include <string>
#include <list>
//#include <unordered_set>
#include "adstar/myheap.h"
#include "adstar/mylist.h"

using namespace std;

class State;
class Environment;

class ADstar {
 public:
  class stateCompare
  {
  public:
    bool operator() (State *s1, State *s2) {
      double k11 = s1->k1;
      double k12 = s1->k2;
      double k21 = s2->k1;
      double k22 = s2->k2;
      
      if(k11 < k21) {
	return true;
      }
      else if (k21 < k11) {
	return false;
      }
      else { // k1[0] == k2[0]
	if(k12 < k22) {
	  return true;
	}
	else {
	  return false;
	}
      }
    }
  };
 
  int xstart, ystart, zstart; // start state
  int xgoal, ygoal, zgoal; // goal state
  int chi, clo;

  //std::pair<std::set<State*>::iterator, bool> ret;
  
  State *start, *goal;

  Environment env3D;
  
  double epsilon, epsilon_start;
  int step_size;
  bool dec_epsilon;

  bool changed;
  vector<State*> changedStates;
  
  //priority_queue<State, vector<State>, stateCompare> open, closed, incons;
  //set<State*, stateCompare> open;
  MyHeap open;
  
  //list<State*> *incons;
  MyList incons;
  
  /** Constructor */
  ADstar(size_t xlen, size_t ylen, size_t zlen, int xs, int ys, int zs, int xg, int yg, int zg, double eps);

  ~ADstar();

  /** Set low cost and high cost values */
  void setCosts (int clo, int chigh);

  /** Read costs from a file */
  void readCosts (ifstream& file);
  
  /** Key function */
  void key(State *s);

  /** Heuristic function */
  double heuristic(State *s1, State *s2);

  /** Update state function */
  void updateState(State *s);

  /** ComputeOrImprovePath function */
  void computeOrImprovePath();

  /** Main plan function */
  void plan(bool print, ofstream& file);

  /** Min one-step lookahead search */
  double minSucc(State *s);

  /** Motion Cost to travel to s2 from s1 */
  double motionCost(State *s1, State *s2);

  /** Update all predecessor states */
  void updateAllPredStates(State *s);

  /** Prints the path */
  void printPath(State *g, ofstream& file);

  /** Prints the path. Inefficient version */
  void printPathIneff(State *g);

  /** Sets the seed for the random number generator */
  void setSeed();

  /** Changes costs of a given percentage of states */
  void changeCosts(double fraction);

  /** Replan function */
  void replan(bool print, ofstream& file);

  /** Set step size for epsilon */
  void setStepSize(int step_size);

  /** Set flag for whether epsilon should be decreased or not */
  void setDecEpsilon(bool dec_eps);
};

#endif
