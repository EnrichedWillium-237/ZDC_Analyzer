# ZDC_Analyzer
ZDC analyzer and plotting macros


Instructions:
Enter the command 

root -l make_plots.C

This will produce various plots using ZDC digis with respect to centrality, number of pixel hits, and other desired observables. 


Code details: 
make_plots.C accesses the scripts plot_style.C and ReadTree.C. 

plot_style.C initializes the histograms (MakeHists) and sets all of the graphics options for the plots in a place that doesn't clutter the main macro. 

ReadZDCTree.C contains functions which gets leafs from trees (GetLeafs) and then fills the histograms with calibrated ZDC digis. 

In order to add a new plot, 
  (1) Declare it in ReadZDCTree.C
  (2) Initialize and set graphing options in plot_style.C
  (3) Create and canvas and draw in make_plots.C
