#pragma once

#include <string>
#include <vector>
#include <codecvt>
#include <locale>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include "globals.hpp"

#include "ZipFile.h"
#include "ZipArchive.h"
#include "ZipArchiveEntry.h"

// #include "iconv.h"

using namespace std;

ZipArchive::Ptr openDocx(const string &zipPath);
ZipArchiveEntry::Ptr getDocument(ZipArchive::Ptr archive, const string &xmlPath);
string getDocumentText(ZipArchive::Ptr archive, const string &xmlPath);

string getDocumentText(ZipArchiveEntry::Ptr entry);

ZipArchiveEntry::Ptr getDocumentContent(ZipArchive::Ptr archive);
ZipArchiveEntry::Ptr getContentTypes(ZipArchive::Ptr archive);

vector<ZipArchiveEntry::Ptr> getHeadersFromArchive(ZipArchive::Ptr archive);
vector<ZipArchiveEntry::Ptr> getFootersFromArchive(ZipArchive::Ptr archive);
vector<string> getMediaFromArchive(ZipArchive::Ptr archive);

// string convertEncoding(const string &input, const char *fromEncoding, const char *toEncoding);