#########################################################################################
# Scientific initiation project
# PADS - Analog and Digital Signal Processing Laboratory
# Theme: Optimization of the MOSFET transistors of an operational amplifier
# Advisor: Fernando A. P. Baruqui
#
# By: Leonardo Fachetti Jovêncio
# Date: 20-05-2024
# File: individual.py
# Description: Definition of the individual class.
#########################################################################################

class Individual:
    '''
    Class parameters
        . id         : Individual identifier
        . chromosome : individual's chromosome    
        . cost       : Cost of the individual returned by the cost function

    Types:
        . id         : type int
        . chromosome : type dic = {"G0":[Wd, Ld], "G1:[Wn, Ln], "G2:[Wp, Lp], "G3":[Ib], "G4":[M], "G5":[Cz, Rz]}
        . cost       : type float
    '''

    # constructor
    def __init__(self, id, chromosome, cost):   
        self.__id = id                 
        self.chromosome = chromosome  
        self.cost = cost 

    # Public methods
    def SetId (self, id):
        self.__id = id

    def getId (self):
        return self.__id