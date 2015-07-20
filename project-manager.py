#!/usr/bin/env python3
#
#    File:    project-manager.py
#    Author:  Marvin Smith
#    Date:    7/20/2015
#
#    Purpose: Manage the CLI-C++ Project.
#

#  Python Libraries
import argparse, subprocess, logging, sys, configparser, os, sys

#  Add the project-manager files
sys.path.append('scripts/ProjectManager')
import ConfigurationManager

#-------------------------------------#
#-    Default Configuration Items    -#
#-------------------------------------#
DEFAULT_CONFIGURATION_FILE='scripts/project-manager.default.cfg'


#--------------------------------#
#-    Parse the Command-Line    -#
#--------------------------------#
def Parse_Command_Line():

    #  Create the argument parser
    parser = argparse.ArgumentParser(description="Run the CLI-C++ Unit-Tests.")

    #  Set the build version
    parser.add_argument('-r','--release',
                        dest='build_type',
                        action='store_const',
                        const='release',
                        required=False,
                        default='release',
                        help='Build or run with a release version.')


    parser.add_argument('-d', '--debug',
                        dest='build_type',
                        action='store_const',
                        const='debug',
                        required=False,
                        help='Build or run with a debug version.')

    #  Set the build action
    parser.add_argument('-m','--make',
                        dest='build_code',
                        action='store_const',
                        const=True,
                        required=False,
                        help='Build source code.')

    #  Run the Unit Tests
    parser.add_argument('-t','--run-tests',
                        dest='run_tests',
                        action='store_const',
                        const=True,
                        required=False,
                        help='Run Unit-Tests.')
    

    #  Set the number of threads
    parser.add_argument('-j','--num-threads',
                        dest='num_threads',
                        required=False,
                        default=1,
                        type=int,
                        help='Set the number of threads to build with.')

    #  Define a configuration file
    parser.add_argument('-c','--config',
                        dest="config_path",
                        required=False,
                        default=None,
                        help='Define a configuration file with standard default options.')

    #  Generate a configuration file
    parser.add_argument('-g','--gen-config',
                        dest="generate_config",
                        action='store_const',
                        const=True,
                        required=False,
                        default=False,
                        help='Provide to generate configuration file if one does not exist.  If the config file does exist, then update any missing fields.')

    #  Write to log file
    parser.add_argument('-log-file',
                        dest='log_path',
                        required=False,
                        default=None,
                        help='Write all output to the given log file.')

    #  Set the log level
    parser.add_argument('-v',
                        dest='log_level',
                        required=False,
                        default='info',
                        action='store_const',
                        const='debug' )
    parser.add_argument('-vv',
                        dest='log_level',
                        required=False,
                        action='store_const',
                        const='trace')

    #  Parse the arguments
    return parser.parse_args()


#--------------------------------------#
#-    Load the Configuration File     -#
#--------------------------------------#
def Load_Configuration_File( options ):

    #  Set our configuration file path
    config_path = options.config_path

    #  Check if the default exists
    if os.path.exists(DEFAULT_CONFIGURATION_FILE) is False:
        logging.error('Default configuration file at ' + DEFAULT_CONFIGURATION_FILE + " does not exist.  Please provide default config.")
        sys.exit(1)


    #  Build our Configuration Manager Object
    config_manager = ConfigurationManager.ConfigurationManager(default_config_path=DEFAULT_CONFIGURATION_FILE,
                                                               config_path=config_path,
                                                               arguments=options)


    #  Check if we need to generate a configuration file
    if options.generate_config is True:
        config_manager.Write_Configuration()


    #  Return the Configuration-Manager Object
    return config_manager


#-------------------------------#
#-      Configure Logging      -#
#-------------------------------#
def Configure_Logging( config ):

    #  Check the log level
    logging.basicConfig(level=config.log_level)

    #  Check if the logfile has been created.
    if config.log_path is not None and config.log_mode== 'file':
        return open(config.log_path, 'w')

    else:
        return sys.stdout


#---------------------------#
#-     Run the command     -#
#---------------------------#
def Run_Command( command, fp ):

    #  Create the popen
    p = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    #  Get output
    while True:

        #  Get output
        line = p.stdout.readline()

        #  Print
        if not line:
            break

        #  Write
        fp.write(line.decode("utf-8"))
        fp.flush()


#---------------------------#
#-      Main Program       -#
#---------------------------#
def Main():

    #  Parse the command-line
    options = Parse_Command_Line()

    #  Load the Configuration File
    config = Load_Configuration_File( options )

    #  Configure Logging
    fp = Configure_Logging(config)

    #  Create Command List
    run_script = config.Build_Run_Script()

    #  Run Commands
    Run_Command( run_script, fp )
    
    #  Delete the script
    if bool(config.general_options['delete_run_script']) == True:
        os.remove(run_script)


if __name__ == '__main__':
    Main()
