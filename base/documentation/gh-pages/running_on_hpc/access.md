# Accessing the Cluster

A general guide for accessing the DTU clusters by the DTU Computing Center can be found [here](https://www.hpc.dtu.dk/?page_id=2501). See the "Command line: SSH access" section to understand how to access via PuTTY. 

Note that you should not transfer large files via the login nodes (e.g. login.gbar.dtu.dk), but through the transfer nodes (e.g. transfer.gbar.dtu.dk). Follow [this guide](https://www.hpc.dtu.dk/?page_id=4377) for transfers using WinSCP. 

:::{warning}
Do not transfer large files or run resource intensive programs directly on the login nodes!

See [WinSCP Example](#winscp-example) for how to transfer large files and [Job Submission](submitting_a_job.md) for submitting resource intensive programs.
:::

## PuTTY Example

:::{figure} ../img/putty_login.jpg 
:name: putty_login
:alt: Logging into PuTTY
:width: 70% 
:align: center
The graphical user interface that appears when starting up PuTTY. 
:::
When starting PuTTY, a graphical user interface appears as illustrated in the [Figure](putty_login) above.
Type login.gbar.dtu.dk as the host-name and enter. This results in a command prompt that asks for your username, see the [code snippet](putty_login_cli) below. Write your DTU initials or student number. This is followed by a password prompt. Note that it does show your password as you type it for security purposes, but your keystrokes are being registered. Type your password confidently and press enter. You can also (in Windows) copy your password and paste it into the password prompt with shift + enter.


:::{code-block} console
:name: putty_login_cli
:caption: The prompts appearing after entering the PuTTY setup. 
login as: user_name
user_name@login.gbar.dtu.dk's password:
:::


## WinSCP Example