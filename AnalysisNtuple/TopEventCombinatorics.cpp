#include "TopEventCombinatorics.h"
#include "TLorentzVector.h"
#include <iostream>

double TopEventCombinatorics::topChiSq(TLorentzVector j1, TLorentzVector j2, TLorentzVector bh, TLorentzVector bl, double sigma_j1, double sigma_j2, double sigma_bh, double sigma_bl){
	
	double sigma2_tHad = sigma_j1*sigma_j1 + sigma_j2*sigma_j2 + sigma_bh*sigma_bh;
	double sigma2_WHad = sigma_j1*sigma_j1 + sigma_j2*sigma_j2;
	double sigma2_tLep = sigma_bl*sigma_bl + pow(met.Pt()*METerror,2) + pow(lepton.Pt()*Leperror,2);

	if (!useResolutions){
		sigma2_tHad = 1.;
		sigma2_WHad = 1.;
		sigma2_tLep = 1.;
	}
	double c = pow( (bh + j1 + j2).M() - mTop,2)/sigma2_tHad + pow( (j1 + j2).M() - mW,2)/sigma2_WHad + pow( (bl + lepton + met).M() - mTop,2)/sigma2_tLep;

}

int TopEventCombinatorics::Calculate(){

	goodCombo = false;

	if (bjets.size() < 2 || ljets.size() < 2) {
		return -1;
	}


	chi2 = 9.e9;
	
	for (int i_b1 = 0; i_b1 < bjets.size(); i_b1++){
		for (int i_b2 = 0; i_b2 < bjets.size(); i_b2++){
			if (i_b1 == i_b2) continue;
			for (int i_j1 = 0; i_j1 < ljets.size(); i_j1++){
				for (int i_j2 = i_j1+1; i_j2 < ljets.size(); i_j2++){
					double comboChi2 = topChiSq(ljets.at(i_j1), ljets.at(i_j2), bjets.at(i_b1), bjets.at(i_b2), ljetsRes.at(i_j1), ljetsRes.at(i_j2), bjetsRes.at(i_b1), bjetsRes.at(i_b2));
					if (comboChi2 < chi2){
						chi2 = comboChi2;
						bhad = bjets.at(i_b1);
						blep = bjets.at(i_b2);
						j1 = ljets.at(i_j1);
						j2 = ljets.at(i_j2);
						goodCombo = true;
					}
				}
			}
		}
	}

	return 0;
}
