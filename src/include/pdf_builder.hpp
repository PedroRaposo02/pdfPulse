#pragma once

#include "hpdf.h"

#include "globals.hpp"
#include "utils.hpp"
#include <stdexcept>

using namespace std;

void createPDF(const PDFStructure &pdfStructure, const std::string &filename);
void createHeader(HPDF_Doc pdf, HPDF_Page page, const Header &header);
void createFooter(HPDF_Doc pdf, HPDF_Page page, const Footer &footer);

void addTextToPage(HPDF_Page page, const Text &text, float &cursorX, float &cursorY);