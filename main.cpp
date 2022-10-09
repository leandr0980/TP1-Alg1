#include "campanha.hpp"

int main() {
  
  int S, P;

  while(1){

    std::cin >> S >> P;

    SAT s(P);

    if(!S && !P)
      return 0;

    for(int i = 0; i < S; i++){
      int x1, x2;
      std::cin >> x1 >> x2;

      s.add(x1, false, x2, false);

      int y1, y2;
      std::cin >> y1 >> y2;

      s.add(y1, true, y2, true);
    }

    std:: cout << ((s.SAT_2()) ? "sim" : "nao") << std::endl;
  }
}
