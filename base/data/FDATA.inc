* File FDATA.inc                                                                                                                                                                                    
                                                                                                                                                                                                    
* This file is part of the Balmorel model, version 2.11 Alpha (April 2004).                                                                                                                         
* For CO2 see http://acm.eionet.europa.eu/docs/ETCACC_TechnPaper_2003_10_CO2_EF_fuels.pdf                                                                                                           
*------------------------------------------------------------------------------                                                                                                                     
                                                                                                                                                                                                    
* PARAMETER FDATA contains information about emission characteristics of fuels.                                                                                                                     
                                                                                                                                                                                                    
* In addition it contains a name (FDACRONYM) for the fuel, note that this must be as an ACRONYM previously.                                                                                         
* Presnetly it also contains a numerical code identication of the individual fuels,                                                                                                                 
* however, this may become invalid, so you shold use only the FDACRONYM.                                                                                                                            
                                                                                                                                                                                                    
                                                                                                                                                                                                    
TABLE FDATA(FFF,FDATASET)   'Fuel specific values'                                                                                                                                                  
* Merge biofuel-related fuels?                                                                                                                                                                      
                                                                                                            FDACRONYM          FDNB    FDCO2   FDSO2       FDN2O         !!             FDCO2       
*                                                                                                           Units                      kg/GJ   kg/GJ       kg/GJ                                    
NUCLEAR                                                                                                     NUCLEAR            1       0       0           0                                        
NATGAS                                                                                                      NATGAS             2       56.1    0           0.001                                    
COAL                                                                                                        COAL               3       94.6    0.714       0.003                                    
LIGNITE                                                                                                     LIGNITE            4       111.1   1.428       0.003                                    
FUELOIL                                                                                                     FUELOIL            5       74      0.446       0.002                                    
LIGHTOIL                                                                                                    LIGHTOIL           6       74      0.023       0.002                                    
HEAVYFUELOIL                                                                                                HEAVYFUELOIL       7       77.4                                                         
ORIMULSION                                                                                                  ORIMULSION         8       80      1.337       0.002                                    
SHALE                                                                                                       SHALE              9       102     1.428       0.003                                    
PEAT                                                                                                        PEAT               10      107     0.24        0.003         !!             kvotepålagt?
MUNIWASTE                                                                                                   MUNIWASTE          11      0       0.156       0.004         !!             19          
STRAW                                                                                                       STRAW              12      0       0.025       0.004                                    
WOOD                                                                                                        WOOD               13      0       0.025       0.004                                    
WOODCHIPS                                                                                                   WOODCHIPS          14                                                                   
DRYWOODCHIPS                                                                                                DRYWOODCHIPS       15                                                                   
RECYCLEDWOOD                                                                                                RECYCLEDWOOD       16                                                                   
WOODPELLETS                                                                                                 WOODPELLETS        17                                                                   
WOODWASTE                                                                                                   WOODWASTE          18      0       0.025       0.004                                    
BIOOIL                                                                                                      BIOOIL             19      0       0.025       0.004                                    
LNG                                                                                                         LNG                20      56.1    0           0.001                                    
LPG                                                                                                         LPG                21      63.1                                                         
BIOGAS                                                                                                      BIOGAS             22      0       0.025       0.004                                    
OTHERGAS                                                                                                    OTHERGAS           23      66.7                                                         
WASTEHEAT                                                                                                   WASTEHEAT          24      0       0           0                                        
WIND                                                                                                        WIND               25      0       0           0                                        
WATER                                                                                                       WATER              26      0       0           0                                        
SUN                                                                                                         SUN                27      0       0           0                                        
ELECTRIC                                                                                                    ELECTRIC           28      0       0           0                                        
WATERRES                                                                                                    WATERRES           29      0       0           0                                        
HEAT                                                                                                        HEAT                                                                                    
THERMGAS                                                                                                    THERMGAS                   0                                                            
DUMMY                                                                                                       DUMMY              30      0       0           0                                        
COAL_EXETS                                                                                                  COAL_EXETS         31              0.714       0.003                                    
NATGAS_EXETS                                                                                                NATGAS_EXETS       32              0           0.001                                    
FUELOIL_EXETS                                                                                               FUELOIL_EXETS      33              0.446       0.002                                    
LPG_EXETS                                                                                                   LPG_EXETS          34                                                                   
HEAVYFUELOIL_EXETS                                                                                          HEAVYFUELOIL_EXETS 35                                                                   
COKE                                                                                                        COKE               36      106     1.428       0.003                                    
RETORTGAS                                                                                                   RETORTGAS          37      56.8    0           0.001                                    
;                                                                                                                                                                                                   
                                                                                                                                                                                                    
TABLE CO2FACTOR(FFF,CCC)                                                                                                                                                                            
                                                                                                            DENMARK            FINLAND GERMANY NETHERLANDS NORWAY SWEDEN UNITED_KINGDOM             
NUCLEAR                                                                                                                                                                                             
NATGAS                                                                                                      57.3                       56                         56.5   58.3                       
COAL                                                                                                        95                         86.7    96.7                                                 
LIGNITE                                                                                                                                                                                             
FUELOIL                                                                                                                                                                                             
LIGHTOIL                                                                                                                                                                                            
HEAVYFUELOIL                                                                                                                                                                                        
ORIMULSION                                                                                                                                                                                          
SHALE                                                                                                                                                                                               
PEAT                                                                                                                                                                                                
MUNIWASTE                                                                                                                                                                                           
STRAW                                                                                                                                                                                               
WOOD                                                                                                                                                                                                
WOODCHIPS                                                                                                                                                                                           
DRYWOODCHIPS                                                                                                                                                                                        
RECYCLEDWOOD                                                                                                                                                                                        
WOODPELLETS                                                                                                                                                                                         
WOODWASTE                                                                                                                                                                                           
BIOOIL                                                                                                                                                                                              
LPG                                                                                                                                                                                                 
BIOGAS                                                                                                                                                                                              
OTHERGAS                                                                                                                                                                                            
WASTEHEAT                                                                                                                                                                                           
WIND                                                                                                                                                                                                
WATER                                                                                                                                                                                               
SUN                                                                                                                                                                                                 
ELECTRIC                                                                                                                                                                                            
WATERRES                                                                                                                                                                                            
HEAT                                                                                                                                                                                                
THERMGAS                                                                                                                                                                                            
DUMMY                                                                                                                                                                                               
COAL_EXETS                                                                                                                                                                                          
NATGAS_EXETS                                                                                                                                                                                        
FUELOIL_EXETS                                                                                                                                                                                       
LPG_EXETS                                                                                                                                                                                           
HEAVYFUELOIL_EXETS                                                                                                                                                                                  
COKE                                                                                                                                                                                                
RETORTGAS                                                                                                                                                                                           
;                                                                                                                                                                                                   
