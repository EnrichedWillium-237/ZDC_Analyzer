{
    
    TFile * f = new TFile("/Users/wmcbraye/root/macros/ZDC/ZdcFTW/CMSSW_7_5_7_patch1/src/2015ZDCruns/masterTree.root");
    TTree *CENT = (TTree *) f->Get("CentTree"); // Centrality tree
    TTree *ZDCHI = (TTree *) f->Get("ZDCDigiTree"); // Digi tree
    Int_t nevents = ZDCHI->GetEntries();

    TH2F* Pos_histogram_2D = new TH2F("Pos_histogram_2D", "pos-EM vs. pos-HAD TS:45_ExpressMerged_NS27", 300, 0, 20000, 300, 0, 20000);
    TH1F* Pos_histogram_1D = new TH1F("Pos_histogram_1D", "MTotalHAD_TS45_ExpressMerged_NS27", 300, 10, 20000);
    TH1F* Pos_histogram_1DSum = new TH1F("Pos_histogram_1DSum", "MTotalHAD+0.1TotalEM_TS45_ExpressMerged_NS27", 300, 10, 20000);
    
    TH2F* Pos_histogram_2D_noNoise = new TH2F("Pos_histogram_2D_noNoise", "pos-EM vs. pos-HAD TS:45_ExpressMerged_NoNoise", 300, 0, 20000, 300, 0, 20000);
    TH1F* Pos_histogram_1D_noNoise = new TH1F("Pos_histogram_1D_noNoise", "MTotalHAD_TS45_ExpressMerged_NoNoise", 300, 10, 20000);
    TH1F* Pos_histogram_1DSumNoNoise = new TH1F("Pos_histogram_1DSumNoNoise", "MTotalHAD+0.1TotalEM_TS45_ExpressMerged_NoNoise", 300, 10, 20000);
    
    // Centrality plots
    TH1F* hcent = new TH1F("hcent", "hcent", 200, 1, 201);
    TH2F* hcent_2D = new TH2F("hcent_2D", "MTotalHAD+0.1TotalEM vs. cent TS:45_ExpressMerged_NS27", 50, 1, 200, 300, 0, 20000);
    TH2F* hcent_2D_noNoise = new TH2F("hcent_2D_noNoise", "MTotalHAD+0.1TotalEM vs. cent TS:45_ExpressMerged_NS27", 50, 1, 200, 300, 0, 20000);
    
    /////////////Get Info From the Leaves/////////////////////////
    
    CENTRAL= (TLeaf*)CENT->GetLeaf("Cent_HFtowers");
    TLeaf * PEM1fC= (TLeaf*)ZDCHI->GetLeaf("posEM1cFtsz");//PEM1
    TLeaf * PEM1ADC= (TLeaf*)ZDCHI->GetLeaf("posEM1ADCtsz");
    TLeaf * PEM2fC= (TLeaf*)ZDCHI->GetLeaf("posEM2cFtsz");//PEM2
    TLeaf * PEM2ADC= (TLeaf*)ZDCHI->GetLeaf("posEM2ADCtsz");
    TLeaf * PEM3fC= (TLeaf*)ZDCHI->GetLeaf("posEM3cFtsz");//PEM3
    TLeaf * PEM3ADC= (TLeaf*)ZDCHI->GetLeaf("posEM3ADCtsz");
    TLeaf * PEM4fC= (TLeaf*)ZDCHI->GetLeaf("posEM4cFtsz");//PEM4
    TLeaf * PEM4ADC= (TLeaf*)ZDCHI->GetLeaf("posEM4ADCtsz");
    TLeaf * PEM5fC= (TLeaf*)ZDCHI->GetLeaf("posEM5cFtsz");//PEM5
    TLeaf * PEM5ADC= (TLeaf*)ZDCHI->GetLeaf("posEM5ADCtsz");
    TLeaf * PHAD1fC= (TLeaf*)ZDCHI->GetLeaf("posHD1cFtsz");//PHAD1
    TLeaf * PHAD1ADC= (TLeaf*)ZDCHI->GetLeaf("posHD1ADCtsz");
    TLeaf * PHAD2fC= (TLeaf*)ZDCHI->GetLeaf("posHD2cFtsz");//PHAD2
    TLeaf * PHAD2ADC= (TLeaf*)ZDCHI->GetLeaf("posHD2ADCtsz");
    TLeaf * PHAD3fC= (TLeaf*)ZDCHI->GetLeaf("posHD3cFtsz");//PHAD3
    TLeaf * PHAD3ADC= (TLeaf*)ZDCHI->GetLeaf("posHD3ADCtsz");
    TLeaf * PHAD4fC= (TLeaf*)ZDCHI->GetLeaf("posHD4cFtsz");//PHAD4
    TLeaf * PHAD4ADC= (TLeaf*)ZDCHI->GetLeaf("posHD4ADCtsz");
    
    // Declaration of leaf types//////////////////////////
    Double_t         posEM1fC[10];
    Double_t         posEM1ADC[10];
    Double_t         posEM2fC[10];
    Double_t         posEM2ADC[10];
    Double_t         posEM3fC[10];
    Double_t         posEM3ADC[10];
    Double_t         posEM4fC[10];
    Double_t         posEM4ADC[10];
    Double_t         posEM5fC[10];
    Double_t         posEM5ADC[10];
    Double_t         posHD1fC[10];
    Double_t         posHD1ADC[10];
    Double_t         posHD2fC[10];
    Double_t         posHD2ADC[10];
    Double_t         posHD3fC[10];
    Double_t         posHD3ADC[10];
    Double_t         posHD4fC[10];
    Double_t         posHD4ADC[10];
    Double_t         centrality;
    
    Double_t HADsum=0;
    Double_t EMsum=0;
    Double_t ETsum=0;
    
    Double_t HADsum_PNS=0;
    Double_t EMsum_PNS=0;
    Double_t ETsum_PNS=0;
    
    
    for(Int_t i =0; i<nevents; i++) {
        
        ZDCHI->GetEntry(i);
        CENT->GetEntry(i);
        
        centrality=(CENTRAL->GetValue());
        hcent->Fill(centrality);
        
        float PEM1TotalSignal=0;
        float PEM2TotalSignal=0;
        float PEM3TotalSignal=0;
        float PEM4TotalSignal=0;
        float PEM5TotalSignal=0;
        float PHAD1TotalSignal=0;
        float PHAD2TotalSignal=0;
        float PHAD3TotalSignal=0;
        float PHAD4TotalSignal=0;
        
        for(int iTS=4;iTS<6;iTS++){
            // declare which Timeslices are of interested
            posEM1fC[iTS]=(PEM1fC->GetValue(iTS));//PEM1
            posEM2fC[iTS]=(PEM2fC->GetValue(iTS));//PEM2
            posEM3fC[iTS]=(PEM3fC->GetValue(iTS));//PEM3
            posEM4fC[iTS]=(PEM4fC->GetValue(iTS));//PEM4
            posEM5fC[iTS]=(PEM5fC->GetValue(iTS));//PEM5
            posHD1fC[iTS]=(PHAD1fC->GetValue(iTS));//PHAD1
            posHD2fC[iTS]=(PHAD2fC->GetValue(iTS));//PHAD2
            posHD3fC[iTS]=(PHAD3fC->GetValue(iTS));//PHAD3
            posHD4fC[iTS]=(PHAD4fC->GetValue(iTS));//PHAD4
            
            //EM1
            if(posEM1fC[iTS]<0){
                posEM1fC[iTS]=0;
            }
            PEM1TotalSignal=PEM1TotalSignal+posEM1fC[iTS];//takes the fC value of that timeslice and adds it to the "TotalSignal" of that HAD1 section
            //EM2
            if(posEM2fC[iTS]<0){
                posEM2fC[iTS]=0;
            }
            PEM2TotalSignal=PEM2TotalSignal+posEM2fC[iTS];
            //EM3
            if(posEM3fC[iTS]<0){
                posEM3fC[iTS]=0;
            }
            PEM3TotalSignal=PEM3TotalSignal+posEM3fC[iTS];
            //EM4
            if(posEM4fC[iTS]<0){
                posEM4fC[iTS]=0;
            }
            PEM4TotalSignal=PEM4TotalSignal+posEM4fC[iTS];
            //EM5
            if(posEM5fC[iTS]<0){
                posEM5fC[iTS]=0;
            }
            PEM5TotalSignal=PEM5TotalSignal+posEM5fC[iTS];
            //HAD1
            if(posHD1fC[iTS]<0){
                posHD1fC[iTS]=0;
            }
            PHAD1TotalSignal=PHAD1TotalSignal+posHD1fC[iTS];
            //HAD2
            if(posHD2fC[iTS]<0){
                posHD2fC[iTS]=0;
            }
            PHAD2TotalSignal=PHAD2TotalSignal+posHD2fC[iTS];
            //HAD3
            if(posHD3fC[iTS]<0){
                posHD3fC[iTS]=0;
            }
            PHAD3TotalSignal=PHAD3TotalSignal+posHD3fC[iTS];
            //HAD4
            if(posHD4fC[iTS]<0){
                posHD4fC[iTS]=0;
            }
            PHAD4TotalSignal=PHAD4TotalSignal+posHD4fC[iTS];
            
        }

        float PEM1TotalNoise=0;
        float PEM2TotalNoise=0;
        float PEM3TotalNoise=0;
        float PEM4TotalNoise=0;
        float PEM5TotalNoise=0;
        float PHAD1TotalNoise=0;
        float PHAD2TotalNoise=0;
        float PHAD3TotalNoise=0;
        float PHAD4TotalNoise=0;
        
        for(int iTS=2;iTS<3;iTS++)
        {
            //EM1
            posEM1fC[iTS]=(PEM1fC->GetValue(iTS));
            PEM1TotalNoise=PEM1TotalNoise+posEM1fC[iTS];
            //EM2
            posEM2fC[iTS]=(PEM2fC->GetValue(iTS));
            PEM2TotalNoise=PEM2TotalNoise+posEM2fC[iTS];
            //EM3
            posEM3fC[iTS]=(PEM3fC->GetValue(iTS));
            PEM3TotalNoise=PEM3TotalNoise+posEM3fC[iTS];
            //EM4
            posEM4fC[iTS]=(PEM4fC->GetValue(iTS));
            PEM4TotalNoise=PEM4TotalNoise+posEM4fC[iTS];
            //EM5
            posEM5fC[iTS]=(PEM5fC->GetValue(iTS));
            PEM5TotalNoise=PEM5TotalNoise+posEM5fC[iTS];
            //HAD1
            posHD1fC[iTS]=(PHAD1fC->GetValue(iTS));
            PHAD1TotalNoise=PHAD1TotalNoise+posHD1fC[iTS];
            //HAD2
            posHD2fC[iTS]=(PHAD2fC->GetValue(iTS));
            PHAD2TotalNoise=PHAD2TotalNoise+posHD2fC[iTS];
            //HAD3
            posHD3fC[iTS]=(PHAD3fC->GetValue(iTS));
            PHAD3TotalNoise=PHAD3TotalNoise+posHD3fC[iTS];
            //HAD4
            posHD4fC[iTS]=(PHAD4fC->GetValue(iTS));
            PHAD4TotalNoise=PHAD4TotalNoise+posHD4fC[iTS];
            
        }
        for(int iTS=7;iTS<8;iTS++)
        {
            //EM1
            posEM1fC[iTS]=(PEM1fC->GetValue(iTS));
            PEM1TotalNoise=PEM1TotalNoise+posEM1fC[iTS];
            //EM2
            posEM2fC[iTS]=(PEM2fC->GetValue(iTS));
            PEM2TotalNoise=PEM2TotalNoise+posEM2fC[iTS];
            //EM3
            posEM3fC[iTS]=(PEM3fC->GetValue(iTS));
            PEM3TotalNoise=PEM3TotalNoise+posEM3fC[iTS];
            //EM4
            posEM4fC[iTS]=(PEM4fC->GetValue(iTS));
            PEM4TotalNoise=PEM4TotalNoise+posEM4fC[iTS];
            //EM5
            posEM5fC[iTS]=(PEM5fC->GetValue(iTS));
            PEM5TotalNoise=PEM5TotalNoise+posEM5fC[iTS];
            //HAD1
            posHD1fC[iTS]=(PHAD1fC->GetValue(iTS));
            PHAD1TotalNoise=PHAD1TotalNoise+posHD1fC[iTS];
            //HAD2
            posHD2fC[iTS]=(PHAD2fC->GetValue(iTS));
            PHAD2TotalNoise=PHAD2TotalNoise+posHD2fC[iTS];
            //HAD3
            posHD3fC[iTS]=(PHAD3fC->GetValue(iTS));
            PHAD3TotalNoise=PHAD3TotalNoise+posHD3fC[iTS];
            //HAD4
            posHD4fC[iTS]=(PHAD4fC->GetValue(iTS));
            PHAD4TotalNoise=PHAD4TotalNoise+posHD4fC[iTS];
            
        }
        
        // No noise subtraction
        HADsum_PNS=(PHAD1TotalSignal)+(PHAD2TotalSignal)+(PHAD3TotalSignal)+(PHAD4TotalSignal);
        ETsum_PNS=(PHAD1TotalSignal)+(PHAD2TotalSignal)+(PHAD3TotalSignal)+(PHAD4TotalSignal)+(.1*PEM1TotalSignal)+(.1*PEM2TotalSignal)+(.1*PEM3TotalSignal)+(.1*PEM4TotalSignal)+(.1*PEM5TotalSignal);
        
        EMsum_PNS=(PEM1TotalSignal)+(PEM2TotalSignal)+(PEM3TotalSignal)+(PEM4TotalSignal)+(PEM5TotalSignal);
        
        Pos_histogram_1D_noNoise->Fill(HADsum_PNS);
        Pos_histogram_1DSumNoNoise->Fill(ETsum_PNS);
        Pos_histogram_2D_noNoise->Fill(HADsum_PNS, EMsum_PNS);
        hcent_2D_noNoise->Fill(centrality, ETsum_PNS);
        
        // Noise subtraction
        HADsum=(PHAD1TotalSignal-PHAD1TotalNoise)+(PHAD2TotalSignal-PHAD2TotalNoise)+(PHAD3TotalSignal-PHAD3TotalNoise)+(PHAD4TotalSignal-PHAD4TotalNoise);
        ETsum=(PHAD1TotalSignal-PHAD1TotalNoise)+(PHAD2TotalSignal-PHAD2TotalNoise)+(PHAD3TotalSignal-PHAD3TotalNoise)+(PHAD4TotalSignal-PHAD4TotalNoise)+(.1)*(PEM1TotalSignal-PEM1TotalNoise)+(.1)*(PEM2TotalSignal-PEM2TotalNoise)+(.1)*(PEM3TotalSignal-PEM3TotalNoise)+(.1)*(PEM4TotalSignal-PEM4TotalNoise)+(.1)*(PEM5TotalSignal-PEM5TotalNoise);
        
        EMsum=(PEM1TotalSignal-PEM1TotalNoise)+(PEM2TotalSignal-PEM2TotalNoise)+(PEM3TotalSignal-PEM3TotalNoise)+(PEM4TotalSignal-PEM4TotalNoise)+(PEM5TotalSignal-PEM5TotalNoise);
        
        Pos_histogram_1D->Fill(HADsum);
        Pos_histogram_1DSum->Fill(ETsum);
        Pos_histogram_2D->Fill(HADsum, EMsum);
        hcent_2D->Fill(centrality, ETsum);
    }
    
    gStyle->SetPalette(1);

    TCanvas * cposNoNoise = new TCanvas("cposNoNoise","cposNoNoise",700,600);
    cposNoNoise->SetLogz();
    hcent_2D_noNoise->SetStats(kFALSE);
    hcent_2D_noNoise->SetTitle("");
    hcent_2D_noNoise->SetXTitle("Cent bin (0.5% per bin)");
    hcent_2D_noNoise->SetYTitle("ZDC+ (fC)");
    hcent_2D_noNoise->GetXaxis()->CenterTitle(kTRUE);
    hcent_2D_noNoise->GetYaxis()->CenterTitle(kTRUE);
    hcent_2D_noNoise->GetYaxis()->SetRangeUser(0,12000);
    hcent_2D_noNoise->Draw("colz");
    hcent_2D_noNoise->ProfileX()->Draw("same");
//    cposNoNoise->Print("hcent.pdf");
    cposNoNoise->Close();
    
    TCanvas * cposNoiseSubbed = new TCanvas("cposNoNoise","cposNoNoise",700,600);
    cposNoiseSubbed->SetLogz();
    hcent_2D->SetStats(kFALSE);
    hcent_2D->SetTitle("");
    hcent_2D->SetXTitle("Cent bin (0.5% per bin)");
    hcent_2D->SetYTitle("ZDC+ (fC) noise subtracted");
    hcent_2D->GetXaxis()->CenterTitle(kTRUE);
    hcent_2D->GetYaxis()->CenterTitle(kTRUE);
    hcent_2D->GetYaxis()->SetRangeUser(0,12000);
    hcent_2D->Draw("colz");
    TH1F * hc2DXproj = (TH1F*) hcent_2D->ProfileX();
    hc2DXproj->Draw("same");
//    cposNoiseSubbed->Print("hcent.pdf");
    cposNoiseSubbed->Close();
    
    TCanvas * cPos = new TCanvas("cPos","cPos",1200,600);
    cPos->Divide(2,1);
    TPad * pad1 = (TPad*) cPos->cd(1);
    pad1->SetLogz();
    hcent_2D_noNoise->Draw("colz");
    hcent_2D_noNoise->ProfileX()->Draw("same");
    TPad * pad2 = (TPad*) cPos->cd(2);
    pad2->SetLogz();
    hcent_2D->Draw("colz");
    hc2DXproj->Draw("same");
}
