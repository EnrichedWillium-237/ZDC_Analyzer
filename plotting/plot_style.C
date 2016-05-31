// plot_style.h
//
// Style options for histograms

const int mrkcolor[] = {kRed, kOrange-3, kYellow+1, kSpring+9, kGreen+3,
    kCyan+1, kBlue, kViolet+7, kMagenta, kPink+7};
const int mrkstyle[] = {20, 20, 20, 20, 20,
    20, 20, 20, 20, 20};
const double mrksize[] = {0.8, 0.8, 0.8, 0.8, 0.8,
    0.8, 0.8, 0.8, 0.8, 0.8};
const double centScan_max = 4000;
const double noffScan_max = 4000;
const int noff_range = 3500;


void MakeHists() {
    
    hcent = new TH1F("cent","cent", 200, 1, 200);
    hnoff = new TH1F("noff","noff", 4001, 0, noff_range);
    hbxing = new TH1F("bxing","bxing", 4001, 0, 3500);
    
    // plots for individual channels per timeslice
    for (int iTS = 0; iTS<nTS; iTS++) {
        for (Int_t EMchan = 0; EMchan<numEMchan; EMchan++) {
            hZDCpEM[iTS][EMchan] = new TH1F(Form("ZDCpEM_TS%i_ch%i",iTS,EMchan),Form("ZDCpEM_TS%i_ch%i",iTS,EMchan), 300, 0, 20000);
            hZDCnEM[iTS][EMchan] = new TH1F(Form("ZDCnEM_TS%i_ch%i",iTS,EMchan),Form("ZDCnEM_TS%i_ch%i",iTS,EMchan), 300, 0, 20000);
            hZDCpEM_Nsub[iTS][EMchan] = new TH1F(Form("ZDCpEM_Nsub_TS%i_ch%i",iTS,EMchan),Form("ZDCpEM_Nsub_TS%i_ch%i",iTS,EMchan), 300, 0, 20000);
            hZDCnEM_Nsub[iTS][EMchan] = new TH1F(Form("ZDCnEM_Nsub_TS%i_ch%i",iTS,EMchan),Form("ZDCnEM_Nsub_TS%i_ch%i",iTS,EMchan), 300, 0, 20000);
            
            hZDCpEM_vs_cent[iTS][EMchan] = new TH2F(Form("ZDCpEM_vs_cent_TS%i_ch%i",iTS,EMchan),Form("ZDCpEM_vs_cent_TS%i_ch%i",iTS,EMchan), 10, 1, 200, 300, 0, 20000);
            hZDCnEM_vs_cent[iTS][EMchan] = new TH2F(Form("ZDCnEM_vs_cent_TS%i_ch%i",iTS,EMchan),Form("ZDCnEM_vs_cent_TS%i_ch%i",iTS,EMchan), 10, 1, 200, 300, 0, 20000);
            hZDCpEM_vs_cent_Nsub[iTS][EMchan] = new TH2F(Form("ZDCpEM_vs_cent_Nsub_TS%i_ch%i",iTS,EMchan),Form("ZDCpEM_vs_cent_Nsub_TS%i_ch%i",iTS,EMchan), 10, 1, 200, 300, 0, 20000);
            hZDCnEM_vs_cent_Nsub[iTS][EMchan] = new TH2F(Form("ZDCnEM_vs_cent_Nsub_TS%i_ch%i",iTS,EMchan),Form("ZDCnEM_vs_cent_Nsub_TS%i_ch%i",iTS,EMchan), 10, 1, 200, 300, 0, 20000);
            
            hZDCpEM_vs_noff[iTS][EMchan] = new TH2F(Form("ZDCpEM_vs_noff_TS%i_ch%i",iTS,EMchan),Form("ZDCpEM_vs_noff_TS%i_ch%i",iTS,EMchan), 50, 1, noff_range, 300, 0, 20000);
            hZDCnEM_vs_noff[iTS][EMchan] = new TH2F(Form("ZDCnEM_vs_noff_TS%i_ch%i",iTS,EMchan),Form("ZDCnEM_vs_noff_TS%i_ch%i",iTS,EMchan), 50, 1, noff_range, 300, 0, 20000);
            hZDCpEM_vs_noff_Nsub[iTS][EMchan] = new TH2F(Form("ZDCpEM_vs_noff_Nsub_TS%i_ch%i",iTS,EMchan),Form("ZDCpEM_vs_noff_Nsub_TS%i_ch%i",iTS,EMchan), 50, 1, noff_range, 300, 0, 20000);
            hZDCnEM_vs_noff_Nsub[iTS][EMchan] = new TH2F(Form("ZDCnEM_vs_noff_Nsub_TS%i_ch%i",iTS,EMchan),Form("ZDCnEM_vs_noff_Nsub_TS%i_ch%i",iTS,EMchan), 50, 1, noff_range, 300, 0, 20000);
        }
        for (int HADchan = 0; HADchan<numHADchan; HADchan++) {
            hZDCpHAD[iTS][HADchan] = new TH1F(Form("ZDCpHAD_TS%i_ch%i",iTS,HADchan),Form("ZDCpHAD_TS%i_ch%i",iTS,HADchan), 300, 0, 20000);
            hZDCnHAD[iTS][HADchan] = new TH1F(Form("ZDCnHAD_TS%i_ch%i",iTS,HADchan),Form("ZDCnHAD_TS%i_ch%i",iTS,HADchan), 300, 0, 20000);
            hZDCpHAD_Nsub[iTS][HADchan] = new TH1F(Form("ZDCpHAD_Nsub_TS%i_ch%i",iTS,HADchan),Form("ZDCpHAD_Nsub_TS%i_ch%i",iTS,HADchan), 300, 0, 20000);
            hZDCnHAD_Nsub[iTS][HADchan] = new TH1F(Form("ZDCnHAD__NsubTS%i_ch%i",iTS,HADchan),Form("ZDCnHAD_Nsub_TS%i_ch%i",iTS,HADchan), 300, 0, 20000);
            
            hZDCpHAD_vs_cent[iTS][HADchan] = new TH2F(Form("ZDCpHAD_vs_cent_TS%i_ch%i",iTS,HADchan),Form("ZDCpHAD_vs_cent_TS%i_ch%i",iTS,HADchan), 10, 1, 200, 300, 0, 20000);
            hZDCnHAD_vs_cent[iTS][HADchan] = new TH2F(Form("ZDCnHAD_vs_cent_TS%i_ch%i",iTS,HADchan),Form("ZDCnHAD_vs_cent_TS%i_ch%i",iTS,HADchan), 10, 1, 200, 300, 0, 20000);
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan] = new TH2F(Form("ZDCpHAD_vs_cent_Nsub_TS%i_ch%i",iTS,HADchan),Form("ZDCpHAD_vs_cent_Nsub_TS%i_ch%i",iTS,HADchan), 10, 1, 200, 300, 0, 20000);
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan] = new TH2F(Form("ZDCnHAD_vs_cent_Nsub_TS%i_ch%i",iTS,HADchan),Form("ZDCnHAD_vs_cent_Nsub_TS%i_ch%i",iTS,HADchan), 10, 1, 200, 300, 0, 20000);
            
            hZDCpHAD_vs_noff[iTS][HADchan] = new TH2F(Form("ZDCpHAD_vs_noff_TS%i_ch%i",iTS,HADchan),Form("ZDCpHAD_vs_noff_TS%i_ch%i",iTS,HADchan), 50, 1, noff_range, 300, 0, 20000);
            hZDCnHAD_vs_noff[iTS][HADchan] = new TH2F(Form("ZDCnHAD_vs_noff_TS%i_ch%i",iTS,HADchan),Form("ZDCnHAD_vs_noff_TS%i_ch%i",iTS,HADchan), 50, 1, noff_range, 300, 0, 20000);
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan] = new TH2F(Form("ZDCpHAD_vs_noff_Nsub_TS%i_ch%i",iTS,HADchan),Form("ZDCpHAD_vs_noff_Nsub_TS%i_ch%i",iTS,HADchan), 50, 1, noff_range, 300, 0, 20000);
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan] = new TH2F(Form("ZDCnHAD_vs_noff_Nsub_TS%i_ch%i",iTS,HADchan),Form("ZDCnHAD_vs_noff_Nsub_TS%i_ch%i",iTS,HADchan), 50, 1, noff_range, 300, 0, 20000);
        }
    }
    // plots for individual channels with all time slices
    for (int EMchan = 0; EMchan<numEMchan; EMchan++) {
        hZDCpEMchan_cent[EMchan] = new TH2F(Form("ZDCpEMchan%d_cent",EMchan+1),Form("ZDCpEMchan%d_cent",EMchan+1), 10, 1, 200, 300, 0 , 20000);
        hZDCnEMchan_cent[EMchan] = new TH2F(Form("ZDCnEMchan%d_cent",EMchan+1),Form("ZDCnEMchan%d_cent",EMchan+1), 10, 1, 200, 300, 0 , 20000);
        hZDCpEMchan_cent_Nsub[EMchan] = new TH2F(Form("ZDCpEMchan%d_cent_Nsub",EMchan+1),Form("ZDCpEMchan%d_cent_Nsub",EMchan+1), 10, 1, 200, 300, 0 , 20000);;
        hZDCnEMchan_cent_Nsub[EMchan] = new TH2F(Form("ZDCnEMchan%d_cent_Nsub",EMchan+1),Form("ZDCnEMchan%d_cent_Nsub",EMchan+1), 10, 1, 200, 300, 0 , 20000);;
        
        hZDCpEMchan_noff[EMchan] = new TH2F(Form("ZDCpEMchan%d_noff",EMchan+1),Form("ZDCpEMchan%d_noff",EMchan+1), 50, 1, noff_range, 300, 0 , 20000);
        hZDCnEMchan_noff[EMchan] = new TH2F(Form("ZDCnEMchan%d_noff",EMchan+1),Form("ZDCnEMchan%d_noff",EMchan+1), 50, 1, noff_range, 300, 0 , 20000);
        hZDCpEMchan_noff_Nsub[EMchan] = new TH2F(Form("ZDCpEMchan%d_noff_Nsub",EMchan+1),Form("ZDCpEMchan%d_noff_Nsub",EMchan+1), 50, 1, noff_range, 300, 0 , 20000);
        hZDCnEMchan_noff_Nsub[EMchan] = new TH2F(Form("ZDCnEMchan%d_noff_Nsub",EMchan+1),Form("ZDCnEMchan%d_noff_Nsub",EMchan+1), 50, 1, noff_range, 300, 0 , 20000);
    }
    for (int HADchan = 0; HADchan<numHADchan; HADchan++) {
        hZDCpHADchan_cent[HADchan] = new TH2F(Form("ZDCpHADchan%d_cent",HADchan+1),Form("ZDCpHADchan%d_cent",HADchan+1), 10, 1, 200, 300, 0, 20000);
        hZDCnHADchan_cent[HADchan] = new TH2F(Form("ZDCnHADchan%d_cent",HADchan+1),Form("ZDCnHADchan%d_cent",HADchan+1), 10, 1, 200, 300, 0, 20000);
        hZDCpHADchan_cent_Nsub[HADchan] = new TH2F(Form("ZDCpHADchan%d_cent_Nsub",HADchan+1),Form("ZDCpHADchan%d_cent_Nsub",HADchan+1), 10, 1, 200, 300, 0, 20000);
        hZDCnHADchan_cent_Nsub[HADchan] = new TH2F(Form("ZDCnHADchan%d_cent_Nsub",HADchan+1),Form("ZDCpHADchan%d_cent_Nsub",HADchan+1), 10, 1, 200, 300, 0, 20000);
        
        hZDCpHADchan_noff[HADchan] = new TH2F(Form("ZDCpHADchan%d_noff",HADchan+1),Form("ZDCpHADchan%d_noff",HADchan+1), 50, 1, noff_range, 300, 0, 20000);
        hZDCnHADchan_noff[HADchan] = new TH2F(Form("ZDCnHADchan%d_noff",HADchan+1),Form("ZDCnHADchan%d_noff",HADchan+1), 50, 1, noff_range, 300, 0, 20000);
        hZDCpHADchan_noff_Nsub[HADchan] = new TH2F(Form("ZDCpHADchan%d_noff_Nsub",HADchan+1),Form("ZDCpHADchan%d_noff_Nsub",HADchan+1), 50, 1, noff_range, 300, 0, 20000);
        hZDCnHADchan_noff_Nsub[HADchan] = new TH2F(Form("ZDCnHADchan%d_noff_Nsub",HADchan+1),Form("ZDCnHADchan%d_noff_Nsub",HADchan+1), 50, 1, noff_range, 300, 0, 20000);
    }
    
    // plots for sums of channels ("_Nsub" for noise subtracted)
    hZDCpEMsum = new TH1F("ZDCpEMsum","ZDCpEMsum", 300, 0, 20000);
    hZDCpHADsum = new TH1F("ZDCpHADsum","ZDCpHADsum", 300, 0, 20000);
    hZDCnEMsum = new TH1F("ZDCnEMsum","ZDCnEMsum", 300, 0, 20000);
    hZDCnHADsum = new TH1F("ZDCnHADsum","ZDCnHADsum", 300, 0, 20000);
    hZDCptotsum_vs_cent = new TH2F("ZDCptotsum_cent","ZDCptotsum_cent", 10, 1, 200, 300, 0, 20000);
    hZDCntotsum_vs_cent = new TH2F("ZDCntotsum_cent","ZDCntotsum_cent", 10, 1, 200, 300, 0, 20000);
    hZDCptotsum_vs_noff = new TH2F("ZDCptotsum_noff","ZDCptotsum_noff", 400, 0, noff_range, 300, 0, 20000);
    hZDCntotsum_vs_noff = new TH2F("ZDCntotsum_noff","ZDCntotsum_noff", 400, 0, noff_range, 300, 0, 20000);
    
    hZDCpEMsum_Nsub = new TH1F("ZDCpEMsum_Nsub","ZDCpEMsum_Nsub", 300, 0, 20000);
    hZDCpHADsum_Nsub = new TH1F("ZDCpHADsum_Nsub","ZDCpHADsum_Nsub", 300, 0, 20000);
    hZDCnEMsum_Nsub = new TH1F("ZDCnEMsum_Nsub","ZDCnEMsum_Nsub", 300, 0, 20000);
    hZDCnHADsum_Nsub = new TH1F("ZDCnHADsum_Nsub","ZDCnHADsum_Nsub", 300, 0, 20000);
    hZDCtotsum_Nsub_vs_cent = new TH2F("hZDCtotsum_Nsub_cent","hZDCtotsum_Nsub_cent", 10, 1, 200, 300, 0, 20000);
    hZDCtotsum_Nsub_vs_noff = new TH2F("hZDCtotsum_Nsub_noff","hZDCtotsum_Nsub_noff", 400, 0, noff_range, 300, 0, 20000);
    
    hZDCpEM_vs_HAD = new TH2F("ZDCpEM_vs_HAD","ZDCpEM_vs_HAD", 1000, 1, 20000, 1000, 1, 20000);
    hZDCnEM_vs_HAD = new TH2F("ZDCnEM_vs_HAD","ZDCnEM_vs_HAD", 1000, 1, 20000, 1000, 1, 20000);
    hZDCpEM_vs_HAD_Nsub = new TH2F("ZDCpEM_vs_HAD_Nsub","ZDCpEM_vs_HAD_Nsub", 1000, 1, 20000, 1000, 1, 20000);
    hZDCnEM_vs_HAD_Nsub = new TH2F("ZDCnEM_vs_HAD_Nsub","ZDCnEM_vs_HAD_Nsub", 1000, 1, 20000, 1000, 1, 20000);
    
    hZDCpEM_vs_tot = new TH2F("ZDCpEM_vs_tot","ZDCpEM_vs_tot", 1000, 1, 20000, 1000, 1, 20000);
    hZDCnEM_vs_tot = new TH2F("ZDCnEM_vs_tot","ZDCnEM_vs_tot", 1000, 1, 20000, 1000, 1, 20000);
    hZDCpEM_vs_tot_Nsub = new TH2F("ZDCpEM_vs_tot_Nsub","ZDCpEM_vs_tot_Nsub", 1000, 1, 20000, 1000, 1, 20000);
    hZDCnEM_vs_tot_Nsub = new TH2F("ZDCnEM_vs_tot_Nsub","ZDCnEM_vs_tot_Nsub", 1000, 1, 20000, 1000, 1, 20000);
    
    hZDCpSum_vs_cent = new TH2F("ZDCpSum_vs_cent","ZDCpSum_vs_cent", 10, 1, 200, 400, 1, 10000);
    hZDCnSum_vs_cent = new TH2F("ZDCnSum_vs_cent","ZDCnSum_vs_cent", 10, 1, 200, 400, 1, 10000);
    hZDCpSum_vs_cent_Nsub = new TH2F("ZDCpSum_vs_cent_Nsub","ZZDCpSum_vs_cent_Nsub", 10, 1, 200, 400, 1, 10000);
    hZDCnSum_vs_cent_Nsub = new TH2F("ZDCnSum_vs_cent_Nsub","ZZDCnSum_vs_cent_Nsub", 10, 1, 200, 400, 1, 10000);
    
    hZDCpSum_vs_noff = new TH2F("ZDCpSum_vs_noff","ZDCpSum_vs_noff", 50, 1, noff_range, 300, 0, 10000);
    hZDCnSum_vs_noff = new TH2F("ZDCnSum_vs_noff","ZDCnSum_vs_noff", 50, 1, noff_range, 300, 0, 10000);
    hZDCpSum_vs_noff_Nsub = new TH2F("ZDCpSum_vs_noff_Nsub","ZDCpSum_vs_noff_Nsub", 50, 1, noff_range, 300, 0, 10000);
    hZDCnSum_vs_noff_Nsub = new TH2F("ZDCnSum_vs_noff_Nsub","ZDCnSum_vs_noff_Nsub", 50, 1, noff_range, 300, 0, 10000);
    
    hZDCpSum_vs_TS = new TH1F("ZDCpSum_vs_TS","ZDCpSum_vs_TS", 10, 0, 9);
    hZDCnSum_vs_TS = new TH1F("ZDCnSum_vs_TS","ZDCnSum_vs_TS", 10, 0, 9);
    hZDCpSum_vs_TS_Nsub = new TH1F("ZDCpSum_vs_TS_Nsub","ZDCpSum_vs_TS_Nsub", 10, 0, 9);
    hZDCnSum_vs_TS_Nsub = new TH1F("ZDCnSum_vs_TS_Nsub","ZDCnSum_vs_TS_Nsub", 10, 0, 9);
    
    for (int chan = 0; chan<numchan; chan++) {
        hZDCpSumTotal[chan] = new TH1F(Form("ZDCpSumTotal_ch%i",chan),Form("ZDCpSumTotal_ch%i",chan), 10, 0, 9);
        hZDCnSumTotal[chan] = new TH1F(Form("ZDCnSumTotal_ch%i",chan),Form("ZDCnSumTotal_ch%i",chan), 10, 0, 9);
    }
}


void plot_style() {
    
    hZDCpEMsum->SetTitle("");
    hZDCpEMsum->SetStats(kFALSE);
    hZDCpEMsum->SetXTitle("ZDC+ EM signal (fC)");
    hZDCpEMsum->GetXaxis()->CenterTitle(kTRUE);
    hZDCpEMsum->SetYTitle("Counts");
    hZDCpEMsum->GetYaxis()->SetTitleOffset(1.75);
    hZDCpEMsum->GetYaxis()->SetTitleSize(0.05);
    hZDCpEMsum->GetYaxis()->SetLabelSize(0.04);
    hZDCpEMsum->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCpHADsum->SetTitle("");
    hZDCpHADsum->SetStats(kFALSE);
    hZDCpHADsum->SetXTitle("ZDC+ HAD signal (fC)");
    hZDCpHADsum->GetXaxis()->CenterTitle(kTRUE);
    hZDCpHADsum->SetYTitle("Counts");
    hZDCpHADsum->GetYaxis()->SetTitleOffset(1.75);
    hZDCpHADsum->GetYaxis()->SetTitleSize(0.05);
    hZDCpHADsum->GetYaxis()->SetLabelSize(0.04);
    hZDCpHADsum->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCnEMsum->SetTitle("");
    hZDCnEMsum->SetStats(kFALSE);
    hZDCnEMsum->SetXTitle("ZDC- EM signal (fC)");
    hZDCnEMsum->GetXaxis()->CenterTitle(kTRUE);
    hZDCnEMsum->SetYTitle("Counts");
    hZDCnEMsum->GetYaxis()->SetTitleOffset(1.75);
    hZDCnEMsum->GetYaxis()->SetTitleSize(0.05);
    hZDCnEMsum->GetYaxis()->SetLabelSize(0.04);
    hZDCnEMsum->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCnHADsum->SetTitle("");
    hZDCnHADsum->SetStats(kFALSE);
    hZDCnHADsum->SetXTitle("ZDC- HAD signal (fC)");
    hZDCnHADsum->GetXaxis()->CenterTitle(kTRUE);
    hZDCnHADsum->SetYTitle("Counts");
    hZDCnHADsum->GetYaxis()->SetTitleOffset(1.75);
    hZDCnHADsum->GetYaxis()->SetTitleSize(0.05);
    hZDCnHADsum->GetYaxis()->SetLabelSize(0.04);
    hZDCnHADsum->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCptotsum_vs_cent->SetTitle("");
    hZDCptotsum_vs_cent->SetStats(kFALSE);
    hZDCptotsum_vs_cent->SetXTitle("Centrality (0.5% per bin)");
    hZDCptotsum_vs_cent->GetXaxis()->CenterTitle(kTRUE);
    hZDCptotsum_vs_cent->SetYTitle("ZDC signal (fC)");
    hZDCptotsum_vs_cent->GetYaxis()->CenterTitle(kTRUE);
    hZDCptotsum_vs_cent->GetYaxis()->SetTitleOffset(1.75);
    hZDCptotsum_vs_cent->GetYaxis()->SetTitleSize(0.05);
    hZDCptotsum_vs_cent->GetYaxis()->SetLabelSize(0.04);
    hZDCptotsum_vs_cent->GetYaxis()->SetRangeUser(1,20000);
    hZDCptotsum_vs_cent->SetOption("colz");
    
    hZDCptotsum_vs_noff->SetTitle("");
    hZDCptotsum_vs_noff->SetStats(kFALSE);
    hZDCptotsum_vs_noff->SetXTitle("N_{pixel tracks}");
    hZDCptotsum_vs_noff->GetXaxis()->CenterTitle(kTRUE);
    hZDCptotsum_vs_noff->SetYTitle("ZDC signal (fC)");
    hZDCptotsum_vs_noff->GetYaxis()->CenterTitle(kTRUE);
    hZDCptotsum_vs_noff->GetYaxis()->SetTitleOffset(1.75);
    hZDCptotsum_vs_noff->GetYaxis()->SetTitleSize(0.05);
    hZDCptotsum_vs_noff->GetYaxis()->SetLabelSize(0.04);
    hZDCptotsum_vs_noff->GetYaxis()->SetRangeUser(1,20000);
    hZDCptotsum_vs_noff->SetOption("colz");
    
    hZDCntotsum_vs_cent->SetTitle("");
    hZDCntotsum_vs_cent->SetStats(kFALSE);
    hZDCntotsum_vs_cent->SetXTitle("Centrality (0.5% per bin)");
    hZDCntotsum_vs_cent->GetXaxis()->CenterTitle(kTRUE);
    hZDCntotsum_vs_cent->SetYTitle("ZDC signal (fC)");
    hZDCntotsum_vs_cent->GetYaxis()->CenterTitle(kTRUE);
    hZDCntotsum_vs_cent->GetYaxis()->SetTitleOffset(1.75);
    hZDCntotsum_vs_cent->GetYaxis()->SetTitleSize(0.05);
    hZDCntotsum_vs_cent->GetYaxis()->SetLabelSize(0.04);
    hZDCntotsum_vs_cent->GetYaxis()->SetRangeUser(1,20000);
    hZDCntotsum_vs_cent->SetOption("colz");
    
    hZDCntotsum_vs_noff->SetTitle("");
    hZDCntotsum_vs_noff->SetStats(kFALSE);
    hZDCntotsum_vs_noff->SetXTitle("N_{pixel tracks}");
    hZDCntotsum_vs_noff->GetXaxis()->CenterTitle(kTRUE);
    hZDCntotsum_vs_noff->SetYTitle("ZDC signal (fC)");
    hZDCntotsum_vs_noff->GetYaxis()->CenterTitle(kTRUE);
    hZDCntotsum_vs_noff->GetYaxis()->SetTitleOffset(1.75);
    hZDCntotsum_vs_noff->GetYaxis()->SetTitleSize(0.05);
    hZDCntotsum_vs_noff->GetYaxis()->SetLabelSize(0.04);
    hZDCntotsum_vs_noff->GetYaxis()->SetRangeUser(1,20000);
    hZDCntotsum_vs_noff->SetOption("colz");
    
    
    
    hZDCpEMsum_Nsub->SetTitle("");
    hZDCpEMsum_Nsub->SetStats(kFALSE);
    hZDCpEMsum_Nsub->SetXTitle("Noise subtracted ZDC+ EM signal (fC)");
    hZDCpEMsum_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCpEMsum_Nsub->SetYTitle("Counts");
    hZDCpEMsum_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCpEMsum_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCpEMsum_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCpEMsum_Nsub->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCpHADsum_Nsub->SetTitle("");
    hZDCpHADsum_Nsub->SetStats(kFALSE);
    hZDCpHADsum_Nsub->SetXTitle("Noise subtracted ZDC+ HAD signal (fC)");
    hZDCpHADsum_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCpHADsum_Nsub->SetYTitle("Counts");
    hZDCpHADsum_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCpHADsum_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCpHADsum_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCpHADsum_Nsub->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCnEMsum_Nsub->SetTitle("");
    hZDCnEMsum_Nsub->SetStats(kFALSE);
    hZDCnEMsum_Nsub->SetXTitle("Noise subtracted ZDC- EM signal (fC)");
    hZDCnEMsum_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCnEMsum_Nsub->SetYTitle("Counts");
    hZDCnEMsum_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCnEMsum_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCnEMsum_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCnEMsum_Nsub->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCnHADsum_Nsub->SetTitle("");
    hZDCnHADsum_Nsub->SetStats(kFALSE);
    hZDCnHADsum_Nsub->SetXTitle("Noise subtracted ZDC- HAD signal (fC)");
    hZDCnHADsum_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCnHADsum_Nsub->SetYTitle("Counts");
    hZDCnHADsum_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCnHADsum_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCnHADsum_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCnHADsum_Nsub->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCtotsum_Nsub_vs_cent->SetTitle("");
    hZDCtotsum_Nsub_vs_cent->SetStats(kFALSE);
    hZDCtotsum_Nsub_vs_cent->SetXTitle("Centrality (0.5% per bin)");
    hZDCtotsum_Nsub_vs_cent->GetXaxis()->CenterTitle(kTRUE);
    hZDCtotsum_Nsub_vs_cent->SetYTitle("Noise subtracted ZDC signal (fC)");
    hZDCtotsum_Nsub_vs_cent->GetYaxis()->CenterTitle(kTRUE);
    hZDCtotsum_Nsub_vs_cent->GetYaxis()->SetTitleOffset(1.75);
    hZDCtotsum_Nsub_vs_cent->GetYaxis()->SetTitleSize(0.05);
    hZDCtotsum_Nsub_vs_cent->GetYaxis()->SetLabelSize(0.04);
    hZDCtotsum_Nsub_vs_cent->GetYaxis()->SetRangeUser(1,6000);
    hZDCtotsum_Nsub_vs_cent->SetOption("colz");
    
    hZDCtotsum_Nsub_vs_noff->SetTitle("");
    hZDCtotsum_Nsub_vs_noff->SetStats(kFALSE);
    hZDCtotsum_Nsub_vs_noff->SetXTitle("N_{pixel tracks}");
    hZDCtotsum_Nsub_vs_noff->GetXaxis()->CenterTitle(kTRUE);
    hZDCtotsum_Nsub_vs_noff->SetYTitle("Noise subtracted ZDC signal (fC)");
    hZDCtotsum_Nsub_vs_noff->GetYaxis()->CenterTitle(kTRUE);
    hZDCtotsum_Nsub_vs_noff->GetYaxis()->SetTitleOffset(1.75);
    hZDCtotsum_Nsub_vs_noff->GetYaxis()->SetTitleSize(0.05);
    hZDCtotsum_Nsub_vs_noff->GetYaxis()->SetLabelSize(0.04);
    hZDCtotsum_Nsub_vs_noff->GetYaxis()->SetRangeUser(1,6000);
    hZDCtotsum_Nsub_vs_noff->SetOption("colz");
    
    
    
    hZDCpEM_vs_HAD->SetTitle("");
    hZDCpEM_vs_HAD->SetStats(kFALSE);
    hZDCpEM_vs_HAD->SetXTitle("ZDC+ HAD signal (fC)");
    hZDCpEM_vs_HAD->GetXaxis()->CenterTitle(kTRUE);
    hZDCpEM_vs_HAD->GetYaxis()->CenterTitle(kTRUE);
    hZDCpEM_vs_HAD->SetYTitle("ZDC+ EM signal (fC)");
    hZDCpEM_vs_HAD->GetYaxis()->SetTitleOffset(1.75);
    hZDCpEM_vs_HAD->GetYaxis()->SetTitleSize(0.05);
    hZDCpEM_vs_HAD->GetYaxis()->SetLabelSize(0.04);
    hZDCpEM_vs_HAD->SetOption("colz");
    
    hZDCnEM_vs_HAD->SetTitle("");
    hZDCnEM_vs_HAD->SetStats(kFALSE);
    hZDCnEM_vs_HAD->SetXTitle("ZDC- HAD signal (fC)");
    hZDCnEM_vs_HAD->GetXaxis()->CenterTitle(kTRUE);
    hZDCnEM_vs_HAD->GetYaxis()->CenterTitle(kTRUE);
    hZDCnEM_vs_HAD->SetYTitle("ZDC- EM signal (fC)");
    hZDCnEM_vs_HAD->GetYaxis()->SetTitleOffset(1.75);
    hZDCnEM_vs_HAD->GetYaxis()->SetTitleSize(0.05);
    hZDCnEM_vs_HAD->GetYaxis()->SetLabelSize(0.04);
    hZDCnEM_vs_HAD->SetOption("colz");
    
    hZDCpEM_vs_HAD_Nsub->SetTitle("");
    hZDCpEM_vs_HAD_Nsub->SetStats(kFALSE);
    hZDCpEM_vs_HAD_Nsub->SetXTitle("Noise subtracted ZDC+ HAD signal (fC)");
    hZDCpEM_vs_HAD_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCpEM_vs_HAD_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCpEM_vs_HAD_Nsub->SetYTitle("Noise subtracted ZDC+ EM signal (fC)");
    hZDCpEM_vs_HAD_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCpEM_vs_HAD_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCpEM_vs_HAD_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCpEM_vs_HAD_Nsub->SetOption("colz");
    
    hZDCnEM_vs_HAD_Nsub->SetTitle("");
    hZDCnEM_vs_HAD_Nsub->SetStats(kFALSE);
    hZDCnEM_vs_HAD_Nsub->SetXTitle("Noise subtracted ZDC+ HAD signal (fC)");
    hZDCnEM_vs_HAD_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCnEM_vs_HAD_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCnEM_vs_HAD_Nsub->SetYTitle("Noise subtracted ZDC+ EM signal (fC)");
    hZDCnEM_vs_HAD_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCnEM_vs_HAD_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCnEM_vs_HAD_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCnEM_vs_HAD_Nsub->SetOption("colz");
    
    
    
    hZDCpEM_vs_tot->SetTitle("");
    hZDCpEM_vs_tot->SetStats(kFALSE);
    hZDCpEM_vs_tot->SetXTitle("ZDC+ SumHAD + 0.1SumEM (fC)");
    hZDCpEM_vs_tot->GetXaxis()->CenterTitle(kTRUE);
    hZDCpEM_vs_tot->GetYaxis()->CenterTitle(kTRUE);
    hZDCpEM_vs_tot->SetYTitle("ZDC+ EM signal (fC)");
    hZDCpEM_vs_tot->GetYaxis()->SetTitleOffset(1.75);
    hZDCpEM_vs_tot->GetYaxis()->SetTitleSize(0.05);
    hZDCpEM_vs_tot->GetYaxis()->SetLabelSize(0.04);
    hZDCpEM_vs_tot->SetOption("colz");
    
    hZDCnEM_vs_tot->SetTitle("");
    hZDCnEM_vs_tot->SetStats(kFALSE);
    hZDCnEM_vs_tot->SetXTitle("ZDC- SumHAD + 0.1SumEM (fC)");
    hZDCnEM_vs_tot->GetXaxis()->CenterTitle(kTRUE);
    hZDCnEM_vs_tot->GetYaxis()->CenterTitle(kTRUE);
    hZDCnEM_vs_tot->SetYTitle("ZDC- EM signal (fC)");
    hZDCnEM_vs_tot->GetYaxis()->SetTitleOffset(1.75);
    hZDCnEM_vs_tot->GetYaxis()->SetTitleSize(0.05);
    hZDCnEM_vs_tot->GetYaxis()->SetLabelSize(0.04);
    hZDCnEM_vs_tot->SetOption("colz");
    
    hZDCpEM_vs_tot_Nsub->SetTitle("");
    hZDCpEM_vs_tot_Nsub->SetStats(kFALSE);
    hZDCpEM_vs_tot_Nsub->SetXTitle("Noise subtracted SumHAD + 0.1SumEM (fC)");
    hZDCpEM_vs_tot_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCpEM_vs_tot_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCpEM_vs_tot_Nsub->SetYTitle("Noise subtracted ZDC+ EM signal (fC)");
    hZDCpEM_vs_tot_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCpEM_vs_tot_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCpEM_vs_tot_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCpEM_vs_tot_Nsub->SetOption("colz");
    
    hZDCnEM_vs_tot_Nsub->SetTitle("");
    hZDCnEM_vs_tot_Nsub->SetStats(kFALSE);
    hZDCnEM_vs_tot_Nsub->SetXTitle("Noise subtracted SumHAD + 0.1SumEM (fC)");
    hZDCnEM_vs_tot_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCnEM_vs_tot_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCnEM_vs_tot_Nsub->SetYTitle("Noise subtracted ZDC+ EM signal (fC)");
    hZDCnEM_vs_tot_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCnEM_vs_tot_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCnEM_vs_tot_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCnEM_vs_tot_Nsub->SetOption("colz");
    
    
    
    hZDCpSum_vs_cent->SetTitle("");
    hZDCpSum_vs_cent->SetStats(kFALSE);
    hZDCpSum_vs_cent->SetXTitle("Cent bin (0.5% per bin)");
    hZDCpSum_vs_cent->GetXaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_cent->GetYaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_cent->SetYTitle("ZDC+ signal (fC)");
    hZDCpSum_vs_cent->GetYaxis()->SetTitleOffset(1.75);
    hZDCpSum_vs_cent->GetYaxis()->SetTitleSize(0.05);
    hZDCpSum_vs_cent->GetYaxis()->SetLabelSize(0.04);
    hZDCpSum_vs_cent->GetYaxis()->SetRangeUser(1,6000);
    hZDCpSum_vs_cent->SetOption("colz");
    
    hZDCnSum_vs_cent->SetTitle("");
    hZDCnSum_vs_cent->SetStats(kFALSE);
    hZDCnSum_vs_cent->SetXTitle("Cent bin (0.5% per bin)");
    hZDCnSum_vs_cent->GetXaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_cent->GetYaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_cent->SetYTitle("ZDC- signal (fC)");
    hZDCnSum_vs_cent->GetYaxis()->SetTitleOffset(1.75);
    hZDCnSum_vs_cent->GetYaxis()->SetTitleSize(0.05);
    hZDCnSum_vs_cent->GetYaxis()->SetLabelSize(0.04);
    hZDCnSum_vs_cent->GetYaxis()->SetRangeUser(1,6000);
    hZDCnSum_vs_cent->SetOption("colz");
    
    hZDCpSum_vs_cent_Nsub->SetTitle("");
    hZDCpSum_vs_cent_Nsub->SetStats(kFALSE);
    hZDCpSum_vs_cent_Nsub->SetXTitle("Cent bin (0.5% per bin)");
    hZDCpSum_vs_cent_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_cent_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_cent_Nsub->SetYTitle("Noise subtracted ZDC+ signal (fC)");
    hZDCpSum_vs_cent_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCpSum_vs_cent_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCpSum_vs_cent_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCpSum_vs_cent_Nsub->GetYaxis()->SetRangeUser(1,6000);
    hZDCpSum_vs_cent_Nsub->SetOption("colz");
    
    hZDCnSum_vs_cent_Nsub->SetTitle("");
    hZDCnSum_vs_cent_Nsub->SetStats(kFALSE);
    hZDCnSum_vs_cent_Nsub->SetXTitle("Cent bin (0.5% per bin)");
    hZDCnSum_vs_cent_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_cent_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_cent_Nsub->SetYTitle("Noise subtracted ZDC- signal (fC)");
    hZDCnSum_vs_cent_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCnSum_vs_cent_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCnSum_vs_cent_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCnSum_vs_cent_Nsub->GetYaxis()->SetRangeUser(1,6000);
    hZDCnSum_vs_cent_Nsub->SetOption("colz");
    
    
    
    hZDCpSum_vs_noff->SetTitle("");
    hZDCpSum_vs_noff->SetStats(kFALSE);
    hZDCpSum_vs_noff->SetXTitle("N_{pixel tracks}");
    hZDCpSum_vs_noff->GetXaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_noff->GetYaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_noff->SetYTitle("ZDC+ signal (fC)");
    hZDCpSum_vs_noff->GetYaxis()->SetTitleOffset(1.75);
    hZDCpSum_vs_noff->GetYaxis()->SetTitleSize(0.05);
    hZDCpSum_vs_noff->GetYaxis()->SetLabelSize(0.04);
    hZDCpSum_vs_noff->GetYaxis()->SetRangeUser(1,6000);
    hZDCpSum_vs_noff->SetOption("colz");
    
    hZDCnSum_vs_noff->SetTitle("");
    hZDCnSum_vs_noff->SetStats(kFALSE);
    hZDCnSum_vs_noff->SetXTitle("N_{pixel tracks}");
    hZDCnSum_vs_noff->GetXaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_noff->GetYaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_noff->SetYTitle("ZDC- signal (fC)");
    hZDCnSum_vs_noff->GetYaxis()->SetTitleOffset(1.75);
    hZDCnSum_vs_noff->GetYaxis()->SetTitleSize(0.05);
    hZDCnSum_vs_noff->GetYaxis()->SetLabelSize(0.04);
    hZDCnSum_vs_noff->GetYaxis()->SetRangeUser(1,6000);
    hZDCnSum_vs_noff->SetOption("colz");
    
    hZDCpSum_vs_noff_Nsub->SetTitle("");
    hZDCpSum_vs_noff_Nsub->SetStats(kFALSE);
    hZDCpSum_vs_noff_Nsub->SetXTitle("N_{pixel tracks}");
    hZDCpSum_vs_noff_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_noff_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_noff_Nsub->SetYTitle("Noise subtracted ZDC+ signal (fC)");
    hZDCpSum_vs_noff_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCpSum_vs_noff_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCpSum_vs_noff_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCpSum_vs_noff_Nsub->GetYaxis()->SetRangeUser(1,6000);
    hZDCpSum_vs_noff_Nsub->SetOption("colz");
    
    hZDCnSum_vs_noff_Nsub->SetTitle("");
    hZDCnSum_vs_noff_Nsub->SetStats(kFALSE);
    hZDCnSum_vs_noff_Nsub->SetXTitle("N_{pixel tracks}");
    hZDCnSum_vs_noff_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_noff_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_noff_Nsub->SetYTitle("Noise subtracted ZDC- signal (fC)");
    hZDCnSum_vs_noff_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCnSum_vs_noff_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCnSum_vs_noff_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCnSum_vs_noff_Nsub->GetYaxis()->SetRangeUser(1,6000);
    hZDCnSum_vs_noff_Nsub->SetOption("colz");
    
    
    
    hZDCpSum_vs_TS->SetTitle("");
    hZDCpSum_vs_TS->SetStats(kFALSE);
    hZDCpSum_vs_TS->SetXTitle("Time slice");
    hZDCpSum_vs_TS->GetXaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_TS->GetYaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_TS->SetYTitle("ZDC+ signal (fC)");
    hZDCpSum_vs_TS->GetYaxis()->SetTitleOffset(1.75);
    hZDCpSum_vs_TS->GetYaxis()->SetTitleSize(0.05);
    hZDCpSum_vs_TS->GetYaxis()->SetLabelSize(0.04);
    hZDCpSum_vs_TS->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCnSum_vs_TS->SetTitle("");
    hZDCnSum_vs_TS->SetStats(kFALSE);
    hZDCnSum_vs_TS->SetXTitle("Time slice");
    hZDCnSum_vs_TS->GetXaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_TS->GetYaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_TS->SetYTitle("ZDC- signal (fC)");
    hZDCnSum_vs_TS->GetYaxis()->SetTitleOffset(1.75);
    hZDCnSum_vs_TS->GetYaxis()->SetTitleSize(0.05);
    hZDCnSum_vs_TS->GetYaxis()->SetLabelSize(0.04);
    hZDCnSum_vs_TS->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCpSum_vs_TS_Nsub->SetTitle("");
    hZDCpSum_vs_TS_Nsub->SetStats(kFALSE);
    hZDCpSum_vs_TS_Nsub->SetXTitle("Time slice");
    hZDCpSum_vs_TS_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_TS_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCpSum_vs_TS_Nsub->SetYTitle("Noise subtracted ZDC+ signal (fC)");
    hZDCpSum_vs_TS_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCpSum_vs_TS_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCpSum_vs_TS_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCpSum_vs_TS_Nsub->GetYaxis()->SetRangeUser(1,6000);
    
    hZDCnSum_vs_TS_Nsub->SetTitle("");
    hZDCnSum_vs_TS_Nsub->SetStats(kFALSE);
    hZDCnSum_vs_TS_Nsub->SetXTitle("Time slice");
    hZDCnSum_vs_TS_Nsub->GetXaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_TS_Nsub->GetYaxis()->CenterTitle(kTRUE);
    hZDCnSum_vs_TS_Nsub->SetYTitle("Noise subtracted ZDC+ signal (fC)");
    hZDCnSum_vs_TS_Nsub->GetYaxis()->SetTitleOffset(1.75);
    hZDCnSum_vs_TS_Nsub->GetYaxis()->SetTitleSize(0.05);
    hZDCnSum_vs_TS_Nsub->GetYaxis()->SetLabelSize(0.04);
    hZDCnSum_vs_TS_Nsub->GetYaxis()->SetRangeUser(1,6000);
    
    
    
    for (int iTS = 0; iTS<nTS; iTS++) {
        for (int EMchan = 0; EMchan<numEMchan; EMchan++) {
            hZDCpEM[iTS][EMchan]->SetTitle("");
            hZDCpEM[iTS][EMchan]->SetStats(kFALSE);
            hZDCpEM[iTS][EMchan]->SetXTitle(Form("ZDCp EM%d TS%d (fC)",EMchan+1,iTS));
            hZDCpEM[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpEM[iTS][EMchan]->SetYTitle("Counts");
            hZDCpEM[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpEM[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpEM[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpEM[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            
            hZDCnEM[iTS][EMchan]->SetTitle("");
            hZDCnEM[iTS][EMchan]->SetStats(kFALSE);
            hZDCnEM[iTS][EMchan]->SetXTitle(Form("ZDCn EM%d TS%d (fC)",EMchan+1,iTS));
            hZDCnEM[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnEM[iTS][EMchan]->SetYTitle("Counts");
            hZDCnEM[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnEM[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnEM[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnEM[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            
            
            hZDCpEM_vs_cent[iTS][EMchan]->SetTitle("");
            hZDCpEM_vs_cent[iTS][EMchan]->SetStats(kFALSE);
            hZDCpEM_vs_cent[iTS][EMchan]->SetXTitle("Centrality (0.5% per bin)");
            hZDCpEM_vs_cent[iTS][EMchan]->SetYTitle(Form("ZDCp EM%d TS%d (fC)",EMchan+1,iTS));
            hZDCpEM_vs_cent[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpEM_vs_cent[iTS][EMchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCpEM_vs_cent[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpEM_vs_cent[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpEM_vs_cent[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpEM_vs_cent[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCpEM_vs_cent[iTS][EMchan]->SetOption("colz");
            
            hZDCnEM_vs_cent[iTS][EMchan]->SetTitle("");
            hZDCnEM_vs_cent[iTS][EMchan]->SetStats(kFALSE);
            hZDCnEM_vs_cent[iTS][EMchan]->SetXTitle("Centrality (0.5% per bin)");
            hZDCnEM_vs_cent[iTS][EMchan]->SetYTitle(Form("ZDCn EM%d TS%d (fC)",EMchan+1,iTS));
            hZDCnEM_vs_cent[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnEM_vs_cent[iTS][EMchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCnEM_vs_cent[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnEM_vs_cent[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnEM_vs_cent[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnEM_vs_cent[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCnEM_vs_cent[iTS][EMchan]->SetOption("colz");
            
            
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->SetTitle("");
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->SetStats(kFALSE);
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->SetXTitle("Centrality (0.5% per bin)");
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->SetYTitle(Form("ZDCp EM%d TS%d noise subbed (fC)",EMchan+1,iTS));
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCpEM_vs_cent_Nsub[iTS][EMchan]->SetOption("colz");
            
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->SetTitle("");
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->SetStats(kFALSE);
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->SetXTitle("Centrality (0.5% per bin)");
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->SetYTitle(Form("ZDCn EM%d TS%d noise subbed (fC)",EMchan+1,iTS));
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCnEM_vs_cent_Nsub[iTS][EMchan]->SetOption("colz");
            
            
            hZDCpEM_vs_noff[iTS][EMchan]->SetTitle("");
            hZDCpEM_vs_noff[iTS][EMchan]->SetStats(kFALSE);
            hZDCpEM_vs_noff[iTS][EMchan]->SetXTitle("N_{pixel tracks}");
            hZDCpEM_vs_noff[iTS][EMchan]->SetYTitle(Form("ZDCp EM%d TS%d (fC)",EMchan+1,iTS));
            hZDCpEM_vs_noff[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpEM_vs_noff[iTS][EMchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCpEM_vs_noff[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpEM_vs_noff[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpEM_vs_noff[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpEM_vs_noff[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCpEM_vs_noff[iTS][EMchan]->SetOption("colz");
            
            hZDCnEM_vs_noff[iTS][EMchan]->SetTitle("");
            hZDCnEM_vs_noff[iTS][EMchan]->SetStats(kFALSE);
            hZDCnEM_vs_noff[iTS][EMchan]->SetXTitle("N_{pixel tracks}");
            hZDCnEM_vs_noff[iTS][EMchan]->SetYTitle(Form("ZDCn EM%d TS%d (fC)",EMchan+1,iTS));
            hZDCnEM_vs_noff[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnEM_vs_noff[iTS][EMchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCnEM_vs_noff[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnEM_vs_noff[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnEM_vs_noff[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnEM_vs_noff[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCnEM_vs_noff[iTS][EMchan]->SetOption("colz");
            
            
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->SetTitle("");
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->SetStats(kFALSE);
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->SetXTitle("N_{pixel tracks}");
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->SetYTitle(Form("ZDCp EM%d TS%d noise subbed (fC)",EMchan+1,iTS));
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCpEM_vs_noff_Nsub[iTS][EMchan]->SetOption("colz");
            
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->SetTitle("");
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->SetStats(kFALSE);
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->SetXTitle("N_{pixel tracks}");
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->SetYTitle(Form("ZDCn EM%d TS%d noise subbed (fC)",EMchan+1,iTS));
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCnEM_vs_noff_Nsub[iTS][EMchan]->SetOption("colz");
        }
        for (int HADchan = 1; HADchan<numHADchan; HADchan++) {
            hZDCpHAD[iTS][HADchan]->SetTitle("");
            hZDCpHAD[iTS][HADchan]->SetStats(kFALSE);
            hZDCpHAD[iTS][HADchan]->SetXTitle(Form("ZDCp HAD%d TS%d (fC)",HADchan+1,iTS));
            hZDCpHAD[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpHAD[iTS][HADchan]->SetYTitle("Counts");
            hZDCpHAD[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpHAD[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpHAD[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpHAD[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            
            hZDCnHAD[iTS][HADchan]->SetTitle("");
            hZDCnHAD[iTS][HADchan]->SetStats(kFALSE);
            hZDCnHAD[iTS][HADchan]->SetXTitle(Form("ZDCn HAD%d TS%d (fC)",HADchan+1,iTS));
            hZDCnHAD[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnHAD[iTS][HADchan]->SetYTitle("Counts");
            hZDCnHAD[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnHAD[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnHAD[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnHAD[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            
            
            hZDCpHAD_vs_cent[iTS][HADchan]->SetTitle("");
            hZDCpHAD_vs_cent[iTS][HADchan]->SetStats(kFALSE);
            hZDCpHAD_vs_cent[iTS][HADchan]->SetXTitle("Centrality (0.5% per bin)");
            hZDCpHAD_vs_cent[iTS][HADchan]->SetYTitle(Form("ZDCp HAD%d TS%d (fC)",HADchan+1,iTS));
            hZDCpHAD_vs_cent[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpHAD_vs_cent[iTS][HADchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCpHAD_vs_cent[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpHAD_vs_cent[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpHAD_vs_cent[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpHAD_vs_cent[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCpHAD_vs_cent[iTS][HADchan]->SetOption("colz");
            
            hZDCnHAD_vs_cent[iTS][HADchan]->SetTitle("");
            hZDCnHAD_vs_cent[iTS][HADchan]->SetStats(kFALSE);
            hZDCnHAD_vs_cent[iTS][HADchan]->SetXTitle("Centrality (0.5% per bin)");
            hZDCnHAD_vs_cent[iTS][HADchan]->SetYTitle(Form("ZDCn HAD%d TS%d (fC)",HADchan+1,iTS));
            hZDCnHAD_vs_cent[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnHAD_vs_cent[iTS][HADchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCnHAD_vs_cent[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnHAD_vs_cent[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnHAD_vs_cent[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnHAD_vs_cent[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCnHAD_vs_cent[iTS][HADchan]->SetOption("colz");
            
            
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->SetTitle("");
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->SetStats(kFALSE);
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->SetXTitle("Centrality (0.5% per bin)");
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->SetYTitle(Form("ZDCp HAD%d TS%d noise subbed (fC)",HADchan+1,iTS));
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCpHAD_vs_cent_Nsub[iTS][HADchan]->SetOption("colz");
            
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->SetTitle("");
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->SetStats(kFALSE);
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->SetXTitle("Centrality (0.5% per bin)");
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->SetYTitle(Form("ZDCn HAD%d TS%d noise subbed (fC)",HADchan+1,iTS));
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCnHAD_vs_cent_Nsub[iTS][HADchan]->SetOption("colz");
            
            
            hZDCpHAD_vs_noff[iTS][HADchan]->SetTitle("");
            hZDCpHAD_vs_noff[iTS][HADchan]->SetStats(kFALSE);
            hZDCpHAD_vs_noff[iTS][HADchan]->SetXTitle("N_{pixel tracks}");
            hZDCpHAD_vs_noff[iTS][HADchan]->SetYTitle(Form("ZDCp HAD%d TS%d (fC)",HADchan+1,iTS));
            hZDCpHAD_vs_noff[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpHAD_vs_noff[iTS][HADchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCpHAD_vs_noff[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpHAD_vs_noff[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpHAD_vs_noff[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpHAD_vs_noff[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCpHAD_vs_noff[iTS][HADchan]->SetOption("colz");
            
            hZDCnHAD_vs_noff[iTS][HADchan]->SetTitle("");
            hZDCnHAD_vs_noff[iTS][HADchan]->SetStats(kFALSE);
            hZDCnHAD_vs_noff[iTS][HADchan]->SetXTitle("N_{pixel tracks}");
            hZDCnHAD_vs_noff[iTS][HADchan]->SetYTitle(Form("ZDCn HAD%d TS%d (fC)",HADchan+1,iTS));
            hZDCnHAD_vs_noff[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnHAD_vs_noff[iTS][HADchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCnHAD_vs_noff[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnHAD_vs_noff[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnHAD_vs_noff[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnHAD_vs_noff[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCnHAD_vs_noff[iTS][HADchan]->SetOption("colz");
            
            
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->SetTitle("");
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->SetStats(kFALSE);
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->SetXTitle("N_{pixel tracks}");
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->SetYTitle(Form("ZDCp HAD%d TS%d noise subbed (fC)",HADchan+1,iTS));
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCpHAD_vs_noff_Nsub[iTS][HADchan]->SetOption("colz");
            
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->SetTitle("");
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->SetStats(kFALSE);
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->SetXTitle("N_{pixel tracks}");
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->SetYTitle(Form("ZDCn HAD%d TS%d noise subbed (fC)",HADchan+1,iTS));
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->GetXaxis()->CenterTitle(kTRUE);
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->CenterTitle(kTRUE);
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->SetTitleOffset(1.75);
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->SetTitleSize(0.05);
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->SetLabelSize(0.04);
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->GetYaxis()->SetRangeUser(1,6000);
            hZDCnHAD_vs_noff_Nsub[iTS][HADchan]->SetOption("colz");
        }
    }
    
    
    
    for (int EMchan = 0; EMchan<numEMchan; EMchan++) {
        hPXpEMchan_cent[EMchan] = (TH1F *) hZDCpEMchan_cent[EMchan]->ProfileX()->Clone(Form("PXpEMchan%d_cent",EMchan+1));
        hPXpEMchan_cent[EMchan]->SetTitle("");
        hPXpEMchan_cent[EMchan]->SetStats(kFALSE);
        hPXpEMchan_cent[EMchan]->SetXTitle("Centrality (0.5% per bin)");
        hPXpEMchan_cent[EMchan]->SetYTitle("ZDC signal (fC)");
        hPXpEMchan_cent[EMchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXpEMchan_cent[EMchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXpEMchan_cent[EMchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXpEMchan_cent[EMchan]->GetYaxis()->SetTitleSize(0.06);
        hPXpEMchan_cent[EMchan]->GetYaxis()->SetLabelSize(0.05);
        hPXpEMchan_cent[EMchan]->GetYaxis()->SetRangeUser(1,centScan_max);
        hPXpEMchan_cent[EMchan]->SetOption("colz");
        
        hPXnEMchan_cent[EMchan] = (TH1F*) hZDCnEMchan_cent[EMchan]->ProfileX()->Clone(Form("PXnEMchan%d_cent",EMchan+1));
        hPXnEMchan_cent[EMchan]->SetTitle("");
        hPXnEMchan_cent[EMchan]->SetStats(kFALSE);
        hPXnEMchan_cent[EMchan]->SetXTitle("Centrality (0.5% per bin)");
        hPXnEMchan_cent[EMchan]->SetYTitle("ZDC signal (fC)");
        hPXnEMchan_cent[EMchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXnEMchan_cent[EMchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXnEMchan_cent[EMchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXnEMchan_cent[EMchan]->GetYaxis()->SetTitleSize(0.06);
        hPXnEMchan_cent[EMchan]->GetYaxis()->SetLabelSize(0.05);
        hPXnEMchan_cent[EMchan]->GetYaxis()->SetRangeUser(1,centScan_max);
        hPXnEMchan_cent[EMchan]->SetOption("colz");
        
        hPXpEMchan_cent_Nsub[EMchan] = (TH1F*) hZDCpEMchan_cent_Nsub[EMchan]->ProfileX()->Clone(Form("PXpEMchan%d_cent_Nsub",EMchan+1));
        hPXpEMchan_cent_Nsub[EMchan]->SetTitle("");
        hPXpEMchan_cent_Nsub[EMchan]->SetStats(kFALSE);
        hPXpEMchan_cent_Nsub[EMchan]->SetXTitle("Centrality (0.5% per bin)");
        hPXpEMchan_cent_Nsub[EMchan]->SetYTitle("ZDC signal noise subbed (fC)");
        hPXpEMchan_cent_Nsub[EMchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXpEMchan_cent_Nsub[EMchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXpEMchan_cent_Nsub[EMchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXpEMchan_cent_Nsub[EMchan]->GetYaxis()->SetTitleSize(0.06);
        hPXpEMchan_cent_Nsub[EMchan]->GetYaxis()->SetLabelSize(0.05);
        hPXpEMchan_cent_Nsub[EMchan]->GetYaxis()->SetRangeUser(1,centScan_max);
        hPXpEMchan_cent_Nsub[EMchan]->SetOption("colz");
        
        hPXnEMchan_cent_Nsub[EMchan] = (TH1F*) hZDCnEMchan_cent_Nsub[EMchan]->ProfileX()->Clone(Form("PXnEMchan%d_cent_Nsub",EMchan+1));
        hPXnEMchan_cent_Nsub[EMchan]->SetTitle("");
        hPXnEMchan_cent_Nsub[EMchan]->SetStats(kFALSE);
        hPXnEMchan_cent_Nsub[EMchan]->SetXTitle("Centrality (0.5% per bin)");
        hPXnEMchan_cent_Nsub[EMchan]->SetYTitle("ZDC signal noise subbed (fC)");
        hPXnEMchan_cent_Nsub[EMchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXnEMchan_cent_Nsub[EMchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXnEMchan_cent_Nsub[EMchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXnEMchan_cent_Nsub[EMchan]->GetYaxis()->SetTitleSize(0.06);
        hPXnEMchan_cent_Nsub[EMchan]->GetYaxis()->SetLabelSize(0.05);
        hPXnEMchan_cent_Nsub[EMchan]->GetYaxis()->SetRangeUser(1,centScan_max);
        hPXnEMchan_cent_Nsub[EMchan]->SetOption("colz");
        
        
        hPXpEMchan_noff[EMchan] = (TH1F*) hZDCpEMchan_noff[EMchan]->ProfileX()->Clone(Form("PXpEMchan%d_noff",EMchan+1));
        hPXpEMchan_noff[EMchan]->SetTitle("");
        hPXpEMchan_noff[EMchan]->SetStats(kFALSE);
        hPXpEMchan_noff[EMchan]->SetXTitle("N_{pixel tracks}");
        hPXpEMchan_noff[EMchan]->SetYTitle("ZDC signal (fC)");
        hPXpEMchan_noff[EMchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXpEMchan_noff[EMchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXpEMchan_noff[EMchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXpEMchan_noff[EMchan]->GetYaxis()->SetTitleSize(0.06);
        hPXpEMchan_noff[EMchan]->GetYaxis()->SetLabelSize(0.05);
        hPXpEMchan_noff[EMchan]->GetYaxis()->SetRangeUser(1,noffScan_max);
        hPXpEMchan_noff[EMchan]->SetOption("colz");
        
        hPXnEMchan_noff[EMchan] = (TH1F*) hZDCnEMchan_noff[EMchan]->ProfileX()->Clone(Form("PXnEMchan%d_noff",EMchan+1));
        hPXnEMchan_noff[EMchan]->SetTitle("");
        hPXnEMchan_noff[EMchan]->SetStats(kFALSE);
        hPXnEMchan_noff[EMchan]->SetXTitle("N_{pixel tracks}");
        hPXnEMchan_noff[EMchan]->SetYTitle("ZDC signal (fC)");
        hPXnEMchan_noff[EMchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXnEMchan_noff[EMchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXnEMchan_noff[EMchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXnEMchan_noff[EMchan]->GetYaxis()->SetTitleSize(0.06);
        hPXnEMchan_noff[EMchan]->GetYaxis()->SetLabelSize(0.05);
        hPXnEMchan_noff[EMchan]->GetYaxis()->SetRangeUser(1,noffScan_max);
        hPXnEMchan_noff[EMchan]->SetOption("colz");
        
        hPXpEMchan_noff_Nsub[EMchan] = (TH1F*) hZDCpEMchan_noff_Nsub[EMchan]->ProfileX()->Clone(Form("PXpEMchan%d_noff_Nsub",EMchan+1));
        hPXpEMchan_noff_Nsub[EMchan]->SetTitle("");
        hPXpEMchan_noff_Nsub[EMchan]->SetStats(kFALSE);
        hPXpEMchan_noff_Nsub[EMchan]->SetXTitle("N_{pixel tracks}");
        hPXpEMchan_noff_Nsub[EMchan]->SetYTitle("ZDC noise subbed (fC)");
        hPXpEMchan_noff_Nsub[EMchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXpEMchan_noff_Nsub[EMchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXpEMchan_noff_Nsub[EMchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXpEMchan_noff_Nsub[EMchan]->GetYaxis()->SetTitleSize(0.06);
        hPXpEMchan_noff_Nsub[EMchan]->GetYaxis()->SetLabelSize(0.05);
        hPXpEMchan_noff_Nsub[EMchan]->GetYaxis()->SetRangeUser(1,noffScan_max);
        hPXpEMchan_noff_Nsub[EMchan]->SetOption("colz");
        
        hPXnEMchan_noff_Nsub[EMchan] = (TH1F*) hZDCnEMchan_noff_Nsub[EMchan]->ProfileX()->Clone(Form("PXnEMchan%d_noff_Nsub",EMchan+1));
        hPXnEMchan_noff_Nsub[EMchan]->SetTitle("");
        hPXnEMchan_noff_Nsub[EMchan]->SetStats(kFALSE);
        hPXnEMchan_noff_Nsub[EMchan]->SetXTitle("N_{pixel tracks}");
        hPXnEMchan_noff_Nsub[EMchan]->SetYTitle("ZDC signal noise subbed (fC)");
        hPXnEMchan_noff_Nsub[EMchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXnEMchan_noff_Nsub[EMchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXnEMchan_noff_Nsub[EMchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXnEMchan_noff_Nsub[EMchan]->GetYaxis()->SetTitleSize(0.06);
        hPXnEMchan_noff_Nsub[EMchan]->GetYaxis()->SetLabelSize(0.05);
        hPXnEMchan_noff_Nsub[EMchan]->GetYaxis()->SetRangeUser(1,noffScan_max);
        hPXnEMchan_noff_Nsub[EMchan]->SetOption("colz");
    }
    for (int HADchan = 0; HADchan<numHADchan; HADchan++) {
        hPXpHADchan_cent[HADchan] = (TH1F*) hZDCpHADchan_cent[HADchan]->ProfileX()->Clone(Form("PXpHADchan%d_cent",HADchan+1));
        hPXpHADchan_cent[HADchan]->SetTitle("");
        hPXpHADchan_cent[HADchan]->SetStats(kFALSE);
        hPXpHADchan_cent[HADchan]->SetXTitle("Centrality (0.5% per bin)");
        hPXpHADchan_cent[HADchan]->SetYTitle("ZDC signal (fC)");
        hPXpHADchan_cent[HADchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXpHADchan_cent[HADchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXpHADchan_cent[HADchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXpHADchan_cent[HADchan]->GetYaxis()->SetTitleSize(0.06);
        hPXpHADchan_cent[HADchan]->GetYaxis()->SetLabelSize(0.05);
        hPXpHADchan_cent[HADchan]->GetYaxis()->SetRangeUser(1,centScan_max);
        hPXpHADchan_cent[HADchan]->SetOption("colz");
        
        hPXnHADchan_cent[HADchan] = (TH1F*) hZDCnHADchan_cent[HADchan]->ProfileX()->Clone(Form("PXnHADchan%d_cent",HADchan+1));
        hPXnHADchan_cent[HADchan]->SetTitle("");
        hPXnHADchan_cent[HADchan]->SetStats(kFALSE);
        hPXnHADchan_cent[HADchan]->SetXTitle("Centrality (0.5% per bin)");
        hPXnHADchan_cent[HADchan]->SetYTitle("ZDC signal (fC)");
        hPXnHADchan_cent[HADchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXnHADchan_cent[HADchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXnHADchan_cent[HADchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXnHADchan_cent[HADchan]->GetYaxis()->SetTitleSize(0.06);
        hPXnHADchan_cent[HADchan]->GetYaxis()->SetLabelSize(0.05);
        hPXnHADchan_cent[HADchan]->GetYaxis()->SetRangeUser(1,10000);
        hPXnHADchan_cent[HADchan]->SetOption("colz");
        
        hPXpHADchan_cent_Nsub[HADchan] = (TH1F*) hZDCpHADchan_cent_Nsub[HADchan]->ProfileX()->Clone(Form("PXpHADchan%d_cent_Nsub",HADchan+1));
        hPXpHADchan_cent_Nsub[HADchan]->SetTitle("");
        hPXpHADchan_cent_Nsub[HADchan]->SetStats(kFALSE);
        hPXpHADchan_cent_Nsub[HADchan]->SetXTitle("Centrality (0.5% per bin)");
        hPXpHADchan_cent_Nsub[HADchan]->SetYTitle("ZDC signal noise subbed (fC)");
        hPXpHADchan_cent_Nsub[HADchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXpHADchan_cent_Nsub[HADchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXpHADchan_cent_Nsub[HADchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXpHADchan_cent_Nsub[HADchan]->GetYaxis()->SetTitleSize(0.06);
        hPXpHADchan_cent_Nsub[HADchan]->GetYaxis()->SetLabelSize(0.05);
        hPXpHADchan_cent_Nsub[HADchan]->GetYaxis()->SetRangeUser(1,centScan_max);
        hPXpHADchan_cent_Nsub[HADchan]->SetOption("colz");
        
        hPXnHADchan_cent_Nsub[HADchan] = (TH1F*) hZDCnHADchan_cent_Nsub[HADchan]->ProfileX()->Clone(Form("PXnHADchan%d_cent_Nsub",HADchan+1));
        hPXnHADchan_cent_Nsub[HADchan]->SetTitle("");
        hPXnHADchan_cent_Nsub[HADchan]->SetStats(kFALSE);
        hPXnHADchan_cent_Nsub[HADchan]->SetXTitle("Centrality (0.5% per bin)");
        hPXnHADchan_cent_Nsub[HADchan]->SetYTitle("ZDC signal noise subbed (fC)");
        hPXnHADchan_cent_Nsub[HADchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXnHADchan_cent_Nsub[HADchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXnHADchan_cent_Nsub[HADchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXnHADchan_cent_Nsub[HADchan]->GetYaxis()->SetTitleSize(0.06);
        hPXnHADchan_cent_Nsub[HADchan]->GetYaxis()->SetLabelSize(0.05);
        hPXnHADchan_cent_Nsub[HADchan]->GetYaxis()->SetRangeUser(1,centScan_max);
        hPXnHADchan_cent_Nsub[HADchan]->SetOption("colz");
        
        
        hPXpHADchan_noff[HADchan] = (TH1F*) hZDCpHADchan_noff[HADchan]->ProfileX()->Clone(Form("PXpHADchan%d_noff",HADchan+1));
        hPXpHADchan_noff[HADchan]->SetTitle("");
        hPXpHADchan_noff[HADchan]->SetStats(kFALSE);
        hPXpHADchan_noff[HADchan]->SetXTitle("N_{pixel tracks}");
        hPXpHADchan_noff[HADchan]->SetYTitle("ZDC signal (fC)");
        hPXpHADchan_noff[HADchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXpHADchan_noff[HADchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXpHADchan_noff[HADchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXpHADchan_noff[HADchan]->GetYaxis()->SetTitleSize(0.06);
        hPXpHADchan_noff[HADchan]->GetYaxis()->SetLabelSize(0.05);
        hPXpHADchan_noff[HADchan]->GetYaxis()->SetRangeUser(1,noffScan_max);
        hPXpHADchan_noff[HADchan]->SetOption("colz");
        
        hPXnHADchan_noff[HADchan] = (TH1F*) hZDCnHADchan_noff[HADchan]->ProfileX()->Clone(Form("PXnHADchan%d_noff",HADchan+1));
        hPXnHADchan_noff[HADchan]->SetTitle("");
        hPXnHADchan_noff[HADchan]->SetStats(kFALSE);
        hPXnHADchan_noff[HADchan]->SetXTitle("N_{pixel tracks}");
        hPXnHADchan_noff[HADchan]->SetYTitle("ZDC signal (fC)");
        hPXnHADchan_noff[HADchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXnHADchan_noff[HADchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXnHADchan_noff[HADchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXnHADchan_noff[HADchan]->GetYaxis()->SetTitleSize(0.06);
        hPXnHADchan_noff[HADchan]->GetYaxis()->SetLabelSize(0.05);
        hPXnHADchan_noff[HADchan]->GetYaxis()->SetRangeUser(1,noffScan_max);
        hPXnHADchan_noff[HADchan]->SetOption("colz");
        
        hPXpHADchan_noff_Nsub[HADchan] = (TH1F*) hZDCpHADchan_noff_Nsub[HADchan]->ProfileX()->Clone(Form("PXpHADchan%d_noff_Nsub",HADchan+1));
        hPXpHADchan_noff_Nsub[HADchan]->SetTitle("");
        hPXpHADchan_noff_Nsub[HADchan]->SetStats(kFALSE);
        hPXpHADchan_noff_Nsub[HADchan]->SetXTitle("N_{pixel tracks}");
        hPXpHADchan_noff_Nsub[HADchan]->SetYTitle("ZDC signal noise subbed (fC)");
        hPXpHADchan_noff_Nsub[HADchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXpHADchan_noff_Nsub[HADchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXpHADchan_noff_Nsub[HADchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXpHADchan_noff_Nsub[HADchan]->GetYaxis()->SetTitleSize(0.06);
        hPXpHADchan_noff_Nsub[HADchan]->GetYaxis()->SetLabelSize(0.05);
        hPXpHADchan_noff_Nsub[HADchan]->GetYaxis()->SetRangeUser(1,noffScan_max);
        hPXpHADchan_noff_Nsub[HADchan]->SetOption("colz");
        
        hPXnHADchan_noff_Nsub[HADchan] = (TH1F*) hZDCnHADchan_noff_Nsub[HADchan]->ProfileX()->Clone(Form("PXnHADchan%d_noff_Nsub",HADchan+1));
        hPXnHADchan_noff_Nsub[HADchan]->SetTitle("");
        hPXnHADchan_noff_Nsub[HADchan]->SetStats(kFALSE);
        hPXnHADchan_noff_Nsub[HADchan]->SetXTitle("N_{pixel tracks}");
        hPXnHADchan_noff_Nsub[HADchan]->SetYTitle("ZDC signal noise subbed (fC)");
        hPXnHADchan_noff_Nsub[HADchan]->GetXaxis()->CenterTitle(kTRUE);
        hPXnHADchan_noff_Nsub[HADchan]->GetYaxis()->CenterTitle(kTRUE);
        hPXnHADchan_noff_Nsub[HADchan]->GetYaxis()->SetTitleOffset(1.55);
        hPXnHADchan_noff_Nsub[HADchan]->GetYaxis()->SetTitleSize(0.06);
        hPXnHADchan_noff_Nsub[HADchan]->GetYaxis()->SetLabelSize(0.05);
        hPXnHADchan_noff_Nsub[HADchan]->GetYaxis()->SetRangeUser(1,noffScan_max);
        hPXnHADchan_noff_Nsub[HADchan]->SetOption("colz");
    }
    
}
