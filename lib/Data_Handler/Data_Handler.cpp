#include "Data_Handler.h"

void Data_Handler::print(vector<double> &data) {
  int N = data.size()/7;
  for(int i=0; i<N; i++) {
    for(int j=0; j<7; j++) {
      cerr << data[i*7+j] << " ";
    }
    cerr << endl;
  }
  cerr << endl;
}
void Data_Handler::print(double &time, int &N, double &tcpu, vector<double> &data) {
  cerr << time << " " << N << " " << tcpu << endl;
  for(int i=0; i<N; i++) {
    for(int j=0; j<7; j++) {
      cerr << data[i*7+j] << " ";
    }
    cerr << endl;
  }
  cerr << endl;
}
void Data_Handler::print(double &time, int &N, double &tcpu, vector<double> &data, ofstream &str) {
  str << time << " " << N << " " << tcpu << endl;
  for(int i=0; i<N; i++) {
    for(int j=0; j<7; j++) {
      str << data[i*7+j] << " ";
    }
    str << endl;
  }
  str << endl;
}
void Data_Handler::print(string time, int &N, double &tcpu, vector<string> &data, ofstream &str) {
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
string Data_Handler::toString(int a) {
  stringstream s;
  s << a;
  string b = s.str();
  return b;
}
string Data_Handler::toString(double a) {
  stringstream s;
  s << a;
  string b = s.str();
  return b;
}

bool Data_Handler::isEmpty(string word) {
  bool isEmpty = true;
  int N = word.length();
  for(int i=0; i<N; i++) {
    char c = word[i];
    if(!isspace(c)) {
      isEmpty = false;    
      break;
    }
  }
  return isEmpty;
}
vector<string> Data_Handler::get_words(string line) {
  vector<string> words;

  stringstream s(line);
  string word;
  while (!s.eof()) {
    s >> word;
    if(!isEmpty(word)) words.push_back(word);
  }

  return words;
}

int Data_Handler::countNumSnapshot(string file) {
  int N = 0;
  ifstream src;
  src.open(file.c_str());
  if(!src) {
    cerr << "Can not open " << file << "!" << endl;
  }
  else {
    while(!src.eof()) {
      string line;
      getline(src, line);
      vector<string> words = get_words(line);
      int M = words.size();
      if(M == 3) N++;
    }
  }
  src.close();
  return N;
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
    vector<double> snapshot;
    while(!str.eof()) {
      getline(str, line);
      vector<string> words = get_words(line);
      int M = words.size();
      if(M == 3 || M == 4) {
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

        time.push_back( toDouble(words[0]) );
        numStar.push_back( toInt(words[1]) );
        tcpu.push_back( toDouble(words[2]) );
      }
      else if (M == 7 || M == 8){
        for(int i=0; i<7; i++) {
          snapshot.push_back(toDouble(words[i]));
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

bool Data_Handler::process_with_radius(string file) {
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
    vector<double> snapshot;
    while(!str.eof()) {
      getline(str, line);
      vector<string> words = get_words(line);
      int M = words.size();
      if(M == 3 || M == 4) {
        if(snapshot.size() > 0) {
          int N_snapshot = snapshot.size()/8;
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

        time.push_back( toDouble(words[0]) );
        numStar.push_back( toInt(words[1]) );
        tcpu.push_back( toDouble(words[2]) );
      }
      else if (M == 8 || M == 9){
        for(int i=0; i<8; i++) {
          snapshot.push_back(toDouble(words[i]));
        }
      }
    }
    if(snapshot.size() > 0) {
      int N_snapshot = snapshot.size()/8;
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

vector<double> Data_Handler::get_time() {
  return time;
}
vector<int> Data_Handler::get_numStar() {
  return numStar;
}
vector<double> Data_Handler::get_tcpu() {
  return tcpu;
}
vector< vector<double> > Data_Handler::get_data() {
  return data;
}






