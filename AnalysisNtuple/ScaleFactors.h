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

double totalST_tchannel      = 67225849.;
double totalST_tbarchannel   = 38810350;
double totalST_schannel      = 2989123.;
double totalST_tW            = 6932903.;
double totalST_tbarW         = 6932903.;

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

double ST_tW_xs             =  35.85 ;
double ST_tbarW_xs          =  35.85 ;
double ST_tchannel_xs       =  136.02 ;
double ST_tbarchannel_xs    =  80.95 ;
double ST_schannel_xs       =  10.32;



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

double ST_tW_SF       = ST_tW_xs * luminosity / totalST_tW;
double ST_tbarW_SF    = ST_tbarW_xs * luminosity / totalST_tbarW;
double ST_tchannel_SF = ST_tchannel_xs * luminosity / totalST_tchannel;
double ST_tbarchannel_SF = ST_tbarchannel_xs * luminosity / totalST_tbarchannel;
double ST_schannel_SF = ST_schannel_xs * luminosity / totalST_schannel;


