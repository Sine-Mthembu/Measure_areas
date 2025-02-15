# Fit Gaussian peaks with ROOT/C++

## Description

The `Fit_Gaussian_peaks` program is a ROOT/C++ application designed to analyze and fit Gaussian peaks in histograms. It processes a set of histograms representing energy distributions, fits Gaussian functions to specified peaks, and saves the fitting parameters to a text file. This tool is particularly useful in experimental physics for analyzing data from detectors, this code can also be used to extract centroids from peaks for calibration purposes, for example.

## Features

- Loads multiple histograms from an attached .root file.
- Fits Gaussian functions with linear backgrounds to specified peaks.
- Outputs fitting parameters like the centroid, width and height and errors to a text file for further analysis.
- The fit parameters are then used to calculate the area under the peaks using the formular;
   - **Mean**: The position of the peak.
   - **Sigma** ($\sigma$): The width of the Gaussian.
   - **Height**: The maximum height of the Gaussian.
- **Area**: The area under the Gaussian curve, calculated as: $\text{Area} = \text{Height} \times \sigma \times \sqrt{2\pi} $
- **Area Error**: The error associated with the area, which can be estimated using the error in height and sigma. The formula for the area error can be approximated as: $\text{Area Error} = \text{Area} \times \sqrt{\left(\frac{\delta \text{Height}}{\text{Height}}\right)^2 + \left(\frac{\delta \sigma}{\sigma}\right)^2} $
- Visualizes the histograms and the fitted curves on a canvas.

## Prerequisites

- ROOT framework (version compatible with your code).
- C++ compiler (e.g., g++, clang++).
- Basic understanding of ROOT and histogram fitting.
