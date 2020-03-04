# Eclipse LaunchConfig

## External Tools: Launch Config
- Open the "External Tools Configurations" dialog.
- Open the "Common" tab.
- Select the "Shared file" radio button and enter a path for the location of the configuration file.

For AntBuild, the Buildfile is the ant file to be run when the tool is launched. The input parameters are from the Arguments with -Dxxx="{string-prompt: label}" (Prompt for string input).

Eclipse will store your External Tools Configuration in the file you specified. 
You can use this file in another instance of Eclipse to load the configuration. 
Add the 'your tool configuration'.launch file you created to the root of your destination project.
The next time you refresh the project, Eclipse will load the configurations.
