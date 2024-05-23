#########################################################################################
# Scientific initiation project
# PADS - Analog and Digital Signal Processing Laboratory
# Theme: Optimization of the MOSFET transistors of an operational amplifier
# Advisor: Fernando A. P. Baruqui
#
# By: Leonardo Fachetti Jovêncio
# Date: 20-05-2024
# File: genetic_algorithm.py
# Description: Definition of the GeneticAlgorithm class.
#########################################################################################

import numpy as np
import random
from individual import Individual # Class Individual


class GeneticAlgorithm:
    '''
    Class parameters

    . num_genes      : Number of genes on an individual's chromosome                  -> type int
    . mutation_rate  : Percentage of the population that will mutate                  -> type float
    . selection_rate : Percentage of the population selected to perform reproductions -> type float
    . specifications : Target specifications to be achieved                           -> type list [spec 0, spec 1, ..., spec N-1]
    . precision      : Number of decimal places to be considered in numerical values  -> type int
    . parameters     : Parameters to be determined                                    -> type dic = {"P0":[scale, min, max], 
                                                                                                     "P1":[scale, min, max], ..., 
                                                                                                   "PN-1":[scale, min, max]}
    . Definitions:
        parameters = dict {"P0":Wd, "P1":Ld, "P2":Wn, "P3":Ln, "P4":Wp, "P5":Lp, "P6":Ib, "P7":M, "P8":Cz, "P9":Rz}
        Chromosome = dict {G0:[Wd, Ld], G1:[Wn, Ln], G2:[Wp, Lp], G3:[Ib], G4:[M], G5:[Cz, Rz]}
        population = dict {"I0":Individual, "I1":Individual, "iN-1":Individual}  ->  Individual (id, chromosome, cost)
    '''
    # constructor
    def __init__(self, mutation_rate, selection_rate, specifications, parameters, precision):
        self.__num_genes = 6
        self.__population = dict()         
        self.__mutation_rate = mutation_rate    
        self.__selection_rate = selection_rate              
        self.__specifications = specifications  
        self.__parameters = parameters
        self.__precision = precision

    # Public methods
    def getPopulation (self):
        return self.__population
    

    def getPopulationSize (self):
        return len (self.__population)
    
    
    def getSelectionRate (self):
        return self.__selection_rate


    def GenerateInitialPopulation (self):
        # This method generates the initial population
        
        individuals_number = int (np.ceil ((1 + self.__selection_rate) / self.__selection_rate**2))

        for id in range (0, individuals_number):
            '''Building the individual's chromosome
                type dic = {"G0":[genes0], "G1:[genes1], ..., "GN-1":[genesN-1]}
                     dic = {"G0":[Wd, Ld], "G1:[Wn, Ln], "G2:[Wp, Lp], "G3":[Ib], "G4":[M], "G5":[Cz, Rz]}
            '''
            for g in range (0, self.__num_genes):
                if (g == 0):    # [Wd, Ld]
                    Wd = self.__DrawValue (self.__parameters["P0"], 1, self.__precision)   # "P0":Wd
                    Ld = self.__DrawValue (self.__parameters["P1"], 1, self.__precision)   # "P1":Ld

                elif (g == 1):  # [Wn, Ln]
                    Wn = self.__DrawValue (self.__parameters["P2"], 1, self.__precision)   # "P2":Wn
                    Ln = self.__DrawValue (self.__parameters["P3"], 1, self.__precision)   # "P3":Wn

                elif (g == 2):  # [Wp, Lp]
                    Wp = self.__DrawValue (self.__parameters["P4"], 1, self.__precision)   # "P4":Wp
                    Lp = self.__DrawValue (self.__parameters["P5"], 1, self.__precision)   # "P5":Wp

                elif (g == 3):  # [Ib]
                    Ib = self.__DrawValue (self.__parameters["P6"], 1, self.__precision)   # "P6":Ib

                elif (g == 4):  # [M]
                    Mp = int (self.__DrawValue (self.__parameters["P7"], 1, self.__precision))   # "P7":M  -> just int

                elif (g == 5):  # [Cz, Rz]
                    Cz = self.__DrawValue (self.__parameters["P8"], 1, self.__precision)   # "P8":Cz
                    Rz = self.__DrawValue (self.__parameters["P9"], 1, self.__precision)   # "P9":Rz

            chromosome = {"G0":[Wd, Ld], "G1":[Wn, Ln], "G2":[Wp, Lp], "G3":[Ib], "G4":[Mp], "G5":[Cz, Rz]}
            individual = Individual (id, chromosome, -1)
            self.__population[f"I{id}"] = individual


    def SelectIndividuals (self):
        # This method selects the best individuals in the population – those with the lowest cost – to reproduce later

        # Calculating the cost of each individual in the population
        self.__ComputeCosts ()

        # Ordering individuals in the population from lowest to highest cost
        ordained_ind = list (dict ((sorted (self.__population.items (), key=lambda item: item[1].cost))).keys ())
        
        # Selecting the best individuals according to the selection rate
        N = int (np.ceil (self.__selection_rate * self.getPopulationSize ()))

        return ordained_ind[0:N]
    

    def Crossover (self, selected_individuals):
        # This method performs the crossovers

        maps = self.__GenerateMaps (selected_individuals)

        children = []
        for c in range (0, len (maps)):
            indiv_1 = selected_individuals[maps[c][0]]
            indiv_2 = selected_individuals[maps[c][1]]

            # Sorting the gene to be combined in the crossover
            drawn_gene = random.choice (list (range (0, self.__num_genes, 1)))

            genes_indiv_1 = self.__population[indiv_1].chromosome[f"G{drawn_gene}"]
            genes_indiv_2 = self.__population[indiv_2].chromosome[f"G{drawn_gene}"]

            avg_genes = []
            for g in range (0, len (genes_indiv_1)):
                avg_genes.append ((genes_indiv_1[g] + genes_indiv_2[g]) / 2)
            
            # Generating children
            chromosome_children_1 = self.__population[indiv_1].chromosome.copy ()
            chromosome_children_1[f"G{drawn_gene}"] = avg_genes
            chromosome_children_2 = self.__population[indiv_2].chromosome.copy ()
            chromosome_children_2[f"G{drawn_gene}"] = avg_genes

            children_1 = Individual (c, chromosome_children_1, -1)
            children_2 = Individual (c + 1, chromosome_children_1, -1)

            children.append (children_1)
            children.append (children_2)

        return maps, children


    # Private methods
    def __RoundNumber (self, number, scale, precision):
        # This method rounds a numerical value from a given scale to a given level of precision
        # Ex: number=0.17823e-6 / scale=e-6 / precision=2 | output=0.18e-6
        # Ex: number=0.17823e-5 / scale=e-6 / precision=2 | output=1.78e-6
        # Ex: number=0.08539e-8 / scale=e-9 / precision=2 | output=0.86e-9
        
        if (scale == 10**-6):  # micro scale
            return round (number, 6 + precision)
        
        elif (scale == 10**-9):  # nano scale
            return round (number, 9 + precision)
        
        elif (scale == 10**-12):  # pico scale
            return round (number, 12 + precision)
        else:                     # others
            return round (number, 2)
            

    def __DrawValue (self, parameter, type_draw, precision):
        # This method randomly draws a value for a given parameter.
        # . parameter : Parameter to be drawn                     -> type list : [scale, min, max]
        # . type_draw : Type of draw to be used                   -> type int  : 0=gaussian / 1=uniform
        # . precision : Number of decimal places to be considered -> type int
        
        if (type_draw == 0):
            x = np.random.uniform (parameter[2], parameter[1])

        elif (type_draw == 1):
            average = (parameter[2] - parameter[1])/2
            sigma = (parameter[2] - average)/3
            x = np.random.normal (average, sigma, size=None)

        # Arredondando para o numero de casas decimais desejado
        return self.__RoundNumber (x, parameter[0], precision)
        

    def __ComputeCosts (self):
        # This method calculates the cost of each individual in the population
        for i in self.__population:
            self.__population[i].cost = (round (np.random.uniform (0, 1), 4))


    def __GenerateMaps (self, selected_individuals):
        '''This method maps the crossovers to be carried out
        The selected_individuals parameter received as an argument is a list containing the keys of
        the selected individuals ordered by the lowest costs'''

        M = len (self.__population)
        N = len (selected_individuals)
        n_crossovers = int (np.ceil (M / 2))

        rotations = int (np.ceil (1 / (2 * self.__selection_rate)))

        maps = []
        indiv_2 = 1
        # Performing rotations
        for r in range (0, rotations):
            for i in range (0, N):
                if (indiv_2 == N):
                    indiv_2 = 0
                maps.append ([i, indiv_2])
                indiv_2 += 1
            indiv_2 += 1

        return maps[0:n_crossovers]
