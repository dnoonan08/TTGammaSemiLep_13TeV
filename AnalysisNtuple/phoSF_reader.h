#include<TH2F.h>
#include<TFile.h>

#include <iostream>


using namespace std;

class PhotonSF
{
 public:
    PhotonSF(string id_fname){
	TFile* idFile = TFile::Open(id_fname.c_str(),"READ");
	idHist = (TH2F*) idFile->Get("EGamma_SF2D");
    }

    double getPhoSF(double pt, double eta, int systLevel);

 private:
    TH2F* idHist;

};



double PhotonSF::getPhoSF(double pt, double eta, int systLevel){


    int phoEtaRegion_ID = -1;
    int phoPtRegion_ID = -1;

    if (eta < -2.000) { phoEtaRegion_ID = 1;}
    else if (eta < -1.566) { phoEtaRegion_ID = 2;}
    else if (eta < -1.444) { phoEtaRegion_ID = 3;}
    else if (eta < -0.800) { phoEtaRegion_ID = 4;}
    else if (eta < 0.000) { phoEtaRegion_ID = 5;}
    else if (eta < 0.800) { phoEtaRegion_ID = 6;}
    else if (eta < 1.444) { phoEtaRegion_ID = 7;}
    else if (eta < 1.566) { phoEtaRegion_ID = 8;}
    else if (eta < 2.000) { phoEtaRegion_ID = 9;}
    else { phoEtaRegion_ID = 10; }

    if (pt < 35.) { phoPtRegion_ID = 1; }
    else if (pt < 50.) { phoPtRegion_ID = 2; }
    else if (pt < 100.) { phoPtRegion_ID = 3; }
    else if (pt < 200.) { phoPtRegion_ID = 4; }
    else { phoPtRegion_ID = 5; }

   

    double id_SF_value = idHist->GetBinContent(phoEtaRegion_ID,phoPtRegion_ID);
    double id_SF_error = idHist->GetBinError(phoEtaRegion_ID,phoPtRegion_ID);

    double id_SF = id_SF_value + (systLevel-1)*id_SF_error;


    double phoEffSF=id_SF;

    return phoEffSF;

}

