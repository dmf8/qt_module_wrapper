# Introduction
## Qt lib module including structure
In a large qmake based Qt project, this structure can provide convenient module managerment. When some modules depend on others, just "include" their reference scripts, which is equivalent to including a header file. 

The key factors for the total project is shown as follows:
- subdir project .pro
- common_dest.pri
- module_list.pri
- lib module1
    - lib1.pro
    - ref_lib1.pri
- lib module2
    - lib2.pro
    - ref_lib2.pri

All sub modules share `common_dest.pri` and `module_list.pri`.
- In `common_dest.pri`, there is build destination and target infomation.
- In `module_list.pri`, there are referring tags of all modules. Each tag points to the reference pri file of one module.

Each sub module has its own pri file, which has 2 main characters:
1. Dependency list of other modules
1. Lib link information for compiling

## Tool Description
This tool is used to generate essential information for .pro and .pri files for a new created module. 
1. It will generate the reference .pri file for the new module.
1. It will append basic information to the .pro file of the new module, to uniformly normalize its building behavior.
1. It will add the new module to module list, to provide a reference tag for those modules which depend on this. 

# Usage
1. Create a new submodule
1. Run this tool, and pick the .pro file of the new module as well as the root path of the subir project
1. Click the `gen` button
1. Build the new submodule once to check everything is right
1. When any module needs to refer to this new module, just check the module list, and find the tag corresponding to this module (in style of `PRI_XXX`), then include it in its own .pri or .pro file