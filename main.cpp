#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main(){

  ifstream ip("yellow_tripdata_2015-01-06.csv");

  if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';
  int cont = 7291703;
  string A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S;

  while(ip.good() && cont--)
  {
    getline(ip,A,',');
    getline(ip,B,',');
    getline(ip,C,',');
    getline(ip,D,',');
    getline(ip,E,',');
    getline(ip,F,',');
    getline(ip,G,',');
    getline(ip,H,',');
    getline(ip,I,',');
    getline(ip,J,',');
    getline(ip,K,',');
    getline(ip,L,',');
    getline(ip,M,',');
    getline(ip,N,',');
    getline(ip,O,',');
    getline(ip,P,',');
    getline(ip,Q,',');
    getline(ip,R,',');
    getline(ip,S,'\n');
    cout<<std::atof(F.c_str())<< " "<<std::atof(G.c_str())<<endl;
  }

  ip.close();
}
