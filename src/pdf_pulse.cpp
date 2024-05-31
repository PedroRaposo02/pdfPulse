#include "pdf_pulse.hpp"


bool isDocx(const string &filename)
{
    return filename.substr(filename.find_last_of(".") + 1) == "docx";
}

bool isPdf(const string &filename)
{
    return filename.substr(filename.find_last_of(".") + 1) == "pdf";
}

bool parseDocument(const string &docx_file, const string &output_file)
{
    ZipArchive::Ptr zipFile = openDocx(docx_file);

    if (!zipFile)
    {
        cerr << "Error reading zip file" << endl;
        return false;
    }

    PDFStructure pdfStructure = PDFStructure();

    string xmlFile = getDocumentText(zipFile, CONTENT_TYPES);

    vector<DocxRelationship> relationships = getRelationshipList(xmlFile);

    if(relationships.size() == 0)
    {
        cerr << "Error reading relationships" << endl;
        return false;
    }

    pdfStructure.relationships = relationships;

    vector<ZipArchiveEntry::Ptr> headers = getHeadersFromArchive(zipFile);
    vector<ZipArchiveEntry::Ptr> footers = getFootersFromArchive(zipFile);
    ZipArchiveEntry::Ptr document = getDocumentContent(zipFile);

    vector<Header> headerList;

    for (auto &header : headers)
    {
        string headerContent = getDocumentText(header);
        Header parsedHeader = parseHeader(headerContent);
        headerList.push_back(parsedHeader);
    }

    pdfStructure.headers = headerList;

    vector<Footer> footerList;

    for (auto &footer : footers)
    {
        string footerContent = getDocumentText(footer);
        Footer parsedFooter = parseFooter(footerContent);
        footerList.push_back(parsedFooter);
    }

    pdfStructure.footers = footerList;

    cout << "Headers: " << headers.size() << endl;
    cout << "Footers: " << footers.size() << endl;

    // print relationships
    for (auto &rel : relationships)
    {
        cout << rel.id << " " << rel.type << " " << rel.target << endl;
    }

    string documentContent = getDocumentText(document);

    Content parsedContent = parseContent(documentContent);

    pdfStructure.content = parsedContent;

    // printer function to print the entire structure
    printPDFStructure(pdfStructure, 0);

    // build pdf
    try
    {
        createPDF(pdfStructure, output_file);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    

    return true;
}
