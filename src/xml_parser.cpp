#include "xml_parser.hpp"

#include <string>
#include <iostream>

#include "extlibs/rapidxml-1.13/rapidxml.hpp"
#include "extlibs/rapidxml-1.13/rapidxml_utils.hpp"

using namespace std;

void parseXml(const string& filePath) {

    rapidxml::file<> xmlFile(filePath.c_str());
    rapidxml::xml_document<> doc;

    try {
        doc.parse<0>(xmlFile.data());
    } catch (rapidxml::parse_error& e) {
        cerr << "Error parsing XML: " << e.what() << endl;
        return;
    } catch (...) {
        cerr << "Unknown error occurred while parsing XML" << endl;
        return;
    }

    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

}