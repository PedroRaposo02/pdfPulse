#include "zip_extractor.hpp"

using namespace std;

/* string convertEncoding(const string& input, const char* fromEncoding, const char* toEncoding) {
    iconv_t cd = iconv_open(toEncoding, fromEncoding);
    if (cd == (iconv_t)-1) {
        cerr << "Error: iconv_open failed" << endl;
        return input; // Return input unchanged on failure
    }

    size_t inSize = input.size();
    size_t outSize = inSize * 2; // Allocate enough space for UTF-8
    const char* inBuf = const_cast<char*>(input.c_str());
    char* outBuf = new char[outSize];
    char* outPtr = outBuf;

    memset(outBuf, 0, outSize);

    const char* inBufPtr = inBuf;

    if (iconv(cd, &inBufPtr, &inSize, &outPtr, &outSize) == (size_t)-1) {
        cerr << "Error: iconv failed" << endl;
        iconv_close(cd);
        delete[] outBuf;
        return input; // Return input unchanged on failure
    }

    string result(outBuf);
    iconv_close(cd);
    delete[] outBuf;

    return result;
} */

ZipArchive::Ptr openDocx(const string &zipPath)
{
    ZipArchive::Ptr zipArchive = ZipFile::Open(zipPath);

    if (!zipArchive)
    {
        cerr << "Error opening zip file" << endl;
        return nullptr;
    }

    return zipArchive;
}

ZipArchiveEntry::Ptr getDocument(ZipArchive::Ptr archive, const string &xmlPath)
{
    auto entry = archive->GetEntry(xmlPath);

    if (!entry)
    {
        cerr << "Entry not found in the archive!" << endl;
        return nullptr;
    }

    return entry;
}

string getDocumentText(ZipArchive::Ptr archive, const string &xmlPath)
{
    ZipArchiveEntry::Ptr entry = archive->GetEntry(xmlPath);
    if (!entry)
    {
        cerr << "Error: Entry for path " << xmlPath << " not found." << endl;
        cerr.flush();
        return "";
    }

    istream *xmlContentStream = entry->GetDecompressionStream();
    if (!xmlContentStream)
    {
        cerr << "Error: Could not get decompression stream for " << xmlPath << endl;
        cerr.flush();
        return "";
    }

    std::stringstream entryContentStream;
    try {
        entryContentStream << xmlContentStream->rdbuf();
    } catch (const std::exception &e) {
        std::cerr << "Error reading entry content: " << e.what() << std::endl;
        return "";
    }


    std::string entryContent = entryContentStream.str();

    // Convert from Latin-1 to UTF-8
    // return convertEncoding(entryContent, "ISO-8859-1", "UTF-8");
    return entryContent;
}

string getDocumentText(ZipArchiveEntry::Ptr entry)
{
    if (!entry)
    {
        cerr << "Error reading xml file" << endl;
        return "";
    }

    istream *xmlContentStream = entry->GetDecompressionStream();
    if (!xmlContentStream)
    {
        cerr << "Error reading xml content" << endl;
        return "";
    }

    string xmlContent = string(istreambuf_iterator<char>(*xmlContentStream), istreambuf_iterator<char>());
    return xmlContent;
}

ZipArchiveEntry::Ptr getDocumentContent(ZipArchive::Ptr archive)
{
    return archive->GetEntry(DOCUMENT_XML);
}

ZipArchiveEntry::Ptr getContentTypes(ZipArchive::Ptr archive)
{
    return archive->GetEntry(CONTENT_TYPES);
}

vector<ZipArchiveEntry::Ptr> getHeadersFromArchive(ZipArchive::Ptr archive)
{
    std::vector<ZipArchiveEntry::Ptr> headers;
    for (size_t i = 0; i < archive->GetEntriesCount(); i++)
    {
        ZipArchiveEntry::Ptr entry = archive->GetEntry(i);
        if (entry->GetFullName().find("header") != std::string::npos)
        {
            headers.push_back(entry);
        }
    }

    return headers;
}

std::vector<ZipArchiveEntry::Ptr> getFootersFromArchive(ZipArchive::Ptr archive)
{
    std::vector<ZipArchiveEntry::Ptr> footers;
    for (size_t i = 0; i < archive->GetEntriesCount(); i++)
    {
        ZipArchiveEntry::Ptr entry = archive->GetEntry(i);
        if (entry->GetFullName().find("footer") != std::string::npos)
        {
            footers.push_back(entry);
        }
    }

    return footers;
}

std::vector<std::string> getMediaFromArchive(ZipArchive::Ptr archive)
{
    std::vector<std::string> media;
    for (size_t i = 0; i < archive->GetEntriesCount(); i++)
    {
        ZipArchiveEntry::Ptr entry = archive->GetEntry(i);
        if (entry->GetFullName().find("media") != std::string::npos)
        {
            media.push_back(entry->GetFullName());
        }
    }

    return media;
}