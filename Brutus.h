#include "Timer.h"

#include "Star.h"
#include "Cluster.h"
#include "Bulirsch_Stoer.h"

#ifndef __Brutus_h
#define __Brutus_h

class Brutus {
  mpreal t;
  int N;  
  vector<mpreal> data;

  mpreal tolerance;
  int numBits;

  mpreal eta, dt;

  Cluster cl;
  Bulirsch_Stoer bs;

  vector<mpreal> dt_step, tcpu_step;

  public:

  vector<mpreal> get_dt_step();
  vector<mpreal> get_tcpu_step();

  Brutus(vector<mpreal> &data);
  Brutus(mpreal &t, vector<mpreal> &data, mpreal &tolerance);
  Brutus(mpreal &t, vector<mpreal> &data, mpreal &tolerance, int &numBits);
  Brutus(mpreal &t, vector<mpreal> &data, mpreal &tolerance, int &numBits, mpreal &eta);
  Brutus(mpreal &t, vector<mpreal> &data, mpreal &tolerance, int &numBits, mpreal &eta, int &nmax);

  mpreal get_eta();
  mpreal get_eta(mpreal tolerance);
  int get_numBits(mpreal tolerance);
  mpreal fit_slope(vector<mpreal> &x, vector<mpreal> &y);

  void setup();
  void setup(int nmax);

  void evolve(mpreal t_end);
  
  mpreal get_t();
  vector<mpreal> get_data();
  vector<double> get_data_double();
  vector<string> get_data_string();
};

#endif


