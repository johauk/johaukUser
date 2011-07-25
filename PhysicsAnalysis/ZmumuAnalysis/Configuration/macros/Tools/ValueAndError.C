#include "ValueAndError.h"

#include <sstream>





std::string ValueAndError::print()const{
  std::stringstream out;
  out<<this->value();
  out<<" +"<<this->absErrUp()<<"-"<<this->absErrDw();
  return out.str();
}



std::string ValueAndErrorStatSyst::print()const{
  std::stringstream out;
  out<<this->value();
  out<<" +"<<this->absErrStatUp()<<"-"<<this->absErrStatDw()<<"(stat.)";
  out<<" +"<<this->absErrSystUp()<<"-"<<this->absErrSystDw()<<"(syst.)";
  out<<" [+"<<this->absErrUp()<<"-"<<this->absErrDw()<<"]";
  return out.str();
}


std::string ValueAndErrorStatSystLumi::print()const{
  std::stringstream out;
  out<<this->value();
  out<<" +"<<this->absErrStatUp()<<"-"<<this->absErrStatDw()<<"(stat.)";
  out<<" +"<<this->absErrSystUp()<<"-"<<this->absErrSystDw()<<"(syst.)";
  out<<" +"<<this->absErrLumiUp()<<"-"<<this->absErrLumiDw()<<"(lumi.)";
  out<<" [+"<<this->absErrUp()<<"-"<<this->absErrDw()<<"]";
  return out.str();
}



const ValueAndError ValueAndError::dummyValues(const double dummyValue, const double dummyAbsErrUp, const double dummyAbsErrDw){
  ValueAndError dummy;
  dummy.setValue(dummyValue);
  dummy.setAbsErrUp(dummyAbsErrUp);
  dummy.setAbsErrDw(dummyAbsErrDw);
  return dummy;
}



const ValueAndErrorStatSyst ValueAndErrorStatSyst::dummyValues(const double dummyValue, const double dummyAbsErrStatUp, const double dummyAbsErrStatDw, const double dummyAbsErrSystUp, const double dummyAbsErrSystDw){
  ValueAndErrorStatSyst dummy;
  dummy.setValue(dummyValue);
  dummy.setAbsErrStatUp(dummyAbsErrStatUp);
  dummy.setAbsErrStatDw(dummyAbsErrStatDw);
  dummy.setAbsErrSystUp(dummyAbsErrSystUp);
  dummy.setAbsErrSystDw(dummyAbsErrSystDw);
  return dummy;
}



const ValueAndErrorStatSystLumi ValueAndErrorStatSystLumi::dummyValues(const double dummyValue, const double dummyAbsErrStatUp, const double dummyAbsErrStatDw, const double dummyAbsErrSystUp, const double dummyAbsErrSystDw, const double dummyAbsErrLumiUp, const double dummyAbsErrLumiDw){
  ValueAndErrorStatSystLumi dummy;
  dummy.setValue(dummyValue);
  dummy.setAbsErrStatUp(dummyAbsErrStatUp);
  dummy.setAbsErrStatDw(dummyAbsErrStatDw);
  dummy.setAbsErrSystUp(dummyAbsErrSystUp);
  dummy.setAbsErrSystDw(dummyAbsErrSystDw);
  dummy.setAbsErrLumiUp(dummyAbsErrLumiUp);
  dummy.setAbsErrLumiDw(dummyAbsErrLumiDw);
  return dummy;
}









