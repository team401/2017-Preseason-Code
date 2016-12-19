How to add new config elements.

There are 3 steps to do this.

Step 1: Defaults list
In the file "ConfigParser.hpp" found in this directory, there is a variable commented "DEFAULTS LIST"
This variable must be populated with a key and value for each element you add.
To add an element to this list, simply insert a comma after the last insertion, go to a new line, and follow this format
make_pair("element_key_name", "element_value")

Step 2: ConfigSettings
In the file "ConfigSettings.hpp" found in this directory, there is a section commented "DECLARATIONS"
Insert into this section before the "END DECLARATIONS" a new variable with the desired type and a name
exactly matching that of your element key name.
In this same file, there is a section commented "CONSTRUCTOR ARGUMENTS"
Insert a comma after the last insertion, then go to a new line and follow this template
variable_type(declared earlier) variableName(declared earlier)_
Make sure to include the underscore at the end
In this same file, there is a section commented "CONSTRUCTOR DECLARATIONS"
Add a new line before the "END CONSTRUCTOR DECLARATIONS", and follow this template
variableName = variableName_ (again make sure to include the underscore)
In this same file, there is a section commented "ACCESSORS"
Insert a new line before the "END ACCESSORS", and follow this template
variable_type getVariableName() { return variableName; }
void setVariableName(variable_type variableName_) { variableName = variableName_; }

Step 3: Config Parser
In the file "ConfigParser.cpp" found in this directory, there is a function commented "GET SETTINGS" (should be the last function in the file)
You must tell the config parser to look for your key in this function.
To do this, add a new line before the "return" statement and use the following template
where "variableName" represents the name of the variable you set up earlier
configSettings.setVariableName(configFind<variable_type>("elementKeyName"));

Your element is now added to the parser, and will be put into the config file on the next program run
with the value you inserted in the defaults map in step 1
