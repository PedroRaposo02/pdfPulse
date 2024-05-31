#pragma once

#include "globals.hpp"
#include "xml_parser.hpp"
#include "zip_extractor.hpp"
#include "pdf_builder.hpp"
#include "printer.hpp"

using namespace std;

bool isDocx(const string &filename);

bool isPdf(const string &filename);

bool parseDocument(const string &docx_file, const string &output_file);
