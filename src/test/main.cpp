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
        string docx_file;
        string output_file;
        if (argc > 1 && argv[1] != NULL)
        {
            docx_file = argv[1];
            if(argc > 2 && argv[2] != NULL)
            {
                output_file = argv[2];
            }
            else
            {
                output_file = "data/output.pdf";
            }
        }
        else
        {
            docx_file = "C:\\Users\\prapo\\Documents\\MerdasUni\\2023-2ndSemester\\PESTI\\pdfPulse\\data\\teste_1.docx";
        }

        cout << "Filepath: " << docx_file << endl; // Print the filepath being used

        ZipArchive::Ptr zipFile = readZipFile(docx_file);

        if (!zipFile)
        {
            cerr << "Error reading zip file" << endl;
            return 1;
        }

        for (size_t i = 0; i < zipFile->GetEntriesCount(); i++)
        {
            ZipArchiveEntry::Ptr entry = zipFile->GetEntry(i);
            cout << "Entry: " << entry->GetFullName() << endl;
        }

        // Grab and parse the document.xml file
        ZipArchiveEntry::Ptr xmlFile = zipFile->GetEntry("word/document.xml");

        if (!xmlFile)
        {
            cerr << "Error reading xml file" << endl;
            return 1;
        }

        cout << "XML File: " << xmlFile->GetFullName() << endl;

        istream* xmlContentStr = xmlFile->GetDecompressionStream();

        if (!xmlContentStr)
        {
            cerr << "Error reading xml content" << endl;
            return 1;
        }

        cout << "XML Content Stream: " << xmlContentStr << endl;

        string xmlContent = string(istreambuf_iterator<char>(*xmlContentStr), istreambuf_iterator<char>());

        cout << "XML Content: " << xmlContent << endl;

        string xmlText = parseXmlString(xmlContent);
        
        vector<string> vec;
        vec.push_back(xmlText);

        buildPdf(output_file, vec);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}