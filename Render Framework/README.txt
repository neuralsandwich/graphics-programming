How to make an application use the render framework.

Everything is bundled together - except Boost.  Boost is assumed to be at C:\boost.  I'll try and get the Games Lab updated to reflect this.

BEFORE DOING ANYTHING - copy the dlls from the dlls folder in the solution to the relevant folder (Windows\Win32 on 32bit Windows, Windows\SysWoW64 for 64bit).

1. Add a new project to this solution.  DO NOT CREATE A NEW SOLUTION - this tutorial is designed for you to work inside this solution.  
The project needs to be a C++ Win32 console application that is empty - no default header.  You will also have to set your project as the start-up project -
right click on your project in the Solution Explorer to do this.
2. Add the property sheet graphics.prop to your project using the property manager.  This file is in the main solution folder.
3. Add a reference to the Render Framework project in your new project.  To do this, right-click on your project in the Solution Explorer, select references, and click
add new reference.  Select the Render Framework project.

You should now be able to build your project and run it.

The render framework is also set up so that it is linked to the Git repository.  Simply use git pull in the Render Framework folder to update your local version.

Any problems let me know.  Don't struggle with this if you are having problems.  You will fall behind.  There is a simple test project attached so that you can run it and
see if everything is OK.

Kevin