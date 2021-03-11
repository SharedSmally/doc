# Flax Game Engine

## Source/:
- Engine: Engine
- Editor: c# for GUI; Engine/UI/GUI
- Shaders: hlsl (High-level shader language) on DirectX
- Tools
- ThirdParty
- Platforms: binaries for different platforms

## Install
- Download and install Visual Studio Code
- download, compile and install msbuild:  see https://github.com/mono/linux-packaging-msbuild
     - git clone https://github.com/mono/linux-packaging-msbuild.git 
     - cd msbuild; ./build.sh  (Download dotnet sdk);  dotnet msbuild MSBuild.slnls
     - Install dotnet [using snap](https://docs.microsoft.com/en-us/dotnet/core/install/linux-snap):
          - sudo snap install dotnet-sdk --classic --channel=5.0
          - sudo snap alias dotnet-sdk.dotnet dotnet
     - Check dotnet SDK and runtime: dotnet --list-sdks and dotnet --list-runtimes
