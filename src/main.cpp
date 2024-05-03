#include <iostream>
#include <string>
#include <vector>

/* #include "xml_parser.hpp"
#include "zip_extractor.hpp"
#include "pdf_builder.hpp" */

using namespace std;


int main(int argc, char* argv[]) {
    /* string filepath;
    if (argc > 1) {
        filepath = argv[1];
    } else {
        filepath = "C:\\Users\\prapo\\Documents\\MerdasUni\\2023 - 2nd Semester\\PESTI\\pdfPulse\\data\\teste_1\\word/document.xml";
    }

    ZipArchive::Ptr zipFile = readZipFile(filepath);

    if (!zipFile) {
        cerr << "Error reading zip file" << endl;
        return 1;
    }

    // print zip archive files

    for (int i = 0; i < zipFile->GetEntriesCount(); i++) {
        ZipArchiveEntry::Ptr entry = zipFile->GetEntry(i); 
        cout << "File: " << entry->GetName() << endl;
    }

    buildPdf("data/output.pdf", {"Hello", "World"}); */

 
    return 0;
}
