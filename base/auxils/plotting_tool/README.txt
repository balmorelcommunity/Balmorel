INSTRUCTIONS:


********************************************************************************************************************
Transmission_Map.ipynb

To do: 
1. Install Jupyter Notebook and the following packages:
	- pandas
	- numpy
	- folium
	- json

2. Insert/update the following files in the 'input' path:
	a) .\input\results\{market}: CapacityGeneration_{scenario}_{year}_{subset}.csv
	b) .\input\results\{market}: CapacityPowerTransmission_{scenario}_{year}_{subset}.csv
	c) .\input\results\{market}: FlowElectricityHourly_{scenario}_{year}_{subset}.csv
		with:
		--> market: the market of the run (e.g. 'DayAhead', 'Balancing', 'Investment', 'FullYear')
		--> scenario: the scenario of the run
		--> year: the year (or years, or 'all') of the run
		--> subset: subset (e.g. 'full')

	d) .\input\transmission_files: coordinates_RRR.csv
		--> i.e. a file with the names and coordinates of all regions/hubs + declaration whether it is a region or hub. 
		--> adding too many regions here is allowed, too few will cause errors. 

3. Open 'Transmission_Map.ipynb' in Jupyter Notebook 

4. Adjust the settings in the first cell of the code
	a) calibrate 'market', 'SCENARIO', 'YEAR' and 'SUBSET' with the file names of step 2.  
	b) 'year': which year needs to be displayed
	c) 'LINES': choose to display either i) the line capacities, ii) single-coloured electricity flows at a certain timestep or iii) electricity flows with a different colour at congested lines.
	d) 'exo_end' (only if'LINES'= 'Capacity' or 'LINES'='CongestionFlow'): display endogenous, exogenous or total capacity. 
	e) 'S' (only if'LINES'= Flow' or 'LINES'='CongestionFlow': Season to be displayed
	e) 'T' (only if'LINES'= Flow' or 'LINES'='CongestionFlow': Timestep to be displayed
	f) Visual options (colours, fonts, etc.)
		--> NB: if 'flowline_colour' is changed, the user must change legend colours as well in the cell under "Add Legend": lines 43-45
********************************************************************************************************************	
