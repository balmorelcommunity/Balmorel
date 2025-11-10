# Structure

When you clone or download Balmorel from GitHub, you will see the following folder structure:
```bash
Balmorel
├── base
│   ├── addons
│   ├── auxils
│   ├── bui
│   ├── data
│   ├── documentation
│   ├── logerror
│   ├── model
│   │   ├── cplex.op4
│   │   ├── balopt.opt
│   │   └── Balmorel.gms
│   └── output
└── simex
```
For now, it will be sufficient to focus on the base/model folder and the Balmorel.gms, balopt.inc and cplex.op4 files.
It is good practice to keep files in the base folder unchanged, unless you want a consistent change in data (base/data) or in the equations of the [addons](../addons.md) (base/addons). The addons folder contain modules that can be turned of and on in balopt.inc, Balmorel.gms is the file to execute to run Balmorel and cplex.op4 contain important solver options. We will use these files to execute Balmorel on the next page.

:::{warning}
Do not rename the base folder! The code of Balmorel needs to be able to locate the base/addons and base/data folders or it will generate errors.
:::
