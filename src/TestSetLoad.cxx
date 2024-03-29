#include <iostream>
#include "Kset.h"
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
  if(argc < 3) {
    std::cout << "Two arguments are required, kmer size and path to FASTA file." << std::endl;
    return 1;
  }
  int k = atoi(argv[1]);
  char* file_path = argv[2];

  string line;
  ifstream fh(file_path);
  Kset* ks = new Kset(k);
  ks->parallel_add_init(4);

  int c = 0;
  if(fh.is_open()) {
    while(getline(fh, line)) {
      //std::cout << "inserting: " << line << std::endl;
      //ks.insert(line.c_str());
      ks->parallel_add(line.c_str());
      c++;
      /*if(ks->size() != c) {
        std::cout << "error at kmer " << c << "\t" << line << std::endl;
      }*/
    }
    fh.close();
    ks->parallel_add_join();
  } else {
    std::cout << "Could not open file: " << file_path << std::endl;
  }

  std::cout << "Kmer set contains " << ks->size() << " kmers" << std::endl;
  delete ks;

  return 0;
}
