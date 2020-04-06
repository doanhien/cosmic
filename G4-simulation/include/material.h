#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#define HYDROGEN    "Hydrogen"
#define HYDROGEN_N   1
#define HYDROGEN_A   1.01*g/mole
#define HYDROGEN_Z   1.
#define HYDROGEN_D   0.071*g/cm3
#define HYDROGEN_R   865.

#define DEUTERIUM   "Deuterium"
#define DEUTERIUM_N  2
#define DEUTERIUM_A  2.01*g/mole
#define DEUTERIUM_Z  1.
#define DEUTERIUM_D  0.162*g/cm3
#define DEUTERIUM_R  757.

#define HELIUM      "Helium"
#define HELIUM_N     3
#define HELIUM_A     4.*g/mole
#define HELIUM_Z     2.
#define HELIUM_D     0.125*g/cm3
#define HELIUM_R     755.

#define LITHIUM     "Lithium"  
#define LITHIUM_N    4
#define LITHIUM_A    6.94*g/mole
#define LITHIUM_Z    3.
#define LITHIUM_D    0.534*g/cm3
#define LITHIUM_R    155.

#define BERYLIUM    "Berylium"
#define BERYLIUM_N   5
#define BERYLIUM_A   9.01*g/mole
#define BERYLIUM_Z   4.
#define BERYLIUM_D   1.848*g/cm3
#define BERYLIUM_R   35.3

#define CARBON      "Carbon"
#define CARBON_N     6
#define CARBON_A     12.01*g/mole
#define CARBON_Z     6.
#define CARBON_D     2.265*g/cm3
#define CARBON_R     18.8

#define NITROGEN    "Nitrogen"
#define NITROGEN_N   7
#define NITROGEN_A   14.01*g/mole
#define NITROGEN_Z   7.
#define NITROGEN_D   0.808*g/cm3
#define NITROGEN_R   44.5

#define NEON        "Neon"
#define NEON_M       8
#define NEON_A       20.18*g/mole
#define NEON_Z       10.
#define NEON_D       1.207*g/cm3
#define NEON_R       24.

#define ALUMINIUM   "Aluminium"
#define ALUMINIUM_N  9 
#define ALUMINIUM_A  26.98*g/mole
#define ALUMINIUM_Z  13.
#define ALUMINIUM_D  2.7*g/cm3
#define ALUMINIUM_R  8.9

#define IRON        "Iron"
#define IRON_N       10
#define IRON_A       55.85*g/mole
#define IRON_Z       26.
#define IRON_D       7.87*g/cm3
#define IRON_R       1.76

#define COPPER      "Copper"
#define COPPER_N     11
#define COPPER_A     63.54*g/mole
#define COPPER_Z     29.
#define COPPER_D     8.96*g/cm3
#define COPPER_R     1.43
    
#define TUNGSTEN    "Tungsten"
#define TUNGSTEN_N   12
#define TUNGSTEN_A   183.85*g/mole
#define TUNGSTEN_Z   74.
#define TUNGSTEN_D   19.3*g/cm3
#define TUNGSTEN_R   0.35

#define LEAD        "Lead"
#define LEAD_N       13
#define LEAD_A       207.19*g/mole
#define LEAD_Z       82.
#define LEAD_D       11.35*g/cm3
#define LEAD_R       0.56

#define URANIUM     "Uranium"
#define URANIUM_N    14
#define URANIUM_A    238.03*g/mole
#define URANIUM_Z    92.
#define URANIUM_D    18.95*g/cm3
#define URANIUM_R    0.32

#define AIR         "Air"
#define AIR_N        15
#define AIR_A        14.61*g/mole
#define AIR_Z        7.3
#define AIR_D        1.205e-3*g/cm3
#define AIR_R        30423

#define VACUUM      "Vacuum" 
#define VACUUM_N     16
#define VACUUM_D     1e-16*g/cm3
#define VACUUM_NC    0

#define MYLAR       "Mylar"
#define MYLAR_N      24
#define MYLAR_D      1.52*g/cm3
#define MYLAR_NC     3
#define MYLAR_ATOM_C 5
#define MYLAR_ATOM_H 4
#define MYLAR_ATOM_O 2

#define MAGCND      "MagConductor"
#define MAGCND_N     23
#define MAGCND_D     3.952*g/cm3
#define MAGCND_NC    7
#define MAGCND_ATOM_NB 0.1012
#define MAGCND_ATOM_TI 0.1012
#define MAGCND_ATOM_CU 0.2495
#define MAGCND_ATOM_AL 0.4993
#define MAGCND_ATOM_C  0.0305
#define MAGCND_ATOM_H  0.00205
#define MAGCND_ATOM_O  0.0162

#define ZYLON       "Zylon"
#define ZYLON_N      51
#define ZYLON_D      1.36*g/cm3
#define ZYLON_NC     4
#define ZYLON_ATOM_C 14
#define ZYLON_ATOM_H 6
#define ZYLON_ATOM_O 2
#define ZYLON_ATOM_N 2

#define ROHACELL    "RohaCell"
#define ROHACELL_N   52
#define ROHACELL_D   0.032
#define ROHACELL_NC  4
#define ROHACELL_ATOM_C 8
#define ROHACELL_ATOM_O 11
#define ROHACELL_ATOM_H 2
#define ROHACELL_ATOM_N 1

#define SCINTI      "Scintilator"
#define SCINTI_N     17
#define SCINTI_D     1.032*g/cm3
#define SCINTI_NC    2
#define SCINTI_ATOM_C 1
#define SCINTI_ATOM_H 1

#define IDCGAS      "IDCGas"
#define IDCGAS_N     19
#define IDCGAS_D     0.001977*0.90*g/cm3
#define IDCGAS_D_P2  0.001977*0.837*g/cm3
#define IDCGAS_NC    2
#define IDCGAS_ATOM_C 1
#define IDCGAS_ATOM_O 2

#define GFRPG10         "GFRPG10"
#define GFRPG10_N        34
#define GFRPG10_D        1.87*g/cm3
#define GFRPG10_NC       4
#define GFRPG10_ATOM_C   0.4518
#define GFRPG10_ATOM_H   0.0426
#define GFRPG10_ATOM_O   0.1056
#define GFRPG10_ATOM_Si  0.4

#define GLUE            "Glue"
#define GLUE_N           25
#define GLUE_D           1.2*g/cm3
#define GLUE_NC          3
#define GLUE_ATOM_C      57
#define GLUE_ATOM_H      64
#define GLUE_ATOM_O      10

#define AIREXULTEM      "Airexultem"
#define AIREXULTEM_N     35
#define AIREXULTEM_D     0.06*g/cm3
#define AIREXULTEM_NC    4 
#define AIREXULTEM_ATOM_C 37
#define AIREXULTEM_ATOM_H 24
#define AIREXULTEM_ATOM_O 6
#define AIREXULTEM_ATOM_N 2

#define CARBONFORM      "Carbonform"
#define CARBONFORM_N     50
#define CARBONFORM_D     1.42*g/cm3
#define CARBONFORM_NC    3
#define CARBONFORM_ATOM_C 169
#define CARBONFORM_ATOM_H 64
#define CARBONFORM_ATOM_O 10

#define GATHERFORM      "Gatherform"
#define GATHERFORM_N     47
#define GATHERFORM_D     0.1722*g/cm3
#define GATHERFORM_NC    2
#define GATHERFORM_ATOM_C 8
#define GATHERFORM_ATOM_H 8

#define STYROFORM      "Styroform"
#define STYROFORM_D     0.032*g/cm3
#define STYROFORM_NC    4
#define STYROFORM_ATOM_C 4 
#define STYROFORM_ATOM_H 8
#define STYROFORM_ATOM_N 6
#define STYROFORM_ATOM_O 1

#define POLYETHYLENE    "Polyethylene"
#define POLYETHYLENE_N   30
#define POLYETHYLENE_D   0.95*g/cm3
#define POLYETHYLENE_NC  2
#define POLYETHYLENE_ATOM_C 1
#define POLYETHYLENE_ATOM_H 2

#define AGELM       "Aeogel"
#define AGELM_N      33
#define AGELM_D      (1.02-1.0)/0.258*g/cm3
#define AGELM_NC     2
#define AGELM_ATOM_SI 1 
#define AGELM_ATOM_O  2




#endif
