#include "Brutus.h"

vector<mpreal> Brutus::get_dt_step() {
  return dt_step;
}
vector<mpreal> Brutus::get_tcpu_step() {
  return tcpu_step;
}

Brutus::Brutus(vector<mpreal> &data) {
  t = "0";
  this->data = data;
  N = data.size()/7;  

  tolerance = "1e-6";
  numBits = 56;

  eta = get_eta(tolerance);

  setup();
}
Brutus::Brutus(mpreal &t, vector<mpreal> &data, mpreal &tolerance) {
  this->t = t;
  this->data = data;
  N = data.size()/7;  

  this->tolerance = tolerance;
  numBits = get_numBits(tolerance);

  eta = get_eta(tolerance);

  setup();
}
Brutus::Brutus(mpreal &t, vector<mpreal> &data, mpreal &tolerance, int &numBits) {
  this->t = t;
  this->data = data;
  N = data.size()/7;  

  this->tolerance = tolerance;
  this->numBits = numBits;

  eta = get_eta(tolerance);

  setup();
}
Brutus::Brutus(mpreal &t, vector<mpreal> &data, mpreal &tolerance, int &numBits, mpreal &eta) {
  this->t = t;
  this->data = data;
  N = data.size()/7;  

  this->tolerance = tolerance;
  this->numBits = numBits;

  this->eta = eta;

  setup();
}
Brutus::Brutus(mpreal &t, vector<mpreal> &data, mpreal &tolerance, int &numBits, mpreal &eta, int &nmax) {
  this->t = t;
  this->data = data;
  N = data.size()/7;  

  this->tolerance = tolerance;
  this->numBits = numBits;

  this->eta = eta;

  setup(nmax);
}

mpreal Brutus::get_eta() {
  return eta;
}
mpreal Brutus::get_eta(mpreal tolerance) {
  mpreal a = "0", b = "0";

  if(tolerance > "1e-50") {
    a = "-0.012";
    b = "-0.40";
  }
  else {
    a = "-0.029";
    b = "0.45";
  }

  mpreal abslogtol = abs( log10(tolerance) );
  mpreal logeta = a*abslogtol+b;
  mpreal eta = pow("10", logeta);
  
  return eta;
}
int Brutus::get_numBits(mpreal tolerance) {
  mpreal absloge = abs( log10(tolerance) );
  return 4*(int)absloge.toLong()+32;
}
mpreal Brutus::fit_slope(vector<mpreal> &x, vector<mpreal> &y) {
  mpreal a = "0";
  int N = x.size();

  if(N < 2) {
    a = "-1e100";
  }
  else {
    mpreal SX="0", SY="0", SX2="0", SXY="0", Xav="0", Yav="0";
    for(int i=0; i<N; i++) {
      SX += x[i];
      SY += y[i];
      SX2 += x[i]*x[i];
      SXY += x[i]*y[i];
    }        
    Xav = SX / (mpreal)N;
    Yav = SY / (mpreal)N;
    a = (SXY - SX * Yav) / (SX2 - SX * Xav);
  }

  return a;
}

void Brutus::setup() {
  Cluster c(data);
  c.eps2 = "0";
  cl = c;

  Bulirsch_Stoer b(tolerance, N);
  bs = b;
}
void Brutus::setup(int nmax) {
  Cluster c(data);
  c.eps2 = "0";
  cl = c;

  Bulirsch_Stoer b(tolerance, nmax, 128, N);
  bs = b;
}

void Brutus::evolve(mpreal t_end) {
  Timer tim;

  //tcpu_step.clear();
  //dt_step.clear();

  while (t<t_end) {
    cl.calcAcceleration_dt();

    dt = eta*cl.dt;
    if(t+dt > t_end) dt = t_end-t;

    //tim.start();
    bool converged = bs.integrate(cl, dt);
    //tim.stop();

    //tcpu_step.push_back(tim.get());
    //dt_step.push_back(dt);

    if(!converged) {
      cerr << "Not converged at " << t << "!" << endl;
      exit(1);
    }

    t += dt;
  }
  this->data = cl.get_data();
}
  
mpreal Brutus::get_t() {
  return t;
}
vector<mpreal> Brutus::get_data() {
  return data;
}
vector<double> Brutus::get_data_double() {
  int N = data.size()/7;
  vector<double> v(7*N, 0);
  for(int i=0; i<N; i++) {
    for(int j=0; j<7; j++) {
      v[i*7+j] = data[i*7+j].toDouble();
    }
  }
  return v;
}
vector<string> Brutus::get_data_string() {
  int N = data.size()/7;
  vector<string> v(7*N, "0");
  for(int i=0; i<N; i++) {
    for(int j=0; j<7; j++) {
      v[i*7+j] = data[i*7+j].toString();
    }
  }
  return v;
}




