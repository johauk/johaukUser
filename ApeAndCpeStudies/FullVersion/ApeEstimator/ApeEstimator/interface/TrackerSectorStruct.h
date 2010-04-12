#ifndef ApeEstimator_ApeEstimator_TrackerSectorStruct_h
#define ApeEstimator_ApeEstimator_TrackerSectorStruct_h


//#include "vector"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TString.h"
//#include "TFileDirectory.h"

#include "EventVariables.h"

class TH1;
class TH2;
//class TH1F;
//class TH2F;
//class TProfile;
//class TString;
class TFileDirectory;









class TrackerSectorStruct{
  public:
  
  TrackerSectorStruct(): directory_(0),
                         norResXMax_(999.), sigmaXHitMax_(999.), sigmaXMax_(999.),
			 apeX(-1.F),
			 ResX(0), NorResX(0), XHit(0), XTrk(0),
			 SigmaX2(0), ProbX(0),
			 WidthVsPhiSensX(0), WidthVsWidthProjected(0), WidthDiffVsMaxStrip(0),
			 PWidthVsPhiSensX(0), PWidthVsWidthProjected(0), PWidthDiffVsMaxStrip(0){}
  
  
  
  
  struct CorrelationHists{
    CorrelationHists():Variable(0),
                       NorResXVsVar(0), ProbXVsVar(0),
	               SigmaXHitVsVar(0), SigmaXTrkVsVar(0), SigmaXVsVar(0),
		       PNorResXVsVar(0), PProbXVsVar(0),
		       PSigmaXHitVsVar(0), PSigmaXTrkVsVar(0), PSigmaXVsVar(0){}
    
    void fillCorrHists(const TrackStruct::HitParameterStruct& hitParameterStruct, double variable);
    
    TH1F *Variable;
    TH2F *NorResXVsVar, *ProbXVsVar,
         *SigmaXHitVsVar, *SigmaXTrkVsVar, *SigmaXVsVar;
    TProfile *PNorResXVsVar, *PProbXVsVar,
             *PSigmaXHitVsVar, *PSigmaXTrkVsVar, *PSigmaXVsVar;
  };
  
  
  void setCorrHistParams(TFileDirectory*, double, double, double);
  CorrelationHists bookCorrHists(TString, TString, TString, TString, int, int, double, double, std::string ="nphtr");
  /// same, but without booking 1D histo 
  CorrelationHists bookCorrHists(TString ,TString ,TString, int, double, double, std::string ="nphtr");
  //void fillCorrHists(double, const TrackStruct::HitParameterStruct&, CorrelationHists&);
  
  TFileDirectory *directory_;
  double norResXMax_, sigmaXHitMax_, sigmaXMax_;
  std::map<std::string,CorrelationHists> mCorrelationHists;
  
  
  std::vector<unsigned int> vRawId;
  
  float apeX;
  
  TH1 *ResX, *NorResX, *XHit, *XTrk,
      *SigmaX2, *ProbX;
  TH2 *WidthVsPhiSensX, *WidthVsWidthProjected, *WidthDiffVsMaxStrip;
  TProfile *PWidthVsPhiSensX, *PWidthVsWidthProjected, *PWidthDiffVsMaxStrip;
  
  std::map<std::string,std::vector<TH1*> > mSigmaX;
  
  
  //for every bin in sigmaX the needful histos to calculate the APE
  std::map<unsigned int, std::map<std::string,TH1*> > mBinnedHists;
  
  
  //for presenting results
  TH1 *Entries, *MeanX, *RmsX, *FitMeanX1, *ResidualWidthX1, *ApeX1,
      *FitMeanX2, *ResidualWidthX2, *ApeX2;
  
};







void
TrackerSectorStruct::setCorrHistParams(TFileDirectory *directory, double norResXMax, double sigmaXHitMax, double sigmaXMax){
  directory_ = directory;
  norResXMax_ = norResXMax;
  sigmaXHitMax_ = sigmaXHitMax;
  sigmaXMax_ = sigmaXMax;
}



TrackerSectorStruct::CorrelationHists
TrackerSectorStruct::bookCorrHists(TString varName,TString varTitle,TString labelX,TString unitX,int nBinX1D,int nBinX2D,double minBinX,double maxBinX,std::string options){
  
  std::string o(options);
  CorrelationHists correlationHists;
  
  if(!(o.find("n") != std::string::npos || o.find("p") != std::string::npos || o.find("h") != std::string::npos || 
       o.find("t") != std::string::npos || o.find("r") != std::string::npos))return correlationHists;
  
  TFileDirectory *directory(directory_);
  double norResXMax(norResXMax_), sigmaXHitMax(sigmaXHitMax_), sigmaXMax(sigmaXMax_);
  
  if(!directory)return correlationHists;
  
  
  correlationHists.Variable = directory->make<TH1F>("h_"+varName,varTitle+" "+labelX+";"+labelX+"  "+unitX+";# hits",nBinX1D,minBinX,maxBinX);
  
  if(options.find("n") != std::string::npos)
  correlationHists.NorResXVsVar = directory->make<TH2F>("h2_norResXVs"+varName,"r_{x}/#sigma_{x} vs. "+labelX+";"+labelX+"  "+unitX+";(x_{track}-x_{hit})'/#sigma_{x}",nBinX2D,minBinX,maxBinX,25,-norResXMax,norResXMax);
  if(options.find("p") != std::string::npos)
  correlationHists.ProbXVsVar = directory->make<TH2F>("h2_probXVs"+varName,"prob_{x} vs. "+labelX+";"+labelX+"  "+unitX+";prob_{x}",nBinX2D,minBinX,maxBinX,60,-0.1,1.1);
  if(options.find("h") != std::string::npos)
  correlationHists.SigmaXHitVsVar = directory->make<TH2F>("h2_sigmaXHitVs"+varName,"#sigma_{x,hit} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x,hit}  [cm]",nBinX2D,minBinX,maxBinX,50,0,sigmaXHitMax);
  if(options.find("t") != std::string::npos)
  correlationHists.SigmaXTrkVsVar = directory->make<TH2F>("h2_sigmaXTrkVs"+varName,"#sigma_{x,track} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x,track}  [cm]",nBinX2D,minBinX,maxBinX,50,0,sigmaXMax);
  if(options.find("r") != std::string::npos)
  correlationHists.SigmaXVsVar = directory->make<TH2F>("h2_sigmaXVs"+varName,"#sigma_{x} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x}  [cm]",nBinX2D,minBinX,maxBinX,50,0,sigmaXMax);
    
  if(options.find("n") != std::string::npos)
  correlationHists.PNorResXVsVar = directory->make<TProfile>("p_norResXVs"+varName,"r_{x}/#sigma_{x} vs. "+labelX+";"+labelX+"  "+unitX+";(x_{track}-x_{hit})'/#sigma_{x}",nBinX2D,minBinX,maxBinX,"s");
  if(options.find("p") != std::string::npos)
  correlationHists.PProbXVsVar = directory->make<TProfile>("p_probXVs"+varName,"prob_{x} vs. "+labelX+";"+labelX+"  "+unitX+";prob_{x}",nBinX2D,minBinX,maxBinX,"s");
  if(options.find("h") != std::string::npos)
  correlationHists.PSigmaXHitVsVar = directory->make<TProfile>("p_sigmaXHitVs"+varName,"#sigma_{x,hit} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x,hit}  [cm]",nBinX2D,minBinX,maxBinX,"s");
  if(options.find("t") != std::string::npos)
  correlationHists.PSigmaXTrkVsVar = directory->make<TProfile>("p_sigmaXTrkVs"+varName,"#sigma_{x,track} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x,track}  [cm]",nBinX2D,minBinX,maxBinX,"s");
  if(options.find("r") != std::string::npos)
  correlationHists.PSigmaXVsVar = directory->make<TProfile>("p_sigmaXVs"+varName,"#sigma_{x} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x}  [cm]",nBinX2D,minBinX,maxBinX,"s");
  
  return correlationHists;
}


TrackerSectorStruct::CorrelationHists
TrackerSectorStruct::bookCorrHists(TString varName,TString labelX,TString unitX,int nBinX,double minBinX,double maxBinX,std::string options){
  
  std::string o(options);
  CorrelationHists correlationHists;
  
  if(!(o.find("n") != std::string::npos || o.find("p") != std::string::npos || o.find("h") != std::string::npos || 
       o.find("t") != std::string::npos || o.find("r") != std::string::npos))return correlationHists;
  
  TFileDirectory *directory(directory_);
  double norResXMax(norResXMax_), sigmaXHitMax(sigmaXHitMax_), sigmaXMax(sigmaXMax_);
  
  if(!directory)return correlationHists;
  
  
  if(options.find("n") != std::string::npos)
  correlationHists.NorResXVsVar = directory->make<TH2F>("h2_norResXVs"+varName,"r_{x}/#sigma_{x} vs. "+labelX+";"+labelX+"  "+unitX+";(x_{track}-x_{hit})'/#sigma_{x}",nBinX,minBinX,maxBinX,25,-norResXMax,norResXMax);
  if(options.find("p") != std::string::npos)
  correlationHists.ProbXVsVar = directory->make<TH2F>("h2_probXVs"+varName,"prob_{x} vs. "+labelX+";"+labelX+"  "+unitX+";prob_{x}",nBinX,minBinX,maxBinX,60,-0.1,1.1);
  if(options.find("h") != std::string::npos)
  correlationHists.SigmaXHitVsVar = directory->make<TH2F>("h2_sigmaXHitVs"+varName,"#sigma_{x,hit} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x,hit}  [cm]",nBinX,minBinX,maxBinX,50,0,sigmaXHitMax);
  if(options.find("t") != std::string::npos)
  correlationHists.SigmaXTrkVsVar = directory->make<TH2F>("h2_sigmaXTrkVs"+varName,"#sigma_{x,track} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x,track}  [cm]",nBinX,minBinX,maxBinX,50,0,sigmaXMax);
  if(options.find("r") != std::string::npos)
  correlationHists.SigmaXVsVar = directory->make<TH2F>("h2_sigmaXVs"+varName,"#sigma_{x} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x}  [cm]",nBinX,minBinX,maxBinX,50,0,sigmaXMax);
    
  if(options.find("n") != std::string::npos)
  correlationHists.PNorResXVsVar = directory->make<TProfile>("p_norResXVs"+varName,"r_{x}/#sigma_{x} vs. "+labelX+";"+labelX+"  "+unitX+";(x_{track}-x_{hit})'/#sigma_{x}",nBinX,minBinX,maxBinX,"s");
  if(options.find("p") != std::string::npos)
  correlationHists.PProbXVsVar = directory->make<TProfile>("p_probXVs"+varName,"prob_{x} vs. "+labelX+";"+labelX+"  "+unitX+";prob_{x}",nBinX,minBinX,maxBinX,"s");
  if(options.find("h") != std::string::npos)
  correlationHists.PSigmaXHitVsVar = directory->make<TProfile>("p_sigmaXHitVs"+varName,"#sigma_{x,hit} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x,hit}  [cm]",nBinX,minBinX,maxBinX);
  if(options.find("t") != std::string::npos)
  correlationHists.PSigmaXTrkVsVar = directory->make<TProfile>("p_sigmaXTrkVs"+varName,"#sigma_{x,track} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x,track}  [cm]",nBinX,minBinX,maxBinX);
  if(options.find("r") != std::string::npos)
  correlationHists.PSigmaXVsVar = directory->make<TProfile>("p_sigmaXVs"+varName,"#sigma_{x} vs. "+labelX+";"+labelX+"  "+unitX+";#sigma_{x}  [cm]",nBinX,minBinX,maxBinX);
  
  return correlationHists;
}

void
TrackerSectorStruct::CorrelationHists::fillCorrHists(const TrackStruct::HitParameterStruct& hitParameterStruct, double variable){
  
  if(Variable){Variable->Fill(variable);}
  
  if(NorResXVsVar){
    NorResXVsVar->Fill(variable,hitParameterStruct.norResX);
    PNorResXVsVar->Fill(variable,hitParameterStruct.norResX);
  }
  if(ProbXVsVar){
    ProbXVsVar->Fill(variable,hitParameterStruct.probX);
    PProbXVsVar->Fill(variable,hitParameterStruct.probX);
  }
  if(SigmaXHitVsVar){
    SigmaXHitVsVar->Fill(variable,hitParameterStruct.errXHit);
    PSigmaXHitVsVar->Fill(variable,hitParameterStruct.errXHit);
  }
  if(SigmaXTrkVsVar){
    SigmaXTrkVsVar->Fill(variable,hitParameterStruct.errXTrk);
    PSigmaXTrkVsVar->Fill(variable,hitParameterStruct.errXTrk);
  }
  if(SigmaXVsVar){
    SigmaXVsVar->Fill(variable,hitParameterStruct.errX);
    PSigmaXVsVar->Fill(variable,hitParameterStruct.errX);
  }
  
}

/*
void
TrackerSectorStruct::fillCorrHists(double variable, const TrackStruct::HitParameterStruct& hitParameterStruct, CorrelationHists& corrHists){
  
  if(corrHists.Variable){corrHists.Variable->Fill(variable);}
  
  if(corrHists.NorResXVsVar){
    corrHists.NorResXVsVar->Fill(variable,hitParameterStruct.norResX);
    corrHists.PNorResXVsVar->Fill(variable,hitParameterStruct.norResX);
  }
  if(corrHists.ProbXVsVar){
    corrHists.ProbXVsVar->Fill(variable,hitParameterStruct.probX);
    corrHists.PProbXVsVar->Fill(variable,hitParameterStruct.probX);
  }
  if(corrHists.SigmaXHitVsVar){
    corrHists.SigmaXHitVsVar->Fill(variable,hitParameterStruct.errXHit);
    corrHists.PSigmaXHitVsVar->Fill(variable,hitParameterStruct.errXHit);
  }
  if(corrHists.SigmaXTrkVsVar){
    corrHists.SigmaXTrkVsVar->Fill(variable,hitParameterStruct.errXTrk);
    corrHists.PSigmaXTrkVsVar->Fill(variable,hitParameterStruct.errXTrk);
  }
  if(corrHists.SigmaXVsVar){
    corrHists.SigmaXVsVar->Fill(variable,hitParameterStruct.errX);
    corrHists.PSigmaXVsVar->Fill(variable,hitParameterStruct.errX);
  }
  
}
*/


#endif
