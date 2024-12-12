#include <iostream>
using namespace std;

#include <fstream>
#include <sstream>
#include <string>

#include <cstdlib>
#include <vector>

int toInt(string word) {
  int a = atoi( word.c_str() );
  return a;  
}
double toDouble(string word) {
  double a = atof( word.c_str() );
  return a;
}

vector<string> get_words(string line) {
  vector<string> words;

  stringstream s(line);
  string word;
  while (!s.eof()) {
    s >> word;
    words.push_back(word);
  }

  return words;
}

bool process(string file, vector<double> &time, vector<int> &N, vector<double> &tcpu, vector< vector<double> > &data) {
  time.clear();
  N.clear();
  tcpu.clear();
  data.clear();

  ifstream str;
  str.open(file.c_str());
  if(!str) {
    cerr << "Can't open " << file << "!" << endl;
    return false;
  }
  else {
    string line;
    vector<double> snapshot;
    while(!str.eof()) {
      getline(str, line);
      vector<string> words = get_words(line);
      int M = words.size();
      if(M == 3) {
        if(snapshot.size() > 0) {
          int N_snapshot = snapshot.size()/7;
          if(N_snapshot == N[N.size()-1]) {
            data.push_back(snapshot);
          }
          else {
            time.pop_back();
            N.pop_back();
            tcpu.pop_back();
          }
        }
        snapshot.clear();

        time.push_back( toDouble(words[0]) );
        N.push_back( toInt(words[1]) );
        tcpu.push_back( toDouble(words[2]) );
      }
      else if (M == 7){
        for(int i=0; i<7; i++) {
          snapshot.push_back(toDouble(words[i]));
        }
      }
    }
    if(snapshot.size() > 0) {
      int N_snapshot = snapshot.size()/7;
      if(N_snapshot == N[N.size()-1]) {
        data.push_back(snapshot);
      }
      else {
        time.pop_back();
        N.pop_back();
        tcpu.pop_back();
      }
    }
  }
  str.close();
  return true;
}

int main(int argc, char* argv[]) {
  string file = argv[1];

  vector<int> N;
  vector<double> time, tcpu;
  vector< vector<double> > data;
  bool read_data = process(file, time, N, tcpu, data);

  if(!read_data) {
    cerr << "Catch error in file..." << endl;
  }
  else {
    int numState = N.size();
    for(int i=0; i<numState; i++) {
      cerr << time[i] << " " << N[i] << " " << tcpu[i] << endl;
      for(int j=0; j<7; j++) {
        cerr << data[i][j] << " ";
      }
      cerr << endl;
    }
  }

  return 0;
}


