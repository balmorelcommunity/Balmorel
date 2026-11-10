# Installation
A [GAMS](https://gams.com/) installation and license is required to run Balmorel. We also recommend installing [git](https://git-scm.com/) to do version control on your Balmorel project.

## Downloading Balmorel Framework and Data
The Balmorel framework can be downloaded from [GitHub](https://github.com/balmorelcommunity/Balmorel) as a .zip file by pressing Code -> Download ZIP.
The corresponding data is in another [GitHub repository](https://github.com/balmorelcommunity/Balmorel_data), and can also be downloaded as a .zip. Place the Balmorel_data folder in Balmorel/base and rename it to "data". 

This installation can also be done using git commands in a command line interface:
```console
git clone https://github.com/balmorelcommunity/Balmorel.git
cd Balmorel/base
git clone https://github.com/balmorelcommunity/Balmorel_data.git
```
Remember to rename Balmorel_data to data inside Balmorel/base. For further instructions on how to install Balmorel using git and how to contribute to the project, we made [this GitHub tutorial](https://balmorelcommunity.github.io/Balmorel/github_tutorial.html#).

:::{tip}
If you use [VS Code](https://code.visualstudio.com/?wt.mc_id=DX_841432) with git, this specific placing of the data repository Balmorel_data inside the framework repository Balmorel/base folder will enable you to simultaneously keep track of changes to both the Balmorel framework and data in your workspace. 
:::

## Choosing a solver and license

By default Balmorel uses the open-source solver [HiGHS](https://highs.dev/), which is included in the [Free Personal GAMS License](https://www.gams.com/free-licenses/). However, when trying to solve larger models, users may need a commercial solver, available through the free academic or commercial license.

:::{tip}
The solver can be chosen in the `base/model/balgams.opt` file.
:::