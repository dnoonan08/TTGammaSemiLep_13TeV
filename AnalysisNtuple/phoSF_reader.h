#include<TH2F.h>
#include<TFile.h>

#include <iostream>


using namespace std;

class PhotonSF
{
 public:
    PhotonSF(string id_fname, string eveto_fname, int _year){
	year = _year;
	TFile* idFile = TFile::Open(id_fname.c_str(),"READ");
	idHist = (TH2F*) idFile->Get("EGamma_SF2D");

        id_ptMax = idHist->GetYaxis()->GetXmax();
	TFile* eVetoFile = TFile::Open(eveto_fname.c_str(),"READ");
	if (year==2016){
	    eVetoHist_2D = (TH2F*) eVetoFile->Get("Scaling_Factors_HasPix_R9 Inclusive");
            veto_ptMax = eVetoHist_2D->GetYaxis()->GetXmax();
	} else if (year==2017){
	    eVetoHist_1D = (TH1F*) eVetoFile->Get("Medium_ID");
	} else if (year==2018){
	    eVetoHist_2D = (TH2F*) eVetoFile->Get("eleVeto_SF");
	    eVetoHist_Unc_2D = (TH2F*) eVetoFile->Get("eleVeto_Unc");
            veto_ptMax = eVetoHist_2D->GetXaxis()->GetXmax();
	}
    }

    std::vector<double> getPhoSF(double pt, double eta, int systLevel, bool verbose=false);

 private:
    TH2F* idHist;
    TH2F* eVetoHist_2D;
    TH2F* eVetoHist_Unc_2D;
    TH1F* eVetoHist_1D;
    int year;

    double id_ptMax;
    double veto_ptMax;


};



std::vector<double> PhotonSF::getPhoSF(double pt, double eta, int systLevel, bool verbose){
    
    int bin = idHist->FindBin(eta, min(pt, id_ptMax-0.01));

    double id_SF_value = idHist->GetBinContent(bin);
    double id_SF_error = idHist->GetBinError(bin);

    double id_SF = id_SF_value + (systLevel-1)*id_SF_error;


    double eVeto_SF;
    double eVeto_error;

    if (year==2016){
        bin = eVetoHist_2D->FindBin(abs(eta), min(pt, veto_ptMax-0.01));
        eVeto_SF = eVetoHist_2D->GetBinContent(bin);
        eVeto_error = eVetoHist_2D->GetBinError(bin);
        
    } else if (year==2017){
	if (abs(eta)< 1.5){
	    eVeto_SF = eVetoHist_1D->GetBinContent(1);
	    eVeto_error = eVetoHist_1D->GetBinError(1);
	}else{
	    eVeto_SF = eVetoHist_1D->GetBinContent(4);
	    eVeto_error = eVetoHist_1D->GetBinError(4);
	}
    } else if (year==2018){
        bin = eVetoHist_2D->FindBin(min(pt, veto_ptMax-0.01), abs(eta));
        eVeto_SF = eVetoHist_2D->GetBinContent(bin);
        eVeto_error = eVetoHist_Unc_2D->GetBinContent(bin);
    }


    eVeto_SF = eVeto_SF + (systLevel-1)*eVeto_error;

    if (verbose){
	cout << "Photon Scale Factors: " << endl;
	cout << "   ID    = " << id_SF << endl;
	cout << "   eVeto = " << eVeto_SF << endl;
	cout << "   Total = " << id_SF*eVeto_SF << endl;
    }

    

    std::vector<double> phoEffSF  {id_SF*eVeto_SF, id_SF, eVeto_SF};

    return phoEffSF;

}

