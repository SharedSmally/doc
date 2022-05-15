# Eclipse RAP with Workbench
![workbench](https://s1.o7planning.com/en/10385/images/756956.png)

## Tutorial
- [Eclipse RAP Tutorial for Beginners - Basic Application ](https://o7planning.org/10121/eclipse-rap-tutorial-for-beginners-basic-application)
- [Eclipse RAP Tutorial for Beginners - e4 Workbench Application](https://o7planning.org/10183/eclipse-rap-tutorial-for-beginners-workbench-application)
- [Eclipse RAP Tutorial for Beginners - Workbench Application-OLD](https://o7planning.org/10385/eclipse-rap-tutorial-for-beginners-workbench-application)


## Target Platform: New > Other > Plugin Development > Target Definition
The Target Platform refers to the plug-ins which your workspace will be built and run against. It describes the platform that you are developing for. When developing with PDE, the target platform is used to:

- Compile - Plug-ins in the workspace are built against the target platform so you do not have to have everything in your workspace
- Launch - When using PDE's launchers you can choose the set of plug-ins you want to launch. By default the Eclipse Application Launcher will start with all plug-ins in the target, but will use workspace plug-ins instead when available
- Calculate Dependencies - PDE assists you in finding the plug-ins your plug-ins was include/require to compile correctly by looking at what is available in the target platform
- State - An OSGi state is created for the target platform so it can be used by other tooling. The state can also be viewed in detail using the Target Platform State View
- Other Tools - Other PDE tools use the target platform to determine their options, such as the import wizards

Whereas the target platform refers to your currently active bundles, a Target Definition is a way of determining the plug-ins to add to the state. You can have multiple target definitions, but only one definition can be selected as the target platform.

The target platform and your target definitions are managed on the Target Platform Preference Page. 

## Target Platform Preferences
Open the target platform preference page Window > Preferences... > Plug-in Development > Target Platform preference page allows you to manage a set of target definitions and select one as the active target platform. A target definition consists of a set of plug-ins and environment settings. The active target platform is used to build and launch your workspace plug-ins.

