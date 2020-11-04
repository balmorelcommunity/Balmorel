User's guide for the Chartmap tool (Chartmap.ipynb).

The Chartmap tool creates maps with a (doughnut/pie/bar) chart for each region, as well as choropleth maps. 
Any variable can be displayed as long as the input files are adjusted to the input requirements (see 'required columns' in Section 2). 


********************************************************************************************************************


To do: 
1. Make sure to have all the packages from cell 1.2 of the code correctly installed.

2. Insert/update the following files in the 'input' path:
	2.1 non-Geo files
 	a) .\input\results\{input_name}_{variable}.csv
 		--> this is the file that contains the data that is to be shown on the charts
		--> with:
			--> {input_name}: name of the run
 			--> {variable}: variable of the run that needs to be shown
		--> required columns (case-sensitive)
			--> Year, Region, Scenario, Unit, Value 

	2.2 Geo files
	a) .\input\geo_files\geojson_files\ and .\input\geo_files\shapefiles\
 		--> make sure that for each region that needs to be displayed (see 2.2b), a geojson_file or shapefile is present in one of these folders. 
		--> if there is both a geojson file and shapefile for the same region, the geojson file is used. 
	b) .\input\geo_files\coordinates_RRR.csv
		--> i.e. a file with the names and coordinates of all regions/hubs + declaration whether it is a region or hub (type) and whether it should be displayed or not (Display). 
		--> adding too many regions here is allowed, too few will cause errors. 

NB: all file names can be changed in cell 1.3. Column names can be changed too in the code.  

3. Open 'Chartmap.ipynb' in Jupyter Notebook 

4. Adjust the settings in the first cell of the code
	a) calibrate 'input_name' and 'variable' with the file name of 2.1.   
	b) 'display_column': choose which column needs to be displayed
	c) 'display_variable': if the chart_type == 'choropleth, show here which variable of the display_column needs to be displayed
	d) 'year' : year to be displayed
	e) 'scenario': scenario(s) to be displayed
	f) 'hub_display': choose if the hubs need to be displayed too or not
	g) Visual options (colours, fonts, etc.)
 	h) 'chart_type': declare if you want to show a doughnut chart, pie chart, bar chart or choropleth map
	i) 'doughnut_location': #Distance of bottom-right corner of the doughnut/pie chart from the region's coordinates. Higher values shift the chart to the West (first value) and North (second value). 
	j) 'bar_location': #Distance of bottom-right corner of the bar chart from the region's coordinates. Higher values shift the chart to the West (first value) and North (second value). 
	k) 'choropleth_location': #Distance of bottom-right corner of the choropleth text from the region's coordinates. Higher values shift the chart to the West (first value) and North (second value). 
 	l) 'manual_bins': only for choropleth, declare here the bins for the choropleth. Enter in the form (for example): [0,40,80,120,160]. If left empty, 0.25 quantiles are used. 
5. Run the code. The result is an html that can be found in .\output\Transmission_Map\{subset}\{market}\...html

********************************************************************************************************************	


********************************************************************************************************************


# Authors
- Martijn Backer (for questions: marback@dtu.dk)

# Acknowledgements
- Juan Gea Bermudez
********************************************************************************************************************

		 

