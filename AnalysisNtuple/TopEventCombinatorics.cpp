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

	// if (bjets.size() < 2 || ljets.size() < 2) {
	// 	return -1;
	// }

	if ( (bjets.size() + ljets.size())<4 ){
		return -1;
	}

	if (ignoreBtagInfo){
		runWithoutBInfo();
	}
	else if ( bjets.size() >= 2 ){
		run4j2b();
	}
	else if ( bjets.size() == 1 ){
		run4j1b();
	}
	else if ( bjets.size() == 0 ){
		run4j0b();
	}


	// chi2 = 9.e9;
	
	// for (int i_b1 = 0; i_b1 < bjets.size(); i_b1++){
	// 	for (int i_b2 = 0; i_b2 < bjets.size(); i_b2++){
	// 		if (i_b1 == i_b2) continue;
	// 		for (int i_j1 = 0; i_j1 < ljets.size(); i_j1++){
	// 			for (int i_j2 = i_j1+1; i_j2 < ljets.size(); i_j2++){
	// 				double comboChi2 = topChiSq(ljets.at(i_j1), ljets.at(i_j2), bjets.at(i_b1), bjets.at(i_b2), ljetsRes.at(i_j1), ljetsRes.at(i_j2), bjetsRes.at(i_b1), bjetsRes.at(i_b2));
	// 				if (comboChi2 < chi2){
	// 					chi2 = comboChi2;
	// 					bhad = bjets.at(i_b1);
	// 					blep = bjets.at(i_b2);
	// 					j1 = ljets.at(i_j1);
	// 					j2 = ljets.at(i_j2);
	// 					goodCombo = true;
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	return 0;
}

int TopEventCombinatorics::run4j2b(){
	chi2 = 9.e9;
	double comboChi2 = 9.e9;

	for (int i_b1 = 0; i_b1 < bjets.size(); i_b1++){
		for (int i_b2 = 0; i_b2 < bjets.size(); i_b2++){
			if (i_b1 == i_b2) continue;

			// for the case where nbjet>2, make a list containing all ljets and the bjets not used above, from which w-jets will be chosen
			tempJetVector.clear();
			for (int i_j1 = 0; i_j1 < ljets.size(); i_j1++){ 
				tempJetVector.push_back(ljets.at(i_j1)); 
				tempJetResVector.push_back(ljetsRes.at(i_j1)); 
			}
			for (int i_j1 = 0; i_j1 < bjets.size(); i_j1++){ 
				if (i_b1 == i_j1 || i_b2 == i_j1) continue;
				tempJetVector.push_back(bjets.at(i_j1)); 
				tempJetResVector.push_back(bjetsRes.at(i_j1)); 
			}


			for (int i_j1 = 0; i_j1 < tempJetVector.size(); i_j1++){
				for (int i_j2 = i_j1+1; i_j2 < tempJetVector.size(); i_j2++){
					comboChi2 = topChiSq(tempJetVector.at(i_j1), tempJetVector.at(i_j2), bjets.at(i_b1), bjets.at(i_b2), tempJetResVector.at(i_j1), tempJetResVector.at(i_j2), bjetsRes.at(i_b1), bjetsRes.at(i_b2));
					if (comboChi2 < chi2){
						chi2 = comboChi2;
						bhad = bjets.at(i_b1);
						blep = bjets.at(i_b2);
						j1 = tempJetVector.at(i_j1);
						j2 = tempJetVector.at(i_j2);
						goodCombo = true;
					}
				}
			}
		}
	}

	return 0;
}

int TopEventCombinatorics::run4j1b(){
	chi2 = 9.e9;
	double comboChi2 = 9.e9;
	//Use one of the bjets as the btagged one, the other comes from the list of light jets
	for (int i_b1 = 0; i_b1 < bjets.size(); i_b1++){
		for (int i_j0 = 0; i_j0 < ljets.size(); i_j0++){
			for (int i_j1 = 0; i_j1 < ljets.size(); i_j1++){
				if (i_j0 == i_j1) continue; //skip when reusing the same jet
				for (int i_j2 = 0; i_j2 < ljets.size(); i_j2++){
					if (i_j0 == i_j2) continue; //skip when reusing the same jet
					if (i_j1 == i_j2) continue; //skip when reusing the same jet
					
					//b1 is the blep, j0 is the bhad
					comboChi2 = topChiSq(ljets.at(i_j1), ljets.at(i_j2), ljets.at(i_j0), bjets.at(i_b1), ljetsRes.at(i_j1), ljetsRes.at(i_j2), ljetsRes.at(i_j0), bjetsRes.at(i_b1));
					if (comboChi2 < chi2){
						chi2 = comboChi2;
						blep = bjets.at(i_b1);
						bhad = ljets.at(i_j0);
						j1 = ljets.at(i_j1);
						j2 = ljets.at(i_j2);
						goodCombo = true;
					}

					//b1 is the bhad, j0 is the blep
					comboChi2 = topChiSq(ljets.at(i_j1), ljets.at(i_j2), bjets.at(i_b1), ljets.at(i_j0), ljetsRes.at(i_j1), ljetsRes.at(i_j2), bjetsRes.at(i_b1), ljetsRes.at(i_j0));
					if (comboChi2 < chi2){
						chi2 = comboChi2;
						bhad = bjets.at(i_b1);
						blep = ljets.at(i_j0);
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

int TopEventCombinatorics::run4j0b(){
	chi2 = 9.e9;
	double comboChi2 = 9.e9;

	for (int i_j1 = 0; i_j1 < ljets.size(); i_j1++){
		for (int i_j2 = 0; i_j2 < ljets.size(); i_j2++){
			if (i_j1 == i_j2) continue; //skip when reusing the same jet
			for (int i_j3 = 0; i_j3 < ljets.size(); i_j3++){
				if (i_j1 == i_j3) continue; //skip when reusing the same jet
				if (i_j2 == i_j3) continue; //skip when reusing the same jet

				for (int i_j4 = 0; i_j4 < ljets.size(); i_j4++){
					if (i_j1 == i_j4) continue; //skip when reusing the same jet
					if (i_j2 == i_j4) continue; //skip when reusing the same jet
					if (i_j3 == i_j4) continue; //skip when reusing the same jet

					comboChi2 = topChiSq(ljets.at(i_j3), ljets.at(i_j4), ljets.at(i_j1), ljets.at(i_j2), ljetsRes.at(i_j3), ljetsRes.at(i_j4), ljetsRes.at(i_j1), ljetsRes.at(i_j2));
					if (comboChi2 < chi2){
						chi2 = comboChi2;
						bhad = ljets.at(i_j1);
						blep = ljets.at(i_j2);
						j1   = ljets.at(i_j3);
						j2   = ljets.at(i_j4);
						goodCombo = true;
					}
				}
			}
		}
	}

	return 0;
}


int TopEventCombinatorics::runWithoutBInfo(){
	chi2 = 9.e9;
	double comboChi2 = 9.e9;

	tempJetVector.clear();
	for (int i_j1 = 0; i_j1 < ljets.size(); i_j1++){ 
		tempJetVector.push_back(ljets.at(i_j1)); 
		tempJetResVector.push_back(ljetsRes.at(i_j1)); 
	}
	for (int i_j1 = 0; i_j1 < bjets.size(); i_j1++){ 
		tempJetVector.push_back(bjets.at(i_j1)); 
		tempJetResVector.push_back(bjetsRes.at(i_j1)); 
	}

	for (int i_j1 = 0; i_j1 < tempJetVector.size(); i_j1++){
		for (int i_j2 = 0; i_j2 < tempJetVector.size(); i_j2++){
			if (i_j1 == i_j2) continue; //skip when reusing the same jet
			for (int i_j3 = 0; i_j3 < tempJetVector.size(); i_j3++){
				if (i_j1 == i_j3) continue; //skip when reusing the same jet
				if (i_j2 == i_j3) continue; //skip when reusing the same jet

				for (int i_j4 = 0; i_j4 < tempJetVector.size(); i_j4++){
					if (i_j1 == i_j4) continue; //skip when reusing the same jet
					if (i_j2 == i_j4) continue; //skip when reusing the same jet
					if (i_j3 == i_j4) continue; //skip when reusing the same jet

					comboChi2 = topChiSq(tempJetVector.at(i_j3), tempJetVector.at(i_j4), tempJetVector.at(i_j1), tempJetVector.at(i_j2), tempJetResVector.at(i_j3), tempJetResVector.at(i_j4), tempJetResVector.at(i_j1), tempJetResVector.at(i_j2));
					if (comboChi2 < chi2){
						chi2 = comboChi2;
						bhad = tempJetVector.at(i_j1);
						blep = tempJetVector.at(i_j2);
						j1   = tempJetVector.at(i_j3);
						j2   = tempJetVector.at(i_j4);
						goodCombo = true;
					}
				}
			}
		}
	}

	return 0;
}

