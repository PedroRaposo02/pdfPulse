#pragma once

#ifndef ZIP_EXTRACTOR_HPP
#define ZIP_EXTRACTOR_HPP

#include <string>

#include "extlibs/ZipLib/Source/ZipLib/ZipArchive.h"

ZipArchive::Ptr readZipFile(const std::string& zipPath);

#endif // ZIP_EXTRACTOR_HPP}
