// -*- C++ -*-
//
// Package:    make_ZDC_plots
//
/*
 
 Description: Plotting macro for the CMS Zero Degree Calorimeter (ZDC)
 
 Note on running:
    The structure of this code is as follows: make_plots.C accessess the root 
 file choice in which the ZDC digis are stored.
    Calibration of channels is done event by event in ReadZDCTree.C. Edit this 
 for changes of channel gains or switching of timeslices/ZDC channels. 
    Histograms and declared and their plotting options set in plot_style.C. 
 The bin sizes, axis limits, and other settings are adjusted here. If a new 
 histogram not already being made is needed, it must first be initialized in 
 ReadZDCTree.C and then then declared in plot_style.C. 
    The histograms are stored into a new, much smaller .root file for quick 
 access called ZDC_plots.root. Lastly, all canvas options are set and drawn in
 make_plots.C.
 
 */
//
// Original Author:  Will McBrayer
// Date:  31st May, 2016
//

# include "ReadZDCTree.C"
# include "plot_style.C"

using namespace std;

void make_plots() {
    
    TH1::SetDefaultSumw2();

    Bool_t close_plots = kFALSE;
    Bool_t print_plots = kTRUE;

//    fin = new TFile("/rfs/wmcbrayer/2015PbPb_ZDC/PbPb2015_PromptReco_MinimumBias2/merged/PbPb2015_PromptReco_MinBias2_262836.root"); // 1.6 GB
//    fin = new TFile("/rfs/wmcbrayer/2015PbPb_ZDC/PbPb2015_PromptReco_MinimumBias2/merged/PbPb2015_PromptReco_MinBias2_263005.root"); // 9.6 GB
//    fin = new TFile("/rfs/wmcbrayer/2015PbPb_ZDC/PbPb2015_PromptReco_MinimumBias2/merged/PbPb2015_PromptReco_MinBias2_263213.root"); // 46 MB
    fin = new TFile("/rfs/wmcbrayer/2015PbPb_ZDC/PbPb2015_PromptReco_MinimumBias2/merged/PbPb2015_PromptReco_MinBias2_263293.root"); // 8.8 GB
//    fin = new TFile("/rfs/wmcbrayer/2015PbPb_ZDC/PbPb2015_PromptReco_MinimumBias2/merged/PbPb2015_PromptReco_MinBias2_263362.root"); // 94 GB
//    fin = new TFile("/rfs/wmcbrayer/2015PbPb_ZDC/PbPb2015_PromptReco_MinimumBias2/merged/PbPb2015_PromptReco_MinBias2_262834_263213.root");

    CentTree = (TTree *) fin->Get("ZDCRecTree");
    // because of a typo the above line needs to stay until the trees are rewritten
    // "ZDCRecTree" will be replaced in output .root files with "CentTree"
//    CentTree = (TTree *) fin->Get("CentTree");
    ZDCDigiTree = (TTree *) fin->Get("ZDCDigiTree");
    BeamTree = (TTree *) fin->Get("BeamTree");
    
    tfout = new TFile("results/ZDC_plots.root","recreate");
    tfout->cd();

    MakeHists();
    GetLeafs();

    // main event loop
    int nextStatus = ZDCDigiTree->GetEntries()/20;
    for (Int_t ievent = 0; ievent<nevents; ievent++)
    {
        if(ievent>nextStatus) {
            cout<<" "<<nextStatus/(double)ZDCDigiTree->GetEntries()<<endl;
            nextStatus+=ZDCDigiTree->GetEntries()/20;
        }
        ZDCDigiTree->GetEntry( ievent );
        ReadZDCTree( ievent );
    }
    plot_style(); // apply plotting options

    
    tdRunInfo = (TDirectory *) tfout->mkdir("Run_Info");
    tdRunInfo->cd();
    hcent->Write();
    hnoff->Write();
    hbxing->Write();
    
    tdIndChans = (TDirectory *) tfout->mkdir("Signal_by_channel");
    tdIndChans->cd();
    for (int EMchan = 0; EMchan<5; EMchan++) {
        hZDCpEMchan_cent[EMchan]->Write();
        hZDCnEMchan_cent[EMchan]->Write();
        hZDCpEMchan_cent_Nsub[EMchan]->Write();
        hZDCnEMchan_cent_Nsub[EMchan]->Write();
        hZDCpEMchan_noff[EMchan]->Write();
        hZDCnEMchan_noff[EMchan]->Write();
        hZDCpEMchan_noff_Nsub[EMchan]->Write();
        hZDCnEMchan_noff_Nsub[EMchan]->Write();
    }
    for (int HADchan = 0; HADchan<4; HADchan++) {
        hZDCpHADchan_cent[HADchan]->Write();
        hZDCnHADchan_cent[HADchan]->Write();
        hZDCpHADchan_cent_Nsub[HADchan]->Write();
        hZDCnHADchan_cent_Nsub[HADchan]->Write();
        hZDCpHADchan_noff[HADchan]->Write();
        hZDCnHADchan_noff[HADchan]->Write();
        hZDCpHADchan_noff_Nsub[HADchan]->Write();
        hZDCnHADchan_noff_Nsub[HADchan]->Write();
    }
    
    tdXprofiles = (TDirectory *) tfout->mkdir("ProfileXs");
    tdXprofiles->cd();
    for (int iTS = TSsigMin; iTS<+TSsigMax; iTS++) {
        for (int EMchan = 0; EMchan<5; EMchan++) {
            hPXpEMchan_cent[EMchan]->Write();
            hPXnEMchan_cent[EMchan]->Write();
            hPXpEMchan_cent_Nsub[EMchan]->Write();
            hPXnEMchan_cent_Nsub[EMchan]->Write();
            hPXpEMchan_noff[EMchan]->Write();
            hPXnEMchan_noff[EMchan]->Write();
            hPXpEMchan_noff_Nsub[EMchan]->Write();
            hPXnEMchan_noff_Nsub[EMchan]->Write();
        }
        for (int HADchan = 0; HADchan<4; HADchan++) {
            hPXpHADchan_cent[HADchan]->Write();
            hPXnHADchan_cent[HADchan]->Write();
            hPXpHADchan_cent_Nsub[HADchan]->Write();
            hPXnHADchan_cent_Nsub[HADchan]->Write();
            hPXpHADchan_noff[HADchan]->Write();
            hPXnHADchan_noff[HADchan]->Write();
            hPXpHADchan_noff_Nsub[HADchan]->Write();
            hPXnHADchan_noff_Nsub[HADchan]->Write();
        }
    }
    
    tdIndChanTS = (TDirectory *) tfout->mkdir("Signal_by_channel_by_TS");
    tdIndChanTS->cd();
    for (int iTS = TSsigMin; iTS<+TSsigMax; iTS++) {
        for (int EMchan = 0; EMchan<5; EMchan++) {
            hZDCpEM[iTS][EMchan]->Write();
            hZDCnEM[iTS][EMchan]->Write();
            hZDCpEM_vs_cent[iTS][EMchan]->Write();
            hZDCnEM_vs_cent[iTS][EMchan]->Write();
            hZDCpEM_vs_noff[iTS][EMchan]->Write();
            hZDCnEM_vs_noff[iTS][EMchan]->Write();
            
            hZDCpEM_Nsub[iTS][EMchan]->Write();
            hZDCnEM_Nsub[iTS][EMchan]->Write();
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->Write();
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->Write();
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->Write();
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->Write();
        }
        for (int HADchan = 0; HADchan<4; HADchan++) {
            hZDCpHAD[iTS][HADchan]->Write();
            hZDCnHAD[iTS][HADchan]->Write();
            hZDCpHAD_vs_cent[iTS][HADchan]->Write();
            hZDCnHAD_vs_cent[iTS][HADchan]->Write();
            hZDCpHAD_vs_noff[iTS][HADchan]->Write();
            hZDCnHAD_vs_noff[iTS][HADchan]->Write();
            
            hZDCpHAD_Nsub[iTS][HADchan]->Write();
            hZDCnHAD_Nsub[iTS][HADchan]->Write();
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->Write();
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->Write();
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->Write();
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->Write();
        }
    }

    tdChanSums = (TDirectory *) tfout->mkdir("Energy_sums");
    tdChanSums->cd();
    hZDCpEMsum->Write();
    hZDCpHADsum->Write();
    hZDCnEMsum->Write();
    hZDCnHADsum->Write();
    hZDCptotsum_vs_cent->Write();
    hZDCntotsum_vs_cent->Write();
    hZDCptotsum_vs_noff->Write();
    hZDCntotsum_vs_noff->Write();
    hZDCpEMsum_Nsub->Write();
    hZDCpHADsum_Nsub->Write();
    hZDCnEMsum_Nsub->Write();
    hZDCnHADsum_Nsub->Write();
    hZDCtotsum_Nsub_vs_cent->Write();
    hZDCtotsum_Nsub_vs_noff->Write();
    hZDCpEM_vs_HAD->Write();
    hZDCnEM_vs_HAD->Write();
    hZDCpEM_vs_HAD_Nsub->Write();
    hZDCnEM_vs_HAD_Nsub->Write();
    hZDCpEM_vs_tot->Write();
    hZDCnEM_vs_tot->Write();
    hZDCpEM_vs_tot_Nsub->Write();
    hZDCnEM_vs_tot_Nsub->Write();
    hZDCpSum_vs_cent->Write();
    hZDCnSum_vs_cent->Write();
    hZDCpSum_vs_cent_Nsub->Write();
//    hZDCnSum_vs_cent_Nsub->Write();
    hZDCpSum_vs_noff->Write();
    hZDCnSum_vs_noff->Write();
    hZDCpSum_vs_noff_Nsub->Write();
    hZDCnSum_vs_noff_Nsub->Write();
    hZDCpSum_vs_TS->Write();
    hZDCnSum_vs_TS->Write();
    hZDCpSum_vs_TS_Nsub->Write();
    hZDCnSum_vs_TS_Nsub->Write();
    for (int chan = 0; chan<numchan; chan++) {
        hZDCpSumTotal[chan]->Write();
        hZDCnSumTotal[chan]->Write();
    }
    
    //------------------Make the plots------------------//
    
    gStyle->SetPalette(1);
    gStyle->SetErrorX(0.5);
    
    TPaveText * txSignalTS = new TPaveText(0.50, 0.87, 0.82, 0.94,"NDC");
    txSignalTS->SetFillColor(kWhite);
    txSignalTS->SetBorderSize(0);
    txSignalTS->SetTextFont(43);
    txSignalTS->SetTextSize(20);
    txSignalTS->AddText(Form("Timeslice(s) for signal: %d-%d",TSsigMin,TSsigMax));
    
    TPaveText * txNoiseTS = new TPaveText(0.50, 0.80, 0.82, 0.87,"NDC");
    txNoiseTS->SetFillColor(kWhite);
    txNoiseTS->SetBorderSize(0);
    txNoiseTS->SetTextFont(43);
    txNoiseTS->SetTextSize(20);
    txNoiseTS->AddText(Form("Timeslice(s) for noise: %d-%d",TSnoiseMin,TSnoiseMax));
    
    //---signal vs. centrality bin---//
    TCanvas * cZDCp_signal_vs_cent = new TCanvas("cZDCp_signal_vs_cent","cZDCp_signal_vs_cent",700,600);
    TPad * padZDCp_signal_vs_cent = (TPad*) cZDCp_signal_vs_cent->cd();
    padZDCp_signal_vs_cent->SetLogz();
    padZDCp_signal_vs_cent->SetRightMargin(0.115);
    hZDCpSum_vs_cent_Nsub->Draw("same");
    hZDCpSum_vs_cent_Nsub->ProfileX()->Draw("same");
    txSignalTS->Draw("same");
    txNoiseTS->Draw("same");
    if (print_plots) cZDCp_signal_vs_cent->Print("results/ZDCp_signal_vs_cent.pdf","pdf");
    if (close_plots) cZDCp_signal_vs_cent->Close();
    
    
    //---signal vs. number of tracks---//
    TCanvas * cZDCp_signal_vs_noff = new TCanvas("cZDCp_signal_vs_noff","cZDCp_signal_vs_noff",700,600);
    TPad * padZDCp_signal_vs_noff = (TPad*) cZDCp_signal_vs_noff->cd();
    padZDCp_signal_vs_noff->SetLogz();
    padZDCp_signal_vs_noff->SetRightMargin(0.115);
    hZDCpSum_vs_noff_Nsub->Draw("same");
    hZDCpSum_vs_noff_Nsub->ProfileX()->Draw("same");
    txSignalTS->Draw("same");
    txNoiseTS->Draw("same");
    if (print_plots) cZDCp_signal_vs_noff->Print("results/ZDCp_signal_vs_noff.pdf","pdf");
    if (close_plots) cZDCp_signal_vs_noff->Close();
    
    
    //---EM vs. HAD + 0.1*EM---//
    TCanvas * cZDCpEM_vs_tot = new TCanvas("cZDCpEM_vs_tot","cZDCpEM_vs_tot",700,650);
    TPad * padZDCpEM_vs_tot = (TPad*) cZDCpEM_vs_tot->cd();
    padZDCpEM_vs_tot->SetRightMargin(0.125);
    cZDCpEM_vs_tot->cd();
    hZDCpEM_vs_tot->Draw("same");
    txSignalTS->Draw("same");
    if (print_plots) cZDCpEM_vs_tot->Print("results/ZDCpEM_vs_tot.pdf","pdf");
    if (close_plots) cZDCpEM_vs_tot->Close();
    
    TCanvas * cZDCpEM_vs_tot_Nsub = new TCanvas("cZDCpEM_vs_tot_Nsub","cZDCpEM_vs_tot_Nsub",700,650);
    TPad * padZDCpEM_vs_tot_Nsub = (TPad*) cZDCpEM_vs_tot_Nsub->cd();
    padZDCpEM_vs_tot_Nsub->SetRightMargin(0.125);
    cZDCpEM_vs_tot_Nsub->cd();
    hZDCpEM_vs_tot_Nsub->Draw("same");
    txSignalTS->Draw("same");
    txNoiseTS->Draw("same");
    if (print_plots) cZDCpEM_vs_tot_Nsub->Print("results/ZDCpEM_vs_tot_Nsub.pdf","pdf");
    if (close_plots) cZDCpEM_vs_tot_Nsub->Close();
    
    
    //---signal scan: entire ZDC signal in each channel---//
    TPaveText * txZDCpchan[9];
    for (int chan = 0; chan<(numEMchan+numHADchan); chan++) {
        txZDCpchan[chan] = new TPaveText(0.62,0.78,0.91,0.90,"NDC");
        txZDCpchan[chan]->SetFillColor(kWhite);
        txZDCpchan[chan]->SetBorderSize(0);
        txZDCpchan[chan]->SetTextFont(43);
        txZDCpchan[chan]->SetTextSize(18);
    }
    
    TCanvas * cPosChannel_Scan_cent = new TCanvas("cPosChannel_Scan_cent","cPosChannel_Scan_cent",1250,550);
    cPosChannel_Scan_cent->Divide(5,2,0,0);
    TPad * padPosChannel_Scan_cent[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padPosChannel_Scan_cent[EMchan-1] = (TPad*) cPosChannel_Scan_cent->cd(EMchan);
        padPosChannel_Scan_cent[EMchan-1]->SetTopMargin(0.05);
        hPXpEMchan_cent[EMchan-1]->Draw("same");
        txZDCpchan[EMchan-1]->AddText(Form("ZDC+ EM%d",EMchan));
        txZDCpchan[EMchan-1]->Draw("same");
    }
    hPXpEMchan_cent[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXpEMchan_cent[0]->GetYaxis()->SetTitleSize(0.07);
    hPXpEMchan_cent[0]->GetYaxis()->SetLabelSize(0.06);
    padPosChannel_Scan_cent[4]->SetRightMargin(0.01);
    padPosChannel_Scan_cent[4]->SetBottomMargin(0.01);
    padPosChannel_Scan_cent[5] = (TPad*) cPosChannel_Scan_cent->cd(6);
    hPXpHADchan_cent[0]->Draw("same");
    txZDCpchan[5]->AddText("ZDC+ HAD1");
    txZDCpchan[5]->Draw("same");
    padPosChannel_Scan_cent[6] = (TPad*) cPosChannel_Scan_cent->cd(7);
    hPXpHADchan_cent[1]->Draw("same");
    txZDCpchan[6]->AddText("ZDC+ HAD2");
    txZDCpchan[6]->Draw("same");
    padPosChannel_Scan_cent[7] = (TPad*) cPosChannel_Scan_cent->cd(8);
    hPXpHADchan_cent[2]->Draw("same");
    txZDCpchan[7]->AddText("ZDC+ HAD3");
    txZDCpchan[7]->Draw("same");
    padPosChannel_Scan_cent[8] = (TPad*) cPosChannel_Scan_cent->cd(9);
    padPosChannel_Scan_cent[8]->SetRightMargin(0.02);
    hPXpHADchan_cent[3]->Draw("same");
    txZDCpchan[8]->AddText("ZDC+ HAD4");
    txZDCpchan[8]->Draw("same");
    padPosChannel_Scan_cent[9] = (TPad*) cPosChannel_Scan_cent->cd(10);
    padPosChannel_Scan_cent[9]->SetTopMargin(0.2);
    txSignalTS->Draw("same");
    txNoiseTS->Draw("same");
    if (print_plots) cPosChannel_Scan_cent->Print("results/PosChannel_Scan_cent.pdf","pdf");
    if (close_plots) cPosChannel_Scan_cent->Close();
    
    
    TCanvas * cPosChannel_Scan_noff = new TCanvas("cPosChannel_Scan_noff","cPosChannel_Scan_noff",1250,550);
    cPosChannel_Scan_noff->Divide(5,2,0,0);
    TPad * padPosChannel_Scan_noff[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padPosChannel_Scan_noff[EMchan-1] = (TPad*) cPosChannel_Scan_noff->cd(EMchan);
        padPosChannel_Scan_noff[EMchan-1]->SetTopMargin(0.05);
        hPXpEMchan_noff[EMchan-1]->Draw("same");
        txZDCpchan[EMchan-1]->Draw("same");
    }
    hPXpEMchan_noff[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXpEMchan_noff[0]->GetYaxis()->SetTitleSize(0.07);
    hPXpEMchan_noff[0]->GetYaxis()->SetLabelSize(0.06);
    padPosChannel_Scan_noff[4]->SetRightMargin(0.01);
    padPosChannel_Scan_noff[4]->SetBottomMargin(0.01);
    padPosChannel_Scan_noff[5] = (TPad*) cPosChannel_Scan_noff->cd(6);
    hPXpHADchan_noff[0]->Draw("same");
    txZDCpchan[5]->Draw("same");
    padPosChannel_Scan_noff[6] = (TPad*) cPosChannel_Scan_noff->cd(7);
    hPXpHADchan_noff[1]->Draw("same");
    txZDCpchan[6]->Draw("same");
    padPosChannel_Scan_noff[7] = (TPad*) cPosChannel_Scan_noff->cd(8);
    hPXpHADchan_noff[2]->Draw("same");
    txZDCpchan[7]->Draw("same");
    padPosChannel_Scan_noff[8] = (TPad*) cPosChannel_Scan_noff->cd(9);
    padPosChannel_Scan_noff[8]->SetRightMargin(0.02);
    hPXpHADchan_noff[3]->Draw("same");
    txZDCpchan[8]->Draw("same");
    padPosChannel_Scan_noff[9] = (TPad*) cPosChannel_Scan_noff->cd(10);
    padPosChannel_Scan_noff[9]->SetTopMargin(0.2);
    txSignalTS->Draw("same");
    txNoiseTS->Draw("same");
    if (print_plots) cPosChannel_Scan_noff->Print("results/PosChannel_Scan_noff.pdf","pdf");
    if (close_plots) cPosChannel_Scan_noff->Close();
 
}
