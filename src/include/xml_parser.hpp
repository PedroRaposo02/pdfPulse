#pragma once

#include "rapidxml.hpp"

#include "globals.hpp"

using namespace std;
using namespace rapidxml;

void getXmlDocument(const string &xmlContent, rapidxml::xml_document<> *doc);

vector<DocxRelationship> getRelationshipList(const string &xmlContent);
DocxRelationship getRelationshipById(const vector<DocxRelationship> relationships, const string &id);

Content parseContent(const string &xmlString);
Footer parseFooter(const string &xmlString);
Header parseHeader(const string &xmlString);

Body parseBody(const rapidxml::xml_node<> *bodyNode);
SectProperties parseSectionProperties(const rapidxml::xml_node<> *sectPrNode);
Paragraph parseParagraph(const rapidxml::xml_node<> *paragraphNode);
ParagraphProperties parseParagraphProperties(const rapidxml::xml_node<> *paragraphPrNode);
Run parseRun(const rapidxml::xml_node<> *runNode);
RunProperties parseRunProperties(const rapidxml::xml_node<> *runPrNode);
Text parseText(const rapidxml::xml_node<> *textNode);
Drawing parseDrawing(const rapidxml::xml_node<> *drawingNode);
vector<Tab> parseTabs(const rapidxml::xml_node<> *tabsNode);