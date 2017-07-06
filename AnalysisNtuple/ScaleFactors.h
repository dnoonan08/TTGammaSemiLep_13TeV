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


double totalTTbarPowheg           = 77227178.;
double totalTTbarMCatNLO          = 77227178.;

double totalW1jets           = 45366416.;
double totalW2jets           = 30318880.;
double totalW3jets           = 39268750.;
double totalW4jets           = 18751100;

double totalDYjets           = 27652599.; 

double totalTTW              = 2160030.;
double totalTTZ              = 59339060.;

double totalZGamma           = 14372399.;
double totalWGamma           = 1.;


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
double totalQCD_Pt800to1000_Mu =        1.;
double totalQCD_Pt1000toInf_Mu =        1.;
double totalQCD_Pt20to30_Ele   =  9218839.;
double totalQCD_Pt30to50_Ele   =  4730140.;
double totalQCD_Pt50to80_Ele   = 22336804.;
double totalQCD_Pt80to120_Ele  = 35841321.;
double totalQCD_Pt120to170_Ele = 35816734.;
double totalQCD_Pt170to300_Ele = 11539879.;
double totalQCD_Pt300toInf_Ele =  7373130.;



//////////////////////////
// Cross Sections Used  //
//////////////////////////

double TTbar_xs             =  831.76;

double TTGamma_hadronic_xs  =  4.599;
double TTGamma_semilept_xs  =  4.499/2.;
double TTGamma_dilept_xs    =  0.899;

double W1jets_xs            =  9493.0;
double W2jets_xs            =  3120.0;
double W3jets_xs            =  942.3;
double W4jets_xs            =  524.2;
double DYjets_xs            =  5765.4; 

double TTW_xs               =  0.57;
double TTZ_xs               =  0.839;

double ZGamma_xs            = 131.3;
double WGamma_xs            = 585.8;

double ST_tW_xs             =  35.85 ;
double ST_tbarW_xs          =  35.85 ;
double ST_tchannel_xs       =  136.02 ;
double ST_tbarchannel_xs    =  80.95 ;
double ST_schannel_xs       =  10.32;



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



double TTGamma_hadronic_SF = TTGamma_hadronic_xs * luminosity / totalTTGamma_hadronic;
double TTGamma_semilept_T_SF = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_T;
double TTGamma_semilept_Tbar_SF = TTGamma_semilept_xs * luminosity / totalTTGamma_semilept_Tbar;
double TTGamma_dilept_SF   = TTGamma_dilept_xs * luminosity / totalTTGamma_dilept;

double TTbarPowheg_SF = TTbar_xs * luminosity / totalTTbarPowheg;
double TTbarMCatNLO_SF = TTbar_xs * luminosity / totalTTbarMCatNLO;

double W1jets_SF = W1jets_xs * luminosity / totalW1jets;
double W2jets_SF = W2jets_xs * luminosity / totalW2jets;
double W3jets_SF = W3jets_xs * luminosity / totalW3jets;
double W4jets_SF = W4jets_xs * luminosity / totalW4jets;

double DYjets_SF = DYjets_xs * luminosity / totalDYjets;

double TTW_SF = TTW_xs * luminosity / totalTTW;
double TTZ_SF = TTZ_xs * luminosity / totalTTZ;

double ZGamma_SF = ZGamma_xs * luminosity / totalZGamma;
double WGamma_SF = WGamma_xs * luminosity / totalWGamma;

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
