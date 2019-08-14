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

    void setIdName(string _idName){
	idName = _idName;
    }
    void setIsoName(string _isoName){
	isoName = _isoName;
    }
    void setTrigName(string _trigName){
	trigName = _trigName;
    }
    bool splitSystsId = false;
    bool splitSystsIso = false;
    bool splitSystsTrig = false;
    
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

    string muEtaRegion_IDIso = "";
    string muPtRegion_IDIso = "";
    string muEtaRegion_Trigger = "";
    string muPtRegion_Trigger = "";
 
    if (abseta < 0.9) {muEtaRegion_IDIso = "abseta:[0.00,0.90]";}
    else if (abseta < 1.2) {muEtaRegion_IDIso = "abseta:[0.90,1.20]";}
    else if (abseta < 2.1) {muEtaRegion_IDIso = "abseta:[1.20,2.10]";}
    else {muEtaRegion_IDIso = "abseta:[2.10,2.40]";}
    
    if (pt<25.) { muPtRegion_IDIso = "pt:[20.00,25.00]";}
    else if (pt<30.){ muPtRegion_IDIso = "pt:[25.00,30.00]";}
    else if (pt<40.){ muPtRegion_IDIso = "pt:[30.00,40.00]";}
    else if (pt<50.){ muPtRegion_IDIso = "pt:[40.00,50.00]";}
    else if (pt<60.){ muPtRegion_IDIso = "pt:[50.00,60.00]";}
    else { muPtRegion_IDIso = "pt:[60.00,120.00]";}

    if (abseta < 0.9) {muEtaRegion_Trigger = "abseta:[0.0,0.9]";}
    else if (abseta < 1.2) {muEtaRegion_Trigger = "abseta:[0.9,1.2]";}
    else if (abseta < 2.1) {muEtaRegion_Trigger = "abseta:[1.2,2.1]";}
    else {muEtaRegion_Trigger = "abseta:[2.1,2.4]";}

    if (pt < 32.) { muPtRegion_Trigger = "pt:[29.0,32.0]";}
    else if (pt < 40.) { muPtRegion_Trigger = "pt:[32.0,40.0]";}
    else if (pt < 50.) { muPtRegion_Trigger = "pt:[40.0,50.0]";}
    else if (pt < 60.) { muPtRegion_Trigger = "pt:[50.0,60.0]";}
    else if (pt < 120.) { muPtRegion_Trigger = "pt:[60.0,120.0]";}
    else if (pt < 200.) { muPtRegion_Trigger = "pt:[120.0,200.0]";}
    else { muPtRegion_Trigger = "pt:[200.0,1200.0]";}


    double id_SF_value = idInfo.get<double>(boost::property_tree::ptree::path_type{idName+"/"+muEtaRegion_IDIso+"/"+muPtRegion_IDIso+"/value",'/'});
    double id_SF_error = 0.;
    if (splitSystsId){
	double statErr = idInfo.get<double>(boost::property_tree::ptree::path_type{idName+"/"+muEtaRegion_IDIso+"/"+muPtRegion_IDIso+"/stat",'/'});
	double systErr = idInfo.get<double>(boost::property_tree::ptree::path_type{idName+"/"+muEtaRegion_IDIso+"/"+muPtRegion_IDIso+"/syst",'/'});
	id_SF_error = pow(statErr*statErr+systErr*systErr,0.5);
    } else{
	id_SF_error = idInfo.get<double>(boost::property_tree::ptree::path_type{idName+"/"+muEtaRegion_IDIso+"/"+muPtRegion_IDIso+"/error",'/'});
    }
    double id_SF = id_SF_value + (systLevel-1)*id_SF_error;


    double iso_SF_value = isoInfo.get<double>(boost::property_tree::ptree::path_type{isoName+"/"+muEtaRegion_IDIso+"/"+muPtRegion_IDIso+"/value",'/'});
    double iso_SF_error = 0.;
    if (splitSystsIso){
	double statErr = isoInfo.get<double>(boost::property_tree::ptree::path_type{isoName+"/"+muEtaRegion_IDIso+"/"+muPtRegion_IDIso+"/stat",'/'});
	double systErr = isoInfo.get<double>(boost::property_tree::ptree::path_type{isoName+"/"+muEtaRegion_IDIso+"/"+muPtRegion_IDIso+"/syst",'/'});
	iso_SF_error = pow(statErr*statErr+systErr*systErr,0.5);
    } else{
	iso_SF_error = isoInfo.get<double>(boost::property_tree::ptree::path_type{isoName+"/"+muEtaRegion_IDIso+"/"+muPtRegion_IDIso+"/error",'/'});
    }
    double iso_SF = iso_SF_value + (systLevel-1)*iso_SF_error;


    double trig_SF_value = trigInfo.get<double>(boost::property_tree::ptree::path_type{trigName+"/"+muEtaRegion_Trigger+"/"+muPtRegion_Trigger+"/value",'/'});
    double trig_SF_error = 0.;
    if (splitSystsTrig){
	double statErr = trigInfo.get<double>(boost::property_tree::ptree::path_type{trigName+"/"+muEtaRegion_Trigger+"/"+muPtRegion_Trigger+"/stat",'/'});
	double systErr = trigInfo.get<double>(boost::property_tree::ptree::path_type{trigName+"/"+muEtaRegion_Trigger+"/"+muPtRegion_Trigger+"/syst",'/'});
	trig_SF_error = pow(statErr*statErr+systErr*systErr,0.5);
    } else{
	trig_SF_error = trigInfo.get<double>(boost::property_tree::ptree::path_type{trigName+"/"+muEtaRegion_Trigger+"/"+muPtRegion_Trigger+"/error",'/'});
    }
    double trig_SF = trig_SF_value + (systLevel-1)*trig_SF_error;

    /* cout << id_SF_value << ", " << iso_SF_value << ", " << trig_SF_value << endl; */
    /* cout << id_SF << ", " << iso_SF << ", " << trig_SF << endl; */
    double muEffSF=id_SF*iso_SF*trig_SF;
	
    return muEffSF;

}

