// import the necessary ROOT/C++ Libraries
#include <iostream>
#include <fstream>
#include <TCanvas.h>
#include <TH1D.h>
#include <TF1.h>

using namespace std;

int Fit_gaussian_peaks() {
    Int_t i, j;
    Int_t Pl, Ph, Peak;
    Int_t m;
    Char_t infoFileName[200];

    // Background gate settings
    Ph = -10; 
    Pl = 10; 
    Peak = 258; // Peak position to fit

    // Create output file name based on the peak value
    sprintf(infoFileName, "Areas_clovers_2021_%d.txt", Peak);
    cout << infoFileName << endl;

    // Open output file in append mode
    ofstream info;
    info.open(infoFileName, ios::app);

    // Create a canvas to display histograms
    TCanvas *Ee = new TCanvas("CurrentHist", "CurrentHist", 1);
    Ee->Divide(4, 4); // Divide canvas into a 4x4 grid

    // Loop over the 16 histograms
    for (int y = 0; y < 16; y++) {
        j = (y / 4); // Row index
        m = y - j * 4; // Column index

        Ee->cd(y + 1); // Select the current pad in the canvas
        cout << j << "  " << m << endl;

        // Create histograms based on the number of detectors and crystals. In this case there are 4 HPGe clover detectors, each with 4 crystals
        if (j == 0) {
            if (m == 0)  TH1D *hist(*Energy_0_0);
            if (m == 1)  TH1D *hist(*Energy_0_1);
            if (m == 2)  TH1D *hist(*Energy_0_2);
            if (m == 3)  TH1D *hist(*Energy_0_3);
        }

        if (j == 1) {
            if (m == 0)  {TH1D *hist(*Energy_1_0);} 
            if (m == 1)  {TH1D *hist(*Energy_1_1);} 
            if (m == 2)  {TH1D *hist(*Energy_1_2);} 
            if (m == 3)  {TH1D *hist(*Energy_1_3);} 
        }

        if (j == 2) {
            if (m == 0)  {TH1D *hist(*Energy_2_0);} 
            if (m == 1)  {TH1D *hist(*Energy_2_1);} 
            if (m == 2)  {TH1D *hist(*Energy_2_2);} 
            if (m == 3)  {TH1D *hist(*Energy_2_3);} 
        }

        if (j == 3) {
            if (m == 0)  {TH1D *hist(*Energy_3_0);} 
            if (m == 1)  {TH1D *hist(*Energy_3_1);} 
            if (m == 2)  {TH1D *hist(*Energy_3_2);} 
            if (m == 3)  {TH1D *hist(*Energy_3_3);} 
        }

        // Variables to store fitting parameters and errors
        double parameter[50][50], error[50][50], peak;
        double height = -99; // Assume the initial height is negative
        double current_height = 0;

        // Find the maximum height in the histogram around the peak, this helps with different peak intensities. The fit may not converge if an incorrect height is used.
        for (int count = Peak - 6; count < Peak + 6; count++) {
            current_height = hist->GetBinContent(count);
            if (current_height > height) {
                height = current_height;    
            }   
        }

        // Create a Gaussian fit function with a linear background
        TF1 *fit1 = new TF1("fit1", "gaus(0)+pol1(3)", 0, 1000);
        peak = hist->GetBin(Peak);
        fit1->SetParameters(height, Peak, 3, 0, 0); // Set initial parameters
        hist->Fit("fit1", "", "", Peak + Ph, Peak + Pl); // Fit the histogram
        hist->GetXaxis()->SetRange(Peak - 20, Peak + 20); // Set x-axis range for drawing
        hist->Draw(); // Draw the histogram

        // Store fitting parameters and errors
        for(int u=0; u<3; u++){

parameter[1][u]=fit1->GetParameter(u);
error[1][u]=fit1->GetParError(u);

}
// Write the area into the output file
info<< parameter[1][1]<<endl;
}
 info.close();

}
