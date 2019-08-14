#include<TH2F.h>
#include<TFile.h>

using namespace std;

class ElectronSF
{
 public:
    ElectronSF(string id_fname, string reco_fname){
	TFile* idFile = TFile::Open(id_fname.c_str(),"READ");
	idHist = (TH2F*) idFile->Get("EGamma_SF2D");

	TFile* recoFile = TFile::Open(reco_fname.c_str(),"READ");
	recoHist = (TH2F*) recoFile->Get("EGamma_SF2D");
    }

    double getEleSF(double pt, double eta, int systLevel);


 private:
    TH2F* idHist;
    TH2F* recoHist;
};



double ElectronSF::getEleSF(double pt, double eta, int systLevel){


    int eleEtaRegion_ID = -1;
    int elePtRegion_ID = -1;

    int eleEtaRegion_RECO = -1;
    int elePtRegion_RECO = -1;

    if (eta < -2.000) { eleEtaRegion_ID = 1;}
    else if (eta < -1.566) { eleEtaRegion_ID = 2;}
    else if (eta < -1.444) { eleEtaRegion_ID = 3;}
    else if (eta < -0.800) { eleEtaRegion_ID = 4;}
    else if (eta < 0.000) { eleEtaRegion_ID = 5;}
    else if (eta < 0.800) { eleEtaRegion_ID = 6;}
    else if (eta < 1.444) { eleEtaRegion_ID = 7;}
    else if (eta < 1.566) { eleEtaRegion_ID = 8;}
    else if (eta < 2.000) { eleEtaRegion_ID = 9;}
    else { eleEtaRegion_ID = 10; }

    if (pt < 20.) { elePtRegion_ID = 1; }
    else if (pt < 35.) { elePtRegion_ID = 2; }
    else if (pt < 50.) { elePtRegion_ID = 3; }
    else if (pt < 100.) { elePtRegion_ID = 4; }
    else if (pt < 200.) { elePtRegion_ID = 5; }
    else { elePtRegion_ID = 6; }


    if (eta < -2.000) { eleEtaRegion_RECO = 1;}
    else if (eta < -1.566) { eleEtaRegion_RECO = 2;}
    else if (eta < -1.444) { eleEtaRegion_RECO = 3;}
    else if (eta < -1.000) { eleEtaRegion_RECO = 4;}
    else if (eta < -0.500) { eleEtaRegion_RECO = 5;}
    else if (eta < 0.000) { eleEtaRegion_RECO = 6;}
    else if (eta < 0.500) { eleEtaRegion_RECO = 7;}
    else if (eta < 1.000) { eleEtaRegion_RECO = 8;}
    else if (eta < 1.444) { eleEtaRegion_RECO = 9;}
    else if (eta < 1.566) { eleEtaRegion_RECO= 10;}
    else if (eta < 2.000) { eleEtaRegion_RECO= 11;}
    else { eleEtaRegion_RECO = 12; }

    if (pt < 45.) { elePtRegion_RECO = 1; }
    else if (pt < 75.) { elePtRegion_RECO = 2; }
    else if (pt < 100.) { elePtRegion_RECO = 3; }
    else { elePtRegion_RECO = 4; }

   

    double id_SF_value = idHist->GetBinContent(eleEtaRegion_ID,elePtRegion_ID);
    double id_SF_error = idHist->GetBinError(eleEtaRegion_ID,elePtRegion_ID);

    double id_SF = id_SF_value + (systLevel-1)*id_SF_error;

    double reco_SF_value = recoHist->GetBinContent(eleEtaRegion_RECO,elePtRegion_RECO);
    double reco_SF_error = recoHist->GetBinError(eleEtaRegion_RECO,elePtRegion_RECO);

    double reco_SF = reco_SF_value + (systLevel-1)*reco_SF_error;

    double eleEffSF=id_SF*reco_SF;

    return eleEffSF;

}

