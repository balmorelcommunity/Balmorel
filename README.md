# Balmorel

A scenario that's possible to run with an academic trial license of GAMS can be found in the balmorel-demo branch.

## What is Balmorel?

Balmorel is a partial equilibrium model for analysing the electricity and combined heat and power sectors in an international perspective. It is highly versatile and may be applied for long range planning as well as shorter time operational analysis. Balmorel is implemented as a mainly linear programming optimisation problem.

The model is developed in a model language, and the source code is readily available under open source conditions, thus providing complete documentation of the functionalities. Moreover, the user may modify the model according to specific requirements, making the model suited for any purpose within the focus parts of the energy system.

## What can Balmorel be used for?

The Balmorel model has been applied in projects or other activities in a number of countries, e.g., in  Denmark, Norway, Sweden, Estonia, Latvia, Lithuania, Poland, Germany, Austria, Ghana, Mauritius, Canada and China. It has been used for analyses of, i.a., security of electricity supply, the role of flexible electricity demand, hydrogen technologies, wind power development, the role of natural gas, development of international electricity markets, market power, heat transmission and pricing, expansion of electricity transmission, international markets for green certificates and emission trading, electric vehicles in the energy system, environmental policy evaluation.

See "Activities" and "Publications" sections in the menu for description of ongoing and past projects using the Balmorel model.

## Who can use Balmorel?

Balmorel is a modelling tool that can be used by energy system experts, energy companies, authorities, transmission system operators, researchers and others for the analyses of future developments of a regional energy sector.

## How is Balmorel supported and further developed?

The model is developed and distributed under open source ideals. The source code has been provided on its homepage since 2001 and was assigned the [ISC license](https://opensource.org/licenses/ISC) in 2017. Ample documentation is available in the folder [within this repository](base/documentation). We also refer to information on [openmod](https://wiki.openmod-initiative.org/wiki/Balmorel). Presently the model development is mainly project driven, with a users' network around it, supporting the open source development idea.

### Procedure for Merging Changes to Master

The DTU Balmorel team has decided on the following procedure for merging new changes to the master:
1. A decision to merge should be agreed upon in a Balmorel meeting with the admins
2. Create a new branch from master, which will be used as a temporary branch to do all the changes
3. Make the desired changes in a new scenario:
    
    a. Add a new scenario called 'changes', which result in the following folder structure:
        
        Balmorel
        ├── base
        ├── changes
        │   └── model
        │   │   ├── cplex.op4
        │   │   └── Balmorel.gms
        ├── simex
        ├── README.md
        ├── .gitignore
        └── .gitattributes

    b. Keep the base scenario identical to the current master and apply all changes to the 'changes' scenario
   
4. Run the [test script](base/auxils/master_merge_tests/merge_tests.ipynb) and make sure that the model stays feasible and that you verify the changes
5. Make a pull request and report the changes made with the KPI outputs from the tests in 4. in ... (todo: check where it makes sense to put these descriptions, as simple as possible)

