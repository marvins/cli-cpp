#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/20/2015
#
#    Purpose:  Constructs the lib and app projects
#


#----------------------------------#
#-      Add the Library Code      -#
#----------------------------------#
add_subdirectory(lib)

#------------------------------------#
#-    Add the Sample Program Code   -#
#------------------------------------#
add_subdirectory(apps)

#---------------------------------#
#-    Add the Unit-Test Code     -#
#---------------------------------#
add_subdirectory(testing)

#--------------------------------#
#-     Add the Utility Code     -#
#--------------------------------#
add_subdirectory(utilities)

