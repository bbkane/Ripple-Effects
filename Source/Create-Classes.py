#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Apr  2 14:15:58 2015

@author: Ben
"""

import re # parse the class name as regex
import argparse # command line parsing
import os # make folders
import sys # log to stderr

DESCRIPTION = """
Creates .cpp and .h files from CamelCased class names to an output directory. 
If the directory is not specified, the current directory is used.
If the directory doesn't exist, it is created.
"""
EPILOG = "Created by Benjamin Kane 2015 April"

HEADER_STRING = """\
#ifndef {include_name}
#define {include_name}

class {class_name} {inherit_name} {brace_style_newline}{{
public:
{con_des_header_name}
private:

}};
#endif
"""

CON_DES_HEADER_NAME = """\
{indent}{class_name}();
{indent}{class_name}();
"""

CPP_STRING = """\
#include \"{class_name}.h\"

{con_des_cpp_name}
"""

CON_DES_CPP_NAME = """\
{class_name}::{class_name} {brace_style_newline}{{
{indent}
}}

~{class_name}::{class_name} {brace_style_newline}{{
{indent}
}}
"""


def make_header_content(class_name, args):
    """Create a single .h as a string from a name and the contents of args"""

    # split on capital letters
    include_name = re.findall('[A-Z][^A-Z]*', class_name)
    # join with '_', convert to upper and add '_H'
    include_name = "_".join(include_name).upper() + '_H'
    
    inherit_name = (': ' + args.inherit if args.inherit != '' else '')
    
    if args.constructors_destructors:
        con_des_header_name = CON_DES_HEADER_NAME.format(class_name = class_name,
                                                         indent = args.indent)
    else:
        con_des_header_name = ''
    
    return HEADER_STRING.format(include_name = include_name,
                                class_name = class_name,
                                inherit_name = inherit_name,
                                brace_style_newline = args.brace_style,
                                con_des_header_name = con_des_header_name
                                )

def make_cpp_content(class_name, args):
    """Create a single .cpp as a string from a name and the contents of args"""
    
    if args.constructors_destructors:
        con_des_cpp_name = CON_DES_CPP_NAME.format(class_name = class_name,
                                                   brace_style_newline = args.brace_style,
                                                   indent = args.indent)
    else:
        con_des_cpp_name = ''
    
    return CPP_STRING.format(class_name = class_name,
                             con_des_cpp_name = con_des_cpp_name)

def write_files(output_dir, class_name, header_content, cpp_content):
    """Write a single class's .h and .cpp files"""
    
    with open(output_dir + class_name + ".h", 'w') as header:
        header.write(header_content)
    with open(output_dir + class_name + ".cpp", 'w') as cpp:
        cpp.write(cpp_content)

def parse_args():
    # set up command line arguments
    parser = argparse.ArgumentParser(description=DESCRIPTION, epilog = EPILOG)
    
    #if this flag is not supplied, default specifies what is
    parser.add_argument('-od', '--output_dir', required=False, default = os.getcwd(),
                        help = "Directory to store paths")
   
    # metavar is for help's purposes
    parser.add_argument('-i', '--inherit', required = False, default = '',
                        metavar = "\'inheritance_type parent_class\'",
                        help = "Class to inherit from. Specify with quotes. \
                        Ex: \"-i 'public Object'\"")
                        
    # not putting a dash in front of names means it's required as a positional argument
    # nargs means it's a list with at least one argument
    parser.add_argument('names', nargs='+',
                        help='Required. List of CamelCased class names')
    
    # action stores a boolean if the flag is used
    parser.add_argument('-cd', '--constructors_destructors', required = False, 
                        action = 'store_true',
                        help='Specifies whether to write constructors and destructors')
    
    # oddly enough, this option works with whitespace strings but not character strings
    parser.add_argument('-in', '--indent', required = False, default = '\t',
                        help='Optional indent characters. Defaults to one tab. \
                        Ex: "-in \'  \'" to use two spaces.')
   
    # default defines what happens when flag not specified
    # const defines what happens when flag is, but no following option is
    parser.add_argument('-b', '--brace_style', required = False, nargs='?',
                        default = '', const = '\n', action='store',
                        help="Specify this style to use Allman style braces \
                        (opening brace on a separate line). \
                        Default is K&R (Opening braces on same line). \
                        Adding a string after the flag places that string before opening braces")
   
    parser.add_argument('-O', '--stdout', required = False, action = 'store_true',
                        help = "If specified, output is written to stdout")
   
    parser.add_argument('-nf', '--no_files', required = False, action = 'store_true',
                        help = "If specified, no files are written")
    
    parser.add_argument('-nl', '--no_log', required = False, action = 'store_true',
                        help = 'If specified, no log is written to stderr')
    
    # can test args with a split string                 
    #return parser.parse_args(' -O -nf -od .. -cd TmpClassOne TmpClassTwo'.split() + ['-in', '\t\t', '-i', 'public ParentClass'])
    return parser.parse_args()

def main():
    args = parse_args() 
    
    # Get correct path separators. Works on Windows
    if os.path.sep == '\\':
        if args.output_dir.find('\\') == -1:
            args.output_dir.replace('/', '\\')
    else: #assuming sep = '/'
        if args.output_dir.find('/') == -1:
            args.output_dir.replace('\\','/')
    
    #make sure folder ends with a separator
    if args.output_dir[-1] != os.path.sep:
        args.output_dir += os.path.sep
        
    # create folder if it doesn't exist
    if not os.path.isdir(args.output_dir):
        os.mkdir(args.output_dir)

    # write files
    for class_name in args.names:
        header_content = make_header_content(class_name, args)
        cpp_content = make_cpp_content(class_name, args)
        if args.stdout:
            print(header_content)
            print(cpp_content)
        if not args.no_files:
            if not args.no_log:
                print('LOG: ' + class_name + ' written to .cpp and .h files', file = sys.stderr)
            write_files(args.output_dir, class_name, header_content, cpp_content)

if __name__ == "__main__":
    main()
