#include "zip_extractor.hpp"

#include <iostream>
#include <string>

#include "ZipFile.h"
#include "ZipArchive.h"

using namespace std;

ZipArchive::Ptr readZipFile(const string& zipPath) {

    ZipArchive::Ptr zipArchive = ZipFile::Open(zipPath);

    if (!zipArchive) {
        cerr << "Error opening zip file" << endl;
        return nullptr;
    }

    return zipArchive;
}