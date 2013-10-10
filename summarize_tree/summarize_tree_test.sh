#!/bin/bash

outputFile=`mktemp /tmp/summarize_tree_output.XXXXX`

testCVersionUsingStatOnSmallDirectory()
{
    rm $outputFile
    ./summarize_tree /home/mcphee/pub/CSci3401/fewer_files/ > $outputFile
    diff small_dir_sizes $outputFile
    assertTrue "Incorrect output file, try 'diff small_dir_sizes $outputFile' for more info" "[[ $? == 0 ]]"
}

testCVersionUsingStatOnLargeDirectory()
{
    rm $outputFile
    ./summarize_tree /home/mcphee/pub/CSci3401/loads_o_files/ > $outputFile
    diff large_dir_sizes $outputFile
    assertTrue "Incorrect output file, try 'diff large_dir_sizes $outputFile' for more info" "[[ $? == 0 ]]"
}

testCVersionUsingFtwOnSmallDirectory()
{
    rm $outputFile
    ./summarize_tree_ftw /home/mcphee/pub/CSci3401/fewer_files/ > $outputFile
    diff small_dir_sizes $outputFile
    assertTrue "Incorrect output file, try 'diff small_dir_sizes $outputFile' for more info" "[[ $? == 0 ]]"
}

testCVersionUsingFtwOnLargeDirectory()
{
    rm $outputFile
    ./summarize_tree_ftw /home/mcphee/pub/CSci3401/loads_o_files/ > $outputFile
    diff large_dir_sizes $outputFile
    assertTrue "Incorrect output file, try 'diff large_dir_sizes $outputFile' for more info" "[[ $? == 0 ]]"
}

testBashVersionOnSmallDirectory()
{
    rm $outputFile
    ./summarize_tree.sh /home/mcphee/pub/CSci3401/fewer_files/ > $outputFile
    diff small_dir_sizes $outputFile
    assertTrue "Incorrect output file, try 'diff small_dir_sizes $outputFile' for more info" "[[ $? == 0 ]]"
}

testBashVersionOnLargeDirectory()
{
    rm $outputFile
    ./summarize_tree.sh /home/mcphee/pub/CSci3401/loads_o_files/ > $outputFile
    diff large_dir_sizes $outputFile
    assertTrue "Incorrect output file, try 'diff large_dir_sizes $outputFile' for more info" "[[ $? == 0 ]]"
}

testRubyVersionOnSmallDirectory()
{
    rm $outputFile
    ./summarize_tree.rb /home/mcphee/pub/CSci3401/fewer_files/ > $outputFile
    diff small_dir_sizes $outputFile
    assertTrue "Incorrect output file, try 'diff small_dir_sizes $outputFile' for more info" "[[ $? == 0 ]]"
}

testRubyVersionOnLargeDirectory()
{
    rm $outputFile
    ./summarize_tree.rb /home/mcphee/pub/CSci3401/loads_o_files/ > $outputFile
    diff large_dir_sizes $outputFile
    assertTrue "Incorrect output file, try 'diff large_dir_sizes $outputFile' for more info" "[[ $? == 0 ]]"
}

# load shunit2
. /home/mcphee/pub/CSci3401/shunit2-2.1.5/src/shell/shunit2
