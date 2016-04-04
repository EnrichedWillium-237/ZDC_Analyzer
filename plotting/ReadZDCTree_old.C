# include "TCanvas.h"
# include "TFile.h"
# include "TH1.h"
# include "TH2.h"
# include "TLeaf.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPad.h"
# include "TPaveText.h"
# include "TProfile.h"
# include "TStyle.h"
# include "TTree.h"
# include <iostream>


static const int nTimeSlices = 10;
static const int TSnoiseMin = 8; // min and max time slices for noise subtraction
static const int TSnoiseMax = 9; // (default time slices 8 and 9)
static const int nEMChannels = 5;
static const int nHadChannels = 4;

//static const int bxmin = 0;
//static const int bxmax = 3500;
// begining of bunch crossings
static const int bxwstrt = 30; // how early into the bxing to start
static const int bxwend = 80; // set to 0 for the end of bxing

static const int bxmin0 = 10 + bxwstrt;
static const int bxmin1 = 100 + bxwstrt;
static const int bxmin2 = 290 + bxwstrt;
static const int bxmin3 = 440 + bxwstrt;
static const int bxmin4 = 630 + bxwstrt;
static const int bxmin5 = 810 + bxwstrt;
static const int bxmin6 = 990 + bxwstrt;
static const int bxmin7 = 1170 + bxwstrt;
static const int bxmin8 = 1520 + bxwstrt;
static const int bxmin9 = 1700 + bxwstrt;
static const int bxmin10 = 1880 + bxwstrt;
static const int bxmin11 = 2060 + bxwstrt;
static const int bxmin12 = 2200 + bxwstrt;
static const int bxmin13 = 2410 + bxwstrt;
static const int bxmin14 = 2590 + bxwstrt;
static const int bxmin15 = 2770 + bxwstrt;
static const int bxmin16 = 2950 + bxwstrt;
static const int bxmin17 = 3110 + bxwstrt;

// end of bunch crossings
static const int bxwm = 40;
/*
 static const int bxmin0 = 70 - bxwm;
 static const int bxmin1 = 250 - bxwm;
 static const int bxmin2 = 410 - bxwm;
 static const int bxmin3 = 600 - bxwm;
 static const int bxmin4 = 780 - bxwm;
 static const int bxmin5 = 970 - bxwm;
 static const int bxmin6 = 1150 - bxwm;
 static const int bxmin7 = 1300 - bxwm;
 static const int bxmin8 = 1670 - bxwm;
 static const int bxmin9 = 1860 - bxwm;
 static const int bxmin10 = 2040 - bxwm;
 static const int bxmin11 = 2200 - bxwm;
 static const int bxmin12 = 2380 - bxwm;
 static const int bxmin13 = 2570 - bxwm;
 static const int bxmin14 = 2750 - bxwm;
 static const int bxmin15 = 2930 - bxwm;
 static const int bxmin16 = 3100 - bxwm;
 static const int bxmin17 = 3270 - bxwm;
 */

static const float gainEMp[5] = {1., 1., 1.2, 1.6, 1.4};
static const float gainHADp[4] = {1., 3., 1., 1.};
static const float gainEMm[5] = {1.25, 1.5, 1.45, 0.79, 1.};
static const float gainHADm[4] = {0.37, 3.4, 1., 1.1};
//static const float gainEMp[5] = {.02, .02, .024, .032, .028};
//static const float gainHADp[4] = {.02, .06, .02, .02};
//static const float gainEMm[5] = {.025, .03, .029, .0158, .02};
//static const float gainHADm[4] = {.0074, .068, .02, .22};

TFile * fin;

TTree * ZDCRecTree;
TTree * ZDCDigiTree;
TTree * BeamTree;

TH1F * Pos_hist_1D;
TH1F * Pos_hist_1DSum;
TH2F * Pos_hist_2D;
TH1F * Pos_hist_1D_NoNoiseSubbed;
TH1F * Pos_hist_1DSumNoNoiseSubbed;
TH2F * Pos_hist_2D_NoNoiseSubbed;

TH1F * Neg_hist_1D;
TH1F * Neg_hist_1DSum;
TH2F * Neg_hist_2D;
TH1F * Neg_hist_1D_NoNoiseSubbed;
TH1F * Neg_hist_1DSumNoNoiseSubbed;
TH2F * Neg_hist_2D_NoNoiseSubbed;

TH1F * hcent;
TH2F * hcentPos_2DNoiseSubbed;
TH2F * hcentPos_2D_NoNoiseSubbed;
TH2F * hcentNeg_2DNoiseSubbed;
TH2F * hcentNeg_2D_NoNoiseSubbed;

TH1F * hNoff;
TH2F * hNoffPos_2DNoiseSubbed;
TH2F * hNoffPos_2D_NoNoiseSubbed;
TH2F * hNoffNeg_2DNoiseSubbed;
TH2F * hNoffNeg_2D_NoNoiseSubbed;

TH1F * hBunchXing;

TH1F * hPosSig_vs_tmslc;
TH1F * hNegSig_vs_tmslc;

// hists for individual channels
TH2F * hZDCpEM_2D[nTimeSlices][nEMChannels];
TH2F * hZDCpHAD_2D[nTimeSlices][nHadChannels];
TH1F * hZDCpEMsig[nTimeSlices][nEMChannels];
TH1F * hZDCpHADsig[nTimeSlices][nHadChannels];

TH2F * hZDCnEM_2D[nTimeSlices][nEMChannels];
TH2F * hZDCnHAD_2D[nTimeSlices][nHadChannels];
TH1F * hZDCnEMsig[nTimeSlices][nEMChannels];
TH1F * hZDCnHADsig[nTimeSlices][nHadChannels];

TLeaf * CENTRAL;
TLeaf * NOFF;
TLeaf * BUNCHXING;

TLeaf * PHAD1fC; // PHAD1
TLeaf * PHAD1ADC;
TLeaf * PHAD2fC; // PHAD2
TLeaf * PHAD2ADC;
TLeaf * PHAD3fC; // PHAD3
TLeaf * PHAD3ADC;
TLeaf * PHAD4fC; // PHAD4
TLeaf * PHAD4ADC;
TLeaf * PEM1fC;  // PEM1
TLeaf * PEM1ADC;
TLeaf * PEM2fC;  // PEM2
TLeaf * PEM2ADC;
TLeaf * PEM3fC;  // PEM3
TLeaf * PEM3ADC;
TLeaf * PEM4fC;  // PEM4
TLeaf * PEM4ADC;
TLeaf * PEM5fC;  // PEM5
TLeaf * PEM5ADC;

TLeaf * NHAD1fC; // NHAD1
TLeaf * NHAD1ADC;
TLeaf * NHAD2fC; // NHAD2
TLeaf * NHAD2ADC;
TLeaf * NHAD3fC; // NHAD3
TLeaf * NHAD3ADC;
TLeaf * NHAD4fC; // NHAD4
TLeaf * NHAD4ADC;
TLeaf * NEM1fC;  // NEM1
TLeaf * NEM1ADC;
TLeaf * NEM2fC;  // NEM2
TLeaf * NEM2ADC;
TLeaf * NEM3fC;  // NEM3
TLeaf * NEM3ADC;
TLeaf * NEM4fC;  // NEM4
TLeaf * NEM4ADC;
TLeaf * NEM5fC;  // NEM5
TLeaf * NEM5ADC;

Double_t posEM1fC[10], posEM1ADC[10];
Double_t posEM2fC[10], posEM2ADC[10];
Double_t posEM3fC[10], posEM3ADC[10];
Double_t posEM4fC[10], posEM4ADC[10];
Double_t posEM5fC[10], posEM5ADC[10];
Double_t posHD1fC[10], posHD1ADC[10];
Double_t posHD2fC[10], posHD2ADC[10];
Double_t posHD3fC[10], posHD3ADC[10];
Double_t posHD4fC[10], posHD4ADC[10];

Double_t negEM1fC[10], negEM1ADC[10];
Double_t negEM2fC[10], negEM2ADC[10];
Double_t negEM3fC[10], negEM3ADC[10];
Double_t negEM4fC[10], negEM4ADC[10];
Double_t negEM5fC[10], negEM5ADC[10];
Double_t negHD1fC[10], negHD1ADC[10];
Double_t negHD2fC[10], negHD2ADC[10];
Double_t negHD3fC[10], negHD3ADC[10];
Double_t negHD4fC[10], negHD4ADC[10];
//    Double_t         centrality[1];
Double_t centrality;
Double_t noff;
Double_t bxing;

Double_t HADsumPos, EMsumPos, ETsumPos;
Double_t HADsumNeg, EMsumNeg, ETsumNeg;

Double_t HADsum_NNSpos, EMsum_NNSpos, ETsum_NNSpos;
Double_t HADsum_NNSneg, EMsum_NNSneg, ETsum_NNSneg;

Int_t nevents;


float PHAD1TotalSignal,PHAD2TotalSignal,PHAD3TotalSignal,PHAD4TotalSignal;
float PEM1TotalSignal,PEM2TotalSignal,PEM3TotalSignal,PEM4TotalSignal,PEM5TotalSignal;

float NHAD1TotalSignal,NHAD2TotalSignal,NHAD3TotalSignal,NHAD4TotalSignal;
float NEM1TotalSignal,NEM2TotalSignal,NEM3TotalSignal,NEM4TotalSignal,NEM5TotalSignal;

// noise
float PEM1TotalNoise,PEM2TotalNoise,PEM3TotalNoise,PEM4TotalNoise,PEM5TotalNoise;
float PHAD1TotalNoise,PHAD2TotalNoise,PHAD3TotalNoise,PHAD4TotalNoise;

float NEM1TotalNoise,NEM2TotalNoise,NEM3TotalNoise,NEM4TotalNoise,NEM5TotalNoise;
float NHAD1TotalNoise,NHAD2TotalNoise,NHAD3TotalNoise,NHAD4TotalNoise;

void GetLeafs() {
    
//    CENTRAL  = (TLeaf*) CENTTree->GetLeaf("Cent_HFtowers");
//    NOFF     = (TLeaf*) CENTTree->GetLeaf("NTrackOff");
    CENTRAL  = (TLeaf*) ZDCRecTree->GetLeaf("Cent_HFtowers");
//    NOFF     = (TLeaf*) ZDCRecTree->GetLeaf("NTracksOff");
    NOFF     = (TLeaf*) ZDCRecTree->GetLeaf("hiNpixelTracks");
    BUNCHXING = (TLeaf*) BeamTree->GetLeaf("BunchXing");
    
    PHAD1fC  = (TLeaf*) ZDCDigiTree->GetLeaf("posHD1cFtsz");
    PHAD1ADC = (TLeaf*) ZDCDigiTree->GetLeaf("posHD1ADCtsz");
    PHAD2fC  = (TLeaf*) ZDCDigiTree->GetLeaf("posHD2cFtsz");
    PHAD2ADC = (TLeaf*) ZDCDigiTree->GetLeaf("posHD2ADCtsz");
    PHAD3fC  = (TLeaf*) ZDCDigiTree->GetLeaf("posHD3cFtsz");
    PHAD3ADC = (TLeaf*) ZDCDigiTree->GetLeaf("posHD3ADCtsz");
    PHAD4fC  = (TLeaf*) ZDCDigiTree->GetLeaf("posHD4cFtsz");
    PHAD4ADC = (TLeaf*) ZDCDigiTree->GetLeaf("posHD4ADCtsz");
    PEM1fC   = (TLeaf*) ZDCDigiTree->GetLeaf("posEM1cFtsz");
    PEM1ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("posEM1ADCtsz");
    PEM2fC   = (TLeaf*) ZDCDigiTree->GetLeaf("posEM2cFtsz");
    PEM2ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("posEM2ADCtsz");
    PEM3fC   = (TLeaf*) ZDCDigiTree->GetLeaf("posEM3cFtsz");
    PEM3ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("posEM3ADCtsz");
    PEM4fC   = (TLeaf*) ZDCDigiTree->GetLeaf("posEM4cFtsz");
    PEM4ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("posEM4ADCtsz");
    PEM5fC   = (TLeaf*) ZDCDigiTree->GetLeaf("posEM5cFtsz");
    PEM5ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("posEM5ADCtsz");
    
    NHAD1fC  = (TLeaf*) ZDCDigiTree->GetLeaf("negHD1cFtsz");
    NHAD1ADC = (TLeaf*) ZDCDigiTree->GetLeaf("negHD1ADCtsz");
    NHAD2fC  = (TLeaf*) ZDCDigiTree->GetLeaf("negHD2cFtsz");
    NHAD2ADC = (TLeaf*) ZDCDigiTree->GetLeaf("negHD2ADCtsz");
    NHAD3fC  = (TLeaf*) ZDCDigiTree->GetLeaf("negHD3cFtsz");
    NHAD3ADC = (TLeaf*) ZDCDigiTree->GetLeaf("negHD3ADCtsz");
    NHAD4fC  = (TLeaf*) ZDCDigiTree->GetLeaf("negHD4cFtsz");
    NHAD4ADC = (TLeaf*) ZDCDigiTree->GetLeaf("negHD4ADCtsz");
    NEM1fC   = (TLeaf*) ZDCDigiTree->GetLeaf("negEM1cFtsz");
    NEM1ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("negEM1ADCtsz");
    NEM2fC   = (TLeaf*) ZDCDigiTree->GetLeaf("negEM2cFtsz");
    NEM2ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("negEM2ADCtsz");
    NEM3fC   = (TLeaf*) ZDCDigiTree->GetLeaf("negEM3cFtsz");
    NEM3ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("negEM3ADCtsz");
    NEM4fC   = (TLeaf*) ZDCDigiTree->GetLeaf("negEM4cFtsz");
    NEM4ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("negEM4ADCtsz");
    NEM5fC   = (TLeaf*) ZDCDigiTree->GetLeaf("negEM5cFtsz");
    NEM5ADC  = (TLeaf*) ZDCDigiTree->GetLeaf("negEM5ADCtsz");
    
    HADsumPos = 0;
    EMsumPos = 0;
    ETsumPos = 0;
    
    HADsumNeg = 0;
    EMsumNeg = 0;
    ETsumNeg = 0;
    
    HADsum_NNSpos = 0;
    EMsum_NNSpos = 0;
    ETsum_NNSpos = 0;
    
    HADsum_NNSneg = 0;
    EMsum_NNSneg = 0;
    ETsum_NNSneg = 0;
    
    //Double_t HADcal=0;
    //Double_t EMcal=0;
    
    nevents = ZDCDigiTree->GetEntries();
}

void ReadZDCTree(int ievent)
{
    ZDCRecTree->GetEntry(ievent);
    centrality=CENTRAL->GetValue();
    noff=(NOFF->GetValue());
//        cout<<"noff = "<<noff<<endl;
    BeamTree->GetEntry(ievent);
    bxing = BUNCHXING->GetValue();
    hcent->Fill(centrality);
    hNoff->Fill(noff);
    hBunchXing->Fill(bxing);
  
    if ((bxing>=bxmin0 && bxing<=(bxmin0+bxwend)) || (bxing>=bxmin1 && bxing<=(bxmin1+bxwend))
        || (bxing>=bxmin2 && bxing<=(bxmin2+bxwend)) || (bxing>=bxmin3 && bxing<=(bxmin3+bxwend))
        || (bxing>=bxmin4 && bxing<=(bxmin4+bxwend)) || (bxing>=bxmin5 && bxing<=(bxmin5+bxwend))
        || (bxing>=bxmin6 && bxing<=(bxmin6+bxwend)) || (bxing>=bxmin7 && bxing<=(bxmin7+bxwend))
        || (bxing>=bxmin8 && bxing<=(bxmin7+bxwend)) || (bxing>=bxmin9 && bxing<=(bxmin9+bxwend))
        || (bxing>=bxmin10 && bxing<=(bxmin10+bxwend)) || (bxing>=bxmin11 && bxing<=(bxmin11+bxwend))
        || (bxing>=bxmin12 && bxing<=(bxmin12+bxwend)) || (bxing>=bxmin13 && bxing<=(bxmin13+bxwend))
        || (bxing>=bxmin14 && bxing<=(bxmin14+bxwend)) || (bxing>=bxmin15 && bxing<=(bxmin15+bxwend))
        || (bxing>=bxmin16 && bxing<=(bxmin16+bxwend)) || (bxing>=bxmin17 && bxing<=(bxmin17+bxwend))
        ) {
//    if(centrality<=200){ // centrality cut
    
    // uncomment below for whole calculation
//    PHAD1TotalSignal = 0;
//    PHAD2TotalSignal = 0;
//    PHAD3TotalSignal = 0;
//    PHAD4TotalSignal = 0;
//    PEM1TotalSignal  = 0;
//    PEM2TotalSignal  = 0;
//    PEM3TotalSignal  = 0;
//    PEM4TotalSignal  = 0;
//    PEM5TotalSignal  = 0;
//    
//    NHAD1TotalSignal = 0;
//    NHAD2TotalSignal = 0;
//    NHAD3TotalSignal = 0;
//    NHAD4TotalSignal = 0;
//    NEM1TotalSignal  = 0;
//    NEM2TotalSignal  = 0;
//    NEM3TotalSignal  = 0;
//    NEM4TotalSignal  = 0;
//    NEM5TotalSignal  = 0;
    
    // analyze timeslices of interest
//    for(int iTS = 4; iTS<=4; iTS++){
    for (int iTS = 0; iTS<=9; iTS++) {
        PHAD1TotalSignal = 0;
        PHAD2TotalSignal = 0;
        PHAD3TotalSignal = 0;
        PHAD4TotalSignal = 0;
        PEM1TotalSignal  = 0;
        PEM2TotalSignal  = 0;
        PEM3TotalSignal  = 0;
        PEM4TotalSignal  = 0;
        PEM5TotalSignal  = 0;
        
        NHAD1TotalSignal = 0;
        NHAD2TotalSignal = 0;
        NHAD3TotalSignal = 0;
        NHAD4TotalSignal = 0;
        NEM1TotalSignal  = 0;
        NEM2TotalSignal  = 0;
        NEM3TotalSignal  = 0;
        NEM4TotalSignal  = 0;
        NEM5TotalSignal  = 0;
        
        posHD1fC[iTS] = (PHAD1fC->GetValue(iTS));
        posHD2fC[iTS] = (PHAD2fC->GetValue(iTS));
        posHD3fC[iTS] = (PHAD3fC->GetValue(iTS));
        posHD4fC[iTS] = (PHAD4fC->GetValue(iTS));
        posEM1fC[iTS] = (PEM1fC->GetValue(iTS));
        posEM2fC[iTS] = (PEM2fC->GetValue(iTS));
        posEM3fC[iTS] = (PEM3fC->GetValue(iTS));
        posEM4fC[iTS] = (PEM4fC->GetValue(iTS));
        posEM5fC[iTS] = (PEM5fC->GetValue(iTS));
        
        negHD1fC[iTS] = (NEM4fC->GetValue(iTS));
        negHD2fC[iTS] = (NHAD2fC->GetValue(iTS));
        negHD3fC[iTS] = (NHAD3fC->GetValue(iTS));
        negHD4fC[iTS] = (NHAD4fC->GetValue(iTS));
        negEM1fC[iTS] = (NEM3fC->GetValue(iTS));
        negEM2fC[iTS] = (NHAD1fC->GetValue(iTS));
        negEM3fC[iTS] = (NEM1fC->GetValue(iTS));
        negEM4fC[iTS] = (NEM2fC->GetValue(iTS));
        negEM5fC[iTS] = (NEM5fC->GetValue(iTS));
        // default channels on minus side
        //        negHD1fC[iTS] = (NHAD1fC->GetValue(iTS));
        //        negHD2fC[iTS] = (NHAD2fC->GetValue(iTS));
        //        negHD3fC[iTS] = (NHAD3fC->GetValue(iTS));
        //        negHD4fC[iTS] = (NHAD4fC->GetValue(iTS));
        //        negEM1fC[iTS] = (NEM1fC->GetValue(iTS));
        //        negEM2fC[iTS] = (NEM2fC->GetValue(iTS));
        //        negEM3fC[iTS] = (NEM3fC->GetValue(iTS));
        //        negEM4fC[iTS] = (NEM4fC->GetValue(iTS));
        //        negEM5fC[iTS] = (NEM5fC->GetValue(iTS));

    
        // take the fC value of a timeslice and add it to the totalSignal of that detector section
        // ZDC plus
        if(posHD1fC[iTS]<0){
            posHD1fC[iTS]=0;
        }  // ensures that we cannot have posative values of charge
        PHAD1TotalSignal=PHAD1TotalSignal + gainHADp[0]*posHD1fC[iTS];
        if(posHD2fC[iTS]<0){
            posHD2fC[iTS]=0;
        }
        PHAD2TotalSignal=PHAD2TotalSignal + gainHADp[1]*posHD2fC[iTS];
        if(posHD3fC[iTS]<0){
            posHD3fC[iTS]=0;
        }
        PHAD3TotalSignal=PHAD3TotalSignal + gainHADp[2]*posHD3fC[iTS];
        if(posHD4fC[iTS]<0){
            posHD4fC[iTS]=0;
        }
        PHAD4TotalSignal=PHAD4TotalSignal + gainHADp[3]*posHD4fC[iTS];
        if(posEM1fC[iTS]<0){
            posEM1fC[iTS]=0;
        }
        PEM1TotalSignal=PEM1TotalSignal + gainEMp[0]*posEM1fC[iTS];
        if(posEM2fC[iTS]<0){
            posEM2fC[iTS]=0;
        }
        PEM2TotalSignal=PEM2TotalSignal + gainEMp[1]*posEM2fC[iTS];
        if(posEM3fC[iTS]<0){
            posEM3fC[iTS]=0;
        }
        PEM3TotalSignal=PEM3TotalSignal + gainEMp[2]*posEM3fC[iTS];
        if(posEM4fC[iTS]<0){
            posEM4fC[iTS]=0;
        }
        PEM4TotalSignal=PEM4TotalSignal + gainEMp[3]*posEM4fC[iTS];
        if(posEM5fC[iTS]<0){
            posEM5fC[iTS]=0;
        }
        PEM5TotalSignal=PEM5TotalSignal + gainEMp[4]*posEM5fC[iTS];
        
        // ZDC minus
        if(negHD1fC[iTS]<0){
            negHD1fC[iTS]=0;
        }  // ensures that we cannot have negative values of charge
        NHAD1TotalSignal=NHAD1TotalSignal + gainHADm[0]*negHD1fC[iTS];
        if(negHD2fC[iTS]<0){
            negHD2fC[iTS]=0;
        }
        NHAD2TotalSignal=NHAD2TotalSignal + gainHADm[1]*negHD2fC[iTS];
        if(negHD3fC[iTS]<0){
            negHD3fC[iTS]=0;
        }
        NHAD3TotalSignal=NHAD3TotalSignal + gainHADm[2]*negHD3fC[iTS];
        if(negHD4fC[iTS]<0){
            negHD4fC[iTS]=0;
        }
        NHAD4TotalSignal=NHAD4TotalSignal + gainHADm[3]*negHD4fC[iTS];
        if(negEM1fC[iTS]<0){
            negEM1fC[iTS]=0;
        }
        NEM1TotalSignal=NEM1TotalSignal + gainEMm[0]*negEM1fC[iTS];
        if(negEM2fC[iTS]<0){
            negEM2fC[iTS]=0;
        }
        NEM2TotalSignal=NEM2TotalSignal + gainEMm[1]*negEM2fC[iTS];
        if(negEM3fC[iTS]<0){
            negEM3fC[iTS]=0;
        }
        NEM3TotalSignal=NEM3TotalSignal + gainEMm[2]*negEM3fC[iTS];
        if(negEM4fC[iTS]<0){
            negEM4fC[iTS]=0;
        }
        NEM4TotalSignal=NEM4TotalSignal + gainEMm[3]*negEM4fC[iTS];
        if(negEM5fC[iTS]<0){
            negEM5fC[iTS]=0;
        }
        NEM5TotalSignal=NEM5TotalSignal + gainEMm[4]*negEM5fC[iTS];
        
        // fill individual channels
        for (int EMChan = 1; EMChan<=nEMChannels; EMChan++) {
            hZDCpEM_2D[iTS][EMChan]->SetOption("colz");
            hZDCnEM_2D[iTS][EMChan]->SetOption("colz");
        }
        for (int HADChan = 1; HADChan<=nHadChannels; HADChan++) {
            hZDCpHAD_2D[iTS][HADChan]->SetOption("colz");
            hZDCnHAD_2D[iTS][HADChan]->SetOption("colz");
        }
        
        hZDCpEMsig[iTS][1]->Fill(PEM1TotalSignal);
        hZDCpEMsig[iTS][2]->Fill(PEM2TotalSignal);
        hZDCpEMsig[iTS][3]->Fill(PEM3TotalSignal);
        hZDCpEMsig[iTS][4]->Fill(PEM4TotalSignal);
        hZDCpEMsig[iTS][5]->Fill(PEM5TotalSignal);
        
        hZDCpHADsig[iTS][1]->Fill(PHAD1TotalSignal);
        hZDCpHADsig[iTS][2]->Fill(PHAD2TotalSignal);
        hZDCpHADsig[iTS][3]->Fill(PHAD3TotalSignal);
        hZDCpHADsig[iTS][4]->Fill(PHAD4TotalSignal);
        
        hZDCnEMsig[iTS][1]->Fill(NEM1TotalSignal);
        hZDCnEMsig[iTS][2]->Fill(NEM2TotalSignal);
        hZDCnEMsig[iTS][3]->Fill(NEM3TotalSignal);
        hZDCnEMsig[iTS][4]->Fill(NEM4TotalSignal);
        hZDCnEMsig[iTS][5]->Fill(NEM5TotalSignal);
        
        hZDCnHADsig[iTS][1]->Fill(NHAD1TotalSignal);
        hZDCnHADsig[iTS][2]->Fill(NHAD2TotalSignal);
        hZDCnHADsig[iTS][3]->Fill(NHAD3TotalSignal);
        hZDCnHADsig[iTS][4]->Fill(NHAD4TotalSignal);
        
        hZDCpEM_2D[iTS][1]->Fill(centrality,PEM1TotalSignal);
        hZDCpEM_2D[iTS][2]->Fill(centrality,PEM2TotalSignal);
        hZDCpEM_2D[iTS][3]->Fill(centrality,PEM3TotalSignal);
        hZDCpEM_2D[iTS][4]->Fill(centrality,PEM4TotalSignal);
        hZDCpEM_2D[iTS][5]->Fill(centrality,PEM5TotalSignal);
        
        hZDCpHAD_2D[iTS][1]->Fill(centrality,PHAD1TotalSignal);
        hZDCpHAD_2D[iTS][2]->Fill(centrality,PHAD2TotalSignal);
        hZDCpHAD_2D[iTS][3]->Fill(centrality,PHAD3TotalSignal);
        hZDCpHAD_2D[iTS][4]->Fill(centrality,PHAD4TotalSignal);
        
        hZDCnEM_2D[iTS][1]->Fill(centrality,NEM1TotalSignal);
        hZDCnEM_2D[iTS][2]->Fill(centrality,NEM2TotalSignal);
        hZDCnEM_2D[iTS][3]->Fill(centrality,NEM3TotalSignal);
        hZDCnEM_2D[iTS][4]->Fill(centrality,NEM4TotalSignal);
        hZDCnEM_2D[iTS][5]->Fill(centrality,NEM5TotalSignal);
        
        hZDCnHAD_2D[iTS][1]->Fill(centrality,NHAD1TotalSignal);
        hZDCnHAD_2D[iTS][2]->Fill(centrality,NHAD2TotalSignal);
        hZDCnHAD_2D[iTS][3]->Fill(centrality,NHAD3TotalSignal);
        hZDCnHAD_2D[iTS][4]->Fill(centrality,NHAD4TotalSignal);
        
//        hZDCpEM_2D[iTS][1]->Fill(noff,PEM1TotalSignal);
//        hZDCpEM_2D[iTS][2]->Fill(noff,PEM2TotalSignal);
//        hZDCpEM_2D[iTS][3]->Fill(noff,PEM3TotalSignal);
//        hZDCpEM_2D[iTS][4]->Fill(noff,PEM4TotalSignal);
//        hZDCpEM_2D[iTS][5]->Fill(noff,PEM5TotalSignal);
//        
//        hZDCpHAD_2D[iTS][1]->Fill(noff,PHAD1TotalSignal);
//        hZDCpHAD_2D[iTS][2]->Fill(noff,PHAD2TotalSignal);
//        hZDCpHAD_2D[iTS][3]->Fill(noff,PHAD3TotalSignal);
//        hZDCpHAD_2D[iTS][4]->Fill(noff,PHAD4TotalSignal);
//        
//        hZDCnEM_2D[iTS][1]->Fill(noff,NEM1TotalSignal);
//        hZDCnEM_2D[iTS][2]->Fill(noff,NEM2TotalSignal);
//        hZDCnEM_2D[iTS][3]->Fill(noff,NEM3TotalSignal);
//        hZDCnEM_2D[iTS][4]->Fill(noff,NEM4TotalSignal);
//        hZDCnEM_2D[iTS][5]->Fill(noff,NEM5TotalSignal);
//        
//        hZDCnHAD_2D[iTS][1]->Fill(noff,NHAD1TotalSignal);
//        hZDCnHAD_2D[iTS][2]->Fill(noff,NHAD2TotalSignal);
//        hZDCnHAD_2D[iTS][3]->Fill(noff,NHAD3TotalSignal);
//        hZDCnHAD_2D[iTS][4]->Fill(noff,NHAD4TotalSignal);
    }
//    } //end centrality cut
    }
    
    PEM1TotalNoise  = 0;
    PEM2TotalNoise  = 0;
    PEM3TotalNoise  = 0;
    PEM4TotalNoise  = 0;
    PEM5TotalNoise  = 0;
    PHAD1TotalNoise = 0;
    PHAD2TotalNoise = 0;
    PHAD3TotalNoise = 0;
    PHAD4TotalNoise = 0;
    
    NEM1TotalNoise  = 0;
    NEM2TotalNoise  = 0;
    NEM3TotalNoise  = 0;
    NEM4TotalNoise  = 0;
    NEM5TotalNoise  = 0;
    NHAD1TotalNoise = 0;
    NHAD2TotalNoise = 0;
    NHAD3TotalNoise = 0;
    NHAD4TotalNoise = 0;
    
    // repeat the above loop for the noise
    for(int iTS=TSnoiseMin; iTS<=TSnoiseMax; iTS++)
    {
        posEM1fC[iTS] = (PEM1fC->GetValue(iTS));
        PEM1TotalNoise = PEM1TotalNoise + posEM1fC[iTS];
        posEM2fC[iTS] = (PEM2fC->GetValue(iTS));
        PEM2TotalNoise = PEM2TotalNoise + posEM2fC[iTS];
        posEM3fC[iTS] = (PEM3fC->GetValue(iTS));
        PEM3TotalNoise = PEM3TotalNoise + posEM3fC[iTS];
        posEM4fC[iTS] = (PEM4fC->GetValue(iTS));
        PEM4TotalNoise = PEM4TotalNoise + posEM4fC[iTS];
        posEM5fC[iTS] = (PEM5fC->GetValue(iTS));
        PEM5TotalNoise = PEM5TotalNoise + posEM5fC[iTS];
        posHD1fC[iTS] = (PHAD1fC->GetValue(iTS));
        PHAD1TotalNoise = PHAD1TotalNoise + posHD1fC[iTS];
        posHD2fC[iTS] = (PHAD2fC->GetValue(iTS));
        PHAD2TotalNoise = PHAD2TotalNoise + posHD2fC[iTS];
        posHD3fC[iTS] = (PHAD3fC->GetValue(iTS));
        PHAD3TotalNoise = PHAD3TotalNoise + posHD3fC[iTS];
        posHD4fC[iTS] = (PHAD4fC->GetValue(iTS));
        PHAD4TotalNoise = PHAD4TotalNoise + posHD4fC[iTS];
        
        negEM1fC[iTS] = (NEM1fC->GetValue(iTS));
        NEM1TotalNoise = NEM1TotalNoise + negEM1fC[iTS];
        negEM2fC[iTS] = (NEM2fC->GetValue(iTS));
        NEM2TotalNoise = NEM2TotalNoise + negEM2fC[iTS];
        negEM3fC[iTS] = (NEM3fC->GetValue(iTS));
        NEM3TotalNoise = NEM3TotalNoise + negEM3fC[iTS];
        negEM4fC[iTS] = (NEM4fC->GetValue(iTS));
        NEM4TotalNoise = NEM4TotalNoise + negEM4fC[iTS];
        negEM5fC[iTS] = (NEM5fC->GetValue(iTS));
        NEM5TotalNoise = NEM5TotalNoise + negEM5fC[iTS];
        negHD1fC[iTS] = (NHAD1fC->GetValue(iTS));
        NHAD1TotalNoise = NHAD1TotalNoise + negHD1fC[iTS];
        negHD2fC[iTS] = (NHAD2fC->GetValue(iTS));
        NHAD2TotalNoise = NHAD2TotalNoise + negHD2fC[iTS];
        negHD3fC[iTS] = (NHAD3fC->GetValue(iTS));
        NHAD3TotalNoise = NHAD3TotalNoise + negHD3fC[iTS];
        negHD4fC[iTS] = (NHAD4fC->GetValue(iTS));
        NHAD4TotalNoise = NHAD4TotalNoise + negHD4fC[iTS];
    }
    
    // no noise subtraction
    HADsum_NNSpos = PHAD1TotalSignal + PHAD2TotalSignal + PHAD3TotalSignal + PHAD4TotalSignal;
    ETsum_NNSpos = PHAD1TotalSignal + PHAD2TotalSignal + PHAD3TotalSignal + PHAD4TotalSignal + (0.1)*(PEM1TotalSignal + PEM2TotalSignal + PEM3TotalSignal + PEM4TotalSignal + PEM5TotalSignal);
    EMsum_NNSpos = PEM1TotalSignal + PEM2TotalSignal + PEM3TotalSignal + PEM4TotalSignal + PEM5TotalSignal;
    
    HADsum_NNSneg = NHAD1TotalSignal + NHAD2TotalSignal + NHAD3TotalSignal + NHAD4TotalSignal;
    ETsum_NNSneg = NHAD1TotalSignal + NHAD2TotalSignal + NHAD3TotalSignal + NHAD4TotalSignal + (0.1)*(NEM1TotalSignal + NEM2TotalSignal + NEM3TotalSignal + NEM4TotalSignal + NEM5TotalSignal);
    EMsum_NNSneg = NEM1TotalSignal + NEM2TotalSignal + NEM3TotalSignal + NEM4TotalSignal + NEM5TotalSignal;
    
    Pos_hist_1D_NoNoiseSubbed->Fill(HADsum_NNSpos);
    Pos_hist_1DSumNoNoiseSubbed->Fill(ETsum_NNSpos);
    Pos_hist_2D_NoNoiseSubbed->Fill(HADsum_NNSpos, EMsum_NNSpos);
    hcentPos_2D_NoNoiseSubbed->Fill(centrality, ETsum_NNSpos);
    
    Neg_hist_1D_NoNoiseSubbed->Fill(HADsum_NNSneg);
    Neg_hist_1DSumNoNoiseSubbed->Fill(ETsum_NNSneg);
    Neg_hist_2D_NoNoiseSubbed->Fill(HADsum_NNSneg, EMsum_NNSneg);
    hcentNeg_2D_NoNoiseSubbed->Fill(centrality, ETsum_NNSneg);
    
    
    hNoffPos_2D_NoNoiseSubbed->Fill(noff, ETsum_NNSpos);
    hNoffNeg_2D_NoNoiseSubbed->Fill(noff, EMsum_NNSneg);
    
    // noise subtraction
    HADsumPos = (PHAD1TotalSignal-PHAD1TotalNoise) + (PHAD2TotalSignal-PHAD2TotalNoise) + (PHAD3TotalSignal-PHAD3TotalNoise) + (PHAD4TotalSignal-PHAD4TotalNoise);
    ETsumPos = (PHAD1TotalSignal-PHAD1TotalNoise) + (PHAD2TotalSignal-PHAD2TotalNoise) + (PHAD3TotalSignal-PHAD3TotalNoise) + (PHAD4TotalSignal-PHAD4TotalNoise) + (0.1)*((PEM1TotalSignal-PEM1TotalNoise) + (PEM2TotalSignal-PEM2TotalNoise) + (PEM3TotalSignal-PEM3TotalNoise) + (PEM4TotalSignal-PEM4TotalNoise) + (PEM5TotalSignal-PEM5TotalNoise));
    EMsumPos = (PEM1TotalSignal-PEM1TotalNoise) + (PEM2TotalSignal-PEM2TotalNoise) + (PEM3TotalSignal-PEM3TotalNoise) + (PEM4TotalSignal-PEM4TotalNoise) + (PEM5TotalSignal-PEM5TotalNoise);
    
    HADsumNeg = (NHAD1TotalSignal-NHAD1TotalNoise) + (NHAD2TotalSignal-NHAD2TotalNoise) + (NHAD3TotalSignal-NHAD3TotalNoise) + (NHAD4TotalSignal-NHAD4TotalNoise);
    ETsumNeg = (NHAD1TotalSignal-NHAD1TotalNoise) + (NHAD2TotalSignal-NHAD2TotalNoise) + (NHAD3TotalSignal-NHAD3TotalNoise) + (NHAD4TotalSignal-NHAD4TotalNoise) + (0.1)*((NEM1TotalSignal-NEM1TotalNoise) + (NEM2TotalSignal-NEM2TotalNoise) + (NEM3TotalSignal-NEM3TotalNoise) + (NEM4TotalSignal-NEM4TotalNoise) + (NEM5TotalSignal-NEM5TotalNoise));
    EMsumNeg = (NEM1TotalSignal-NEM1TotalNoise) + (NEM2TotalSignal-NEM2TotalNoise) + (NEM3TotalSignal-NEM3TotalNoise) + (NEM4TotalSignal-NEM4TotalNoise) + (NEM5TotalSignal-NEM5TotalNoise);
    
    Pos_hist_1D->Fill(HADsumPos);
    Pos_hist_1DSum->Fill(ETsumPos);
    Pos_hist_2D->Fill(HADsumPos, EMsumPos);
    hcentPos_2DNoiseSubbed->Fill(centrality, ETsumPos);
    
    Neg_hist_1D->Fill(HADsumNeg);
    Neg_hist_1DSum->Fill(ETsumNeg);
    Neg_hist_2D->Fill(HADsumNeg, EMsumNeg);
    hcentNeg_2DNoiseSubbed->Fill(centrality, ETsumNeg);
    
    for (int iTS = 1; iTS<=10; iTS++) {
        hPosSig_vs_tmslc->SetBinContent(iTS,hZDCpEMsig[iTS][3]);
    }
    
    
    
    hNoffPos_2DNoiseSubbed->Fill(noff, ETsumPos);
    hNoffNeg_2DNoiseSubbed->Fill(noff, ETsumNeg);
    
}


