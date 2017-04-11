#    File:    BuildRPM.cmake
#    Author:  Marvin Smith
#    Date:    October 27, 2016
#
#    Purpose:  Build an RPM.
#

message( STATUS "Configuring CPack RPM" )

#  CPack Configuration
set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "CLI-CPP" )
set( CPACK_PACKAGE_VENDOR              "Marvin Smith" )
set( CPACK_PACKAGE_DESCRIPTION_FILE    "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set( CPACK_PACKAGE_FILE_LICENSE        "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.md")

set(CPACK_SOURCE_GENERATOR "RPM")

include(CPack)

