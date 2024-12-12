#include <iostream>
using namespace std;

#include <fstream>
#include <sstream>
#include <string>

#include <cstdlib>
#include <vector>

#include "mpreal.h"
using namespace mpfr;

#ifndef __Data_Handler_h
#define __Data_Handler_h

class Data_Handler {
  vector<mpreal> time;
  vector<int> numStar;
  vector<double> tcpu;
  vector< vector<mpreal> > data;

  public:

  void print(vector<mpreal> &data);
  void print(mpreal &time, int &N, double &tcpu, vector<mpreal> &data);
  void print(mpreal &time, int &N, double &tcpu, vector<mpreal> &data, ofstream &str);

  int toInt(string word);
  double toDouble(string word);
  mpreal tompreal(string word);
  vector<string> get_words(string line);

  bool process(string file);

  vector<mpreal> get_time();
  vector<int> get_numStar();
  vector<double> get_tcpu();
  vector< vector<mpreal> > get_data();
};

#endif


