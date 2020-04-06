code for simulation cosmic ray using BESS magnet
with detector including subdetectors:
1) TOF on top and bottom of BESS MAGnet
   using plastic scintillator
   each TOF has 2 layers: one with segment in X-axis, the other in Z-axis
   dimention: , thickness: 10 cm

2) BESS Magnet, outer radius: 45.16 cm, inner radius: 44.81 cm, very thin material
   with magnet = 0.8 Tesla

   inside Magnet contains: tracker of silicon detector,
   5 layers of silicon, thickness of each: 300 um, sensor width: 2mm

3) TOF below Magnet

4) Sampling calorimeter: absorber: Pb (thickness 10 cm), plastic scintillator

v1.
v2. Save information in root file with 1 ntuple, calling in EventAction class
v3. Modify code of detector construction, every sub-detector defined with own functions.
    Save information in root file with 1 ntuple, calling in EventAction class
    using RootSaver class (to store as ROOT style: Branch....)

