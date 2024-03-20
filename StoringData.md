## Storing the Data
All code is stored in git, but input data is not tracked
Execute the following commands in powershell to zip data:

powershell Compress-Archive -Path "base/data, nuts2/data, nuts3/data, muni/data" -DestinationPath "Balmorel_branch_version.zip"

## Unzipping the Data on HPC
Use the following command to unzip - -qq disables logging output, -o overwrites existing files 
unzip -qq -o Balmorel_branch_version.zip

If unzipping the data file on a HPC, you may need to ensure writing capabilities on the extracted files by doing the following commands on the extracted folders: 
chmod -R +x data
chmod -R +x Pre-Processing
chmod -R +x input

Otherwise, these files will not be editable, which is needed in the framework