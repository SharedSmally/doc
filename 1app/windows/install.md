
* Install WSL2:

Before installing WSL 2, you must enable the "Virtual Machine Platform" optional feature.
- Open PowerShell as Administrator and run:
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

- Open PowerShell as Administrator and run this command to set WSL 2 as the default version when installing a new Linux distribution:
wsl --set-default-version 2
