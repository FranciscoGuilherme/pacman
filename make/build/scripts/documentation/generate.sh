#!/bin/bash

readonly REPLACE_DISABLED=0
readonly REPLACE_ACTIVATED=1
readonly CONFIG=(
    'OUTPUT_LANGUAGE'
    'EXTRACT_ALL'
    'RECURSIVE'
    'SOURCE_BROWSER'
    'GENERATE_TREEVIEW'
)

: '
|------------------------------------------------------
| [language]    English
| [description] Create new doxyfile based on a specific
|               directory
|
| [param  : string] $1 Doxyfile directory
| [param  : string] $2 Flag to override default settings
| [param  : string] $3 Language to export documentation
|
| [return : void]
|------------------------------------------------------
'
function create_doxyfile()
{
    local doxyfile_directory="$1"
    local doxyfile_replace="$2"
    local doxyfile_language="$3"

    if [ ! -z "$doxyfile_directory" ] && [ -d "$doxyfile_directory" ]; then
        cd "$doxyfile_directory"

        doxygen -d _PT_BR
        doxygen -g "$doxyfile_directory"/Doxyfile

        if [ "$doxyfile_replace" == '1' ]; then
            replace_configurations "$doxyfile_directory" Doxyfile
        fi

        set_language "$doxyfile_directory" Doxyfile "$3"

        doxygen "$doxyfile_directory"/Doxyfile
    fi
}

: '
|------------------------------------------------------
| [language]    English
| [description] Searches for a specific setting in the
|               doxygen file and overrides the default
|               settings
|
| [param : string] $1 Doxyfile directory
| [param : string] $2 Doxygen configuration file name
|
| [return : void]
|------------------------------------------------------
'
function replace_configurations()
{
    local doxyfile_directory="$1"
    local doxyfile_file_name="$2"

    for configuration in "${CONFIG[@]}"; do
        sed -i 's/^'"$configuration"'.*NO$/'"$configuration"' = YES/g' "$doxyfile_directory"/"$doxyfile_file_name"
    done
}

: '
|------------------------------------------------------
| [language]    English
| [description] Set output language for doxyfile
|
| [param : string] $1 Doxyfile directory
| [param : string] $2 Doxygen configuration file name
| [param : string] $3 Documentation language
|
| [return : void]
|------------------------------------------------------
'
function set_language()
{
    local doxyfile_directory="$1"
    local doxyfile_file_name="$2"
    local doxyfile_language="$3"

    case "$doxyfile_language" in
        '_PT_BR') sed -i 's/^OUTPUT_LANGUAGE.*$/OUTPUT_LANGUAGE = Portuguese/g' "$doxyfile_directory"/"$doxyfile_file_name" ;;
        *)        sed -i 's/^OUTPUT_LANGUAGE.*$/OUTPUT_LANGUAGE = English/g' "$doxyfile_directory"/"$doxyfile_file_name" ;;
    esac
}
