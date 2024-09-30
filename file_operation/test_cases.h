#ifndef TEST_CASES_H
#define TEST_CASES_H

#include <QStringList>

QStringList path_items = {
    "",            // same as .
    ".",           //
    "..",          //
    "...",         //
    "/",           //
    "//",          //
    "///",         //
    "./",          //
    "/./",         //
    "/.//",        //
    "abc",         //
    "abc/",        //
    "/abc",        //
    "//abc",       //
    "file_name",   //
    "not_exist",   //
    "not_exist/",  //
    "a.b",         //
    "a.b/",        //
    "a/.b/",       //
    "a./b/",       //
    "../up",       //
};

QStringList file_items = {
    "...",           //
    "folder_name",   //
    "folder_name/",  //
    "file_name/",    //
    "file_name",     //
    "not_exist",     //
    "not_exist/",    //
};

#endif  // TEST_CASES_H
