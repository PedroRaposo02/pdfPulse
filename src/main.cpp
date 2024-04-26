#include <iostream>
#include <string>
#include <vector>
#include "./extLibs/ZipLib/source/ZipLib/ZipFile.h"
#include "./extLibs/RapidXml/rapidxml.hpp"
#include "./extLibs/RapidXml/rapidxml_utils.hpp"

using namespace std;

void parseXML(const string& filePath) {

    // Load XML file
    rapidxml::file<> xmlFile(filePath.c_str());
    rapidxml::xml_document<char> doc;
    doc.parse<0>(xmlFile.data());

    // print something
    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

}

bool isFileExists(const string& filePath) {
    ifstream file(filePath);
    return file.good();
}

bool unzipFile(string& zipedPath, string& zipFileName, string& destPath) {
    if (!isFileExists(zipedPath)) {
        cout << "File does not exist" << endl;
        return false;
    }

    ZipFile::ExtractEncryptedFile(zipedPath, zipFileName, destPath);

    return true;
}


int main(int argc, char* argv[]) {
    /* string basePath = (argc > 1) ? argv[1] : "./data";
    string filePath = (argc > 2) ? argv[2] : "xml/file_7.xml";
    string fullPath = basePath + '/' + filePath;

    cout << "File path: " << fullPath << endl;

    // Parse XML file and measure time
    vector<Person> persons = parseXML(fullPath); */
    string zipedPath = "data/teste_1.docx";
    string document = "word/document.xml";
    string destPath = "data";

    unzipFile(zipedPath, document, destPath);

    return 0;
}
