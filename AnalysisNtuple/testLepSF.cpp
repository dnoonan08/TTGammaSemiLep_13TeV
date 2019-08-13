#define testSF_cxx
#include "elemuSF_reader.h"

using namespace std;
int main(){

    MuonSF muSF = MuonSF("RunBCDEF_SF_ID.json", "RunBCDEF_SF_ISO.json", "theJSONfile_RunBtoF_Nov17Nov2017.json");


    // cout << getMuSF(1,1,1) << endl;
    // cout << getMuSF(27,1,1) << endl;
    // cout << getMuSF(27.,-1,1) << endl;
    cout << muSF.getMuSF(27.,-1.9,0) << endl;
    cout << muSF.getMuSF(27.,-1.9,1) << endl;
    cout << muSF.getMuSF(27.,-1.9,2) << endl;
    return 1;
}
