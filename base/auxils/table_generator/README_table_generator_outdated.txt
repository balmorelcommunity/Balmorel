
Steps
1) Place gdx-files that need to be read in the '.\input\results\' directory in the folder of the right market. 

2) For each variable, create an Excel file named 'settings_' + variable name + '.xlsx' in the '.\input\settings\' directory. 
   If there is no settings file for a certain variable, a table is returned that has all scenarios appended.  

3) In every settings Excel file, create a separate sheet for each variable (sheet names are not important). The condition types are:

	Condition types (NB: capital-sensitive)
	Single:
	- List_condition
	- Dict_condition
	- na_condition
	Double:
	- List_list_condition
	- Dict_list_condition
	- na_list_condition
	- na_dict_condition

-----------------------------------------
	Single:
	- List_condition: if column_in (row 0) is in list (row 1), column_out (row 2) changes to part after outcome  (row 3). In outcome column, write:
			--> 'string_' to display outcome value (e.g. 'string_Denmark' will display 'Denmark')
			--> 'column_' to display the value in the table under that column (e.g. 'column_Country' will display 'Denmark' if this is the value in that row in column 'Country')
	- Dict_condition: if column_in (row 0) is in list (row 1), column_out (row 2) changes to corresponding value in outcome list (row 3). In outcome column, write:
			--> 'dict_' to indicate that the value has to be read as part of a dictionary (i.e. when the key of column_in applies, the outcome is the corresponding 'dict_' value. 
			--> 'string_' to indicate that this string needs to be added to every outcome. 
	- na_condition: if column_out (row 0) is NA, column_out (row 0) changes to outcome (row 1).
	
	Double:
	- List_list_condition: if column_in1 (row 0) is in list1 (row 1) and column_in2 (row 2) is in list2 (row 3), column_out (row 4) changes to outcome (row 5).
	- Dict_list_condition: if column_in1 (row 0) is in list1 (row 1) and column_in2 (row 2) is in list2 (row 3), column_out (row 4) changes to corresponding value in outcome list (row 5).
	- na_list_condition: if column_out (row 2) is NA and column_in (row 0) is in list (row 1), column_out (row 2) changes to outcome (row 3). 
	- na_dict_condition: if column_out (row 2) is NA and column_in (row 0) is in list (row 1), column_out (row 2) changes to corresponding value in outcome list (row 3). 


If multiple outcome values apply, they are concatenated. 
 
*for all na_conditions, column_out has to be an existing column (otherwise it cannot have NA values).  

4) Write the desired column names in the './input/Dict_column_names.csv' file. 

5) Declare which variables need to be processed in the './input/include.csv' file [YES/NO]. 

6) Open 'Table_generator.ipynb'. 

7) In cell "1.2 User Inputs", state the GAMS directory, market to analyze and output names for the CSV files. 
   Also, state if the output type should be CSV files, one Excel file (with multiple sheets), or both. 

8) Run the code. 

9) The output CSV files and/or Excel file appear in the './output/' directory. 