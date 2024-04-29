#pragma once

#ifndef PDF_BUILDER_HPP
#define PDF_BUILDER_HPP

#include <string>
#include <vector>

void buildPdf(const std::string& outputPdfPath, const std::vector<std::string>& text);

#endif // PDF_BUILDER_HPP