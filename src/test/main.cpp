#include "pdf_pulse.hpp"

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
            if (argc > 2 && argv[2] != NULL)
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
            docx_file = "C:\\Users\\prapo\\Documents\\MerdasUni\\2023-2ndSemester\\PESTI\\pdfPulse\\data\\gIc\\reports\\GERAL-dw198s6.docx";
        }

        cout << "Parsing file: " << docx_file << endl;

        if (!isDocx(docx_file))
        {
            cerr << "Invalid file format" << endl;
            return 1;
        }

        cout << "File format is valid" << endl;

        ZipArchive::Ptr zipFile = openDocx(docx_file);

        if (!zipFile)
        {
            cerr << "Error reading zip file" << endl;
            return 1;
        }

        cout << "Zip file read successfully" << endl;

        cout << "Output Path is: " << output_file << endl;

        if (!parseDocument(docx_file, output_file))
        {
            cerr << "Error parsing document" << endl;
            return 1;
        }

        cout << "PDF created successfully in " << output_file << endl;
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}


