#   
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/22/2015
#

#---------------------------------#
#-     Load the CORE Module      -#
#---------------------------------#
add_subdirectory(core)


#--------------------------------#
#-     Load the CLI Module      -#
#--------------------------------#
add_subdirectory(cli)


#------------------------------------#
#-     Load the Command Module      -#
#------------------------------------#
add_subdirectory(cmd)


#-------------------------------#
#-     Load the IO Module      -#
#-------------------------------#
add_subdirectory(io)


#------------------------------------#
#-     Load the Render Module       -#
#------------------------------------#
add_subdirectory(render)


#------------------------------------#
#-    Load the ThirdParty Module    -#
#------------------------------------#
add_subdirectory(thirdparty)


#------------------------------------#
#-     Load the Utility Module      -#
#------------------------------------#
add_subdirectory(utility)

