#ifndef ValueAndError_h
#define ValueAndError_h


#include <cmath>




class ValueAndError{
  public:
    
    ValueAndError():value_(-999.), absoluteErrorSquaredUp_(-999.), absoluteErrorSquaredDown_(-999.){}
    ~ValueAndError(){}
    
    double value()const{return value_;};
    double relErrUp()const{return std::sqrt(absoluteErrorSquaredUp_/std::pow(value_,2));}
    double relErrDw()const{return std::sqrt(absoluteErrorSquaredDown_/std::pow(value_,2));}
    double absErrUp()const{return std::sqrt(absoluteErrorSquaredUp_);}
    double absErrDw()const{return std::sqrt(absoluteErrorSquaredDown_);}
    double relErr2Up()const{return absoluteErrorSquaredUp_/std::pow(value_,2);}
    double relErr2Dw()const{return absoluteErrorSquaredDown_/std::pow(value_,2);}
    double absErr2Up()const{return absoluteErrorSquaredUp_;}
    double absErr2Dw()const{return absoluteErrorSquaredDown_;}
    
    void setValue(const double input){value_ = input;}
    void setRelErrUp(const double input){absoluteErrorSquaredUp_ = input*input*std::pow(value_,2);}
    void setRelErrDw(const double input){absoluteErrorSquaredDown_ = input*input*std::pow(value_,2);}
    void setAbsErrUp(const double input){absoluteErrorSquaredUp_ = input*input;}
    void setAbsErrDw(const double input){absoluteErrorSquaredDown_ = input*input;}
    void setRelErr2Up(const double input){absoluteErrorSquaredUp_ = input*std::pow(value_,2);}
    void setRelErr2Dw(const double input){absoluteErrorSquaredDown_ = input*std::pow(value_,2);}
    void setAbsErr2Up(const double input){absoluteErrorSquaredUp_ = input;}
    void setAbsErr2Dw(const double input){absoluteErrorSquaredDown_ = input;}
    
    std::string print(const double =1.)const;
    
    static const ValueAndError dummyValues(const double =1., const double =0.1, const double =0.1);
    
  private:
    
    double value_;
    // Use absoulte errors, since relative errors are not well defined for value~0.0
    double absoluteErrorSquaredUp_;
    double absoluteErrorSquaredDown_;
};





class ValueAndErrorStatSyst : public ValueAndError{
  public:
    
    ValueAndErrorStatSyst():
        absoluteErrorSquaredStatUp_(0.), absoluteErrorSquaredStatDown_(0.), 
        absoluteErrorSquaredSystUp_(0.), absoluteErrorSquaredSystDown_(0.){}
    ~ValueAndErrorStatSyst(){}
    
    double relErrStatUp()const{return std::sqrt(absoluteErrorSquaredStatUp_/std::pow(this->value(),2));}
    double relErrStatDw()const{return std::sqrt(absoluteErrorSquaredStatDown_/std::pow(this->value(),2));}
    double absErrStatUp()const{return std::sqrt(absoluteErrorSquaredStatUp_);}
    double absErrStatDw()const{return std::sqrt(absoluteErrorSquaredStatDown_);}
    double relErr2StatUp()const{return absoluteErrorSquaredStatUp_/std::pow(this->value(),2);}
    double relErr2StatDw()const{return absoluteErrorSquaredStatDown_/std::pow(this->value(),2);}
    double absErr2StatUp()const{return absoluteErrorSquaredStatUp_;}
    double absErr2StatDw()const{return absoluteErrorSquaredStatDown_;}
    
    void setRelErrStatUp(const double input){absoluteErrorSquaredStatUp_ = input*input*std::pow(this->value(),2);this->setError();}
    void setRelErrStatDw(const double input){absoluteErrorSquaredStatDown_ = input*input*std::pow(this->value(),2);this->setError();}
    void setAbsErrStatUp(const double input){absoluteErrorSquaredStatUp_ = input*input;this->setError();}
    void setAbsErrStatDw(const double input){absoluteErrorSquaredStatDown_ = input*input;this->setError();}
    void setRelErr2StatUp(const double input){absoluteErrorSquaredStatUp_ = input*std::pow(this->value(),2);this->setError();}
    void setRelErr2StatDw(const double input){absoluteErrorSquaredStatDown_ = input*std::pow(this->value(),2);this->setError();}
    void setAbsErr2StatUp(const double input){absoluteErrorSquaredStatUp_ = input;this->setError();}
    void setAbsErr2StatDw(const double input){absoluteErrorSquaredStatDown_ = input;this->setError();}
    
    
    double relErrSystUp()const{return std::sqrt(absoluteErrorSquaredSystUp_/std::pow(this->value(),2));}
    double relErrSystDw()const{return std::sqrt(absoluteErrorSquaredSystDown_/std::pow(this->value(),2));}
    double absErrSystUp()const{return std::sqrt(absoluteErrorSquaredSystUp_);}
    double absErrSystDw()const{return std::sqrt(absoluteErrorSquaredSystDown_);}
    double relErr2SystUp()const{return absoluteErrorSquaredSystUp_/std::pow(this->value(),2);}
    double relErr2SystDw()const{return absoluteErrorSquaredSystDown_/std::pow(this->value(),2);}
    double absErr2SystUp()const{return absoluteErrorSquaredSystUp_;}
    double absErr2SystDw()const{return absoluteErrorSquaredSystDown_;}
    
    void setRelErrSystUp(const double input){absoluteErrorSquaredSystUp_ = input*input*std::pow(this->value(),2);this->setError();}
    void setRelErrSystDw(const double input){absoluteErrorSquaredSystDown_ = input*input*std::pow(this->value(),2);this->setError();}
    void setAbsErrSystUp(const double input){absoluteErrorSquaredSystUp_ = input*input;this->setError();}
    void setAbsErrSystDw(const double input){absoluteErrorSquaredSystDown_ = input*input;this->setError();}
    void setRelErr2SystUp(const double input){absoluteErrorSquaredSystUp_ = input*std::pow(this->value(),2);this->setError();}
    void setRelErr2SystDw(const double input){absoluteErrorSquaredSystDown_ = input*std::pow(this->value(),2);this->setError();}
    void setAbsErr2SystUp(const double input){absoluteErrorSquaredSystUp_ = input;this->setError();}
    void setAbsErr2SystDw(const double input){absoluteErrorSquaredSystDown_ = input;this->setError();}
    
    std::string print(const double =1.)const;
    
    static const ValueAndErrorStatSyst dummyValues(const double =1., const double =0.1, const double =0.1, const double =0.1, const double =0.1);
    
  private:
    
    void setError(){
      this->setAbsErr2Up(absoluteErrorSquaredStatUp_ + absoluteErrorSquaredSystUp_);
      this->setAbsErr2Dw(absoluteErrorSquaredStatDown_ + absoluteErrorSquaredSystDown_);
    }
    
    double absoluteErrorSquaredStatUp_;
    double absoluteErrorSquaredStatDown_;
    double absoluteErrorSquaredSystUp_;
    double absoluteErrorSquaredSystDown_;
};




class ValueAndErrorStatSystLumi : public ValueAndErrorStatSyst{
  public:
    
    ValueAndErrorStatSystLumi():
        absoluteErrorSquaredLumiUp_(0.), absoluteErrorSquaredLumiDown_(0.){}
    ~ValueAndErrorStatSystLumi(){}
    
    double relErrLumiUp()const{return std::sqrt(absoluteErrorSquaredLumiUp_/std::pow(this->value(),2));}
    double relErrLumiDw()const{return std::sqrt(absoluteErrorSquaredLumiDown_/std::pow(this->value(),2));}
    double absErrLumiUp()const{return std::sqrt(absoluteErrorSquaredLumiUp_);}
    double absErrLumiDw()const{return std::sqrt(absoluteErrorSquaredLumiDown_);}
    double relErr2LumiUp()const{return absoluteErrorSquaredLumiUp_/std::pow(this->value(),2);}
    double relErr2LumiDw()const{return absoluteErrorSquaredLumiDown_/std::pow(this->value(),2);}
    double absErr2LumiUp()const{return absoluteErrorSquaredLumiUp_;}
    double absErr2LumiDw()const{return absoluteErrorSquaredLumiDown_;}
    
    void setRelErrLumiUp(const double input){absoluteErrorSquaredLumiUp_ = input*input*std::pow(this->value(),2);this->setError();}
    void setRelErrLumiDw(const double input){absoluteErrorSquaredLumiDown_ = input*input*std::pow(this->value(),2);this->setError();}
    void setAbsErrLumiUp(const double input){absoluteErrorSquaredLumiUp_ = input*input;this->setError();}
    void setAbsErrLumiDw(const double input){absoluteErrorSquaredLumiDown_ = input*input;this->setError();}
    void setRelErr2LumiUp(const double input){absoluteErrorSquaredLumiUp_ = input*std::pow(this->value(),2);this->setError();}
    void setRelErr2LumiDw(const double input){absoluteErrorSquaredLumiDown_ = input*std::pow(this->value(),2);this->setError();}
    void setAbsErr2LumiUp(const double input){absoluteErrorSquaredLumiUp_ = input;this->setError();}
    void setAbsErr2LumiDw(const double input){absoluteErrorSquaredLumiDown_ = input;this->setError();}
    
    std::string print(const double =1.)const;
    
    static const ValueAndErrorStatSystLumi dummyValues(const double =1., const double =0.1, const double =0.1, const double =0.1, const double =0.1, const double =0.1, const double =0.1);
    
  private:
    
    void setError(){
      this->setAbsErr2Up(this->absErr2StatUp() + this->absErr2SystUp() + absoluteErrorSquaredLumiUp_);
      this->setAbsErr2Dw(this->absErr2StatDw() + this->absErr2SystDw() + absoluteErrorSquaredLumiDown_);
    }
    
    double absoluteErrorSquaredLumiUp_;
    double absoluteErrorSquaredLumiDown_;
};





#endif







