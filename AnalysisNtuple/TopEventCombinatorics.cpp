#include "TopEventCombinatorics.h"
#include "TLorentzVector.h"
#include <iostream>

double TopEventCombinatorics::topChiSq(TLorentzVector j1, double sigma_j1,
				       TLorentzVector j2, double sigma_j2,
				       TLorentzVector bh, double sigma_bh,
				       TLorentzVector bl, double sigma_bl,
				       double nu_pz_hypo){

    met.SetXYZM(met.Px(), met.Py(), nu_pz_hypo, 0);

    double sigma2_tHad = 34.0*34.0;
    double sigma2_WHad = 24.0*24.0;
    double sigma2_tLep = 30.0*30.0;
    // double sigma2_tHad = sigma_j1*sigma_j1 + sigma_j2*sigma_j2 + sigma_bh*sigma_bh;
    // double sigma2_WHad = sigma_j1*sigma_j1 + sigma_j2*sigma_j2;
    // double sigma2_tLep = sigma_bl*sigma_bl + METRes*METRes + leptonRes*leptonRes;
    // double sigma2_tLep = sigma_bl*sigma_bl + pow(met.Pt()*METRes,2) + pow(lepton.Pt()*leptonRes,2);

    // if (!useResolutions){
    //     sigma2_tHad = 1.;
    //     sigma2_WHad = 1.;
    //     sigma2_tLep = 1.;
    // }
    double tHadM = (bh + j1 + j2).M();
    double WHadM = (j1 + j2).M();
    double tLepM = (bl + lepton + met).M();
    
    double c = pow( tHadM - mTop,2)/(sigma2_tHad) + pow( WHadM - mW,2)/(sigma2_WHad) + pow( tLepM - mTop,2)/(sigma2_tLep);

    return c;
}

int TopEventCombinatorics::Calculate(){

    goodCombo = false;

    if (jets.size() < 4){
	return -1;
    }

    bJetsList.clear();
    nu_pz_List.clear();

    if (nBjetSize==-1){
	for (unsigned int i =0; i < jets.size(); i++) bJetsList.push_back(i);
    } else {
	for (unsigned int i =0; i < jets.size(); i++){
	    if (btag[i] > btagThresh) bJetsList.push_back(i);
	}
	if (bJetsList.size() < nBjetSize){
	    for (unsigned int i =0; i < jets.size(); i++){
		if (std::find(bJetsList.begin(), bJetsList.end(), i) == bJetsList.end()){
		    bJetsList.push_back(i);
		}
		if (bJetsList.size()==nBjetSize) break;
	    }
	}
    }

    double _nu_pz_1 = metZ.Calculate();
    double _nu_pz_2 = metZ.getOther();

    nu_pz_List.push_back(_nu_pz_1);
    if (_nu_pz_1!=_nu_pz_2) nu_pz_List.push_back(_nu_pz_2);

    chi2_TT = 9.e9;
    double comboChi2 = 9.e9;

    for (const auto& i_bhad : bJetsList){
	for (const auto& i_blep : bJetsList){
	    if (i_bhad==i_blep) continue;
	    for (unsigned int i_j1=0; i_j1<jets.size(); i_j1++){
		if (i_bhad==i_j1 || i_blep==i_j1) continue; //skip if i_j1 is already used as a bjet
		for (unsigned int i_j2=i_j1+1; i_j2<jets.size(); i_j2++){
		    if (i_bhad==i_j2 || i_blep==i_j2) continue; //skip if i_j2 is already used as a bjet

		    //loop over nu_pz solutions
		    for (const auto& test_nu_pz: nu_pz_List){

			comboChi2 = topChiSq(jets.at(i_j1), jetsRes.at(i_j1),
                                             jets.at(i_j2), jetsRes.at(i_j2),
                                             jets.at(i_bhad), jetsRes.at(i_bhad),
                                             jets.at(i_blep), jetsRes.at(i_blep),
                                             test_nu_pz);
                        
                        //std::cout << comboChi2 << ":   " << i_bhad << ", " << i_blep << ", " << i_j1 << ", " << i_j2 << std::endl;

			if (comboChi2 < chi2_TT){
			    chi2_TT = comboChi2;
			    blep_idx = i_blep;
			    bhad_idx = i_bhad;
			    j1_idx = i_j1;
			    j2_idx = i_j2;
			    nu_pz = test_nu_pz;
			    goodCombo = true;
			}
		    }
		}
	    }
	}
    }

    return 0;
}


double TopEventCombinatorics::tstarChiSq(TLorentzVector j1,
                                         TLorentzVector j2,
                                         TLorentzVector bh,
                                         TLorentzVector bl,
                                         TLorentzVector hadDecay,
                                         TLorentzVector lepDecay,
                                         double nu_pz_hypo){

    met.SetXYZM(met.Px(), met.Py(), nu_pz_hypo, 0);

    //https://arxiv.org/pdf/1711.10949.pdf
    double sigma2_tHad = 34.0*34.0;
    double sigma2_WHad = 24.0*24.0;
    double sigma2_tLep = 30.0*30.0;
    double sigma2_tstar = 230.0*230.0;

    double chi2_tHad = pow( (bh + j1 + j2).M() - mTop,2)/sigma2_tHad;
    double chi2_WHad = pow( (j1 + j2).M() - mW,2)/sigma2_WHad;
    double chi2_tLep = pow( (bl + lepton + met).M() - mTop,2)/sigma2_tLep;
    double chi2_tStar = pow( (bh + j1 + j2 + hadDecay).M() - (bl + lepton + met + lepDecay).M(),2)/sigma2_tstar;

    return chi2_tHad + chi2_WHad + chi2_tLep + chi2_tStar;

}

double TopEventCombinatorics::tstarChiSq_boosted(TLorentzVector ak8j,
                                                 TLorentzVector bl,
                                                 TLorentzVector hadDecay,
                                                 TLorentzVector lepDecay,
                                                 double nu_pz_hypo){
    
    met.SetXYZM(met.Px(), met.Py(), nu_pz_hypo, 0);

    //https://arxiv.org/pdf/1711.10949.pdf
    double sigma2_tHad = 34.0*34.0;
    double sigma2_WHad = 24.0*24.0;
    double sigma2_tLep = 30.0*30.0;
    double sigma2_tstar = 230.0*230.0;

    double chi2_tHad = pow( ak8j.M() - mTop,2)/sigma2_tHad;
    double chi2_tLep = pow( (bl + lepton + met).M() - mTop,2)/sigma2_tLep;
    double chi2_tStar = pow( (ak8j + hadDecay).M() - (bl + lepton + met + lepDecay).M(),2)/sigma2_tstar;

    return chi2_tHad + chi2_tLep + chi2_tStar;

}

int TopEventCombinatorics::CalculateTstarGluGlu(int N){

    goodCombo_TstarGluGlu = false;

    if (jets.size() < 6){
	return -1;
    }

    int nJets = jets.size();
    if (N>0) nJets = std::min(nJets,N);

    nu_pz_List.clear();

    // count the number of btags in the leading N jets
    int nBtags = 0;
    for (unsigned int i =0; i < nJets; i++){
        if (btag[i] > btagThresh) nBtags += 1;
    }
    // if more than 2 btags, set at 2
    if (nBtags>2){
        nBtags = 2;
    }

    double _nu_pz_1 = metZ.Calculate();
    double _nu_pz_2 = metZ.getOther();

    nu_pz_List.push_back(_nu_pz_1);
    if (_nu_pz_1!=_nu_pz_2) nu_pz_List.push_back(_nu_pz_2);

    chi2_TstarGluGlu = 9.e9;
    double comboChi2 = 9.e9;

    for (unsigned int i_bhad=0; i_bhad<nJets; i_bhad++){
        int bcandHad_tag = 0;
        if (btag[i_bhad]>btagThresh) bcandHad_tag = 1;
        for (unsigned int i_blep=0; i_blep<nJets; i_blep++){
	    if (i_bhad==i_blep) continue;
            int bcandLep_tag = 0;
            if (btag[i_blep]>btagThresh) bcandLep_tag = 1;

            // skip combinations which haven't used all of the btagged jets as b-candidates
            if ((bcandHad_tag + bcandLep_tag) != nBtags) continue;

	    for (unsigned int i_j1=0; i_j1<nJets; i_j1++){
		if (i_bhad==i_j1 || i_blep==i_j1) continue; //skip if i_j1 is already used as a bjet

		for (unsigned int i_j2=i_j1+1; i_j2<nJets; i_j2++){
		    if (i_bhad==i_j2 || i_blep==i_j2) continue; //skip if i_j2 is already used as a bjet

                    for (unsigned int i_ghad=0; i_ghad<nJets; i_ghad++){
                        if (i_bhad==i_ghad || i_blep==i_ghad || i_ghad==i_j1 || i_ghad==i_j2) continue; //skip if i_ghad is already used as a bjet or one of the light jets

                        for (unsigned int i_glep=0; i_glep<nJets; i_glep++){
                            if (i_bhad==i_glep || i_blep==i_glep || i_glep==i_j1 || i_glep==i_j2 || i_glep==i_ghad) continue; //skip if i_j1 is already used as a bjet or one of the light jets

                            //loop over nu_pz solutions
                            for (const auto& test_nu_pz: nu_pz_List){

                                comboChi2 = tstarChiSq(jets.at(i_j1),
                                                       jets.at(i_j2),
                                                       jets.at(i_bhad),
                                                       jets.at(i_blep),
                                                       jets.at(i_ghad),
                                                       jets.at(i_glep),
                                                       test_nu_pz);

                                if (comboChi2 < chi2_TstarGluGlu){
                                    chi2_TstarGluGlu = comboChi2;
                                    blep_idx = i_blep;
                                    bhad_idx = i_bhad;
                                    j1_idx = i_j1;
                                    j2_idx = i_j2;
                                    ghad_idx = i_ghad;
                                    glep_idx = i_glep;
                                    nu_pz = test_nu_pz;
                                    goodCombo_TstarGluGlu = true;
                                }
                            }
			}
		    }
		}
	    }
	}
    }

    return 0;
}



int TopEventCombinatorics::CalculateTstarGluGamma(int N){

    goodCombo_TstarGluGamma = false;

    if (jets.size() < 5){
	return -1;
    }

    int nJets = jets.size();

    if (N>0) nJets = std::min(nJets,N);

    nu_pz_List.clear();

    // count number of btags in the jet list
    int nTags = 0;
    for (unsigned int i =0; i < nJets; i++){
        if (btag[i] > btagThresh) nTags += 1;
    }
    if (nTags>2) nTags=2;

    double _nu_pz_1 = metZ.Calculate();
    double _nu_pz_2 = metZ.getOther();

    nu_pz_List.push_back(_nu_pz_1);
    if (_nu_pz_1!=_nu_pz_2) nu_pz_List.push_back(_nu_pz_2);

    chi2_TstarGluGamma = 9.e9;
    double comboChi2 = 9.e9;

    for (unsigned int i_pho=0; i_pho<photons.size(); i_pho++){
        for (unsigned int i_bhad=0; i_bhad<nJets; i_bhad++){
            for (unsigned int i_blep=0; i_blep<nJets; i_blep++){
                if (i_bhad==i_blep) continue;
                int comboTags = 1*(btag[i_bhad] > btagThresh) + 1*(btag[i_blep] > btagThresh);
                if (comboTags!=nTags) continue;

                for (unsigned int i_j1=0; i_j1<nJets; i_j1++){
                    if (i_bhad==i_j1 || i_blep==i_j1) continue; //skip if i_j1 is already used as a bjet

                    for (unsigned int i_j2=i_j1+1; i_j2<nJets; i_j2++){
                        if (i_bhad==i_j2 || i_blep==i_j2) continue; //skip if i_j2 is already used as a bjet

                        for (unsigned int i_glu=0; i_glu<nJets; i_glu++){
                            if (i_bhad==i_glu || i_blep==i_glu || i_glu==i_j1 || i_glu==i_j2) continue; //skip if i_glu is already used as a bjet or one of the light jets
                            //loop over nu_pz solutions
                            for (const auto& test_nu_pz: nu_pz_List){

                                // calculate the chi2, assuming the photon is on the leptonic decay side
                                comboChi2 = tstarChiSq(jets.at(i_j1),
                                                       jets.at(i_j2),
                                                       jets.at(i_bhad),
                                                       jets.at(i_blep),
                                                       jets.at(i_glu), //gluon in hadronic decay side
                                                       photons.at(i_pho), //photon in leptonic decay side
                                                       test_nu_pz);

                                if (comboChi2 < chi2_TstarGluGamma){
                                    chi2_TstarGluGamma = comboChi2;
                                    blep_idx = i_blep;
                                    bhad_idx = i_bhad;
                                    j1_idx = i_j1;
                                    j2_idx = i_j2;
                                    g_idx = i_glu;
                                    pho_idx = i_pho;
                                    photonIsLeptonSide=true;
                                    nu_pz = test_nu_pz;
                                    goodCombo_TstarGluGamma = true;
                                }

                                // calculate the chi2 again, assuming the photon is on the hadronic decay side
                                comboChi2 = tstarChiSq(jets.at(i_j1),
                                                       jets.at(i_j2),
                                                       jets.at(i_bhad),
                                                       jets.at(i_blep),
                                                       photons.at(i_pho), //photon in hadronic decay side
                                                       jets.at(i_glu), //gluon in leptonic decay side
                                                       test_nu_pz);

                                if (comboChi2 < chi2_TstarGluGamma){
                                    chi2_TstarGluGamma = comboChi2;
                                    blep_idx = i_blep;
                                    bhad_idx = i_bhad;
                                    j1_idx = i_j1;
                                    j2_idx = i_j2;
                                    g_idx = i_glu;
                                    pho_idx = i_pho;
                                    photonIsLeptonSide=false;
                                    nu_pz = test_nu_pz;
                                    goodCombo_TstarGluGamma = true;
                                }
                            }
			}
		    }
		}
	    }
	}
    }

    return 0;
}

int TopEventCombinatorics::CalculateTstarGluGamma_Boosted(int N){

    goodCombo_TstarGluGamma = false;

    if (jets.size() < 2){
	return -1;
    }
    if (ak8jets.size() < 1){
	return -1;
    }

    int nJets = jets.size();
    if (N>0) nJets = std::min(nJets,N);

    nu_pz_List.clear();

    // count number of btags in the jet list
    int nTags = 0;
    for (unsigned int i =0; i < nJets; i++){
        if (btag[i] > btagThresh) nTags += 1;
    }
    if (nTags>1) nTags=1;

    double _nu_pz_1 = metZ.Calculate();
    double _nu_pz_2 = metZ.getOther();

    nu_pz_List.push_back(_nu_pz_1);
    if (_nu_pz_1!=_nu_pz_2) nu_pz_List.push_back(_nu_pz_2);

    chi2_TstarGluGamma = 9.e9;
    double comboChi2 = 9.e9;

    for (unsigned int i_pho=0; i_pho<photons.size(); i_pho++){
        for (unsigned int i_blep=0; i_blep<nJets; i_blep++){
            if (nTags>0 && btag[i_blep]<btagThresh) continue;
            for (unsigned int i_glu=0; i_glu<nJets; i_glu++){
                if (i_blep==i_glu) continue; //skip if i_glu is already used as a bjet or one of the light jets
                for (unsigned int i_tHad=0; i_tHad<ak8jets.size(); i_tHad++){
                
                    //loop over nu_pz solutions
                    for (const auto& test_nu_pz: nu_pz_List){

                        // calculate the chi2, assuming the photon is on the leptonic decay side
                        comboChi2 = tstarChiSq_boosted(ak8jets.at(i_tHad),
                                                       jets.at(i_blep),
                                                       jets.at(i_glu), //gluon in hadronic decay side
                                                       photons.at(i_pho), //photon in leptonic decay side
                                                       test_nu_pz);
                        
                        if (comboChi2 < chi2_TstarGluGamma){
                            chi2_TstarGluGamma = comboChi2;
                            blep_idx = i_blep;
                            tHad_idx = i_tHad;
                            g_idx = i_glu;
                            pho_idx = i_pho;
                            photonIsLeptonSide=true;
                            nu_pz = test_nu_pz;
                            goodCombo_TstarGluGamma = true;
                        }

                        // calculate the chi2, assuming the photon is on the leptonic decay side
                        comboChi2 = tstarChiSq_boosted(ak8jets.at(i_tHad),
                                                       jets.at(i_blep),
                                                       photons.at(i_pho), //photon in hadronic decay side
                                                       jets.at(i_glu), //gluon in leptonic decay side
                                                       test_nu_pz);

                        if (comboChi2 < chi2_TstarGluGamma){
                            chi2_TstarGluGamma = comboChi2;
                            blep_idx = i_blep;
                            tHad_idx = i_tHad;
                            g_idx = i_glu;
                            pho_idx = i_pho;
                            photonIsLeptonSide=false;
                            nu_pz = test_nu_pz;
                            goodCombo_TstarGluGamma = true;
                        }
                    }
		}
	    }
	}
    }

    return 0;
}

