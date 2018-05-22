#ifndef CANONS_HPP_
#define CANONS_HPP_

class Canons {
  private:
    uint8_t currentCanon;
    int canons[4] = {22, 23, 24, 25};

  public:
    Canons(void){
      currentCanon = 0;
    };
    bool fire(void){
      digitalWrite(canons[currentCanon], HIGH);
      delay(5);
      digitalWrite(canons[currentCanon++], LOW);
      if (currentCanon>3)
        return false;
      return true;
    };
};

#endif