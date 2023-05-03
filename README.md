# **Discrete FIR and CORDIC processing chain**

This repository contains all relevant source files for a discrete signal processing chain, designed and deployed as an FPGA hardware accelerator. The processing chain contains a discrete 25-tap FIR filter, and also a CORDIC rotational computer. The FIR filter passes a 1-d filter over the incoming data, and the CORDIC converts the rectangular coordinates from the FIR into polar coordinates. These polar coordinates indicate the magnitude and phase of the system.

## **Final Report**

A complete final report was written, including an extensive analysis of the processing chain and the optimization available. The source code for the report is available in the [report](report/) folder. A pre-compiled PDF can be found [here](report/report_polarFIR.pdf) for quick access.

### FIR Filter

The FIR filter runs a user-configurable set of taps across a 1-d dataset in rectangular form. The filter is highly optimized for parallel computation and specifically uses the DSPs onboard the FPGA.


### CORDIC 

Rectangular pairs produced by the FIR filter are converted into polar coordinates using the CORDIC algorithm. This particular algorithm uses 8 iterations of precision, resulting in a highly accurate computed value. The algorithm was also optimized for parallelism, as is traditional in any FPGA deployment.


