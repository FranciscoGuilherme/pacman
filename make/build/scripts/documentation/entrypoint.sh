#!/bin/bash

: '
|------------------------------------------------------
| GENERATE THE PROJECT DOCUMENTATION WITH doxygen
|------------------------------------------------------
|
| Project  : Doxygen generator
| Filename : entrypoint.sh
| Version  : 0.0.0
| Date     : July 29, 2019
|
|------------------------------------------------------
|
| Copyright (c) 2019, Francisco G. A. S. Bessa
| All rights reserved.
|
|------------------------------------------------------
'

source "$(pwd)"/generate.sh

: '
|------------------------------------------------------
| [language]    English
| [description] Override default doxygen file settings
|
| [param : string] $1 Parameter for input directory
| [param : string] $2 Doxyfile directory
| [param : string] $3 Parameter to override default
|                     file settings
| [param : string] $4 Optional parameter for exporting
|                     documentation in a specific lang
|
| [return : void]
|------------------------------------------------------
'

function _replace_status()
{
    local arguments=("$1" "$2" "$3" "$4")

    case "${arguments[2]}" in
        '--replace') create_doxyfile "${arguments[1]}" "$REPLACE_ACTIVATED" "${arguments[3]}" ;;
        *)           create_doxyfile "${arguments[1]}" "$REPLACE_DISABLED" "${arguments[3]}" ;;
    esac
}

: '
|------------------------------------------------------
| [language]    English
| [description] Verify the input arguments
|
| [param : string] $1 Parameter for input directory
| [param : string] $2 Doxyfile directory
| [param : string] $3 Parameter to override default
|                     file settings
| [param : string] $4 Optional parameter for exporting
|                     documentation in a specific lang
|
| [return : void]
|------------------------------------------------------
'
function verify_parameters()
{
    local arguments=("$1" "$2" "$3" "$4")

    case "${arguments[0]}" in
        '-d')
                if [ ! -z "${arguments[1]}" ] && [ -d "${arguments[1]}" ]; then
                    _replace_status "${arguments[@]}"
                fi

                if [ ! -d "${arguments[1]}" ]; then
                    arguments[3]="${arguments[2]}"
                    arguments[2]="${arguments[1]}"

                    read_doxyfile_path; arguments[1]=${__}
                    _replace_status "${arguments[@]}"
                fi
            ;;
        *) printf "%s\n" 'Usage: bash <script.sh> -d <doxygen_file_directory> [--replace] [<lang-country>]' && exit ;;
    esac
}

: '
|------------------------------------------------------
| [language]    English
| [description] Read the doxygen location file
|
| [return : string] Doxygen location
|------------------------------------------------------
'
function read_doxyfile_path()
{
    local doxygen_directory

    while [ -z "$doxygen_directory" ]; do
        printf "%s" "Input the absolute path of the directory: "
        read -r doxygen_directory
    done

    __="$doxygen_directory"
}

: '
|------------------------------------------------------
| [language]    English
| [description] Entrypoint function
|
| [param : string] $1 Parameter for input directory
| [param : string] $2 Doxyfile directory
| [param : string] $3 Parameter to override default
|                     file settings
| [param : string] $4 Optional parameter for exporting
|                     documentation in a specific lang
|
| [return : void]
|------------------------------------------------------
'
function main()
{
    local arguments=("$1" "$2" "$3" "$4")

    verify_parameters "${arguments[@]}"
}

main "$1" "$2" "$3" "$4"
