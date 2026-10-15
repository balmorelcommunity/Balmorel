# Outputs

The main outputs after a succesful Balmorel execution are **all_endofmodel.gdx** and **MainResults.gdx**. **all_endofmodel.gdx** contains *everything*, from sets, parameters, decision variable levels, etc. **MainResults.gdx** is post-processed outputs that are readable to a human energy system analyst. 

We recommend the [interactive bar plotting tool](https://balmorelcommunity.github.io/pybalmorel/autoapi/pybalmorel/classes/index.html#pybalmorel.classes.MainResults.interactive_bar_chart) from the [pybalmorel](https://balmorelcommunity.github.io/pybalmorel/) package for quick inspections. You will also find functions for [plotting maps of transmission capacities](https://balmorelcommunity.github.io/pybalmorel/autoapi/pybalmorel/classes/index.html#pybalmorel.classes.MainResults.plot_map) and [production profiles](https://balmorelcommunity.github.io/pybalmorel/autoapi/pybalmorel/classes/index.html#pybalmorel.classes.MainResults.plot_profile). See examples [here](https://github.com/balmorelcommunity/pybalmorel/blob/master/examples/PostProcessing.ipynb).

The video below gives some tips on typical plots and practical guidance on analysing results using GAMS, excel or python.
<div style="display: flex; justify-content: center;">
    <iframe width="560" height="315" src="https://www.youtube.com/embed/zwHoo5zLm6g?si=_9gCkqq1ugRf2g30" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
</div>
<br>
