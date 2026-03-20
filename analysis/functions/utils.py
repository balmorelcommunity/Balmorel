"""
Utilities

Utility functions for analyses

Created on 20.03.2026
@author: Mathias Berg Rosendal
         PhD Student at DTU Management (Energy Economics & Modelling)
"""
# ------------------------------- #
#        0. Script Settings       #
# ------------------------------- #

from pathlib import Path

# ------------------------------- #
#          1. Functions           #
# ------------------------------- #

def find_most_recent_result(sc_folder: str):
    """Find the most recent MainResults in a scenario/model folder"""

    path = Path(f'{sc_folder}/model')
    results =  [p for p in path.iterdir() if 'MainResults' in str(p)]
    mtimes = [modified.stat().st_mtime for modified in results]
    most_recent = mtimes.index(max(mtimes))
    path = Path(results[most_recent])
    print(f'\nMost recent results in {sc_folder}: {path.name}\n')

    return path.name, str(path.parent)


# ------------------------------- #
#            2. Main              #
# ------------------------------- #


if __name__ == '__main__':
    pass

