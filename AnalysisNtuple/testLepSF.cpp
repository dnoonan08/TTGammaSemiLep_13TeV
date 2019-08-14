#define testSF_cxx
#include "muSF_reader.h"
#include "eleSF_reader.h"
#include "phoSF_reader.h"

using namespace std;
int main(){

    MuonSF muSF = MuonSF("../MuEGammaScaleFactors/mu2017/RunBCDEF_SF_ID.json", 
			 "../MuEGammaScaleFactors/mu2017/RunBCDEF_SF_ISO.json", 
			 "../MuEGammaScaleFactors/mu2017/theJSONfile_RunBtoF_Nov17Nov2017.json");

    muSF.setIdName("NUM_TightID_DEN_genTracks/abseta_pt");
    muSF.setIsoName("NUM_TightRelIso_DEN_TightIDandIPCut/abseta_pt");
    muSF.setTrigName("IsoMu27_PtEtaBins/abseta_pt_DATA");

    cout << muSF.getMuSF(29.5,0,1) << endl;

    ElectronSF eleSF = ElectronSF("../MuEGammaScaleFactors/ele2017/2017_ElectronTight.root",
				  "../MuEGammaScaleFactors/ele2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");

    cout << eleSF.getEleSF(29.5,0,1) << endl;


    PhotonSF phoSF = PhotonSF("../MuEGammaScaleFactors/pho2017/2017_PhotonsTight.root");

    cout << phoSF.getPhoSF(150,2.3,1) << endl;

    return 1;
}
