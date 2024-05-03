#include "xml_parser.hpp"

#include <string>
#include <iostream>

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

string parseXmlString(const string& xmlString) {

    rapidxml::xml_document<> doc;
    try {
        doc.parse<0>(const_cast<char*>(xmlString.c_str()));
    } catch (rapidxml::parse_error& e) {
        cerr << "Error parsing XML: " << e.what() << endl;
        return "";
    } catch (...) {
        cerr << "Unknown error occurred while parsing XML" << endl;
        return "";
    }

    cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

    rapidxml::xml_node<> *textNode;
    try
    {
        textNode = doc.first_node()->first_node("w:body")->first_node("w:p")->first_node("w:r")->first_node("w:t"); 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    if (textNode) {
        cout << "Text node found: " << textNode->value() << "\n";
        return textNode->value();
    } else {
        cout << "No text node found\n";
        return "";
    }
}