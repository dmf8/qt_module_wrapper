# random text stream

# text editor
## file operation
- set file handler
- write to disk
## get status
- row count
- column count
- output content as lines
## read
- get row as elements
    1. get row
    1. split
- get column as elements
    1. get each row
    1. split
    1. take last item
    1. compose vector

## write 
- append row/column
    1. check if column/row size fit new row/column, span origin table if necessary
    1. append new row/column
    1. sync row/column count
- set row/column
- set element
- private
    - append empty row/rows
        - generate empty row with current column count
    - append empty column/columns
        1. get each line
        1. append with separator(`,`)
        1. set new line
    - join elements to line
    - split line into elements
    - set row/column count
        1. if current count is larger, remove redundant rows/columns
        1. else, append empty rows/columns
        1. set number
    - resize list count
