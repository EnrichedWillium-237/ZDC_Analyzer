// ReadZDCTree.C
//
// Contains the functions neccessary to calibrate the ZDC digis

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

static const int numEMchan = 5;
static const int numHADchan = 4;
static const int numchan = 9;

static const int nTS = 10; // number of time slices
static const int TSsigMin = 4;
static const int TSsigMax = 5;
static const int TSnoiseMin = 8;
static const int TSnoiseMax = 9;

//static const float gainEMp[numEMchan] = {1., 1., 1., 1., 1.};
//static const float gainHADp[numHADchan] = {1., 1., 1., 1.};
//static const float gainEMn[numEMchan] = {1., 1., 1., 1., 1.};
//static const float gainHADn[numHADchan] = {1., 1., 1., 1.};

static const float gainEMp[numEMchan] = {1., 1., 1., 1., 1.};
static const float gainHADp[numHADchan] = {1., 5.31, 4.14, 1.};
static const float gainEMn[numEMchan] = {0.6, 0.8, 1.75, 0.9, 2.};
static const float gainHADn[numHADchan] = {0.31, 5.0, 5.1, 3.1};

//static const float gainEMp[numEMchan] = {.02, .02, .024, .032, .028};
//static const float gainHADp[numHADchan] = {.02, .06, .02, .02};
//static const float gainEMn[numEMchan] = {.025, .03, .029, .0158, .02};
//static const float gainHADn[numHADchan] = {.0074, .068, .02, .22};


TFile * fin;

TTree * CentTree;
TTree * ZDCDigiTree;
TTree * BeamTree;

TH1F * hcent;
TH1F * hnoff;
TH1F * hbxing;

// plots for individual channels by time slice
TH1F * hZDCpEM[nTS][numEMchan];
TH1F * hZDCpHAD[nTS][numHADchan];
TH1F * hZDCnEM[nTS][numEMchan];
TH1F * hZDCnHAD[nTS][numHADchan];

TH1F * hZDCpEM_Nsub[nTS][numEMchan];
TH1F * hZDCpHAD_Nsub[nTS][numHADchan];
TH1F * hZDCnEM_Nsub[nTS][numEMchan];
TH1F * hZDCnHAD_Nsub[nTS][numHADchan];

TH2F * hZDCpEM_vs_cent[nTS][numEMchan];
TH2F * hZDCpHAD_vs_cent[nTS][numHADchan];
TH2F * hZDCnEM_vs_cent[nTS][numEMchan];
TH2F * hZDCnHAD_vs_cent[nTS][numHADchan];

TH2F * hZDCpEM_vs_cent_Nsub[nTS][numEMchan];
TH2F * hZDCpHAD_vs_cent_Nsub[nTS][numHADchan];
TH2F * hZDCnEM_vs_cent_Nsub[nTS][numEMchan];
TH2F * hZDCnHAD_vs_cent_Nsub[nTS][numHADchan];

TH2F * hZDCpEM_vs_noff[nTS][numEMchan];
TH2F * hZDCpHAD_vs_noff[nTS][numHADchan];
TH2F * hZDCnEM_vs_noff[nTS][numEMchan];
TH2F * hZDCnHAD_vs_noff[nTS][numHADchan];

TH2F * hZDCpEM_vs_noff_Nsub[nTS][numEMchan];
TH2F * hZDCpHAD_vs_noff_Nsub[nTS][numHADchan];
TH2F * hZDCnEM_vs_noff_Nsub[nTS][numEMchan];
TH2F * hZDCnHAD_vs_noff_Nsub[nTS][numHADchan];

// plots for individual channels ("_Nsub" for noise subtracted)
TH2F * hZDCpEMchan_cent[numEMchan];
TH2F * hZDCpHADchan_cent[numHADchan];
TH2F * hZDCnEMchan_cent[numEMchan];
TH2F * hZDCnHADchan_cent[numHADchan];

TH2F * hZDCpEMchan_cent_Nsub[numEMchan];
TH2F * hZDCpHADchan_cent_Nsub[numHADchan];
TH2F * hZDCnEMchan_cent_Nsub[numEMchan];
TH2F * hZDCnHADchan_cent_Nsub[numHADchan];

TH2F * hZDCpEMchan_noff[numEMchan];
TH2F * hZDCpHADchan_noff[numHADchan];
TH2F * hZDCnEMchan_noff[numEMchan];
TH2F * hZDCnHADchan_noff[numHADchan];

TH2F * hZDCpEMchan_noff_Nsub[numEMchan];
TH2F * hZDCpHADchan_noff_Nsub[numHADchan];
TH2F * hZDCnEMchan_noff_Nsub[numEMchan];
TH2F * hZDCnHADchan_noff_Nsub[numHADchan];

// ProfileX's ove the individual channels
TH1F * hPXpEMchan_cent[numEMchan];
TH1F * hPXpHADchan_cent[numHADchan];
TH1F * hPXnEMchan_cent[numEMchan];
TH1F * hPXnHADchan_cent[numHADchan];

TH1F * hPXpEMchan_cent_Nsub[numEMchan];
TH1F * hPXpHADchan_cent_Nsub[numHADchan];
TH1F * hPXnEMchan_cent_Nsub[numEMchan];
TH1F * hPXnHADchan_cent_Nsub[numHADchan];

TH1F * hPXpEMchan_noff[numEMchan];
TH1F * hPXpHADchan_noff[numHADchan];
TH1F * hPXnEMchan_noff[numEMchan];
TH1F * hPXnHADchan_noff[numHADchan];

TH1F * hPXpEMchan_noff_Nsub[numEMchan];
TH1F * hPXpHADchan_noff_Nsub[numHADchan];
TH1F * hPXnEMchan_noff_Nsub[numEMchan];
TH1F * hPXnHADchan_noff_Nsub[numHADchan];

// plots for sums of channels
TH1F * hZDCpEMsum;
TH1F * hZDCpHADsum;
TH1F * hZDCnEMsum;
TH1F * hZDCnHADsum;
TH2F * hZDCtotsum_vs_cent;
TH2F * hZDCtotsum_vs_noff;

TH1F * hZDCpEMsum_Nsub;
TH1F * hZDCpHADsum_Nsub;
TH1F * hZDCnEMsum_Nsub;
TH1F * hZDCnHADsum_Nsub;
TH2F * hZDCtotsum_Nsub_vs_cent;
TH2F * hZDCtotsum_Nsub_vs_noff;

TH2F * hZDCpEM_vs_HAD;
TH2F * hZDCnEM_vs_HAD;
TH2F * hZDCpEM_vs_HAD_Nsub;
TH2F * hZDCnEM_vs_HAD_Nsub;

TH2F * hZDCpSum_vs_cent;
TH2F * hZDCnSum_vs_cent;
TH2F * hZDCpSum_vs_cent_Nsub;
TH2F * hZDCnSum_vs_cent_Nsub;

TH2F * hZDCpSum_vs_noff;
TH2F * hZDCnSum_vs_noff;
TH2F * hZDCpSum_vs_noff_Nsub;
TH2F * hZDCnSum_vs_noff_Nsub;

TH1F * hZDCpSum_vs_TS;
TH1F * hZDCnSum_vs_TS;
TH1F * hZDCpSum_vs_TS_Nsub;
TH1F * hZDCnSum_vs_TS_Nsub;

TH1F * hZDCpSumTotal[numchan];
TH1F * hZDCnSumTotal[numchan];

TLeaf * CENTRAL;
TLeaf * NOFF;
TLeaf * BXING;

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

Int_t nevents;
Double_t centrality, noff, bxing;

Double_t posEM1fC[nTS], posEM1ADC[nTS];
Double_t posEM2fC[nTS], posEM2ADC[nTS];
Double_t posEM3fC[nTS], posEM3ADC[nTS];
Double_t posEM4fC[nTS], posEM4ADC[nTS];
Double_t posEM5fC[nTS], posEM5ADC[nTS];
Double_t posHD1fC[nTS], posHD1ADC[nTS];
Double_t posHD2fC[nTS], posHD2ADC[nTS];
Double_t posHD3fC[nTS], posHD3ADC[nTS];
Double_t posHD4fC[nTS], posHD4ADC[nTS];

Double_t negEM1fC[nTS], negEM1ADC[nTS];
Double_t negEM2fC[nTS], negEM2ADC[nTS];
Double_t negEM3fC[nTS], negEM3ADC[nTS];
Double_t negEM4fC[nTS], negEM4ADC[nTS];
Double_t negEM5fC[nTS], negEM5ADC[nTS];
Double_t negHD1fC[nTS], negHD1ADC[nTS];
Double_t negHD2fC[nTS], negHD2ADC[nTS];
Double_t negHD3fC[nTS], negHD3ADC[nTS];
Double_t negHD4fC[nTS], negHD4ADC[nTS];

Double_t EMpsum, HADpsum, ETpsum;
Double_t EMpsum_Nsubbed, HADpsum_Nsubbed, ETpsum_Nsubbed;
Double_t EMnsum, HADnsum, ETnsum;
Double_t EMnsum_Nsubbed, HADnsum_Nsubbed, ETnsum_Nsubbed;

float PEM1TotSig, PEM2TotSig, PEM3TotSig, PEM4TotSig, PEM5TotSig;
float PHAD1TotSig, PHAD2TotSig, PHAD3TotSig, PHAD4TotSig;
float NEM1TotSig, NEM2TotSig, NEM3TotSig, NEM4TotSig, NEM5TotSig;
float NHAD1TotSig, NHAD2TotSig, NHAD3TotSig, NHAD4TotSig;

float PEM1TotSig_Noise, PEM2TotSig_Noise, PEM3TotSig_Noise, PEM4TotSig_Noise, PEM5TotSig_Noise;
float PHAD1TotSig_Noise, PHAD2TotSig_Noise, PHAD3TotSig_Noise, PHAD4TotSig_Noise;
float NEM1TotSig_Noise, NEM2TotSig_Noise, NEM3TotSig_Noise, NEM4TotSig_Noise, NEM5TotSig_Noise;
float NHAD1TotSig_Noise, NHAD2TotSig_Noise, NHAD3TotSig_Noise, NHAD4TotSig_Noise;


void GetLeafs() {
    CENTRAL = (TLeaf *) CentTree->GetLeaf("Cent_HFtowers");
    NOFF    = (TLeaf *) CentTree->GetLeaf("hiNpixelTracks");
    BXING   = (TLeaf *) BeamTree->GetLeaf("BunchXing");
    
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
    
    EMpsum = 0;
    HADpsum = 0;
    ETpsum = 0;
    EMnsum = 0;
    HADnsum = 0;
    ETnsum = 0;
    
    EMpsum_Nsubbed = 0;
    HADpsum_Nsubbed = 0;
    ETpsum_Nsubbed = 0;
    EMnsum_Nsubbed = 0;
    HADnsum_Nsubbed = 0;
    ETnsum_Nsubbed = 0;
    
    nevents = ZDCDigiTree->GetEntries();
}


void ReadZDCTree(int ievent)
{
    CentTree->GetEntry(ievent);
    centrality = CENTRAL->GetValue();
    noff = NOFF->GetValue();
    
    BeamTree->GetEntry(ievent);
    bxing = BXING->GetValue();
    
    hcent->Fill(centrality);
    hnoff->Fill(noff);
    hbxing->Fill(bxing);
    
    // without noise subtraction
    for (int iTS = TSsigMin; iTS<TSsigMax; iTS++) {
        PEM1TotSig = 0;
        PEM2TotSig = 0;
        PEM3TotSig = 0;
        PEM4TotSig = 0;
        PEM5TotSig = 0;
        PHAD1TotSig = 0;
        PHAD2TotSig = 0;
        PHAD3TotSig = 0;
        PHAD4TotSig = 0;
        
        NEM1TotSig = 0;
        NEM2TotSig = 0;
        NEM3TotSig = 0;
        NEM4TotSig = 0;
        NEM5TotSig = 0;
        NHAD1TotSig = 0;
        NHAD2TotSig = 0;
        NHAD3TotSig = 0;
        NHAD4TotSig = 0;
        
        posEM1fC[iTS] = PEM1fC->GetValue(iTS);
        posEM2fC[iTS] = PEM2fC->GetValue(iTS);
        posEM3fC[iTS] = PEM3fC->GetValue(iTS);
        posEM4fC[iTS] = PEM4fC->GetValue(iTS);
        posEM5fC[iTS] = PEM5fC->GetValue(iTS);
        posHD1fC[iTS] = PHAD1fC->GetValue(iTS);
        posHD2fC[iTS] = PHAD2fC->GetValue(iTS);
        posHD3fC[iTS] = PHAD3fC->GetValue(iTS);
        posHD4fC[iTS] = PHAD4fC->GetValue(iTS);

//        negEM1fC[iTS] = NEM1fC->GetValue(iTS);
//        negEM2fC[iTS] = NEM2fC->GetValue(iTS);
//        negEM3fC[iTS] = NEM3fC->GetValue(iTS);
//        negEM4fC[iTS] = NEM4fC->GetValue(iTS);
//        negEM5fC[iTS] = NEM5fC->GetValue(iTS);
//        negHD1fC[iTS] = NHAD1fC->GetValue(iTS);
//        negHD2fC[iTS] = NHAD2fC->GetValue(iTS);
//        negHD3fC[iTS] = NHAD3fC->GetValue(iTS);
//        negHD4fC[iTS] = NHAD4fC->GetValue(iTS);
        
//        negEM1fC[iTS] = NEM3fC->GetValue(iTS);
//        negEM2fC[iTS] = NHAD1fC->GetValue(iTS);
//        negEM3fC[iTS] = NEM1fC->GetValue(iTS);
//        negEM4fC[iTS] = NEM2fC->GetValue(iTS);
//        negEM5fC[iTS] = NEM5fC->GetValue(iTS);
//        negHD1fC[iTS] = NEM4fC->GetValue(iTS);
//        negHD2fC[iTS] = NHAD2fC->GetValue(iTS);
//        negHD3fC[iTS] = NHAD3fC->GetValue(iTS);
//        negHD4fC[iTS] = NHAD4fC->GetValue(iTS);

        negEM1fC[iTS] = NEM1fC->GetValue(iTS);
        negEM2fC[iTS] = NEM2fC->GetValue(iTS);
        negEM3fC[iTS] = NEM3fC->GetValue(iTS);
        negEM4fC[iTS] = NHAD1fC->GetValue(iTS);
        negEM5fC[iTS] = NEM5fC->GetValue(iTS);
        negHD1fC[iTS] = NEM4fC->GetValue(iTS);
        negHD2fC[iTS] = NHAD2fC->GetValue(iTS);
        negHD3fC[iTS] = NHAD3fC->GetValue(iTS);
        negHD4fC[iTS] = NHAD4fC->GetValue(iTS);
        
        
        // take the fC value of a timeslice and add it to the total signal
        // ZDC positive
        if (posEM1fC[iTS]<0) {
            posEM1fC[iTS] = 0;
        }
        PEM1TotSig = PEM1TotSig + gainEMp[0]*posEM1fC[iTS];
        if (posEM2fC[iTS]<0) {
            posEM2fC[iTS] = 0;
        }
        PEM2TotSig = PEM2TotSig + gainEMp[1]*posEM2fC[iTS];
        if (posEM3fC[iTS]<0) {
            posEM3fC[iTS] = 0;
        }
        PEM3TotSig = PEM3TotSig + gainEMp[2]*posEM3fC[iTS];
        if (posEM4fC[iTS]<0) {
            posEM4fC[iTS] = 0;
        }
        PEM4TotSig = PEM4TotSig + gainEMp[3]*posEM4fC[iTS];
        if (posEM5fC[iTS]<0) {
            posEM5fC[iTS] = 0;
        }
        PEM5TotSig = PEM5TotSig + gainEMp[4]*posEM5fC[iTS];
        if (posHD1fC[iTS]<0) {
            PHAD1TotSig = 0;
        }
        PHAD1TotSig = PHAD1TotSig + gainHADp[0]*posHD1fC[iTS];
        if (posHD2fC[iTS]<0) {
            PHAD2TotSig = 0;
        }
        PHAD2TotSig = PHAD2TotSig + gainHADp[1]*posHD2fC[iTS];
        if (posHD3fC[iTS]<0) {
            PHAD3TotSig = 0;
        }
        PHAD3TotSig = PHAD3TotSig + gainHADp[2]*posHD3fC[iTS];
        if (posHD4fC[iTS]<0) {
            PHAD4TotSig = 0;
        }
        PHAD4TotSig = PHAD4TotSig + gainHADp[3]*posHD4fC[iTS];
        
        // ZDC negative side
        if (negEM1fC[iTS]<0) {
            negEM1fC[iTS] = 0;
        }
        NEM1TotSig = NEM1TotSig + gainEMn[0]*negEM1fC[iTS];
        if (negEM2fC[iTS]<0) {
            negEM2fC[iTS] = 0;
        }
        NEM2TotSig = NEM2TotSig + gainEMn[1]*negEM2fC[iTS];
        if (negEM3fC[iTS]<0) {
            negEM3fC[iTS] = 0;
        }
        NEM3TotSig = NEM3TotSig + gainEMn[2]*negEM3fC[iTS];
        if (negEM4fC[iTS]<0) {
            negEM4fC[iTS] = 0;
        }
        NEM4TotSig = NEM4TotSig + gainEMn[3]*negEM4fC[iTS];
        if (negEM5fC[iTS]<0) {
            negEM5fC[iTS] = 0;
        }
        NEM5TotSig = NEM5TotSig + gainEMn[4]*negEM5fC[iTS];
        if (negHD1fC[iTS]<0) {
            NHAD1TotSig = 0;
        }
        NHAD1TotSig = NHAD1TotSig + gainHADn[0]*negHD1fC[iTS];
        if (negHD2fC[iTS]<0) {
            NHAD2TotSig = 0;
        }
        NHAD2TotSig = NHAD2TotSig + gainHADn[1]*negHD2fC[iTS];
        if (negHD3fC[iTS]<0) {
            NHAD3TotSig = 0;
        }
        NHAD3TotSig = NHAD3TotSig + gainHADn[2]*negHD3fC[iTS];
        if (negHD4fC[iTS]<0) {
            NHAD4TotSig = 0;
        }
        NHAD4TotSig = NHAD4TotSig + gainHADn[3]*negHD4fC[iTS];
        
        // fill individual channels
        hZDCpEM[iTS][0]->Fill(PEM1TotSig);
        hZDCpEM[iTS][1]->Fill(PEM2TotSig);
        hZDCpEM[iTS][2]->Fill(PEM3TotSig);
        hZDCpEM[iTS][3]->Fill(PEM4TotSig);
        hZDCpEM[iTS][4]->Fill(PEM5TotSig);
        hZDCpHAD[iTS][0]->Fill(PHAD1TotSig);
        hZDCpHAD[iTS][1]->Fill(PHAD2TotSig);
        hZDCpHAD[iTS][2]->Fill(PHAD3TotSig);
        hZDCpHAD[iTS][3]->Fill(PHAD4TotSig);
        
        hZDCnEM[iTS][0]->Fill(NEM1TotSig);
        hZDCnEM[iTS][1]->Fill(NEM2TotSig);
        hZDCnEM[iTS][2]->Fill(NEM3TotSig);
        hZDCnEM[iTS][3]->Fill(NEM4TotSig);
        hZDCnEM[iTS][4]->Fill(NEM5TotSig);
        hZDCnHAD[iTS][0]->Fill(NHAD1TotSig);
        hZDCnHAD[iTS][1]->Fill(NHAD2TotSig);
        hZDCnHAD[iTS][2]->Fill(NHAD3TotSig);
        hZDCnHAD[iTS][3]->Fill(NHAD4TotSig);
        
        hZDCpEM_vs_cent[iTS][0]->Fill(centrality,PEM1TotSig);
        hZDCpEM_vs_cent[iTS][1]->Fill(centrality,PEM2TotSig);
        hZDCpEM_vs_cent[iTS][2]->Fill(centrality,PEM3TotSig);
        hZDCpEM_vs_cent[iTS][3]->Fill(centrality,PEM4TotSig);
        hZDCpEM_vs_cent[iTS][4]->Fill(centrality,PEM5TotSig);
        hZDCpHAD_vs_cent[iTS][0]->Fill(centrality,PHAD1TotSig);
        hZDCpHAD_vs_cent[iTS][1]->Fill(centrality,PHAD2TotSig);
        hZDCpHAD_vs_cent[iTS][2]->Fill(centrality,PHAD3TotSig);
        hZDCpHAD_vs_cent[iTS][3]->Fill(centrality,PHAD4TotSig);
        
        hZDCnEM_vs_cent[iTS][0]->Fill(centrality,NEM1TotSig);
        hZDCnEM_vs_cent[iTS][1]->Fill(centrality,NEM2TotSig);
        hZDCnEM_vs_cent[iTS][2]->Fill(centrality,NEM3TotSig);
        hZDCnEM_vs_cent[iTS][3]->Fill(centrality,NEM4TotSig);
        hZDCnEM_vs_cent[iTS][4]->Fill(centrality,NEM5TotSig);
        hZDCnHAD_vs_cent[iTS][0]->Fill(centrality,NHAD1TotSig);
        hZDCnHAD_vs_cent[iTS][1]->Fill(centrality,NHAD2TotSig);
        hZDCnHAD_vs_cent[iTS][2]->Fill(centrality,NHAD3TotSig);
        hZDCnHAD_vs_cent[iTS][3]->Fill(centrality,NHAD4TotSig);
        
        hZDCpEM_vs_noff[iTS][0]->Fill(noff,PEM1TotSig);
        hZDCpEM_vs_noff[iTS][1]->Fill(noff,PEM2TotSig);
        hZDCpEM_vs_noff[iTS][2]->Fill(noff,PEM3TotSig);
        hZDCpEM_vs_noff[iTS][3]->Fill(noff,PEM4TotSig);
        hZDCpEM_vs_noff[iTS][4]->Fill(noff,PEM5TotSig);
        hZDCpHAD_vs_noff[iTS][0]->Fill(noff,PHAD1TotSig);
        hZDCpHAD_vs_noff[iTS][1]->Fill(noff,PHAD2TotSig);
        hZDCpHAD_vs_noff[iTS][2]->Fill(noff,PHAD3TotSig);
        hZDCpHAD_vs_noff[iTS][3]->Fill(noff,PHAD4TotSig);
        
        hZDCnEM_vs_noff[iTS][0]->Fill(noff,NEM1TotSig);
        hZDCnEM_vs_noff[iTS][1]->Fill(noff,NEM2TotSig);
        hZDCnEM_vs_noff[iTS][2]->Fill(noff,NEM3TotSig);
        hZDCnEM_vs_noff[iTS][3]->Fill(noff,NEM4TotSig);
        hZDCnEM_vs_noff[iTS][4]->Fill(noff,NEM5TotSig);
        hZDCnHAD_vs_noff[iTS][0]->Fill(noff,NHAD1TotSig);
        hZDCnHAD_vs_noff[iTS][1]->Fill(noff,NHAD2TotSig);
        hZDCnHAD_vs_noff[iTS][2]->Fill(noff,NHAD3TotSig);
        hZDCnHAD_vs_noff[iTS][3]->Fill(noff,NHAD4TotSig);
        
        
        hZDCpEMchan_cent[0]->Fill(centrality,PEM1TotSig);
        hZDCpEMchan_cent[1]->Fill(centrality,PEM2TotSig);
        hZDCpEMchan_cent[2]->Fill(centrality,PEM3TotSig);
        hZDCpEMchan_cent[3]->Fill(centrality,PEM4TotSig);
        hZDCpEMchan_cent[4]->Fill(centrality,PEM5TotSig);
        
        hZDCnEMchan_cent[0]->Fill(centrality,NEM1TotSig);
        hZDCnEMchan_cent[1]->Fill(centrality,NEM2TotSig);
        hZDCnEMchan_cent[2]->Fill(centrality,NEM3TotSig);
        hZDCnEMchan_cent[3]->Fill(centrality,NEM4TotSig);
        hZDCnEMchan_cent[4]->Fill(centrality,NEM5TotSig);
        
        hZDCpHADchan_cent[0]->Fill(centrality,PHAD1TotSig);
        hZDCpHADchan_cent[1]->Fill(centrality,PHAD2TotSig);
        hZDCpHADchan_cent[2]->Fill(centrality,PHAD3TotSig);
        hZDCpHADchan_cent[3]->Fill(centrality,PHAD4TotSig);
        
        hZDCnHADchan_cent[0]->Fill(centrality,NHAD1TotSig);
        hZDCnHADchan_cent[1]->Fill(centrality,NHAD2TotSig);
        hZDCnHADchan_cent[2]->Fill(centrality,NHAD3TotSig);
        hZDCnHADchan_cent[3]->Fill(centrality,NHAD4TotSig);
        
        hZDCpEMchan_noff[0]->Fill(noff,PEM1TotSig);
        hZDCpEMchan_noff[1]->Fill(noff,PEM2TotSig);
        hZDCpEMchan_noff[2]->Fill(noff,PEM3TotSig);
        hZDCpEMchan_noff[3]->Fill(noff,PEM4TotSig);
        hZDCpEMchan_noff[4]->Fill(noff,PEM5TotSig);
        
        hZDCnEMchan_noff[0]->Fill(noff,NEM1TotSig);
        hZDCnEMchan_noff[1]->Fill(noff,NEM2TotSig);
        hZDCnEMchan_noff[2]->Fill(noff,NEM3TotSig);
        hZDCnEMchan_noff[3]->Fill(noff,NEM4TotSig);
        hZDCnEMchan_noff[4]->Fill(noff,NEM5TotSig);
        
        hZDCpHADchan_noff[0]->Fill(noff,PHAD1TotSig);
        hZDCpHADchan_noff[1]->Fill(noff,PHAD2TotSig);
        hZDCpHADchan_noff[2]->Fill(noff,PHAD3TotSig);
        hZDCpHADchan_noff[3]->Fill(noff,PHAD4TotSig);
        
        hZDCnHADchan_noff[0]->Fill(noff,NHAD1TotSig);
        hZDCnHADchan_noff[1]->Fill(noff,NHAD2TotSig);
        hZDCnHADchan_noff[2]->Fill(noff,NHAD3TotSig);
        hZDCnHADchan_noff[3]->Fill(noff,NHAD4TotSig);
    }
    
    // with noise subtraction
    PEM1TotSig_Noise = 0;
    PEM2TotSig_Noise = 0;
    PEM3TotSig_Noise = 0;
    PEM4TotSig_Noise = 0;
    PEM5TotSig_Noise = 0;
    PHAD1TotSig_Noise = 0;
    PHAD2TotSig_Noise = 0;
    PHAD3TotSig_Noise = 0;
    PHAD4TotSig_Noise = 0;
    
    NEM1TotSig_Noise = 0;
    NEM2TotSig_Noise = 0;
    NEM3TotSig_Noise = 0;
    NEM4TotSig_Noise = 0;
    NEM5TotSig_Noise = 0;
    NHAD1TotSig_Noise = 0;
    NHAD2TotSig_Noise = 0;
    NHAD3TotSig_Noise = 0;
    NHAD4TotSig_Noise = 0;
    
    for (int iTS = TSnoiseMin; iTS<=TSnoiseMax; iTS++) {
        posEM1fC[iTS] = PEM1fC->GetValue(iTS);
        posEM2fC[iTS] = PEM2fC->GetValue(iTS);
        posEM3fC[iTS] = PEM3fC->GetValue(iTS);
        posEM4fC[iTS] = PEM4fC->GetValue(iTS);
        posEM5fC[iTS] = PEM5fC->GetValue(iTS);
        posHD1fC[iTS] = PHAD1fC->GetValue(iTS);
        posHD2fC[iTS] = PHAD2fC->GetValue(iTS);
        posHD3fC[iTS] = PHAD3fC->GetValue(iTS);
        posHD4fC[iTS] = PHAD4fC->GetValue(iTS);
        
//        negEM1fC[iTS] = NEM1fC->GetValue(iTS);
//        negEM2fC[iTS] = NEM2fC->GetValue(iTS);
//        negEM3fC[iTS] = NEM3fC->GetValue(iTS);
//        negEM4fC[iTS] = NEM4fC->GetValue(iTS);
//        negEM5fC[iTS] = NEM5fC->GetValue(iTS);
//        negHD1fC[iTS] = NHAD1fC->GetValue(iTS);
//        negHD2fC[iTS] = NHAD2fC->GetValue(iTS);
//        negHD3fC[iTS] = NHAD3fC->GetValue(iTS);
//        negHD4fC[iTS] = NHAD4fC->GetValue(iTS);
        
        negEM1fC[iTS] = NEM3fC->GetValue(iTS);
        negEM2fC[iTS] = NHAD1fC->GetValue(iTS);
        negEM3fC[iTS] = NEM1fC->GetValue(iTS);
        negEM4fC[iTS] = NEM2fC->GetValue(iTS);
        negEM5fC[iTS] = NEM5fC->GetValue(iTS);
        negHD1fC[iTS] = NEM4fC->GetValue(iTS);
        negHD2fC[iTS] = NHAD2fC->GetValue(iTS);
        negHD3fC[iTS] = NHAD3fC->GetValue(iTS);
        negHD4fC[iTS] = NHAD4fC->GetValue(iTS);
        
        // take the fC value of a timeslice and add it to the total signal
        // ZDC positive
        if (posEM1fC[iTS]<0) {
            posEM1fC[iTS] = 0;
        }
        PEM1TotSig_Noise = PEM1TotSig_Noise + gainEMp[0]*posEM1fC[iTS];
        if (posEM2fC[iTS]<0) {
            posEM2fC[iTS] = 0;
        }
        PEM2TotSig_Noise = PEM2TotSig_Noise + gainEMp[1]*posEM2fC[iTS];
        if (posEM3fC[iTS]<0) {
            posEM3fC[iTS] = 0;
        }
        PEM3TotSig_Noise = PEM3TotSig_Noise + gainEMp[2]*posEM3fC[iTS];
        if (posEM4fC[iTS]<0) {
            posEM4fC[iTS] = 0;
        }
        PEM4TotSig_Noise = PEM4TotSig_Noise + gainEMp[3]*posEM4fC[iTS];
        if (posEM5fC[iTS]<0) {
            posEM5fC[iTS] = 0;
        }
        PEM5TotSig_Noise = PEM5TotSig_Noise + gainEMp[4]*posEM5fC[iTS];
        if (posHD1fC[iTS]<0) {
            PHAD1TotSig = 0;
        }
        PHAD1TotSig_Noise = PHAD1TotSig_Noise + gainHADp[0]*posHD1fC[iTS];
        if (posHD2fC[iTS]<0) {
            PHAD2TotSig = 0;
        }
        PHAD2TotSig_Noise = PHAD2TotSig_Noise + gainHADp[1]*posHD2fC[iTS];
        if (posHD3fC[iTS]<0) {
            PHAD3TotSig = 0;
        }
        PHAD3TotSig_Noise = PHAD3TotSig_Noise + gainHADp[2]*posHD3fC[iTS];
        if (posHD4fC[iTS]<0) {
            PHAD4TotSig = 0;
        }
        PHAD4TotSig_Noise = PHAD4TotSig_Noise + gainHADp[3]*posHD4fC[iTS];
        
        // ZDC negative side
//        if (negEM1fC[iTS]<0) {
//            negEM1fC[iTS] = 0;
//        }
        NEM1TotSig_Noise = NEM1TotSig_Noise + gainEMn[0]*negEM1fC[iTS];
        if (negEM2fC[iTS]<0) {
            negEM2fC[iTS] = 0;
        }
        NEM2TotSig_Noise = NEM2TotSig_Noise + gainEMn[1]*negEM2fC[iTS];
        if (negEM3fC[iTS]<0) {
            negEM3fC[iTS] = 0;
        }
        NEM3TotSig_Noise = NEM3TotSig_Noise + gainEMn[2]*negEM3fC[iTS];
        if (negEM4fC[iTS]<0) {
            negEM4fC[iTS] = 0;
        }
        NEM4TotSig_Noise = NEM4TotSig_Noise + gainEMn[3]*negEM4fC[iTS];
        if (negEM5fC[iTS]<0) {
            negEM5fC[iTS] = 0;
        }
        NEM5TotSig_Noise = NEM5TotSig_Noise + gainEMn[4]*negEM5fC[iTS];
        if (negHD1fC[iTS]<0) {
            NHAD1TotSig = 0;
        }
        NHAD1TotSig_Noise = NHAD1TotSig_Noise + gainHADn[0]*negHD1fC[iTS];
        if (negHD2fC[iTS]<0) {
            NHAD2TotSig = 0;
        }
        NHAD2TotSig_Noise = NHAD2TotSig_Noise + gainHADn[1]*negHD2fC[iTS];
        if (negHD3fC[iTS]<0) {
            NHAD3TotSig = 0;
        }
        NHAD3TotSig_Noise = NHAD3TotSig_Noise + gainHADn[2]*negHD3fC[iTS];
        if (negHD4fC[iTS]<0) {
            NHAD4TotSig = 0;
        }
        NHAD4TotSig_Noise = NHAD4TotSig_Noise + gainHADn[3]*negHD4fC[iTS];
        
        // fill individual channels
        hZDCpEM_Nsub[iTS][0]->Fill(PEM1TotSig_Noise);
        hZDCpEM_Nsub[iTS][1]->Fill(PEM2TotSig_Noise);
        hZDCpEM_Nsub[iTS][2]->Fill(PEM3TotSig_Noise);
        hZDCpEM_Nsub[iTS][3]->Fill(PEM4TotSig_Noise);
        hZDCpEM_Nsub[iTS][4]->Fill(PEM5TotSig_Noise);
        hZDCpHAD_Nsub[iTS][0]->Fill(PHAD1TotSig_Noise);
        hZDCpHAD_Nsub[iTS][1]->Fill(PHAD2TotSig_Noise);
        hZDCpHAD_Nsub[iTS][2]->Fill(PHAD3TotSig_Noise);
        hZDCpHAD_Nsub[iTS][3]->Fill(PHAD4TotSig_Noise);
        
        hZDCnEM_Nsub[iTS][0]->Fill(NEM1TotSig_Noise);
        hZDCnEM_Nsub[iTS][1]->Fill(NEM2TotSig_Noise);
        hZDCnEM_Nsub[iTS][2]->Fill(NEM3TotSig_Noise);
        hZDCnEM_Nsub[iTS][3]->Fill(NEM4TotSig_Noise);
        hZDCnEM_Nsub[iTS][4]->Fill(NEM5TotSig_Noise);
        hZDCnHAD_Nsub[iTS][0]->Fill(NHAD1TotSig_Noise);
        hZDCnHAD_Nsub[iTS][1]->Fill(NHAD2TotSig_Noise);
        hZDCnHAD_Nsub[iTS][2]->Fill(NHAD3TotSig_Noise);
        hZDCnHAD_Nsub[iTS][3]->Fill(NHAD4TotSig_Noise);
        
        hZDCpEM_vs_cent_Nsub[iTS][0]->Fill(centrality,PEM1TotSig_Noise);
        hZDCpEM_vs_cent_Nsub[iTS][1]->Fill(centrality,PEM2TotSig_Noise);
        hZDCpEM_vs_cent_Nsub[iTS][2]->Fill(centrality,PEM3TotSig_Noise);
        hZDCpEM_vs_cent_Nsub[iTS][3]->Fill(centrality,PEM4TotSig_Noise);
        hZDCpEM_vs_cent_Nsub[iTS][4]->Fill(centrality,PEM5TotSig_Noise);
        hZDCpHAD_vs_cent_Nsub[iTS][0]->Fill(centrality,PHAD1TotSig_Noise);
        hZDCpHAD_vs_cent_Nsub[iTS][1]->Fill(centrality,PHAD2TotSig_Noise);
        hZDCpHAD_vs_cent_Nsub[iTS][2]->Fill(centrality,PHAD3TotSig_Noise);
        hZDCpHAD_vs_cent_Nsub[iTS][3]->Fill(centrality,PHAD4TotSig_Noise);
        
        hZDCnEM_vs_cent_Nsub[iTS][0]->Fill(centrality,NEM1TotSig_Noise);
        hZDCnEM_vs_cent_Nsub[iTS][1]->Fill(centrality,NEM2TotSig_Noise);
        hZDCnEM_vs_cent_Nsub[iTS][2]->Fill(centrality,NEM3TotSig_Noise);
        hZDCnEM_vs_cent_Nsub[iTS][3]->Fill(centrality,NEM4TotSig_Noise);
        hZDCnEM_vs_cent_Nsub[iTS][4]->Fill(centrality,NEM5TotSig_Noise);
        hZDCnHAD_vs_cent_Nsub[iTS][0]->Fill(centrality,NHAD1TotSig_Noise);
        hZDCnHAD_vs_cent_Nsub[iTS][1]->Fill(centrality,NHAD2TotSig_Noise);
        hZDCnHAD_vs_cent_Nsub[iTS][2]->Fill(centrality,NHAD3TotSig_Noise);
        hZDCnHAD_vs_cent_Nsub[iTS][3]->Fill(centrality,NHAD4TotSig_Noise);
        
        hZDCpEM_vs_noff_Nsub[iTS][0]->Fill(noff,PEM1TotSig_Noise);
        hZDCpEM_vs_noff_Nsub[iTS][1]->Fill(noff,PEM2TotSig_Noise);
        hZDCpEM_vs_noff_Nsub[iTS][2]->Fill(noff,PEM3TotSig_Noise);
        hZDCpEM_vs_noff_Nsub[iTS][3]->Fill(noff,PEM4TotSig_Noise);
        hZDCpEM_vs_noff_Nsub[iTS][4]->Fill(noff,PEM5TotSig_Noise);
        hZDCpHAD_vs_noff_Nsub[iTS][0]->Fill(noff,PHAD1TotSig_Noise);
        hZDCpHAD_vs_noff_Nsub[iTS][1]->Fill(noff,PHAD2TotSig_Noise);
        hZDCpHAD_vs_noff_Nsub[iTS][2]->Fill(noff,PHAD3TotSig_Noise);
        hZDCpHAD_vs_noff_Nsub[iTS][3]->Fill(noff,PHAD4TotSig_Noise);
        
        hZDCnEM_vs_noff_Nsub[iTS][0]->Fill(noff,NEM1TotSig_Noise);
        hZDCnEM_vs_noff_Nsub[iTS][1]->Fill(noff,NEM2TotSig_Noise);
        hZDCnEM_vs_noff_Nsub[iTS][2]->Fill(noff,NEM3TotSig_Noise);
        hZDCnEM_vs_noff_Nsub[iTS][3]->Fill(noff,NEM4TotSig_Noise);
        hZDCnEM_vs_noff_Nsub[iTS][4]->Fill(noff,NEM5TotSig_Noise);
        hZDCnHAD_vs_noff_Nsub[iTS][0]->Fill(noff,NHAD1TotSig_Noise);
        hZDCnHAD_vs_noff_Nsub[iTS][1]->Fill(noff,NHAD2TotSig_Noise);
        hZDCnHAD_vs_noff_Nsub[iTS][2]->Fill(noff,NHAD3TotSig_Noise);
        hZDCnHAD_vs_noff_Nsub[iTS][3]->Fill(noff,NHAD4TotSig_Noise);
        
        
        hZDCpEMchan_cent_Nsub[0]->Fill(centrality,PEM1TotSig_Noise);
        hZDCpEMchan_cent_Nsub[1]->Fill(centrality,PEM2TotSig_Noise);
        hZDCpEMchan_cent_Nsub[2]->Fill(centrality,PEM3TotSig_Noise);
        hZDCpEMchan_cent_Nsub[3]->Fill(centrality,PEM4TotSig_Noise);
        hZDCpEMchan_cent_Nsub[4]->Fill(centrality,PEM5TotSig_Noise);
        
        hZDCnEMchan_cent_Nsub[0]->Fill(centrality,NEM1TotSig_Noise);
        hZDCnEMchan_cent_Nsub[1]->Fill(centrality,NEM2TotSig_Noise);
        hZDCnEMchan_cent_Nsub[2]->Fill(centrality,NEM3TotSig_Noise);
        hZDCnEMchan_cent_Nsub[3]->Fill(centrality,NEM4TotSig_Noise);
        hZDCnEMchan_cent_Nsub[4]->Fill(centrality,NEM5TotSig_Noise);
        
        hZDCpHADchan_cent_Nsub[0]->Fill(centrality,PHAD1TotSig_Noise);
        hZDCpHADchan_cent_Nsub[1]->Fill(centrality,PHAD2TotSig_Noise);
        hZDCpHADchan_cent_Nsub[2]->Fill(centrality,PHAD3TotSig_Noise);
        hZDCpHADchan_cent_Nsub[3]->Fill(centrality,PHAD4TotSig_Noise);
        
        hZDCnHADchan_cent_Nsub[0]->Fill(centrality,NHAD1TotSig_Noise);
        hZDCnHADchan_cent_Nsub[1]->Fill(centrality,NHAD2TotSig_Noise);
        hZDCnHADchan_cent_Nsub[2]->Fill(centrality,NHAD3TotSig_Noise);
        hZDCnHADchan_cent_Nsub[3]->Fill(centrality,NHAD4TotSig_Noise);
        
        hZDCpEMchan_noff_Nsub[0]->Fill(noff,PEM1TotSig_Noise);
        hZDCpEMchan_noff_Nsub[1]->Fill(noff,PEM2TotSig_Noise);
        hZDCpEMchan_noff_Nsub[2]->Fill(noff,PEM3TotSig_Noise);
        hZDCpEMchan_noff_Nsub[3]->Fill(noff,PEM4TotSig_Noise);
        hZDCpEMchan_noff_Nsub[4]->Fill(noff,PEM5TotSig_Noise);
        
        hZDCnEMchan_noff_Nsub[0]->Fill(noff,NEM1TotSig_Noise);
        hZDCnEMchan_noff_Nsub[1]->Fill(noff,NEM2TotSig_Noise);
        hZDCnEMchan_noff_Nsub[2]->Fill(noff,NEM3TotSig_Noise);
        hZDCnEMchan_noff_Nsub[3]->Fill(noff,NEM4TotSig_Noise);
        hZDCnEMchan_noff_Nsub[4]->Fill(noff,NEM5TotSig_Noise);
        
        hZDCpHADchan_noff_Nsub[0]->Fill(noff,PHAD1TotSig_Noise);
        hZDCpHADchan_noff_Nsub[1]->Fill(noff,PHAD2TotSig_Noise);
        hZDCpHADchan_noff_Nsub[2]->Fill(noff,PHAD3TotSig_Noise);
        hZDCpHADchan_noff_Nsub[3]->Fill(noff,PHAD4TotSig_Noise);
        
        hZDCnHADchan_noff_Nsub[0]->Fill(noff,NHAD1TotSig_Noise);
        hZDCnHADchan_noff_Nsub[1]->Fill(noff,NHAD2TotSig_Noise);
        hZDCnHADchan_noff_Nsub[2]->Fill(noff,NHAD3TotSig_Noise);
        hZDCnHADchan_noff_Nsub[3]->Fill(noff,NHAD4TotSig_Noise);
    }
    
    EMpsum = PEM1TotSig + PEM2TotSig + PEM3TotSig + PEM4TotSig + PEM5TotSig;
    HADpsum = PHAD1TotSig + PHAD2TotSig + PHAD3TotSig + PHAD4TotSig;
    ETpsum = 0.1*EMpsum + HADpsum;
    
    EMnsum = NEM1TotSig + NEM2TotSig + NEM3TotSig + NEM4TotSig + NEM5TotSig;
    HADnsum = NHAD1TotSig + NHAD2TotSig + NHAD3TotSig + NHAD4TotSig;
    ETnsum = 0.1*EMnsum + HADnsum;
    
    EMpsum_Nsubbed = (PEM1TotSig - PEM1TotSig_Noise) + (PEM2TotSig - PEM2TotSig_Noise) + (PEM3TotSig - PEM3TotSig_Noise) + (PEM4TotSig - PEM4TotSig_Noise) + (PEM5TotSig - PEM5TotSig_Noise);
    HADpsum_Nsubbed = (PHAD1TotSig - PHAD1TotSig_Noise) + (PHAD2TotSig - PHAD2TotSig_Noise) + (PHAD3TotSig - PHAD3TotSig_Noise) + (PHAD4TotSig - PHAD4TotSig_Noise);
    ETpsum_Nsubbed = 0.1*EMpsum_Nsubbed + HADpsum_Nsubbed;
    
    EMnsum_Nsubbed = (NEM1TotSig - NEM1TotSig_Noise) + (NEM2TotSig - NEM2TotSig_Noise) + (NEM3TotSig - NEM3TotSig_Noise) + (NEM4TotSig - NEM4TotSig_Noise) + (NEM5TotSig - NEM5TotSig_Noise);
    HADnsum_Nsubbed = (NHAD1TotSig - NHAD1TotSig_Noise) + (NHAD2TotSig - NHAD2TotSig_Noise) + (NHAD3TotSig - NHAD3TotSig_Noise) + (NHAD4TotSig - NHAD4TotSig_Noise);
    ETnsum_Nsubbed = 0.1*EMnsum_Nsubbed + HADnsum_Nsubbed;
    
    
    hZDCpSumTotal[0]->Fill(PEM1TotSig);
    hZDCpSumTotal[1]->Fill(PEM2TotSig);
    hZDCpSumTotal[2]->Fill(PEM3TotSig);
    hZDCpSumTotal[3]->Fill(PEM4TotSig);
    hZDCpSumTotal[4]->Fill(PEM5TotSig);
    hZDCpSumTotal[5]->Fill(PHAD1TotSig);
    hZDCpSumTotal[6]->Fill(PHAD2TotSig);
    hZDCpSumTotal[7]->Fill(PHAD3TotSig);
    hZDCpSumTotal[8]->Fill(PHAD4TotSig);
    
    hZDCnSumTotal[0]->Fill(NEM1TotSig);
    hZDCnSumTotal[1]->Fill(NEM2TotSig);
    hZDCnSumTotal[2]->Fill(NEM3TotSig);
    hZDCnSumTotal[3]->Fill(NEM4TotSig);
    hZDCnSumTotal[4]->Fill(NEM5TotSig);
    hZDCnSumTotal[5]->Fill(NHAD1TotSig);
    hZDCnSumTotal[6]->Fill(NHAD2TotSig);
    hZDCnSumTotal[7]->Fill(NHAD3TotSig);
    hZDCnSumTotal[8]->Fill(NHAD4TotSig);
    
    hZDCpEMsum->Fill(EMpsum);
    hZDCnEMsum->Fill(EMnsum);
    hZDCpHADsum->Fill(HADpsum);
    hZDCnHADsum->Fill(HADnsum);
    hZDCtotsum_vs_cent->Fill(centrality,ETpsum+ETnsum);
    hZDCtotsum_vs_noff->Fill(noff,ETpsum+ETnsum);
    
    hZDCpEMsum_Nsub->Fill(EMpsum_Nsubbed);
    hZDCnEMsum_Nsub->Fill(EMnsum_Nsubbed);
    hZDCpHADsum_Nsub->Fill(HADpsum_Nsubbed);
    hZDCnHADsum_Nsub->Fill(HADnsum_Nsubbed);
    hZDCtotsum_Nsub_vs_cent->Fill(centrality,ETpsum_Nsubbed+ETnsum_Nsubbed);
    hZDCtotsum_Nsub_vs_noff->Fill(noff,ETpsum_Nsubbed+ETnsum_Nsubbed);
    
    hZDCpEM_vs_HAD->Fill(HADpsum, EMpsum);
    hZDCnEM_vs_HAD->Fill(HADnsum, EMnsum);
    hZDCpEM_vs_HAD_Nsub->Fill(HADpsum_Nsubbed, EMpsum_Nsubbed);
    hZDCnEM_vs_HAD_Nsub->Fill(HADnsum_Nsubbed, EMnsum_Nsubbed);
    
    hZDCpSum_vs_cent->Fill(centrality, ETpsum);
    hZDCnSum_vs_cent->Fill(centrality, ETnsum);
    hZDCpSum_vs_cent_Nsub->Fill(centrality, ETpsum_Nsubbed);
    hZDCnSum_vs_cent_Nsub->Fill(centrality, ETnsum_Nsubbed);
    
    hZDCpSum_vs_noff->Fill(noff, ETpsum);
    hZDCnSum_vs_noff->Fill(noff, ETnsum);
    hZDCpSum_vs_noff_Nsub->Fill(noff, ETpsum_Nsubbed);
    hZDCnSum_vs_noff_Nsub->Fill(noff, ETnsum_Nsubbed);
    
    hZDCpSum_vs_TS->Fill(noff, ETpsum);
    hZDCnSum_vs_TS->Fill(noff, ETnsum);
    hZDCpSum_vs_TS_Nsub->Fill(ETpsum_Nsubbed);
    hZDCnSum_vs_TS_Nsub->Fill(ETnsum_Nsubbed);
}

