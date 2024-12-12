#include "Data_Handler.h"

void Data_Handler::print(vector<mpreal> &data) {
  int N = data.size()/7;
  for(int i=0; i<N; i++) {
    for(int j=0; j<7; j++) {
      cerr << data[i*7+j] << " ";
    }
    cerr << endl;
  }
  cerr << endl;
}
void Data_Handler::print(mpreal &time, int &N, double &tcpu, vector<mpreal> &data) {
  cerr << time << " " << N << " " << tcpu << endl;
  for(int i=0; i<N; i++) {
    for(int j=0; j<7; j++) {
      cerr << data[i*7+j] << " ";
    }
    cerr << endl;
  }
  cerr << endl;
}
void Data_Handler::print(mpreal &time, int &N, double &tcpu, vector<mpreal> &data, ofstream &str) {
  str << time << " " << N << " " << tcpu << endl;
  for(int i=0; i<N; i++) {
    for(int j=0; j<7; j++) {
      str << data[i*7+j] << " ";
    }
    str << endl;
  }
  str << endl;
}

int Data_Handler::toInt(string word) {
  int a = atoi( word.c_str() );
  return a;  
}
double Data_Handler::toDouble(string word) {
  double a = atof( word.c_str() );
  return a;  
}
mpreal Data_Handler::tompreal(string word) {
  mpreal a = word;
  return a;
}

vector<string> Data_Handler::get_words(string line) {
  vector<string> words;

  stringstream s(line);
  string word;
  while (!s.eof()) {
    s >> word;
    words.push_back(word);
  }

  return words;
}

bool Data_Handler::process(string file) {
  time.clear();
  numStar.clear();
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
    vector<mpreal> snapshot;
    while(!str.eof()) {
      getline(str, line);
      vector<string> words = get_words(line);
      int M = words.size();
      if(M == 3) {
        if(snapshot.size() > 0) {
          int N_snapshot = snapshot.size()/7;
          if(N_snapshot == numStar[numStar.size()-1]) {
            data.push_back(snapshot);
          }
          else {
            time.pop_back();
            numStar.pop_back();
            tcpu.pop_back();
          }
        }
        snapshot.clear();

        time.push_back( tompreal(words[0]) );
        numStar.push_back( toInt(words[1]) );
        tcpu.push_back( toDouble(words[2]) );
      }
      else if (M == 7+1){
        for(int i=0; i<7; i++) {
          snapshot.push_back(tompreal(words[i]));
        }
      }
    }
    if(snapshot.size() > 0) {
      int N_snapshot = snapshot.size()/7;
      if(N_snapshot == numStar[numStar.size()-1]) {
        data.push_back(snapshot);
      }
      else {
        time.pop_back();
        numStar.pop_back();
        tcpu.pop_back();
      }
    }
  }
  str.close();
  return true;
}

vector<mpreal> Data_Handler::get_time() {
  return time;
}
vector<int> Data_Handler::get_numStar() {
  return numStar;
}
vector<double> Data_Handler::get_tcpu() {
  return tcpu;
}
vector< vector<mpreal> > Data_Handler::get_data() {
  return data;
}






