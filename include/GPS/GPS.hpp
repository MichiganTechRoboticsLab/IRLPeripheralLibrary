#ifndef GPS_HPP
#define GPS_HPP


namespace IRL 
{
  
  enum PostionType {
    
  };
  
  class GPS 
  {
  public:
    ~GPS() {};
    virtual bool hasGPSFix() = 0;
    virtual int64_t getGPSSeconds() = 0;
    virtual int64_t getGPSWeek() = 0;
    virtual uint16_t getNumOfSat() = 0;
    virtual triple getPosLLA() = 0;
    virtual triple gotPosECEF() = 0;
    virtual triple getGPSVelocityECEF() = 0;
    virtual triple getGPSVelocityNED() = 0;
    
    
  };
}

#endif // GPS_HPP