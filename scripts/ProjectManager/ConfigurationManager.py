#    File:     ConfigurationManager.py
#    Author:   Marvin Smith
#    Date:     7/20/2015
#
#    Purpose:  Provide the configuration options required to run the application.
#
__author__ = 'Marvin Smith'


#  Python Libraries
import configparser, os, logging, subprocess

#------------------------------------------#
#-      Configuration Manager Object      -#
#------------------------------------------#
class ConfigurationManager(object):

    #  Argument Parser
    arguments = None

    #  Configuration File Path
    config_path = None

    #  Override Config
    config = None

    #  Default Config Path
    default_config_path = None

    #  Default Config
    default_config = None

    #  Default Options
    general_options = {}

    #  Release Options
    release_options = {}

    #  Debug Options
    debug_options = {}

    #  Log Level
    log_level = logging.info

    #  Log Path
    log_path = None

    #  Log Mode
    log_mode='console'

    #------------------------#
    #-     Constructor      -#
    #------------------------#
    def __init__(self, default_config_path=None,
                       config_path=None,
                       arguments=None ):

        #  Set the arguments
        if arguments is not None:
            self.arguments = arguments

        #  Set the default config path
        if default_config_path is not None:
            self.default_config_path = default_config_path

        # Load the config file
        self.Load_Default_Config()


        #  Set the config path
        if config_path is not None:
            self.config_path = config_path

        #  Load the config file
        self.Load_Config()

        #  Configure Arguments
        self.Process_Arguments()


    #--------------------------#
    #-    Load Config File    -#
    #--------------------------#
    def Load_Config(self):

        #  Create the configuration
        self.config = configparser.ConfigParser(interpolation=configparser.ExtendedInterpolation())

        #  Check if file was provided
        if self.config_path is None:
            logging.warning('Configuration file was not provided. Using default.')

        #  Check if file exists
        elif os.path.exists(self.config_path) is False:
            logging.warning('Configuration file at ' + self.config_path + " does not exist. Using default.")

        # Load if file exists
        elif os.path.exists(self.config_path) is True:
            self.config.read(self.config_path)


        #  Merge options with default
        if 'general' in self.config.keys():
            self.general_options.update( self.config['general'] )

        if 'release' in self.config.keys():
            self.release_options.update( self.config['release'] )

        if 'debug' in self.config.keys():
            self.debug_options.update(   self.config['debug']   )


    #------------------------------------------#
    #-     Load the Default Configuration     -#
    #------------------------------------------#
    def Load_Default_Config(self):

        #  Create teh configuration parser
        self.default_config = configparser.ConfigParser(interpolation=configparser.ExtendedInterpolation())

        #  Load the file
        self.default_config.read(self.default_config_path)

        #  Grab the default options
        self.general_options = self.default_config['general']

        #  Grab the release options
        self.release_options = self.default_config['release']

        #  Grab the debug options
        self.debug_options = self.default_config['debug']


    #--------------------------------------#
    #-    Write the Configuration File    -#
    #--------------------------------------#
    def Write_Configuration(self):

        #  Make sure there is a configuration path
        if self.config_path is None:
            raise Exception('No configuration file path provided.')

        #  Check if the overrides config exists
        if self.config is None:
            raise Exception('No configuration object. Error.')

        #  Set the DEFAULT block
        self.config['general'] = self.general_options

        #  Set the Release Block
        self.config['release'] = {}
        self.config['release'] = self.release_options

        #  Set the debug Block
        self.config['debug'] = {}
        self.config['debug'] = self.debug_options

        #  Write the file
        logging.debug('Writing config file to ' + self.config_path)
        with open( self.config_path, 'w') as configfile:
            self.config.write(configfile)


    #---------------------------#
    #-    Process Arguments    -#
    #---------------------------#
    def Process_Arguments(self):

        #  Make sure the arguments are not null
        if self.arguments is None:
            raise Exception('argument cannot be None.')

        #  Set the log path
        if self.arguments.log_path is not None:
            self.config['general']['log_path'] = self.arguments.log_path


    #---------------------------------#
    #-     Build the Command-List    -#
    #---------------------------------#
    def Build_Run_Script(self):

        #  Create output list
        commands = []

        #  Write the shell name
        commands.append('#!/bin/sh\n')

        #  Get our current directory
        current_dir = os.environ['PWD']

        #  Check the build type
        build_dir=None
        BUILD_TYPE=None
        if self.general_options['build_type'] == 'release':
            build_dir = self.release_options['build_dir']
            BUILD_TYPE='Release'
        elif self.general_options['build_type'] == 'debug':
            build_dir = self.debug_options['build_dir']
            BUILD_TYPE='Debug'
        else:
            build_dir = self.config[self.general_options['build_type']]['build_dir']
            BUILD_TYPE=self.config['build_type']

        #  Check if we need to make
        if self.arguments.build_code is True:

            #  Enter Directory
            commands.append('mkdir -p ' + build_dir + "\n")
            commands.append('cd ' + build_dir + "\n")
            commands.append('pwd' + "\n")

            #  Run CMake
            commands.append('cmake ' + current_dir + ' -DCMAKE_BUILD_TYPE=' + BUILD_TYPE + '\n')

            #  Run Make
            commands.append('make -j' + str(self.general_options['number_threads']) + '\n')

            #  Exit Directory
            commands.append('cd ' + current_dir + "\n")

        #  Check if we need to run unit tests
        if self.arguments.run_tests is True:

            #  Run executable
            commands.append( build_dir + '/bin/cli_cpp_unit_tests' + '\n')

        #  Write new file
        with open(self.general_options['temp_script_path'], 'w') as script_file:
            script_file.writelines(commands)

        #  Make script runnable
        p = subprocess.Popen('chmod +x ' + self.general_options['temp_script_path'], shell=True,stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        output = p.communicate()


        #  Return command list
        return self.general_options['temp_script_path']
