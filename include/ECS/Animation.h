#ifndef B496B339_E2A6_438A_AE34_4DDDDD8C5762
#define B496B339_E2A6_438A_AE34_4DDDDD8C5762

struct Animation {
  int index;
  int frames;
  int speed;

  Animation(){};
  Animation(int i, int f, int s) : index(i), frames(f), speed(s) {}
};

#endif /* B496B339_E2A6_438A_AE34_4DDDDD8C5762 */
