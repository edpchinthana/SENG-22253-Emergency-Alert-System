#define GPS_POSITION_H

class GPSPosition {
  public:
    GPSPosition();
    void set(float _lat, float _lng);
    float lat;
    float lng;
};

GPSPosition::GPSPosition() {}

void GPSPosition::set(float _lat, float _lng) {
  lat = _lat;
  lng = _lng;
}