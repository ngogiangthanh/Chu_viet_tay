

#include "dtw.h"
#include<iostream>
#include<fstream>

using namespace std;
// this just generates some random array
vector<double> getrandomwalk(uint size) {
    vector<double> data(size);
    data[0] = 0.0;
    for (uint k = 1; k < size; ++k){
        data[k] = (1.0 * rand() / (RAND_MAX)) - 0.5 + data[k - 1];
        }
    return data;
}

void demo(uint size) {
  std::cout << " I generated a random walk and I will try to match it with other random walks. " << std::endl;

  vector<double> target = getrandomwalk(size); // this is our target
  //LB_Improved filter(target, size / 10); // we use the DTW with a tolerance of 10% (size/10)
  dtw _dtw(size, size/10);
  //double bestsofar = filter.getLowestCost();
  double bestsofar = 10000000;
  uint howmany = 5000;
  for(uint i = 0; i < 5000; i++) {
    vector<double> candidate = getrandomwalk(size);
    //double newbest = filter.test(candidate);
    double newbest = _dtw.fastdynamic(target, candidate);
    if(newbest < bestsofar) {
      std::cout << " we found a new nearest neighbor, distance (L1 norm) = " << newbest << std::endl;
      bestsofar = newbest;
    }
  }
  //std::cout << " I compared it with " << howmany << " random walks, closest match is at a distance (L1 norm) of " << filter.getLowestCost() << std::endl;
 std::cout << " I compared it with " << howmany << " random walks, closest match is at a distance (L1 norm) of " <<bestsofar << std::endl;
 // std::cout << "full dtw " << filter.getNumberOfDTW() << endl;
 // std::cout << "number of keo lb " << filter.getNumberOfCandidates() << endl;
}

void readFile()
{
     ifstream myReadFile;
	 myReadFile.open("D:\\Thesis\\Chu_viet_tay\\Experiments\\Computational\\pp_series.txt");
	 string output;
	 if (myReadFile.is_open()) {
	
    int number;
    std::string str;
    char c;
    while (myReadFile >> number >> c >> str)
        cout << number << " " << str << "\n";
	}
	myReadFile.close();
}

int main() {
	readFile();
  //demo(10000);
}
