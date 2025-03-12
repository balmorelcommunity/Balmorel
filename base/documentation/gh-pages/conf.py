project = "Balmorel"
copyright = "2024, Mathias Berg Rosendal, Tim Graulich"
author = "Mathias Berg Rosendal, Tim Graulich"
release = "5.0"

exclude_patterns = ["_build", "Thumbs.db", ".DS_Store", ".testenv", ".testenv/**", "README.md"]

conf_py_path = "/base/documentation/gh-pages"  # with leading and trailing slash

html_static_path = ["css"]

# General configurations
extensions = [
    "myst_parser",  # in order to use markdown
    'sphinx_copybutton',
    'sphinx_tabs.tabs',
    # "autoapi.extension",  # in order to use markdown
]

# search this directory for Python files
# autoapi_dirs = ["../src/pybalmorel"]

# ignore this file when generating API documentation
# autoapi_ignore = ["*/conf.py"]

myst_enable_extensions = [
    "colon_fence",  # ::: can be used instead of ``` for better rendering
]

html_theme = "sphinx_rtd_theme"

def setup(app):
    app.add_css_file('css_options.css')  # may also be an URL
