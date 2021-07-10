## Simple application with plugins

Application input - path to folder with plugins.
Application parse folder with plugins and dynamically load all dll-s.
Dll-s have interface to dynamic link and load function from it.
Function with specific to plugins name return pointer to object. Object is instance of class inherited by interface IPlugin.
plugin interface is abstract class and has pure virtual function. 
In main application in for loop call virtual function of all plugins.