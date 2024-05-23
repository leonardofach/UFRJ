#########################################################################################
# Scientific initiation project
# PADS - Analog and Digital Signal Processing Laboratory
# Theme: Optimization of the MOSFET transistors of an operational amplifier
# Advisor: Fernando A. P. Baruqui
#
# By: Leonardo Fachetti Jovêncio
# Date: 20-05-2024
# File: main.py
# Description: Genetic algorithm test program.
#########################################################################################

from genetic_algorithm import GeneticAlgorithm


# AMPOP target specifications -> type list [spec 0, spec 1, ..., spec N-1]
THD_alvo=0.2/100
MF_alvo=45
GBW_alvo=60e6
Av_dc_alvo=5e3
ft_alvo=5e6
SR_alvo=40e6
Area_alvo=300e-12
custo_alvo=0

# Limits of interest for AMPOP parameters
# type  dic = {"P0":[scale, min, max], "P1":[scale, min, max], ..., "PN-1":[scale, min, max]}
# order dic = {"P0":Wd, "P1":Ld, "P2":Wn, "P3":Ln, "P4":Wp, "P5":Lp, "P6":Ib, "P7":M, "P8":Cz, "P9":Rz}
Wd_min=0.5e-6
Wd_max=200e-6
Wn_min=0.5e-6
Wn_max=100e-6
Wp_min=0.5e-6
Wp_max=100e-6
Ld_min=0.5e-6
Ld_max=10e-6
Ln_min=0.5e-6
Ln_max=5e-6
Lp_min=0.5e-6
Lp_max=5e-6
Ib_min=1e-6
Ib_max=500e-6
M_min=1
M_max=50
Cz_min=0.1e-12
Cz_max=2e-12
Rz_min=100
Rz_max=100e3

# Debug messages
# type=0  –> Don’t show anything
# type=1  –> Show all
# type=2  –> Show population of the 1st generation
# type=3  –> Show selected individuals
# type=4  –> Show reproductions
# type=5  –> Show mutations
# type=6  –> Show resulting population
debug_type = 4

#########################################################################################
# Start of the genetic algorithm
#########################################################################################

# Defining algorithm parameters
mutation_rate = 0.05
selection_rate = 0.8
precision = 2
specifications = [THD_alvo, MF_alvo, GBW_alvo, Av_dc_alvo, ft_alvo, SR_alvo, Area_alvo, custo_alvo]

parameters = {"P0":[10**-6, Wd_min, Wd_max], "P1":[10**-6, Ld_min, Ld_max], "P2":[10**-6, Wn_min, Wn_max], 
              "P3":[10**-6, Ln_min, Ln_max], "P4":[10**-6, Wp_min, Wp_max], "P5":[10**-6, Lp_min, Lp_max], 
              "P6":[10**-6, Ib_min, Ib_max], "P7":[10, M_min, M_max],       "P8":[10**-12, Cz_min, Cz_max], 
              "P9":[10*3, Rz_min, Rz_max]}

# Instantiating a GeneticAlgorithm class object and generating the initial population
genetic_algorithm = GeneticAlgorithm (mutation_rate, selection_rate, specifications, parameters, precision)
genetic_algorithm.GenerateInitialPopulation ()
population = genetic_algorithm.getPopulation ()

# Show population of the 1st generation
if (debug_type in [1, 2]):
    print ("\n" + 160*"*")
    print (60*" " + "1ST GENERATION POPULATION")
    print (160*"*")
    print (f"\nTa = {genetic_algorithm.getSelectionRate ()} ")
    print (f"M >= (1+Ta)/Ta^2 = {genetic_algorithm.getPopulationSize ()}\n")
    print (160*"*")
    print ("\nChromosome shape : dic = {G0:[Wd, Ld], G1:[Wn, Ln], G2:[Wp, Lp], G3:[Ib], G4:[M], G5:[Cz, Rz]}\n")
    print (160*"*")
    for i in population:
        print (f"\nId individual: {population[i].getId ()}")
        print (f"chromosome: {population[i].chromosome}")
        print (f"Cost: {population[i].cost}")
        print ("\n" + 160*"-")
if (debug_type == 2):
    exit ()

# Selecting the best individuals - those with the lowest cost
selected_ind = genetic_algorithm.SelectIndividuals ()

if (debug_type in [1, 3]):
    population = genetic_algorithm.getPopulation ()
    print ("\n" + 160*"*")
    print (70*" " + "SELECTED INDIVIDUALS")
    print (160*"*")
    print (f"\nTa = {genetic_algorithm.getSelectionRate ()} ")
    print (f"M >= (1+Ta)/Ta^2 = {genetic_algorithm.getPopulationSize ()}")
    print (f"N = Ta.M = {len (selected_ind)}\n")
    print (160*"*")
    for i in selected_ind:
        print (f"\nId individual: {population[i].getId ()}")
        print (f"chromosome: {population[i].chromosome}")
        print (f"Cost: {population[i].cost}")
        print ("\n" + 160*"-")
if (debug_type == 3):
    exit ()

# Performing the reproductions
maps, children = genetic_algorithm.Crossover (selected_ind)

if (debug_type in [1, 4]):
    print ("\n" + 160*"*")
    print (70*" " + "CROSSOVERS")
    print (160*"*")
    print (f"\nTa = {genetic_algorithm.getSelectionRate ()} ")
    print (f"M >= (1+Ta)/Ta^2 = {genetic_algorithm.getPopulationSize ()}")
    print (f"N = Ta.M = {len (selected_ind)}")
    print (f"\nNumber of crossovers = M/2 = {len (maps)}\n")
    count = 0
    for i in range (0, len (maps)):
        if (count == len (selected_ind)):
            print ("\n")
            count = 0
        print (maps[i])
        count += 1
    
    #print (children)