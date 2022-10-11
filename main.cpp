#include "campanha.hpp"

int main() {
  
  while(1){

    int S, P;
    std::cin >> S >> P;

    SAT sat(P);

    if(S == 0 && P == 0)
      return 0;

    for(int i = 0; i < S; i++){

      int x1, x2, y1, y2;
      std::cin >> x1 >> x2 >> y1 >> y2;

      sat.add(x1, false, x2, false);
      sat.add(y1, true, y2, true);
    }

    std::cout << ((sat.SAT_2()) ? "sim" : "nao") << std::endl;
  }
}
