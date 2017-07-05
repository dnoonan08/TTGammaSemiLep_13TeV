isMC=999
isData=1

from ROOT import *

samples = {"TTGamma":[["TTGamma_SingleLeptFromTbar_AnalysisNtuple.root",
                       "TTGamma_SingleLeptFromT_AnalysisNtuple.root",
                       "TTGamma_Dilepton_AnalysisNtuple.root",
                       "TTGamma_Hadronic_AnalysisNtuple.root",
                       ],
                      kAzure+7,
                      "t#bar{t}+#gamma",
                      isMC
                      ],
           "TTbar":[["TTbar_AnalysisNtuple.root",
                     ],
                    kRed,
                    "t#bar{t}",
                    isMC
                    ],
           "WJets":[["W1jets_AnalysisNtuple.root",
                     "W2jets_AnalysisNtuple.root",
                     "W3jets_AnalysisNtuple.root",
                     "W4jets_AnalysisNtuple.root",
                     ],
                    kGreen+3,
                    "W+jets",
                    isMC
                    ],
           "ZJets":[["DYjets_AnalysisNtuple.root",
                     ],
                    kGreen+2,
                    "Z+jets",
                    isMC
                    ],
           "SingleTop":[["ST_s-channel_AnalysisNtuple.root",
                         "ST_t-channel_AnalysisNtuple.root",
                         "ST_tW-channel_AnalysisNtuple.root",
                         "ST_tbar-channel_AnalysisNtuple.root",
                         "ST_tbarW-channel_AnalysisNtuple.root",
                         ],
                        kOrange,
                        "Single top",
                        isMC
                        ],
           "TTV":[["TTW_AnalysisNtuple.root",
                   "TTZ_AnalysisNtuple.root",
                   ],
                  kMagenta,
                  "ttV",
                  isMC
                  ],
           "DataMu":[["Data_SingleMu_b_AnalysisNtuple.root",
                      "Data_SingleMu_c_AnalysisNtuple.root",
                      "Data_SingleMu_d_AnalysisNtuple.root",
                      "Data_SingleMu_e_AnalysisNtuple.root",
                      "Data_SingleMu_f_AnalysisNtuple.root",
                      "Data_SingleMu_g_AnalysisNtuple.root",
                      "Data_SingleMu_h_AnalysisNtuple.root",
                      ],
                     kBlack,
                     "Data",
                     isData
                     ],
           "DataEle":[["Data_SingleEle_b_AnalysisNtuple.root",
                      "Data_SingleEle_c_AnalysisNtuple.root",
                      "Data_SingleEle_d_AnalysisNtuple.root",
                      "Data_SingleEle_e_AnalysisNtuple.root",
                      "Data_SingleEle_f_AnalysisNtuple.root",
                      "Data_SingleEle_g_AnalysisNtuple.root",
                      "Data_SingleEle_h_AnalysisNtuple.root",
                       ],
                      kBlack,
                      "Data",
                      isData
                      ],
           }



# List that is the same as the keys of samples, but given in the order we want to draw
sampleList = ["TTGamma",
              "TTbar",
              "WJets",
              "ZJets",
              "SingleTop",
              "TTV",
              "Data",
              ]



