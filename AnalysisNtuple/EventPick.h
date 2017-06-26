#ifndef EVENTPICK_H
#define EVENTPICK_H

#include<vector>
#include<string>
#include<set>
#include<iostream>
#include<TH1F.h>
#include<TH1D.h>

#include"EventTree.h"
#include"Selector.h"

class EventPick{
public:
	EventPick(std::string titleIn);
	~EventPick();
	
	void process_event(const EventTree* inp_tree, const Selector* inp_selector, double weight=1.0);
	void print_cutflow_mu(TH1D* _cutflow);
	void print_cutflow_ele(TH1D* _cutflow);
	
	std::string title;
	
	// selected object indices
	std::vector<int> Electrons;
	std::vector<int> ElectronsLoose;
	std::vector<int> ElectronsMedium;
	std::vector<int> Muons;
	std::vector<int> MuonsLoose;
	std::vector<int> Jets;
	std::vector<int> bJets;
	// indices and selection cuts for photons
	std::vector<int> Photons;
	std::vector<int> PhotonsPresel;
	std::vector<bool> PhoPassChHadIso;
	std::vector<bool> PhoPassPhoIso;
	std::vector<bool> PhoPassSih;
	
	// delta R cuts
	double veto_jet_dR;
	double veto_lep_jet_dR;
	double veto_pho_jet_dR;
	double veto_pho_lep_dR;
	
	// cuts as parameters, to modify easily
	double MET_cut;
	bool no_trigger;

	int Nlep_eq;
	
	int Njet_ge;
	int NBjet_ge;
	int SkimNjet_ge;
	int SkimNBjet_ge;

	int Jet_Pt_cut_1;
	int Jet_Pt_cut_2;
	int Jet_Pt_cut_3;	
	int Nele_eq;
	int Nmu_eq;
	int NEleVeto_le;
	
	int Npho_ge;
	int NlooseMuVeto_le;
	int NlooseEleVeto_le;
	int NmediumEleVeto_le;
	
	bool skimEle;
	bool skimMu;

	// variables showing passing or failing selections
	bool passSkim;
	bool passPresel_ele; // passed preselection
	bool passAll_ele; // single flag: event passed all cuts: preselection + photon
	bool passPresel_mu; // passed preselection
	bool passAll_mu; // single flag: event passed all cuts: preselection + photon
	bool passFirstcut; // pass the sync cut	
	// histograms
	std::vector<TH1D*> histVector;
	TH1D* cutFlow_mu;
	TH1D* cutFlowWeight_mu;
	TH1D* cutFlow_ele;
	TH1D* cutFlowWeight_ele;
	TH1D* genPhoRegionWeight;
	TH1D* genPhoRegionWeight_1l_2l;
	TH1D* genPhoRegionWeight_1fiducial;
	TH1D* genPhoMinDR;

private:
	const EventTree* tree;
	const Selector* selector;
	
	void clear_vectors();
	void set_cutflow_labels(TH1D* hist);
	double dR_jet_ele(int jetInd, int eleInd);
	double dR_jet_mu(int jetInd, int muInd);
	double dR_jet_pho(int jetInd, int phoInd);
	double dR_ele_pho(int eleInd, int phoInd);
	double dR_mu_pho(int muInd, int phoInd);
};
#endif
