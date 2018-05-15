#!/usr/bin/env python3

import argparse, configparser, os, collections


class Options:

    def __init__(self):

        #  Set required params
        self.data = {}

        #  Parse the Command-Line
        self.Parse_Command_Line()

        #  Parse the Configuration-File
        self.Parse_Configuration_File()

        #  Merge Options
        self.Merge_Configuration()

    def Parse_Command_Line(self):

        #  Create Argument Parser
        parser = argparse.ArgumentParser(description='CLI-CPP RPM Builder.')

        #  Set the config file path
        parser.add_argument('-c','--config',
                            dest='config_pathname',
                            default='scripts/RPM-Builder/rpm-builder.cfg',
                            required=False,
                            help='Set configuration file path.')

        #  Set the template file pathname
        parser.add_argument('-t','--template',
                            dest='template_path',
                            default=None,
                            required=False,
                            help='Provide template rpm spec file.')

        #  Return parser
        self.cmd_options = parser.parse_args()


    def Parse_Configuration_File(self):
        
        #  Create Config Parser
        parser = configparser.ConfigParser()

        #  Read the Path
        if os.path.exists(self.cmd_options.config_pathname):

            parser.read(self.cmd_options.config_pathname)

        #  Return
        self.cfg_options = parser

    def Merge_Configuration(self):

        #  Check Template Path
        if not self.cmd_options.template_path is None:
            self.data['TEMPLATE_PATH'] = self.cmd_options.template_path
        else:
            self.data['TEMPLATE_PATH'] = self.cfg_options.get('rpm','template_path')


def Load_Template( template_path ):

    file_data = ''

    #  Open file
    with open(template_path,'r') as fin:

        for line in fin.readlines():
            file_data += line

    return file_data

def Format_Spec_File( options, template ):

    #  Initialize our output
    output = template

    #  Construct the version
    output = output.replace('__VERSION__',)

    return output

def Main():
    
    #  Configure Options
    options = Options()
    
    #  Load the template file
    template = Load_Template( options.data['TEMPLATE_PATH'] )

    #  Format Template
    spec_str = Format_Spec_File( options, template )

if __name__ == '__main__':
    Main()

