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


********************************************************************************************************************
# WS_correlations

Creates scatter plots that show the correlations between hourly wind speeds, electricity prices and on-shore wind generation. 

# The following software is required to run the script:
- python 3.7 with packages: 
	- os
	- datetime
	- glob
	- pandas
	- numpy
	- matplotlib
	- time
	- itertools
- Jupyter Notebook

# Execution

	1. Place the price and production input files in the right folder and name them: 
		- folder: "./input/results/{market}/"
		- file name price: {price}_{scenario}_{year}_{subset}.csv
		- file name production: {production}_{scenario}_{year}_{subset}.csv	
		with:
		--> market: the market of the run (e.g. 'DayAhead', 'Balancing', 'Investment', 'FullYear')
		--> price: name of variable showing the hourly electricity prices (e.g. 'PriceElectricityHourly')
		--> production: name of variable showing the hourly production(e.g. 'ProductionHourly')
		--> scenario: the scenario of the run
		--> year: the year (or years, or 'all') of the run
		--> subset: subset (e.g. 'full').
	
	2. Place the wind speed csv-files in the "./input/" folder.
	3. Place the timestep dictionary in the "./input/" folder and call it: "full_timesteps_{meaning_SSS_TTT}", 
		with: {meaning_SSS_TTT} referring to the meaning of SSS and TTT (e.g. 'DaysHours, 'WeeksHours')
 
	4. Place the dictionary containing the information about which area lies in which region in the "./input/" folder and call it: "RRRAAA.csv".

	5. In cell 2 of the code, update 'markets', 'input_price', 'input_prod', 'WS_file1', 'WS_file2' and 'WS_file3' and 'meaning_SSS_TTT' to the the markets and file names of steps 1 - 4. 
	
	6. In cell 2 of the code, select for 'regions' which regions must be displayed (e.g. ['NL', 'DK1', 'DK2'] or 'all').
	7. In cell 2 of the code, set the colors according to preference. 	
	8. In cell 2 of the code, set the name of the output folder (e.g. 'WS_correlations'). 
	
	8. In cell 10 of the code (under "Change names"), change the names of those areas are not in the wind speed files, to assign them a wind speed for every hour.  
		--> it is up to the user which wind profile has to be assigned to the areas that have none. 

	9. Run the entire code top-down ( << Kernel >>, << Restart & Run All >>, << Restart And Run All Cells >> ). 
 	10. The HTML files open automatically. Also, they are saved to: "./output/{output}/{market}/{scenario}/{year}/{output}_{scenario}_{year}_{suffix}.html". 
		--> due to display constraints, a new HTML file will be created for each 8 regions.
			--> they will be saved with the suffix defined in cell 18 of the code (last cell). 

# Authors
- Martijn Backer (for questions: marback@dtu.dk)

# Acknowledgements
- Juan Gea Bermudez
********************************************************************************************************************

		 

