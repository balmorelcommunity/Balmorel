* Specify which tecnologies the policies cover

* Defined by individual tecnologi
SET POLTECH(POLICY,G)
/
    POL1.(CC-C1-NGn)
    POL2.(CC-C1-NGn)

/;

* OR by assigning from group of technologies.
* Choose between:
* Predefined: IGCND, IGBPR, IGEXT, IGHOB, IGETOH, IGHSTO, IGHSTO_S, IGHSTOALL, IGESTO, IGHYRS, IGHYRR, IGWND, IGSOLE, IGSOLH, IGWAVE, IGHH,
* IGHHNOSTO, IGNOTETOH, IGKH, IGKHNOSTO, IGKE, IGKENOSTO, IGDISPATCH, IGEE, IGEENOSTO, IGKKNOWN, IGKFIND, IGEH, IGE or IGH.
* Addon defined: VETECH,....
* Userdefined: USERTECH  (is defined in pol_set.inc)

*POLTECH('POL1',G) = YES$(  IGWND(G)    );



