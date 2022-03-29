# WS_correlations

Creates scatter plots that show the correlations between hourly wind speeds, electricity prices and on-shore wind generation. 

# The following softwares are required to run the script:
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

	1. Place the price csv input files in the right folder and name them: 
		- folder: "./input/results/{market}/"
		- file name price: {price}_{scenario}_{year}_{subset}.csv
		with:
		--> market: the market of the run (e.g. 'DayAhead', 'Balancing', 'Investment', 'FullYear')
		--> price: name of variable showing the hourly electricity prices (e.g. 'PriceElectricityHourly')
		--> production: name of variable showing the hourly production(e.g. 'ProductionHourly')
		--> scenario: the scenario of the run
		--> year: the year (or years, or 'all') of the run
		--> subset: subset (e.g. 'full').
	
	2. Open PriceDurationCurve.ipynb and run the code. 

# Authors
- Martijn Backer (for questions: marback@dtu.dk)

# Acknowledgements
- Juan Gea Bermudez

		 
