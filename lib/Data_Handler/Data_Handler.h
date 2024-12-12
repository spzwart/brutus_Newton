#include <iostream>
using namespace std;

#include <fstream>
#include <sstream>
#include <string>

#include <cstdlib>
#include <vector>

#ifndef __Data_Handler_h
#define __Data_Handler_h

class Data_Handler {
  vector<double> time;
  vector<int> numStar;
  vector<double> tcpu;
  vector< vector<double> > data;

  public:

  void print(vector<double> &data);
  void print(double &time, int &N, double &tcpu, vector<double> &data);
  void print(double &time, int &N, double &tcpu, vector<double> &data, ofstream &str);
  void print(string time, int &N, double &tcpu, vector<string> &data, ofstream &str);

  int toInt(string word);
  double toDouble(string word);
  string toString(int a);
  string toString(double a);

  bool isEmpty(string word);
  vector<string> get_words(string line);

  int countNumSnapshot(string file);
  bool process(string file);

  bool process_with_radius(string file);

  vector<double> get_time();
  vector<int> get_numStar();
  vector<double> get_tcpu();
  vector< vector<double> > get_data();
};

#endif


