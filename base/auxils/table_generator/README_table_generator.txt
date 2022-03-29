
Steps
1) Place gdx-files that need to be read in the '.\input\results\{market}' directory in the folder of the right market.
   Call the gdx file: '*_{scenario}_{year}_{subset}, e.g. 'MainResults_P2X_2045_all', with:
	- {market}: market run, e.g. 'DayAhead', 'FullYear', 'Investment', 'Balancing'
	- {scenario}: scenario of the run
	- {year}: the year/years that is/are simulated in the run
	- {subset}: the subset of the run that is analyzed 


2) Declare which variables need to be processed in the './input/include.csv' file [YES/NO]. 

3) For each variable that is used ('YES' in step 2), create an Excel file named 'settings_{variable}.xlsx' in the '.\input\settings\' directory. 
   If there is no settings file for a certain variable (with 'YES'in step 2), a table is returned that has all scenarios appended.  

4) In every settings Excel file, create a separate sheet for each grouping condition (sheet names are not important), with the following columns:
	- 'Fields_in': contains the field(s) on which the new field is based
	- 'Keys': list of values that the 'Fields_in' fields must be in, in order to be used in the new field
	- 'Field_out': the name of the new field
	- 'Values': the value that the new field gets in all rows where the value of 'Fields_in' is in 'Keys'. 
	- 'nan_option': 'field', 'string', or leave empty. 
 		--> If 'field', all nan values in the new field are filled with the value that is in the field defined at 'nan_output'.
		--> If 'string', all nan values in the new field are filled with the string defined in 'nan_output'. 
		--> If left empty, all nan values remain nan in the new field
	- 'nan_output': name of the filling field or string for nan rows
 	
	So, if the value at location [x,'Fields_in'] from the original table, is in a key of 'Keys' (from the settings Excel), 
	a new column is created with the name of 'Field_out'. The value at location [x, 'Field_out'] is then equal to the value
	in the 'Values' column (of the settings Excel) at the same row of the key in 'Keys' (of the settings Excel) that the 
	value [x, 'Fields_in'] corresponds to. 

	'Fields_in' can contain multiple values. In this case, 'Keys' need to contain concatenations of the values in 'Fields_in'. 

	This all may sound very abstract and confusing. Therefore, the reader is recommended to check out the example settings Excel file, 
	which is called 'settings_G_CAP_YCRAF.xls'. 

5) Write the desired new column names in the './input/Dict_column_names.csv' file. Only necessary if new column names are wanted. 

6) Open 'Table_generator.ipynb'. 

7) In cell "1.2 User Inputs", state whether to use gdx or csv files as input, the GAMS directory, market to analyze and output names for the CSV files. 
   Also, state if the output type should be CSV files, one Excel file (with multiple sheets), or both. 

8) Run the code. 

9) The output CSV files and/or Excel file appear in the './output/' directory. 


********************************************************************************************************************	


********************************************************************************************************************


# Author
- Martijn Backer (for questions: marback@dtu.dk)

# Acknowledgements
- Juan Gea Bermudez
********************************************************************************************************************

		 

