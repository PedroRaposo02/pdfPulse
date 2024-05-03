#include <iostream>
#include <string>
#include <vector>

#include "xml_parser.hpp"
#include "zip_extractor.hpp"
#include "pdf_builder.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        string filepath;
        if (argc > 1 && argv[1] != NULL)
        {
            filepath = argv[1];
        }
        else
        {
            filepath = "C:\\Users\\prapo\\Documents\\MerdasUni\\2023-2ndSemester\\PESTI\\pdfPulse\\data\\teste_1\\word/document.xml";
        }

        cout << "Filepath: " << filepath << endl; // Print the filepath being used

        ZipArchive::Ptr zipFile = readZipFile(filepath);

        if (!zipFile)
        {
            cerr << "Error reading zip file" << endl;
            return 1;
        }

        cout << "Zip archive contents:" << endl; // Print a message before printing the zip archive files

        // Print zip archive files
        for (int i = 0; i < zipFile->GetEntriesCount(); i++)
        {
            ZipArchiveEntry::Ptr entry = zipFile->GetEntry(i);
            cout << "File: " << entry->GetName() << endl;
        }

        // parseXml("C:\\Users\\prapo\\Documents\\MerdasUni\\2023-2ndSemester\\PESTI\\pdfPulse\\data\\teste_1\\word/document.xml");

        buildPdf("data/output.pdf", {"Hello", "World"});
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}