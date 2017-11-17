#include "TopEventCombinatorics.h"
#include "TLorentzVector.h"

double TopEventCombinatorics::topChiSq(TLorentzVector j1, TLorentzVector j2, TLorentzVector bh, TLorentzVector bl){
	
	double c = pow( (bh + j1 + j2).M() - mTop,2) + pow( (j1 + j2).M() - mW,2) + pow( (bl + lepton + met).M() - mTop,2);

}

int TopEventCombinatorics::Calculate(){

	goodCombo = false;

	if (bjets.size() < 2 || ljets.size() < 2) {
		return -1;
	}


	chi2 = 99999.;
	
	for (int i_b1 = 0; i_b1 < bjets.size(); i_b1++){
		for (int i_b2 = 0; i_b2 < bjets.size(); i_b2++){
			if (i_b1 == i_b2) continue;
			for (int i_j1 = 0; i_j1 < ljets.size(); i_j1++){
				for (int i_j2 = i_j1+1; i_j2 < ljets.size(); i_j2++){
					double comboChi2 = topChiSq(ljets.at(i_j1), ljets.at(i_j2), bjets.at(i_b1), bjets.at(i_b2));
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
