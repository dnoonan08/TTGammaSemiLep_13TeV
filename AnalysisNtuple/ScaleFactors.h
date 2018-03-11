/////////////////////////////////
// Total integrated luminosity //
/////////////////////////////////


double luminosity = 35860;
 
/////////////////////////////////////////////////
// Total number of events in the MC simulation //
/////////////////////////////////////////////////

double totalTTGamma_hadronic      = 4966371.;
double totalTTGamma_semilept_Tbar = 4836134.;
double totalTTGamma_semilept_T    = 4791766.;
double totalTTGamma_dilept        = 4907307.;

double totalTTGJets               = 3199101.; //9884993 Total before weights (6542047 +weights, 3342946 -weights)

double totalTGJets                = 310437.; //1556973 before negative weights

double totalTTbarPowheg           = 77227178.;
double totalTTbarMCatNLO          = 77227178.;

double totalTTbarMadgraph_SingleLeptFromT     = 11956689.;
double totalTTbarMadgraph_SingleLeptFromTbar  = 11943716.;
double totalTTbarMadgraph_Dilepton            = 6094300.;

double totalTTbarMadgraph         = 10139697.;

double totalWjetsInclusive   = 161142175.; // 235572523 Total before weights (198357349 +weights, 37215174 -weights)

double totalW1jets           = 45366416.;
double totalW2jets           = 30318880.;
double totalW3jets           = 39268750.;
double totalW4jets           = 18751100.;

double totalDYjetsM50       = 122053259.;
double totalDYjetsM10to50   = 71301217.;

double totalTTWtoQQ         = 833257.;
double totalTTWtoLNu        = 2160030.;
double totalTTZtoLL         = 5933898.;

double totalZGamma           = 11411341.; //Total 16679515 before negative weights 
double totalWGamma           = 17589398.; //Total 27426836 before negative weights

double totalWW               = 6987017.;
double totalWZ               = 2995783.;
double totalZZ               = 998018.;

double totalST_tchannel      = 67225849.;
double totalST_tbarchannel   = 38810350;
double totalST_schannel      = 2989123.;
double totalST_tW            = 6932903.;
double totalST_tbarW         = 6932903.;

double totalQCD_Pt20to30_Mu    = 31474692.;
double totalQCD_Pt30to50_Mu    = 29954322.;
double totalQCD_Pt50to80_Mu    = 19806515.;
double totalQCD_Pt80to120_Mu   = 13786651.;
double totalQCD_Pt120to170_Mu  =  8042452.;
double totalQCD_Pt170to300_Mu  =  7946703.;
double totalQCD_Pt300to470_Mu  =  7936465.;
double totalQCD_Pt470to600_Mu  =  3850452.;
double totalQCD_Pt600to800_Mu  =  4008200.;
double totalQCD_Pt800to1000_Mu =  3959757.;
double totalQCD_Pt1000toInf_Mu =  3985729.;
double totalQCD_Pt20to30_Ele   =  9218839.;
double totalQCD_Pt30to50_Ele   =  4730140.;
double totalQCD_Pt50to80_Ele   = 22336804.;
double totalQCD_Pt80to120_Ele  = 35841321.;
double totalQCD_Pt120to170_Ele = 35816734.;
double totalQCD_Pt170to300_Ele = 11539879.;
double totalQCD_Pt300toInf_Ele =  7373130.;

double totalGJets_HT40to100  = 4467939.;
double totalGJets_HT100to200 = 5131808.;
double totalGJets_HT200to400 = 9930766.;
double totalGJets_HT400to600 = 2529663.;
double totalGJets_HT600toInf = 2463751.;

//// systematics samples
double totalTTGamma_dilept_fsrDown      = 3983729.;
double totalTTGamma_dilept_fsrUp        = 3926890.;
double totalTTGamma_dilept_isrDown      = 3886639.;
double totalTTGamma_dilept_isrUp        = 3940857.;

double totalTTGamma_semilept_T_fsrDown  = 4813819.;
double totalTTGamma_semilept_T_fsrUp    = 4985392.;
double totalTTGamma_semilept_T_isrDown  = 4966800.;
double totalTTGamma_semilept_T_isrUp    = 4922478.;

double totalTTGamma_semilept_Tbar_fsrDown = 4770115.;
double totalTTGamma_semilept_Tbar_fsrUp   = 4802977.;
double totalTTGamma_semilept_Tbar_isrDown = 4952386.;
double totalTTGamma_semilept_Tbar_isrUp   = 4838684.;




//////////////////////////
// Cross Sections Used  //
//////////////////////////

double TTbar_xs             =  831.76;  //ttbar NNLO (http://inspirehep.net/search?p=find+eprint+1112.5675)

double TTbar_dilepton_xs             =  87.315;
double TTbar_semilept_xs             =  182.175;
double TTbar_hadronic_xs             =  831.76-TTbar_dilepton_xs-2*TTbar_semilept_xs;

double TTGJets_xs               =  3.697; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#TT_X

double TGJets_xs                =  2.967;

double TTGamma_hadronic_xs  =  3.482;   //4.599;
double TTGamma_semilept_xs  =  5.017/2.;//4.499/2.;
double TTGamma_dilept_xs    =  1.679;   //0.899;

double WjetsInclusive_xs    = 61526.7; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#W_jets

double W1jets_xs            =  9493.0;
double W2jets_xs            =  3120.0;
double W3jets_xs            =  942.3;
double W4jets_xs            =  524.2;

double DYjetsM50_xs         =  5765.4; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
double DYjetsM10to50_xs     =  18610.; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

double TTWtoQQ_xs               =  0.40620; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
double TTWtoLNu_xs              =  0.2043; //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
double TTZtoLL_xs               =  0.2728;  //????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 0.2529

double ZGamma_xs            = 131.3; // ?????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 117.864
double WGamma_xs            = 585.8; // ?????? https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns lists it as 489

double WW_xs                = 118.7;
double WZ_xs                = 47.13;
double ZZ_xs                = 16.523;  //https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns

double ST_tW_xs             =  35.85 ;
double ST_tbarW_xs          =  35.85 ;
double ST_tchannel_xs       =  136.02 ;
double ST_tbarchannel_xs    =  80.95 ;
double ST_schannel_xs       =  10.32;


//Product fo XS and filter eff from table at:
//https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD
double QCD_Pt20to30_Mu_xs    = 2960198.4;
double QCD_Pt30to50_Mu_xs    = 1652471.46;
double QCD_Pt50to80_Mu_xs    =  437504.1;
double QCD_Pt80to120_Mu_xs   =  106033.6648;
double QCD_Pt120to170_Mu_xs  =   25190.5151;
double QCD_Pt170to300_Mu_xs  =    8654.4932;
double QCD_Pt300to470_Mu_xs  =     797.3527;
double QCD_Pt470to600_Mu_xs  =      79.0255;
double QCD_Pt600to800_Mu_xs  =      25.0951;
double QCD_Pt800to1000_Mu_xs =       4.7074;
double QCD_Pt1000toInf_Mu_xs =       1.6213;
double QCD_Pt20to30_Ele_xs   = 5352960.;
double QCD_Pt30to50_Ele_xs   = 9928000.;
double QCD_Pt50to80_Ele_xs   = 2890800.;
double QCD_Pt80to120_Ele_xs  =  350000.;
double QCD_Pt120to170_Ele_xs =   62964.;
double QCD_Pt170to300_Ele_xs =   18810.;
double QCD_Pt300toInf_Ele_xs =    1350.;

// GJets cross sections taken from AN2016_471_v6 (SUSY photon + MET analysis)
double GJets_HT40to100_xs  = 20790.;
double GJets_HT100to200_xs = 9238.;
double GJets_HT200to400_xs = 2305.;
double GJets_HT400to600_xs = 274.4;
double GJets_HT600toInf_xs = 93.46;

double TTGJets_SF               = TTGJets_xs * luminosity / totalTTGJets;

double TGJets_SF               = TGJets_xs * luminosity / totalTGJets;
double TTGamma_hadronic_SF = TTGamma_hadronic_xs * luminosity / totalTTGamma_hadronic;
double TTGamma_semilept_T_SF = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_T;
double TTGamma_semilept_Tbar_SF = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_Tbar;
double TTGamma_dilept_SF   = TTGamma_dilept_xs * luminosity / totalTTGamma_dilept;

double TTbarPowheg_SF = TTbar_xs * luminosity / totalTTbarPowheg;
double TTbarMCatNLO_SF = TTbar_xs * luminosity / totalTTbarMCatNLO;
double TTbarMadgraph_SF = TTbar_xs * luminosity / totalTTbarMadgraph;

double TTbarMadgraph_SingleLeptFromT_SF = TTbar_semilept_xs * luminosity / totalTTbarMadgraph_SingleLeptFromT;
double TTbarMadgraph_SingleLeptFromTbar_SF = TTbar_semilept_xs * luminosity / totalTTbarMadgraph_SingleLeptFromTbar;
double TTbarMadgraph_Dilepton_SF = TTbar_dilepton_xs * luminosity / totalTTbarMadgraph_Dilepton;

double WjetsInclusive_SF = WjetsInclusive_xs * luminosity / totalWjetsInclusive;

double W1jets_SF = W1jets_xs * luminosity / totalW1jets;
double W2jets_SF = W2jets_xs * luminosity / totalW2jets;
double W3jets_SF = W3jets_xs * luminosity / totalW3jets;
double W4jets_SF = W4jets_xs * luminosity / totalW4jets;

double DYjetsM10to50_SF = DYjetsM10to50_xs * luminosity / totalDYjetsM10to50;
double DYjetsM50_SF = DYjetsM50_xs * luminosity / totalDYjetsM50;

double TTWtoQQ_SF = TTWtoQQ_xs * luminosity / totalTTWtoQQ;
double TTWtoLNu_SF = TTWtoLNu_xs * luminosity / totalTTWtoLNu;
double TTZtoLL_SF = TTZtoLL_xs * luminosity / totalTTZtoLL;

double ZGamma_SF = ZGamma_xs * luminosity / totalZGamma;
double WGamma_SF = WGamma_xs * luminosity / totalWGamma;

double WW_SF = WW_xs * luminosity / totalWW;
double WZ_SF = WZ_xs * luminosity / totalWZ;
double ZZ_SF = ZZ_xs * luminosity / totalZZ;

double ST_tW_SF       = ST_tW_xs * luminosity / totalST_tW;
double ST_tbarW_SF    = ST_tbarW_xs * luminosity / totalST_tbarW;
double ST_tchannel_SF = ST_tchannel_xs * luminosity / totalST_tchannel;
double ST_tbarchannel_SF = ST_tbarchannel_xs * luminosity / totalST_tbarchannel;
double ST_schannel_SF = ST_schannel_xs * luminosity / totalST_schannel;

double QCD_Pt20to30_Mu_SF    = QCD_Pt20to30_Mu_xs    * luminosity / totalQCD_Pt20to30_Mu    ;
double QCD_Pt30to50_Mu_SF    = QCD_Pt30to50_Mu_xs    * luminosity / totalQCD_Pt30to50_Mu    ;
double QCD_Pt50to80_Mu_SF    = QCD_Pt50to80_Mu_xs    * luminosity / totalQCD_Pt50to80_Mu    ;
double QCD_Pt80to120_Mu_SF   = QCD_Pt80to120_Mu_xs   * luminosity / totalQCD_Pt80to120_Mu   ;
double QCD_Pt120to170_Mu_SF  = QCD_Pt120to170_Mu_xs  * luminosity / totalQCD_Pt120to170_Mu  ;
double QCD_Pt170to300_Mu_SF  = QCD_Pt170to300_Mu_xs  * luminosity / totalQCD_Pt170to300_Mu  ;
double QCD_Pt300to470_Mu_SF  = QCD_Pt300to470_Mu_xs  * luminosity / totalQCD_Pt300to470_Mu  ;
double QCD_Pt470to600_Mu_SF  = QCD_Pt470to600_Mu_xs  * luminosity / totalQCD_Pt470to600_Mu  ;
double QCD_Pt600to800_Mu_SF  = QCD_Pt600to800_Mu_xs  * luminosity / totalQCD_Pt600to800_Mu  ;
double QCD_Pt800to1000_Mu_SF = QCD_Pt800to1000_Mu_xs * luminosity / totalQCD_Pt800to1000_Mu ;
double QCD_Pt1000toInf_Mu_SF = QCD_Pt1000toInf_Mu_xs * luminosity / totalQCD_Pt1000toInf_Mu ;
double QCD_Pt20to30_Ele_SF   = QCD_Pt20to30_Ele_xs   * luminosity / totalQCD_Pt20to30_Ele   ;
double QCD_Pt30to50_Ele_SF   = QCD_Pt30to50_Ele_xs   * luminosity / totalQCD_Pt30to50_Ele   ;
double QCD_Pt50to80_Ele_SF   = QCD_Pt50to80_Ele_xs   * luminosity / totalQCD_Pt50to80_Ele   ;
double QCD_Pt80to120_Ele_SF  = QCD_Pt80to120_Ele_xs  * luminosity / totalQCD_Pt80to120_Ele  ;
double QCD_Pt120to170_Ele_SF = QCD_Pt120to170_Ele_xs * luminosity / totalQCD_Pt120to170_Ele ;
double QCD_Pt170to300_Ele_SF = QCD_Pt170to300_Ele_xs * luminosity / totalQCD_Pt170to300_Ele ;
double QCD_Pt300toInf_Ele_SF = QCD_Pt300toInf_Ele_xs * luminosity / totalQCD_Pt300toInf_Ele ;

double GJets_HT40to100_SF  = GJets_HT40to100_xs  * luminosity / totalGJets_HT40to100  ;
double GJets_HT100to200_SF = GJets_HT100to200_xs * luminosity / totalGJets_HT100to200 ;
double GJets_HT200to400_SF = GJets_HT200to400_xs * luminosity / totalGJets_HT200to400 ;
double GJets_HT400to600_SF = GJets_HT400to600_xs * luminosity / totalGJets_HT400to600 ;
double GJets_HT600toInf_SF = GJets_HT600toInf_xs * luminosity / totalGJets_HT600toInf ;

double TTGamma_dilept_fsrDown_SF   = TTGamma_dilept_xs * luminosity / totalTTGamma_dilept_fsrDown;
double TTGamma_dilept_fsrUp_SF     = TTGamma_dilept_xs * luminosity / totalTTGamma_dilept_fsrUp;
double TTGamma_dilept_isrDown_SF   = TTGamma_dilept_xs * luminosity / totalTTGamma_dilept_isrDown;
double TTGamma_dilept_isrUp_SF     = TTGamma_dilept_xs * luminosity / totalTTGamma_dilept_isrUp;

double TTGamma_semilept_T_fsrDown_SF = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_T_fsrDown;
double TTGamma_semilept_T_fsrUp_SF   = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_T_fsrUp;
double TTGamma_semilept_T_isrDown_SF = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_T_isrDown;
double TTGamma_semilept_T_isrUp_SF   = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_T_isrUp;

double TTGamma_semilept_Tbar_fsrDown_SF = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_Tbar_fsrDown;
double TTGamma_semilept_Tbar_fsrUp_SF   = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_Tbar_fsrUp;
double TTGamma_semilept_Tbar_isrDown_SF = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_Tbar_isrDown;
double TTGamma_semilept_Tbar_isrUp_SF   = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_Tbar_isrUp;



double getEvtWeight(string sampleType){
	double evtWeight = -1.;
	if( sampleType.substr(0,4)=="Data") {evtWeight = 1.;}
	else if( sampleType=="Test") {evtWeight = 1.;}
	else if( sampleType=="TestAll") {evtWeight = 1.;}
	else if( sampleType=="TGJets"){evtWeight = TGJets_SF;} 
	else if( sampleType=="TTGJets"){evtWeight = TTGJets_SF;} 
	else if( sampleType=="TTGamma_Hadronic") {evtWeight = TTGamma_hadronic_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromTbar") {evtWeight = TTGamma_semilept_Tbar_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromT") {evtWeight = TTGamma_semilept_T_SF;}
	else if( sampleType=="TTGamma_Dilepton") {evtWeight = TTGamma_dilept_SF;}
	else if( sampleType=="TTbarPowheg") {evtWeight = TTbarPowheg_SF;}
	else if( sampleType=="TTbarPowheg1") {evtWeight = TTbarPowheg_SF;}
	else if( sampleType=="TTbarPowheg2") {evtWeight = TTbarPowheg_SF;}
	else if( sampleType=="TTbarPowheg3") {evtWeight = TTbarPowheg_SF;}
	else if( sampleType=="TTbarPowheg4") {evtWeight = TTbarPowheg_SF;}
	else if( sampleType=="TTbarMCatNLO") {evtWeight = TTbarMCatNLO_SF;}
	else if( sampleType=="TTbarMadgraph") {evtWeight = TTbarMadgraph_SF;}
	else if( sampleType=="TTbarMadgraph_Dilepton") {evtWeight = TTbarMadgraph_Dilepton_SF;}
	else if( sampleType=="TTbarMadgraph_SingleLeptFromT") {evtWeight = TTbarMadgraph_SingleLeptFromT_SF;}
	else if( sampleType=="TTbarMadgraph_SingleLeptFromTbar") {evtWeight = TTbarMadgraph_SingleLeptFromTbar_SF;}
	else if( sampleType=="WjetsInclusive") {evtWeight = WjetsInclusive_SF;}
	else if( sampleType=="WjetsInclusive1") {evtWeight = WjetsInclusive_SF;}
	else if( sampleType=="WjetsInclusive2") {evtWeight = WjetsInclusive_SF;}
	else if( sampleType=="WjetsInclusive3") {evtWeight = WjetsInclusive_SF;}
	else if( sampleType=="WjetsInclusive4") {evtWeight = WjetsInclusive_SF;}
	else if( sampleType=="WjetsInclusive5") {evtWeight = WjetsInclusive_SF;}
	else if( sampleType=="WjetsInclusive6") {evtWeight = WjetsInclusive_SF;}
	else if( sampleType=="W1jets") {evtWeight = W1jets_SF;}
	else if( sampleType=="W2jets") {evtWeight = W2jets_SF;}
	else if( sampleType=="W3jets") {evtWeight = W3jets_SF;}
	else if( sampleType=="W4jets") {evtWeight = W4jets_SF;}
	else if( sampleType=="DYjetsM10to50") {evtWeight = DYjetsM10to50_SF;}
	else if( sampleType=="DYjetsM50") {evtWeight = DYjetsM50_SF;}
	else if( sampleType=="TTWtoQQ") {evtWeight = TTWtoLNu_SF;}
	else if( sampleType=="TTWtoLNu") {evtWeight = TTWtoLNu_SF;}
	else if( sampleType=="TTZtoLL") {evtWeight = TTZtoLL_SF;}
	else if( sampleType=="ZGamma") {evtWeight = ZGamma_SF;}
	else if( sampleType=="WGamma") {evtWeight = WGamma_SF;}
	else if( sampleType=="WW") {evtWeight = WW_SF;}
	else if( sampleType=="WZ") {evtWeight = WZ_SF;}
	else if( sampleType=="ZZ") {evtWeight = ZZ_SF;}
	else if( sampleType=="ST_tW-channel") {evtWeight = ST_tW_SF;}
	else if( sampleType=="ST_tbarW-channel") {evtWeight = ST_tbarW_SF;}
	else if( sampleType=="ST_t-channel") {evtWeight = ST_tchannel_SF;}
	else if( sampleType=="ST_tbar-channel") {evtWeight = ST_tbarchannel_SF;}
	else if( sampleType=="ST_s-channel") {evtWeight = ST_schannel_SF;}
	else if( sampleType=="QCD_Pt20to30_Mu") {evtWeight = QCD_Pt20to30_Mu_SF;}
	else if( sampleType=="QCD_Pt30to50_Mu") {evtWeight = QCD_Pt30to50_Mu_SF;}
	else if( sampleType=="QCD_Pt50to80_Mu") {evtWeight = QCD_Pt50to80_Mu_SF;}
	else if( sampleType=="QCD_Pt80to120_Mu") {evtWeight = QCD_Pt80to120_Mu_SF;}
	else if( sampleType=="QCD_Pt120to170_Mu") {evtWeight = QCD_Pt120to170_Mu_SF;}
	else if( sampleType=="QCD_Pt170to300_Mu") {evtWeight = QCD_Pt170to300_Mu_SF;}
	else if( sampleType=="QCD_Pt300to470_Mu") {evtWeight = QCD_Pt300to470_Mu_SF;}
	else if( sampleType=="QCD_Pt470to600_Mu") {evtWeight = QCD_Pt470to600_Mu_SF;}
	else if( sampleType=="QCD_Pt600to800_Mu") {evtWeight = QCD_Pt600to800_Mu_SF;}
	else if( sampleType=="QCD_Pt800to1000_Mu") {evtWeight = QCD_Pt800to1000_Mu_SF;}
	else if( sampleType=="QCD_Pt1000toInf_Mu") {evtWeight = QCD_Pt1000toInf_Mu_SF;}
	else if( sampleType=="QCD_Pt20to30_Ele") {evtWeight = QCD_Pt20to30_Ele_SF;}
	else if( sampleType=="QCD_Pt30to50_Ele") {evtWeight = QCD_Pt30to50_Ele_SF;}
	else if( sampleType=="QCD_Pt50to80_Ele") {evtWeight = QCD_Pt50to80_Ele_SF;}
	else if( sampleType=="QCD_Pt80to120_Ele") {evtWeight = QCD_Pt80to120_Ele_SF;}
	else if( sampleType=="QCD_Pt120to170_Ele") {evtWeight = QCD_Pt120to170_Ele_SF;}
	else if( sampleType=="QCD_Pt170to300_Ele") {evtWeight = QCD_Pt170to300_Ele_SF;}
	else if( sampleType=="QCD_Pt300toInf_Ele") {evtWeight = QCD_Pt300toInf_Ele_SF;}
	else if( sampleType=="GJets_HT-40To100")  {evtWeight = GJets_HT40to100_SF;}
	else if( sampleType=="GJets_HT-100To200") {evtWeight = GJets_HT100to200_SF;}
	else if( sampleType=="GJets_HT-200To400") {evtWeight = GJets_HT200to400_SF;}
	else if( sampleType=="GJets_HT-400To600") {evtWeight = GJets_HT400to600_SF;}
	else if( sampleType=="GJets_HT-600ToInf") {evtWeight = GJets_HT600toInf_SF;}

	else if( sampleType=="TTGamma_Dilepton_fsrDown") {evtWeight = TTGamma_dilept_fsrDown_SF;}
	else if( sampleType=="TTGamma_Dilepton_fsrUp")   {evtWeight = TTGamma_dilept_fsrUp_SF;}
	else if( sampleType=="TTGamma_Dilepton_isrDown") {evtWeight = TTGamma_dilept_isrDown_SF;}
	else if( sampleType=="TTGamma_Dilepton_isrUp")   {evtWeight = TTGamma_dilept_isrUp_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromT_fsrDown") {evtWeight = TTGamma_semilept_T_fsrDown_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromT_fsrUp")   {evtWeight = TTGamma_semilept_T_fsrUp_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromT_isrDown") {evtWeight = TTGamma_semilept_T_isrDown_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromT_isrUp")   {evtWeight = TTGamma_semilept_T_isrUp_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromTbar_fsrDown") {evtWeight = TTGamma_semilept_Tbar_fsrDown_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromTbar_fsrUp")   {evtWeight = TTGamma_semilept_Tbar_fsrUp_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromTbar_isrDown") {evtWeight = TTGamma_semilept_Tbar_isrDown_SF;}
	else if( sampleType=="TTGamma_SingleLeptFromTbar_isrUp")   {evtWeight = TTGamma_semilept_Tbar_isrUp_SF;}
	else {
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-- Unable to find event weight for this sample --" << endl;
		cout << "-- Sample will be saved with a weight of -1    --" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;
	}

	cout << "Using event weight " << evtWeight << endl;

	return evtWeight;
}











const std::string allowedSampleTypes[99] = {"Data",
											"Data_SingleMu_b",
											"Data_SingleMu_c",
											"Data_SingleMu_d",
											"Data_SingleMu_e",
											"Data_SingleMu_f",
											"Data_SingleMu_g",
											"Data_SingleMu_h",
											"Data_SingleEle_b",
											"Data_SingleEle_c",
											"Data_SingleEle_d",
											"Data_SingleEle_e",
											"Data_SingleEle_f",
											"Data_SingleEle_g",
											"Data_SingleEle_h",
											"TTGamma_Hadronic",
											"TTGamma_SingleLeptFromTbar",
											"TTGamma_SingleLeptFromT",
											"TTGamma_Dilepton",
											"TTbarPowheg",
											"TTbarPowheg1",
											"TTbarPowheg2",
											"TTbarPowheg3",
											"TTbarPowheg4",
											"TTbarMCatNLO",
											"TTbarMadgraph",
											"TTbarMadgraph_SingleLeptFromTbar",
											"TTbarMadgraph_SingleLeptFromT",
											"TTbarMadgraph_Dilepton",
											"WjetsInclusive",
											"WjetsInclusive1",
											"WjetsInclusive2",
											"WjetsInclusive3",
											"WjetsInclusive4",
											"WjetsInclusive5",
											"WjetsInclusive6",
											"W1jets",
											"W2jets",
											"W3jets",
											"W4jets",
											"DYjetsM10to50",
											"DYjetsM50",
											"TTWtoQQ",
											"TTWtoLNu",
											"TTZtoLL",
											"ZGamma",
											"WGamma",
											"WW",
											"WZ",
											"ZZ",
											"ST_tW-channel",
											"ST_tbarW-channel",
											"ST_t-channel",
											"ST_tbar-channel",
											"ST_s-channel",
											"QCD_Pt20to30_Mu",
											"QCD_Pt30to50_Mu",
											"QCD_Pt50to80_Mu",
											"QCD_Pt80to120_Mu",
											"QCD_Pt120to170_Mu",
											"QCD_Pt170to300_Mu",
											"QCD_Pt300to470_Mu",
											"QCD_Pt470to600_Mu",
											"QCD_Pt600to800_Mu",
											"QCD_Pt800to1000_Mu",
											"QCD_Pt1000toInf_Mu",
											"QCD_Pt20to30_Ele",
											"QCD_Pt30to50_Ele",
											"QCD_Pt50to80_Ele",
											"QCD_Pt80to120_Ele",
											"QCD_Pt120to170_Ele",
											"QCD_Pt170to300_Ele",
											"QCD_Pt300toInf_Ele",
											"GJets_HT-40To100",
											"GJets_HT-100To200",
											"GJets_HT-200To400",
											"GJets_HT-400To600",
											"GJets_HT-600ToInf",
											"TGJets",
											"TTGJets",
											"TTGamma_SingleLeptFromTbar_isrUp",
											"TTGamma_SingleLeptFromT_isrUp",
											"TTGamma_Dilepton_isrUp",
											"TTGamma_SingleLeptFromTbar_isrDown",
											"TTGamma_SingleLeptFromT_isrDown",
											"TTGamma_Dilepton_isrDown",
											"TTGamma_SingleLeptFromTbar_fsrUp",
											"TTGamma_SingleLeptFromT_fsrUp",
											"TTGamma_Dilepton_fsrUp",
											"TTGamma_SingleLeptFromTbar_fsrDown",
											"TTGamma_SingleLeptFromT_fsrDown",
											"TTGamma_Dilepton_fsrDown",
											"TestAll",
											"Test",
                                                                                        };


