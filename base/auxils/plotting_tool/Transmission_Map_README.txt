User's guide for the Transmission_Map tool (Transmission_Map.ipynb). 

The Transmission_Map tool is a tool to create maps with the symbolic representation of trade between regions. 
The initial intention of the tool was to visualize electricity trade, but any trade (e.g. H2, heat, other) can be displayed. 
The tool can show the trade capacity, as well as the instantaneous trade flows and level of congestion on lines between regions. 

*********************************************************************************************************************


To do: 
1. Make sure to have all the packages from cell 1.2 of the code correctly installed.

2. Insert/update the following files in the 'input' path:
	2.1 non-Geo files
    	NB: the required files depend on the option you want to display. For example, if only 'Capacity' is displayed, files b) and d) are not required. 
	a) .\input\results\{market}: Capacity{commodity}Transmission_{scenario}_{year}_{subset}.csv
		--> required columns: Y, C, IRRRE, IRRRI, VARIABLE_CATEGORY, UNITS, Value	
			--> indicating year, country, exporting region, importing region, Exogenous/Endogenous/Decommissioning, units, value
	b) .\input\results\{market}: Flow{commodity}Hourly_{scenario}_{year}_{subset}.csv
		--> required columns: Y, C, IRRRE, IRRRI, SSS, TTT, UNITS, Val	
			--> indicating  year, country, exporting region, importing region, season, timestep, units, value
	
	if hubs are to be displayed (i.e. 'hub_display' == True):
		c) .\input\results\{market}: Capacity{commodity}Generation_{scenario}_{year}_{subset}.csv
			--> required columns: Y, C, RRR, G, UNITS, Val	
				--> indicating year, country, region, generator, units and value
		d) .\input\results\{market}: Production{commodity}Hourly_{scenario}_{year}_{subset}.csv
			--> required columns: Y, C, RRR, G, SSS, TTT, UNITS, Val	
				--> indicating year, country, region, generator, season, timestep, units and value
	with:
	--> market: the market of the run (e.g. 'DayAhead', 'Balancing', 'Investment', 'FullYear')
	--> commodity: commodity to be displayed, e.g. 'Electricity', 'H2', 'Heat', 'Coffee'
	--> scenario: the scenario of the run
	--> year: the year (or years, or 'all') of the run
	--> subset: subset (e.g. 'full')
	
	2.2 Geo files
	a) .\input\geo_files\geojson_files\ and .\input\geo_files\shapefiles\
 		--> make sure that for each region that needs to be displayed (see 2.2b), a geojson_file or shapefile is present in one of these folders. 
		--> if there is both a geojson file and shapefile for the same region, the geojson file is used. 
	b) .\input\geo_files\coordinates_RRR.csv
		--> i.e. a file with the names and coordinates of all regions/hubs + declaration whether it is a region or hub (type) and whether it should be displayed or not (Display). 
		--> adding too many regions here is allowed, too few will cause errors. 
	c) .\input\geo_files\bypass_lines.csv
 		--> if a line needs to make a turn to avoid crossing crossing a third region, this can be stated here
			in the first row:
				--> write the exporting region in IRRRE, with its coordinates under LatExp and LonExp
				--> write the importing region in IRRRI and the coordinates of the bypass point in LatImp and LonImp
 			in the second row:
				--> write the exporting region in IRRRE, and the coordinates of the bypass point in LatExp and LonExp
 				--> write the importing region in IRRRI, with its coordinates under LatImp and LonImp. 
		--> hence, if you want the bypass to apply both ways, you need 4 rows. 
 	if hubs are to be displayed (i.e. 'hub_display' == True): 
		d) \input\geo_files\hub_technologies.csv
			--> file with the names of the hub_technologies
			--> required column: hub_name

NB: all file names can be changed in cell 1.3. Column names can be changed too in the code.  

3. Open 'Transmission_Map.ipynb' in Jupyter Notebook 

4. Adjust the settings in the first cell of the code
	a) calibrate 'market', 'COMMODITY', 'SCENARIO', 'YEAR' and 'SUBSET' with the file names of step 2.1.  
	b) 'year': which year needs to be displayed
	c) 'LINES': choose to display either i) the line capacities, ii) single-coloured electricity flows at a certain timestep or iii) electricity flows with a different colour at congested lines.
	d) 'exo_end' (only if'LINES'== 'Capacity' or 'LINES'=='CongestionFlow'): display endogenous, exogenous or total capacity. 
	e) 'S' (only if'LINES'== Flow' or 'LINES'=='CongestionFlow': Season to be displayed
	f) 'T' (only if'LINES'== Flow' or 'LINES'=='CongestionFlow': Timestep to be displayed
    g) set 'hubs' options. 
	g) Visual options (colours, fonts, etc.)

5. Run the code. The result is an html that can be found in .\output\Transmission_Map\{commodity}\{lines}\{scenario}\{market}\...html

********************************************************************************************************************	


********************************************************************************************************************


# Author
- Martijn Backer (marback@dtu.dk)

# Acknowledgements
- Juan Gea Bermudez
- Matti Koivisto
********************************************************************************************************************

		 

