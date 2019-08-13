#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//#include <iostream>


using namespace std;

class MuonSF
{
 public:
    MuonSF(string idJson_fname, string isoJson_fname, string trigJson_fname){
	boost::property_tree::read_json(idJson_fname, idInfo);
	boost::property_tree::read_json(isoJson_fname, isoInfo);
	boost::property_tree::read_json(trigJson_fname, trigInfo);
    }
    double getMuSF(double pt, double eta, int systLevel);

    double doubleSetId(string _idName){
	idName = _idName;
    }
    double doubleSetIso(string _isoName){
	isoName = _isoName;
    }
    double doubleSetTrig(string _trigName){
	trigName = _trigName;
    }
    

    
 private:
    boost::property_tree::ptree idInfo;
    boost::property_tree::ptree isoInfo;
    boost::property_tree::ptree trigInfo;
    string isoName;
    string idName;
    string trigName;
};



double MuonSF::getMuSF(double pt, double eta, int systLevel){

    double abseta = fabs(eta);

    string muEtaRegion = "";
    string muPtRegion_IDIso = "";
    string muPtRegion_Trigger = "";
 
    if (abseta < 0.9) {muEtaRegion = "abseta:[0.00,0.90]";}
    else if (abseta < 1.2) {muEtaRegion = "abseta:[0.90,1.20]";}
    else if (abseta < 2.1) {muEtaRegion = "abseta:[1.20,2.10]";}
    else {muEtaRegion = "abseta:[2.10,2.40]";}
    
    if (pt<25.) { muPtRegion_IDIso = "pt:[20.00,25.00]";}
    else if (pt<30.){ muPtRegion_IDIso = "pt:[25.00,30.00]";}
    else if (pt<40.){ muPtRegion_IDIso = "pt:[30.00,40.00]";}
    else if (pt<50.){ muPtRegion_IDIso = "pt:[40.00,50.00]";}
    else if (pt<60.){ muPtRegion_IDIso = "pt:[50.00,60.00]";}
    else { muPtRegion_IDIso = "pt:[60.00,120.00]";}

    double id_SF_value = idInfo.get<double>(boost::property_tree::ptree::path_type{idName+"/abseta_pt/"+muEtaRegion+"/"+muPtRegion_IDIso+"/value",'/'});
    double id_SF_error = idInfo.get<double>(boost::property_tree::ptree::path_type{idName+"/abseta_pt/"+muEtaRegion+"/"+muPtRegion_IDIso+"/error",'/'});

    double id_SF = id_SF_value + (systLevel-1)*id_SF_error;

    double iso_SF_value = isoInfo.get<double>(boost::property_tree::ptree::path_type{isoName+"/abseta_pt/"+muEtaRegion+"/"+muPtRegion_IDIso+"/value",'/'});
    double iso_SF_error = isoInfo.get<double>(boost::property_tree::ptree::path_type{isoName+"/abseta_pt/"+muEtaRegion+"/"+muPtRegion_IDIso+"/error",'/'});

    double iso_SF = iso_SF_value + (systLevel-1)*iso_SF_error;


    double muEffSF=id_SF*iso_SF;
	
    return muEffSF;

}

