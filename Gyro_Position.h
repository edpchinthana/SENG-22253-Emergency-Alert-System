#define GYRO_POSITION_H

class GyroPosition {
public:
  GyroPosition();
  void set(int x, int y, int z);
  String toString();
  int x;
  int y;
  int z;
};

GyroPosition::GyroPosition() {}

void GyroPosition::set(int xAng, int yAng, int zAng) {
  x = xAng;
  y = yAng;
  z = zAng;
}

String GyroPosition::toString() {
  return String(x)+","+String(y)+","+String(z);
}