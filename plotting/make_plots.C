// -*- C++ -*-
//
// Package:    make_ZDC_plots
//
/*
 
 Description: Plotting macro for the CMS Zero Degree Calorimeter (ZDC)
 
 Implementation: 
 <Notes of implementation>
 
 */
//
// Original Author:  Will McBrayer
//
//

# include "ReadZDCTree.C" 
# include "plot_style.C"

using namespace std;

void make_plots() {
    
    TH1::SetDefaultSumw2();
    TH2::SetDefaultSumw2();
    
    Bool_t close_plots = kFALSE;
    Bool_t print_plots = kFALSE;
    
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
    
    MakeHists();
    GetLeafs();
    
    // main event loop
    for (Int_t ievent = 0; ievent<nevents; ievent++)
    {
        ZDCDigiTree->GetEntry( ievent );
        ReadZDCTree( ievent );
    }
    
    plot_style(); // apply plotting options
    
    //------------------Make the plots------------------//
    gStyle->SetPalette(1);
    gStyle->SetErrorX(0.5);
    
    //---signal vs. centrality bin---//
    TCanvas * cZDCp_signal_vs_cent = new TCanvas("cZDCp_signal_vs_cent","cZDCp_signal_vs_cent",700,600);
    TPad * padZDCp_signal_vs_cent = (TPad*) cZDCp_signal_vs_cent->cd();
    padZDCp_signal_vs_cent->SetLogz();
    padZDCp_signal_vs_cent->SetRightMargin(0.115);
//    hZDCpSum_vs_cent->Draw();
//    hZDCpSum_vs_cent->ProfileX()->Draw("same");
    hZDCpSum_vs_cent_Nsub->Draw();
    hZDCpSum_vs_cent_Nsub->ProfileX()->Draw("same");
    if (print_plots) cZDCp_signal_vs_cent->Print("ZDCp_signal_vs_cent.pdf","pdf");
    if (close_plots) cZDCp_signal_vs_cent->Close();

    
    TCanvas * cZDCn_signal_vs_cent = new TCanvas("cZDCn_signal_vs_cent","cZDCn_signal_vs_cent",700,600);
    TPad * padZDCn_signal_vs_cent = (TPad*) cZDCn_signal_vs_cent->cd();
    padZDCn_signal_vs_cent->SetLogz();
    padZDCn_signal_vs_cent->SetRightMargin(0.115);
//    hZDCnSum_vs_cent->Draw();
//    hZDCnSum_vs_cent->ProfileX()->Draw("same");
    hZDCnSum_vs_cent_Nsub->Draw();
    hZDCnSum_vs_cent_Nsub->ProfileX()->Draw("same");
    if (print_plots) cZDCn_signal_vs_cent->Print("ZDCn_signal_vs_cent.pdf","pdf");
    if (close_plots) cZDCn_signal_vs_cent->Close();
    
    
    
    //---signal vs. number of tracks---//
    TCanvas * cZDCp_signal_vs_noff = new TCanvas("cZDCp_signal_vs_noff","cZDCp_signal_vs_noff",700,600);
    TPad * padZDCp_signal_vs_noff = (TPad*) cZDCp_signal_vs_noff->cd();
    padZDCp_signal_vs_noff->SetLogz();
    padZDCp_signal_vs_noff->SetRightMargin(0.115);
//    hZDCpSum_vs_noff->Draw();
//    hZDCpSum_vs_noff->ProfileX()->Draw("same");
    hZDCpSum_vs_noff_Nsub->Draw();
    hZDCpSum_vs_noff_Nsub->ProfileX()->Draw("same");
    if (print_plots) cZDCp_signal_vs_noff->Print("ZDCp_signal_vs_noff.pdf","pdf");
    if (close_plots) cZDCp_signal_vs_noff->Close();
    
    TCanvas * cZDCn_signal_vs_noff = new TCanvas("cZDCn_signal_vs_noff","cZDCn_signal_vs_noff",700,600);
    TPad * padZDCn_signal_vs_noff = (TPad*) cZDCn_signal_vs_noff->cd();
    padZDCn_signal_vs_noff->SetLogz();
    padZDCn_signal_vs_noff->SetRightMargin(0.115);
//    hZDCnSum_vs_noff->Draw();
//    hZDCnSum_vs_noff->ProfileX()->Draw("same");
    hZDCnSum_vs_noff_Nsub->Draw();
    hZDCnSum_vs_noff_Nsub->ProfileX()->Draw("same");
    if (print_plots) cZDCn_signal_vs_noff->Print("ZDCn_signal_vs_noff.pdf","pdf");
    if (close_plots) cZDCn_signal_vs_noff->Close();
    
    
    
    //---total ZDC signal---//
    TCanvas * cZDCsum_cent = new TCanvas("cZDCsum_cent","cZDCsum_cent",700,600);
    TPad * padZDCsum_cent = (TPad*) cZDCsum_cent->cd();
    padZDCsum_cent->SetLogz();
    padZDCsum_cent->SetRightMargin(0.115);
    hZDCtotsum_vs_cent->Draw();
    hZDCtotsum_vs_cent->ProfileX()->Draw("same");
    if (print_plots) cZDCsum_cent->Print("ZDCsum_cent.pdf","pdf");
    if (close_plots) cZDCsum_cent->Close();
    
    TCanvas * cZDCsum_Nsub_cent = new TCanvas("cZDCsum_Nsub_cent","cZDCsum_Nsub_cent",700,600);
    TPad * padZDCsum_Nsub_cent = (TPad*) cZDCsum_Nsub_cent->cd();
    padZDCsum_Nsub_cent->SetLogz();
    padZDCsum_Nsub_cent->SetRightMargin(0.115);
    hZDCtotsum_Nsub_vs_cent->Draw();
    hZDCtotsum_Nsub_vs_cent->ProfileX()->Draw("same");
    if (print_plots) cZDCsum_Nsub_cent->Print("ZDCsum_Nsub_cent.pdf","pdf");
    if (close_plots) cZDCsum_Nsub_cent->Close();
    
    TCanvas * cZDCsum_noff = new TCanvas("cZDCsum_noff","cZDCsum_noff",700,600);
    TPad * padZDCsum_noff = (TPad*) cZDCsum_noff->cd();
    padZDCsum_noff->SetLogz();
    padZDCsum_noff->SetRightMargin(0.115);
    hZDCtotsum_vs_noff->Draw();
    hZDCtotsum_vs_noff->ProfileX()->Draw("same");
    if (print_plots) cZDCsum_noff->Print("ZDCsum_noff.pdf","pdf");
    if (close_plots) cZDCsum_noff->Close();
    
    TCanvas * cZDCsum_Nsub_noff = new TCanvas("cZDCsum_Nsub_noff","cZDCsum_Nsub_noff",700,600);
    TPad * padZDCsum_Nsub_noff = (TPad*) cZDCsum_Nsub_noff->cd();
    padZDCsum_Nsub_noff->SetLogz();
    padZDCsum_Nsub_noff->SetRightMargin(0.115);
    hZDCtotsum_Nsub_vs_noff->Draw();
    hZDCtotsum_Nsub_vs_noff->ProfileX()->Draw("same");
    if (print_plots) cZDCsum_Nsub_noff->Print("ZDCsum_Nsub_noff.pdf","pdf");
    if (close_plots) cZDCsum_Nsub_noff->Close();
    
    
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
        hPXpEMchan_cent[EMchan-1]->Draw();
        txZDCpchan[EMchan-1]->AddText(Form("ZDC+ EM%d",EMchan));
        txZDCpchan[EMchan-1]->Draw();
    }
    hPXpEMchan_cent[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXpEMchan_cent[0]->GetYaxis()->SetTitleSize(0.07);
    hPXpEMchan_cent[0]->GetYaxis()->SetLabelSize(0.06);
    padPosChannel_Scan_cent[4]->SetRightMargin(0.01);
    padPosChannel_Scan_cent[4]->SetBottomMargin(0.01);
    padPosChannel_Scan_cent[5] = (TPad*) cPosChannel_Scan_cent->cd(6);
    hPXpHADchan_cent[0]->Draw();
    txZDCpchan[5]->AddText("ZDC+ HAD1");
    txZDCpchan[5]->Draw();
    padPosChannel_Scan_cent[6] = (TPad*) cPosChannel_Scan_cent->cd(7);
    hPXpHADchan_cent[1]->Draw();
    txZDCpchan[6]->AddText("ZDC+ HAD2");
    txZDCpchan[6]->Draw();
    padPosChannel_Scan_cent[7] = (TPad*) cPosChannel_Scan_cent->cd(8);
    hPXpHADchan_cent[2]->Draw();
    txZDCpchan[7]->AddText("ZDC+ HAD3");
    txZDCpchan[7]->Draw();
    padPosChannel_Scan_cent[8] = (TPad*) cPosChannel_Scan_cent->cd(9);
    padPosChannel_Scan_cent[8]->SetRightMargin(0.02);
    hPXpHADchan_cent[3]->Draw();
    txZDCpchan[8]->AddText("ZDC+ HAD4");
    txZDCpchan[8]->Draw();
    padPosChannel_Scan_cent[9] = (TPad*) cPosChannel_Scan_cent->cd(10);
    padPosChannel_Scan_cent[9]->SetTopMargin(0.2);
    if (print_plots) cPosChannel_Scan_cent->Print("PosChannel_Scan_cent.pdf","pdf");
    if (close_plots) cPosChannel_Scan_cent->Close();
    
    
    TCanvas * cPosChannel_Scan_cent_Nsub = new TCanvas("cPosChannel_Scan_cent_Nsub","cPosChannel_Scan_cent_Nsub",1250,550);
    cPosChannel_Scan_cent_Nsub->Divide(5,2,0,0);
    TPad * padPosChannel_Scan_cent_Nsub[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padPosChannel_Scan_cent_Nsub[EMchan-1] = (TPad*) cPosChannel_Scan_cent_Nsub->cd(EMchan);
        padPosChannel_Scan_cent_Nsub[EMchan-1]->SetTopMargin(0.05);
        hPXpEMchan_cent_Nsub[EMchan-1]->Draw();
        txZDCpchan[EMchan-1]->Draw();
    }
    hPXpEMchan_cent_Nsub[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXpEMchan_cent_Nsub[0]->GetYaxis()->SetTitleSize(0.07);
    hPXpEMchan_cent_Nsub[0]->GetYaxis()->SetLabelSize(0.06);
    padPosChannel_Scan_cent_Nsub[4]->SetRightMargin(0.01);
    padPosChannel_Scan_cent_Nsub[4]->SetBottomMargin(0.01);
    padPosChannel_Scan_cent_Nsub[5] = (TPad*) cPosChannel_Scan_cent_Nsub->cd(6);
    hPXpHADchan_cent_Nsub[0]->Draw();
    txZDCpchan[5]->Draw();
    padPosChannel_Scan_cent_Nsub[6] = (TPad*) cPosChannel_Scan_cent_Nsub->cd(7);
    hPXpHADchan_cent_Nsub[1]->Draw();
    txZDCpchan[6]->Draw();
    padPosChannel_Scan_cent_Nsub[7] = (TPad*) cPosChannel_Scan_cent_Nsub->cd(8);
    hPXpHADchan_cent_Nsub[2]->Draw();
    txZDCpchan[7]->Draw();
    padPosChannel_Scan_cent_Nsub[8] = (TPad*) cPosChannel_Scan_cent_Nsub->cd(9);
    padPosChannel_Scan_cent_Nsub[8]->SetRightMargin(0.02);
    hPXpHADchan_cent_Nsub[3]->Draw();
    txZDCpchan[8]->Draw();
    padPosChannel_Scan_cent_Nsub[9] = (TPad*) cPosChannel_Scan_cent_Nsub->cd(10);
    padPosChannel_Scan_cent_Nsub[9]->SetTopMargin(0.2);
    if (print_plots) cPosChannel_Scan_cent_Nsub->Print("PosChannel_Scan_cent_Nsub.pdf","pdf");
    if (close_plots) cPosChannel_Scan_cent_Nsub->Close();

    
    TCanvas * cPosChannel_Scan_noff = new TCanvas("cPosChannel_Scan_noff","cPosChannel_Scan_noff",1250,550);
    cPosChannel_Scan_noff->Divide(5,2,0,0);
    TPad * padPosChannel_Scan_noff[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padPosChannel_Scan_noff[EMchan-1] = (TPad*) cPosChannel_Scan_noff->cd(EMchan);
        padPosChannel_Scan_noff[EMchan-1]->SetTopMargin(0.05);
        hPXpEMchan_noff[EMchan-1]->Draw();
        txZDCpchan[EMchan-1]->Draw();
    }
    hPXpEMchan_noff[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXpEMchan_noff[0]->GetYaxis()->SetTitleSize(0.07);
    hPXpEMchan_noff[0]->GetYaxis()->SetLabelSize(0.06);
    padPosChannel_Scan_noff[4]->SetRightMargin(0.01);
    padPosChannel_Scan_noff[4]->SetBottomMargin(0.01);
    padPosChannel_Scan_noff[5] = (TPad*) cPosChannel_Scan_noff->cd(6);
    hPXpHADchan_noff[0]->Draw();
    txZDCpchan[5]->Draw();
    padPosChannel_Scan_noff[6] = (TPad*) cPosChannel_Scan_noff->cd(7);
    hPXpHADchan_noff[1]->Draw();
    txZDCpchan[6]->Draw();
    padPosChannel_Scan_noff[7] = (TPad*) cPosChannel_Scan_noff->cd(8);
    hPXpHADchan_noff[2]->Draw();
    txZDCpchan[7]->Draw();
    padPosChannel_Scan_noff[8] = (TPad*) cPosChannel_Scan_noff->cd(9);
    padPosChannel_Scan_noff[8]->SetRightMargin(0.02);
    hPXpHADchan_noff[3]->Draw();
    txZDCpchan[8]->Draw();
    padPosChannel_Scan_noff[9] = (TPad*) cPosChannel_Scan_noff->cd(10);
    padPosChannel_Scan_noff[9]->SetTopMargin(0.2);
    if (print_plots) cPosChannel_Scan_noff->Print("PosChannel_Scan_noff.pdf","pdf");
    if (close_plots) cPosChannel_Scan_noff->Close();

    
    TCanvas * cPosChannel_Scan_noff_Nsub = new TCanvas("cPosChannel_Scan_noff_Nsub","cPosChannel_Scan_noff_Nsub",1250,550);
    cPosChannel_Scan_noff_Nsub->Divide(5,2,0,0);
    TPad * padPosChannel_Scan_noff_Nsub[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padPosChannel_Scan_noff_Nsub[EMchan-1] = (TPad*) cPosChannel_Scan_noff_Nsub->cd(EMchan);
        padPosChannel_Scan_noff_Nsub[EMchan-1]->SetTopMargin(0.05);
        hPXpEMchan_noff_Nsub[EMchan-1]->Draw();
        txZDCpchan[EMchan-1]->Draw();
    }
    hPXpEMchan_noff_Nsub[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXpEMchan_noff_Nsub[0]->GetYaxis()->SetTitleSize(0.07);
    hPXpEMchan_noff_Nsub[0]->GetYaxis()->SetLabelSize(0.06);
    padPosChannel_Scan_noff_Nsub[4]->SetRightMargin(0.01);
    padPosChannel_Scan_noff_Nsub[4]->SetBottomMargin(0.01);
    padPosChannel_Scan_noff_Nsub[5] = (TPad*) cPosChannel_Scan_noff_Nsub->cd(6);
    hPXpHADchan_noff_Nsub[0]->Draw();
    txZDCpchan[5]->Draw();
    padPosChannel_Scan_noff_Nsub[6] = (TPad*) cPosChannel_Scan_noff_Nsub->cd(7);
    hPXpHADchan_noff_Nsub[1]->Draw();
    txZDCpchan[6]->Draw();
    padPosChannel_Scan_noff_Nsub[7] = (TPad*) cPosChannel_Scan_noff_Nsub->cd(8);
    hPXpHADchan_noff_Nsub[2]->Draw();
    txZDCpchan[7]->Draw();
    padPosChannel_Scan_noff_Nsub[8] = (TPad*) cPosChannel_Scan_noff_Nsub->cd(9);
    padPosChannel_Scan_noff_Nsub[8]->SetRightMargin(0.02);
    hPXpHADchan_noff_Nsub[3]->Draw();
    txZDCpchan[8]->Draw();
    padPosChannel_Scan_noff_Nsub[9] = (TPad*) cPosChannel_Scan_noff->cd(10);
    padPosChannel_Scan_noff_Nsub[9]->SetTopMargin(0.2);
    if (print_plots) cPosChannel_Scan_noff_Nsub->Print("PosChannel_Scan_noff_Nsub.pdf","pdf");
    if (close_plots) cPosChannel_Scan_noff_Nsub->Close();
    
    
    
    
    
    TPaveText * txZDCnchan[9];
    for (int chan = 0; chan<(numEMchan+numHADchan); chan++) {
        txZDCnchan[chan] = new TPaveText(0.62,0.78,0.91,0.90,"NDC");
        txZDCnchan[chan]->SetFillColor(kWhite);
        txZDCnchan[chan]->SetBorderSize(0);
        txZDCnchan[chan]->SetTextFont(43);
        txZDCnchan[chan]->SetTextSize(18);
    }
    
    TCanvas * cNegChannel_Scan_cent = new TCanvas("cNegChannel_Scan_cent","cNegChannel_Scan_cent",1250,550);
    cNegChannel_Scan_cent->Divide(5,2,0,0);
    TPad * padNegChannel_Scan_cent[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padNegChannel_Scan_cent[EMchan-1] = (TPad*) cNegChannel_Scan_cent->cd(EMchan);
        padNegChannel_Scan_cent[EMchan-1]->SetTopMargin(0.05);
        hPXnEMchan_cent[EMchan-1]->Draw();
        txZDCnchan[EMchan-1]->AddText(Form("ZDC- EM%d",EMchan));
        txZDCnchan[EMchan-1]->Draw();
    }
    hPXnEMchan_cent[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXnEMchan_cent[0]->GetYaxis()->SetTitleSize(0.07);
    hPXnEMchan_cent[0]->GetYaxis()->SetLabelSize(0.06);
    padNegChannel_Scan_cent[4]->SetRightMargin(0.01);
    padNegChannel_Scan_cent[4]->SetBottomMargin(0.01);
    padNegChannel_Scan_cent[5] = (TPad*) cNegChannel_Scan_cent->cd(6);
    hPXnHADchan_cent[0]->Draw();
    txZDCnchan[5]->AddText("ZDC- HAD1");
    txZDCnchan[5]->Draw();
    padNegChannel_Scan_cent[6] = (TPad*) cNegChannel_Scan_cent->cd(7);
    hPXnHADchan_cent[1]->Draw();
    txZDCnchan[6]->AddText("ZDC- HAD2");
    txZDCnchan[6]->Draw();
    padNegChannel_Scan_cent[7] = (TPad*) cNegChannel_Scan_cent->cd(8);
    hPXnHADchan_cent[2]->Draw();
    txZDCnchan[7]->AddText("ZDC- HAD3");
    txZDCnchan[7]->Draw();
    padNegChannel_Scan_cent[8] = (TPad*) cNegChannel_Scan_cent->cd(9);
    padNegChannel_Scan_cent[8]->SetRightMargin(0.02);
    hPXnHADchan_cent[3]->Draw();
    txZDCnchan[8]->AddText("ZDC- HAD4");
    txZDCnchan[8]->Draw();
    padNegChannel_Scan_cent[9] = (TPad*) cNegChannel_Scan_cent->cd(10);
    padNegChannel_Scan_cent[9]->SetTopMargin(0.2);
    if (print_plots) cNegChannel_Scan_cent->Print("NegChannel_Scan_cent.pdf","pdf");
    if (close_plots) cNegChannel_Scan_cent->Close();
    
    
    TCanvas * cNegChannel_Scan_cent_Nsub = new TCanvas("cNegChannel_Scan_cent_Nsub","cNegChannel_Scan_cent_Nsub",1250,550);
    cNegChannel_Scan_cent_Nsub->Divide(5,2,0,0);
    TPad * padNegChannel_Scan_cent_Nsub[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padNegChannel_Scan_cent_Nsub[EMchan-1] = (TPad*) cNegChannel_Scan_cent_Nsub->cd(EMchan);
        padNegChannel_Scan_cent_Nsub[EMchan-1]->SetTopMargin(0.05);
        hPXnEMchan_cent_Nsub[EMchan-1]->Draw();
        txZDCnchan[EMchan-1]->Draw();
    }
    hPXnEMchan_cent_Nsub[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXnEMchan_cent_Nsub[0]->GetYaxis()->SetTitleSize(0.07);
    hPXnEMchan_cent_Nsub[0]->GetYaxis()->SetLabelSize(0.06);
    padNegChannel_Scan_cent_Nsub[4]->SetRightMargin(0.01);
    padNegChannel_Scan_cent_Nsub[4]->SetBottomMargin(0.01);
    padNegChannel_Scan_cent_Nsub[5] = (TPad*) cNegChannel_Scan_cent_Nsub->cd(6);
    hPXnHADchan_cent_Nsub[0]->Draw();
    txZDCnchan[5]->Draw();
    padNegChannel_Scan_cent_Nsub[6] = (TPad*) cNegChannel_Scan_cent_Nsub->cd(7);
    hPXnHADchan_cent_Nsub[1]->Draw();
    txZDCnchan[6]->Draw();
    padNegChannel_Scan_cent_Nsub[7] = (TPad*) cNegChannel_Scan_cent_Nsub->cd(8);
    hPXnHADchan_cent_Nsub[2]->Draw();
    txZDCnchan[7]->Draw();
    padNegChannel_Scan_cent_Nsub[8] = (TPad*) cNegChannel_Scan_cent_Nsub->cd(9);
    padNegChannel_Scan_cent_Nsub[8]->SetRightMargin(0.02);
    hPXnHADchan_cent_Nsub[3]->Draw();
    txZDCnchan[8]->Draw();
    padNegChannel_Scan_cent_Nsub[9] = (TPad*) cNegChannel_Scan_cent_Nsub->cd(10);
    padNegChannel_Scan_cent_Nsub[9]->SetTopMargin(0.2);
    if (print_plots) cNegChannel_Scan_cent_Nsub->Print("NegChannel_Scan_cent_Nsub.pdf","pdf");
    if (close_plots) cNegChannel_Scan_cent_Nsub->Close();
    
    
    TCanvas * cNegChannel_Scan_noff = new TCanvas("cNegChannel_Scan_noff","cNegChannel_Scan_noff",1250,550);
    cNegChannel_Scan_noff->Divide(5,2,0,0);
    TPad * padNegChannel_Scan_noff[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padNegChannel_Scan_noff[EMchan-1] = (TPad*) cNegChannel_Scan_noff->cd(EMchan);
        padNegChannel_Scan_noff[EMchan-1]->SetTopMargin(0.05);
        hPXnEMchan_noff[EMchan-1]->Draw();
        txZDCnchan[EMchan-1]->Draw();
    }
    hPXnEMchan_noff[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXnEMchan_noff[0]->GetYaxis()->SetTitleSize(0.07);
    hPXnEMchan_noff[0]->GetYaxis()->SetLabelSize(0.06);
    padNegChannel_Scan_noff[4]->SetRightMargin(0.01);
    padNegChannel_Scan_noff[4]->SetBottomMargin(0.01);
    padNegChannel_Scan_noff[5] = (TPad*) cNegChannel_Scan_noff->cd(6);
    hPXnHADchan_noff[0]->Draw();
    txZDCnchan[5]->Draw();
    padNegChannel_Scan_noff[6] = (TPad*) cNegChannel_Scan_noff->cd(7);
    hPXnHADchan_noff[1]->Draw();
    txZDCnchan[6]->Draw();
    padNegChannel_Scan_noff[7] = (TPad*) cNegChannel_Scan_noff->cd(8);
    hPXnHADchan_noff[2]->Draw();
    txZDCnchan[7]->Draw();
    padNegChannel_Scan_noff[8] = (TPad*) cNegChannel_Scan_noff->cd(9);
    padNegChannel_Scan_noff[8]->SetRightMargin(0.02);
    hPXnHADchan_noff[3]->Draw();
    txZDCnchan[8]->Draw();
    padNegChannel_Scan_noff[9] = (TPad*) cNegChannel_Scan_noff->cd(10);
    padNegChannel_Scan_noff[9]->SetTopMargin(0.2);
    if (print_plots) cNegChannel_Scan_noff->Print("NegChannel_Scan_noff.pdf","pdf");
    if (close_plots) cNegChannel_Scan_noff->Close();
    
    TCanvas * cNegChannel_Scan_noff_Nsub = new TCanvas("cNegChannel_Scan_noff_Nsub","cNegChannel_Scan_noff_Nsub",1250,550);
    cNegChannel_Scan_noff_Nsub->Divide(5,2,0,0);
    TPad * padNegChannel_Scan_noff_Nsub[10];
    for (int EMchan = 1; EMchan<=numEMchan; EMchan++) {
        padNegChannel_Scan_noff_Nsub[EMchan-1] = (TPad*) cNegChannel_Scan_noff_Nsub->cd(EMchan);
        padNegChannel_Scan_noff_Nsub[EMchan-1]->SetTopMargin(0.05);
        hPXnEMchan_noff_Nsub[EMchan-1]->Draw();
        txZDCnchan[EMchan-1]->Draw();
    }
    hPXnEMchan_noff_Nsub[0]->GetYaxis()->SetTitleOffset(1.35);
    hPXnEMchan_noff_Nsub[0]->GetYaxis()->SetTitleSize(0.07);
    hPXnEMchan_noff_Nsub[0]->GetYaxis()->SetLabelSize(0.06);
    padNegChannel_Scan_noff_Nsub[4]->SetRightMargin(0.01);
    padNegChannel_Scan_noff_Nsub[4]->SetBottomMargin(0.01);
    padNegChannel_Scan_noff_Nsub[5] = (TPad*) cNegChannel_Scan_noff_Nsub->cd(6);
    hPXnHADchan_noff_Nsub[0]->Draw();
    txZDCnchan[5]->Draw();
    padNegChannel_Scan_noff_Nsub[6] = (TPad*) cNegChannel_Scan_noff_Nsub->cd(7);
    hPXnHADchan_noff_Nsub[1]->Draw();
    txZDCnchan[6]->Draw();
    padNegChannel_Scan_noff_Nsub[7] = (TPad*) cNegChannel_Scan_noff_Nsub->cd(8);
    hPXnHADchan_noff_Nsub[2]->Draw();
    txZDCnchan[7]->Draw();
    padNegChannel_Scan_noff_Nsub[8] = (TPad*) cNegChannel_Scan_noff_Nsub->cd(9);
    padNegChannel_Scan_noff_Nsub[8]->SetRightMargin(0.02);
    hPXnHADchan_noff_Nsub[3]->Draw();
    txZDCnchan[8]->Draw();
    padNegChannel_Scan_noff_Nsub[9] = (TPad*) cNegChannel_Scan_noff->cd(10);
    padNegChannel_Scan_noff_Nsub[9]->SetTopMargin(0.2);
    if (print_plots) cNegChannel_Scan_noff_Nsub->Print("NegChannel_Scan_noff_Nsub.pdf","pdf");
    if (close_plots) cNegChannel_Scan_noff_Nsub->Close();

    
}
