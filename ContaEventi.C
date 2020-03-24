# include <iostream>
#include <fstream>
# include <TChain.h>

using namespace std;


void conta( char* input )
{
  TChain *a_ = new TChain("TNT/BOOM");

 std::ifstream ifs(input);

 std::string line;

 while(std::getline(ifs, line)){
  // cout << line << endl;
   a_->Add(line.c_str());
 }

  cout << input << " ==> " <<  a_->GetEntries() << endl;
}

int main(int argc, char** argv){

  conta(argv[1]);

  return 0;
}
