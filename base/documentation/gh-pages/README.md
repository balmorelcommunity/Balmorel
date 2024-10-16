# GitHub Pages Tutorial: A Quick Start Guide for Balmorel

This folder contain all necessary files for developing the Balmorel GitHub pages.


## Purpose

On the short-term: to make it easier getting started with Balmorel. 

On the long-term: interlink development of Balmorel with development of documentation. I.e., by tracking markdown documents within the Balmorel repository, the process of editing documentation becomes identical to the process of editing Balmorel source code.


## Requirements

The documentation can be tested on a local machine by running:
```bash
sphinx-build base/documentation/gh-pages build
```
Then, build/index.html can be opened by, e.g., VS Code's "Go Live" extension and the website can be browsed.

This requires the following python packages:
```yaml
name: docs_building
channels:
  - conda-forge
dependencies:
  - python=3.12
  - myst-parser
  - sphinx
  - sphinx-rtd-theme
  - sphinx-autoapi
  - sphinx-copybutton
```

## Installation instructions

For more information on how to manage and install virtual python environments check out [this resource](https://docs.python.org/3/library/venv.html), or if you are a conda user, [this resource](https://docs.conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html).

The correct virtual environment can be installed using the [provided .yaml file](base/documentation/gh-pages/docs_environment.yml) that is equal to the environments above.

## Example


## Authors 

Mathias Berg Rosendal

## Contribution guide

Similar to developing Balmorel - create your own branch, remember to commit all small changes and create a pull request to master when a feature or tutorial section is done