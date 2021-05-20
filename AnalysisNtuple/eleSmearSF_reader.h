#include<TH2F.h>
#include<TFile.h>

#include <iostream>


using namespace std;

class EleSmearSF
{
 public:
    EleSmearSF(string unc_fname){
	TFile* uncFile = TFile::Open(unc_fname.c_str(),"READ");
	uncHist_up = (TH2F*) uncFile->Get("pt_eta_ResUp");
    uncHist_do = (TH2F*) uncFile->Get("pt_eta_ResDown");

    }

    double getEleSmearSFDo(double pt, double eta);
    double getEleSmearSFUp(double pt, double eta);
    
 private:
    TH2F* uncHist_up;
    TH2F* uncHist_do;
};



double EleSmearSF::getEleSmearSFDo(double pt, double eta){


    int xBin=1;
    int yBin=1;

    if      ((pt > 10  && pt <=40)  && (eta >=0 && eta<=0.48)){xBin=1;yBin=1;}
    else if ((pt > 40  && pt <=70)  && (eta >=0 && eta<=0.48)){xBin=2;yBin=1;}
    else if ((pt > 70  && pt <=100) && (eta >=0 && eta<=0.48)){xBin=3;yBin=1;}
    else if ((pt > 100 && pt <=130) && (eta >=0 && eta<=0.48)){xBin=4;yBin=1;}
    else if ((pt > 130 && pt <=160) && (eta >=0 && eta<=0.48)){xBin=5;yBin=1;}
    else if ((pt > 160 && pt <=190) && (eta >=0 && eta<=0.48)){xBin=6;yBin=1;}
    else if ((pt > 190 && pt <=220) && (eta >=0 && eta<=0.48)){xBin=7;yBin=1;}
    else if ((pt > 220 && pt <=250) && (eta >=0 && eta<=0.48)){xBin=8;yBin=1;}
    else if ((pt > 250 && pt <=280) && (eta >=0 && eta<=0.48)){xBin=9;yBin=1;}
    else {xBin=10;yBin=1;}
    // else if ((pt > 280 && pt <=310) && (eta >=0 && eta<=0.48)){xBin=10;yBin=1;}

    double unc_SF_value = uncHist_do->GetBinContent(xBin,yBin);

    return unc_SF_value;

}


double EleSmearSF::getEleSmearSFUp(double pt, double eta){


    int xBin=1;
    int yBin=1;

    if      ((pt > 10  && pt <=40)  && (eta >=0 && eta<=0.48)){xBin=1;yBin=1;}
    else if ((pt > 40  && pt <=70)  && (eta >=0 && eta<=0.48)){xBin=2;yBin=1;}
    else if ((pt > 70  && pt <=100) && (eta >=0 && eta<=0.48)){xBin=3;yBin=1;}
    else if ((pt > 100 && pt <=130) && (eta >=0 && eta<=0.48)){xBin=4;yBin=1;}
    else if ((pt > 130 && pt <=160) && (eta >=0 && eta<=0.48)){xBin=5;yBin=1;}
    else if ((pt > 160 && pt <=190) && (eta >=0 && eta<=0.48)){xBin=6;yBin=1;}
    else if ((pt > 190 && pt <=220) && (eta >=0 && eta<=0.48)){xBin=7;yBin=1;}
    else if ((pt > 220 && pt <=250) && (eta >=0 && eta<=0.48)){xBin=8;yBin=1;}
    else if ((pt > 250 && pt <=280) && (eta >=0 && eta<=0.48)){xBin=9;yBin=1;}
    else {xBin=10;yBin=1;}

    // else if ((pt > 280 && pt <=310) && (eta >=0 && eta<=0.48)){xBin=10;yBin=1;}

    double unc_SF_value = uncHist_up->GetBinContent(xBin,yBin);

    return unc_SF_value;

}

