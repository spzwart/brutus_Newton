#include "Star.h"
#include "Cluster.h"

#ifndef __Bulirsch_Stoer_h
#define __Bulirsch_Stoer_h

#include <vector>


class Bulirsch_Stoer {
  mpreal tolerance;
  int n_max, k_max;

  std::vector<std::vector<mpreal>> x_sample, y_sample, z_sample, vx_sample, vy_sample, vz_sample;

  public:

  Bulirsch_Stoer();
  Bulirsch_Stoer(mpreal tolerance, int N);
  Bulirsch_Stoer(mpreal tolerance, int n_max, int k_max, int N);

  void set_tolerance(mpreal tolerance);
  void set_n_max(int n_max);
  void set_k_max(int k_max);

  mpreal get_tolerance();
  int get_n_max();
  int get_k_max();

  bool integrate(Cluster &cl, mpreal &dt);
  bool step(Cluster &cl, mpreal &dt);
  void extrapol(Cluster &cl_exp, vector<mpreal> &dt, vector<Cluster> &c);
  mpreal extrapolate(vector<mpreal> x, vector<mpreal> &y, mpreal x0);
  bool error_control(Cluster &c1, Cluster &c2);
};

#endif


