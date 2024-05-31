#include "xml_parser.hpp"

void getXmlDocument(const string &xmlContent, rapidxml::xml_document<char> *doc)
{
    try
    {
        cout << "Parsing xml content: " << xmlContent << "\n";
        doc->parse<rapidxml::parse_no_entity_translation>(const_cast<char *>(xmlContent.c_str()));
    }
    catch (const rapidxml::parse_error &e)
    {
        cerr << "Error parsing xml content: " << e.what() << endl;
        return;
    }
}

vector<DocxRelationship> getRelationshipList(const string &xmlContent)
{
    vector<DocxRelationship> relationships;
    rapidxml::xml_document<> relationshipDoc;
    getXmlDocument(xmlContent, &relationshipDoc);

    // Get root
    rapidxml::xml_node<> *root = relationshipDoc.first_node();

    if (!root)
    {
        cerr << "Error getting xml root" << endl;
        return relationships;
    }

    if (std::string(root->name(), root->name_size()) != "Relationships")
    {
        cerr << "Invalid xml root" << endl;
        return relationships;
    }
    // Iterate through the child nodes
    for (rapidxml::xml_node<> *node = root->first_node(); node; node = node->next_sibling())
    {
        DocxRelationship relationship;
        // Check if the node is a "Relationship" element
        if (std::string(node->name(), node->name_size()) != "Relationship")
        {
            continue;
        }
        // Extract attributes from the "Relationship" element
        rapidxml::xml_attribute<> *idAttr = node->first_attribute("Id");
        rapidxml::xml_attribute<> *typeAttr = node->first_attribute("Type");
        rapidxml::xml_attribute<> *targetAttr = node->first_attribute("Target");
        if (idAttr && typeAttr && targetAttr)
        {
            relationship.id = idAttr->value();
            relationship.type = typeAttr->value();
            relationship.target = targetAttr->value();
            relationships.push_back(relationship);
        }
    }

    return relationships;
}

DocxRelationship getRelationshipById(const vector<DocxRelationship> relationships, const string &id)
{
    for (auto relationship : relationships)
    {
        if (relationship.id == id)
        {
            return relationship;
        }
    }
    return DocxRelationship();
}

Content parseContent(const string &xmlString)
{
    rapidxml::xml_document<> doc;
    getXmlDocument(xmlString, &doc);

    cout << "Parsing content on xmlString: " << xmlString << "\n";

    rapidxml::xml_node<> *root = doc.first_node();
    Content content;
    for (rapidxml::xml_node<> *child = root->first_node(); child; child = child->next_sibling())
    {
        auto tag_name = std::string(child->name(), child->name_size());
        cout << "Tag name: " << tag_name << "\n";
        if (tag_name == TAG_BODY)
        {
            content.body = parseBody(child);
        }
    }

    return content;
}

Body parseBody(const rapidxml::xml_node<> *node)
{
    if (std::string(node->name(), node->name_size()) != TAG_BODY)
    {
        return Body();
    }

    Body body;
    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_P)
        {
            body.paragraphs.push_back(parseParagraph(child));
        }
        else if (std::string(child->name(), child->name_size()) == TAG_SECTPR)
        {
            body.sectProperties = parseSectionProperties(child);
        } // TODO Tables
    }
    return body;
}

SectProperties parseSectionProperties(const rapidxml::xml_node<> *node)
{
    if (std::string(node->name(), node->name_size()) != TAG_SECTPR)
    {
        return SectProperties();
    }

    SectProperties sectProperties;
    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_PG_SZ)
        {
            PageSize pageSize;
            rapidxml::xml_attribute<> *widthAttr = child->first_attribute("w");
            rapidxml::xml_attribute<> *heightAttr = child->first_attribute("h");
            if (widthAttr)
            {
                pageSize.width = widthAttr->value();
            }
            if (heightAttr)
            {
                pageSize.height = heightAttr->value();
            }
            sectProperties.pageSize = pageSize;
        }
        else if (std::string(child->name(), child->name_size()) == TAG_PG_MAR)
        {
            PageMargin pageMargin;
            rapidxml::xml_attribute<> *topAttr = child->first_attribute("top");
            rapidxml::xml_attribute<> *bottomAttr = child->first_attribute("bottom");
            rapidxml::xml_attribute<> *leftAttr = child->first_attribute("left");
            rapidxml::xml_attribute<> *rightAttr = child->first_attribute("right");
            rapidxml::xml_attribute<> *headerAttr = child->first_attribute("header");
            rapidxml::xml_attribute<> *footerAttr = child->first_attribute("footer");
            rapidxml::xml_attribute<> *gutterAttr = child->first_attribute("gutter");
            if (topAttr)
            {
                pageMargin.top = topAttr->value();
            }
            if (bottomAttr)
            {
                pageMargin.bottom = bottomAttr->value();
            }
            if (leftAttr)
            {
                pageMargin.left = leftAttr->value();
            }
            if (rightAttr)
            {
                pageMargin.right = rightAttr->value();
            }
            if (headerAttr)
            {
                pageMargin.header = headerAttr->value();
            }
            if (footerAttr)
            {
                pageMargin.footer = footerAttr->value();
            }
            if (gutterAttr)
            {
                pageMargin.gutter = gutterAttr->value();
            }
            sectProperties.pageMargin = pageMargin;
        }
        else if (std::string(child->name(), child->name_size()) == TAG_COLS)
        {
            sectProperties.columns = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_DOCGRID)
        {
            sectProperties.docGrid = child->value();
        }
    }

    return sectProperties;
}

Footer parseFooter(const string &xmlString)
{
    rapidxml::xml_document<> doc;
    getXmlDocument(xmlString, &doc);

    rapidxml::xml_node<> *root = doc.first_node();

    Footer footer;
    footer.paragraphs = vector<Paragraph>();
    for (rapidxml::xml_node<> *child = root->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_P)
        {
            Paragraph paragraph = parseParagraph(child);
            // it can have no runs, only properties
            if (paragraph.paragraphProperties.style != "" || paragraph.runs.size() > 0)
            {
                footer.paragraphs.push_back(paragraph);
            }
        }
    }
    return footer;
}

Header parseHeader(const string &xmlString)
{
    rapidxml::xml_document<> doc;
    getXmlDocument(xmlString, &doc);

    rapidxml::xml_node<> *root = doc.first_node();

    Header header;
    header.paragraphs = vector<Paragraph>();
    for (rapidxml::xml_node<> *child = root->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_P)
        {
            Paragraph paragraph = parseParagraph(child);
            // it can have no runs, only properties
            if (paragraph.paragraphProperties.style != "" || paragraph.runs.size() > 0)
            {
                header.paragraphs.push_back(paragraph);
            }
        }
    }
    return header;
}

Paragraph parseParagraph(const rapidxml::xml_node<> *node)
{

    if (std::string(node->name(), node->name_size()) != TAG_P)
    {
        return Paragraph();
    }

    Paragraph paragraph;
    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_PPR)
        {
            paragraph.paragraphProperties = parseParagraphProperties(child);
        }
        else if (std::string(child->name(), child->name_size()) == TAG_R)
        {
            paragraph.runs.push_back(parseRun(child));
        }
    }
    return paragraph;
}

ParagraphProperties parseParagraphProperties(const rapidxml::xml_node<> *node)
{
    if (std::string(node->name(), node->name_size()) != TAG_PPR)
    {
        return ParagraphProperties();
    }

    ParagraphProperties paragraphProperties;
    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_PSTYLE)
        {
            paragraphProperties.style = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_JC)
        {
            paragraphProperties.justification = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_SPACING)
        {
            paragraphProperties.spacing = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_U)
        {
            paragraphProperties.u = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_KEEPNEXT)
        {
            paragraphProperties.keepNext = true;
        }
        else if (std::string(child->name(), child->name_size()) == TAG_TABS)
        {
            paragraphProperties.tabs = parseTabs(child);
        }
        else if (std::string(child->name(), child->name_size()) == TAG_RPR)
        {
            paragraphProperties.runProperties = parseRunProperties(child);
        }
    }
    return paragraphProperties;
}

Run parseRun(const rapidxml::xml_node<> *node)
{
    if (std::string(node->name(), node->name_size()) != TAG_R)
    {
        return Run();
    }

    Run run;
    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_RPR)
        {
            run.runProperties = parseRunProperties(child);
        }
        else if (std::string(child->name(), child->name_size()) == TAG_T)
        {
            run.t = parseText(child);
        }
        else if (std::string(child->name(), child->name_size()) == TAG_DRAWING)
        {
            run.drawing = parseDrawing(child);
        }
        else if (std::string(child->name(), child->name_size()) == TAG_TAB)
        {
            run.tab = true;
        }
        else if (std::string(child->name(), child->name_size()) == TAG_BR)
        {
            run.br = true;
        }
    }
    return run;
}

RunProperties parseRunProperties(const rapidxml::xml_node<> *node)
{
    if (std::string(node->name(), node->name_size()) != TAG_RPR)
    {
        return RunProperties();
    }

    RunProperties runProperties;
    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_B)
        {
            runProperties.bold = true;
        }
        else if (std::string(child->name(), child->name_size()) == TAG_I)
        {
            runProperties.italic = true;
        }
        else if (std::string(child->name(), child->name_size()) == TAG_SZ)
        {
            runProperties.size = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_COLOR)
        {
            runProperties.color = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_U)
        {
            runProperties.underline = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_SPACING)
        {
            runProperties.spacing = true;
        }
        else if (std::string(child->name(), child->name_size()) == TAG_LANG)
        {
            runProperties.lang = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_SZCS)
        {
            runProperties.szCs = child->value();
        }
        else if (std::string(child->name(), child->name_size()) == TAG_BCS)
        {
            runProperties.bCs = child->value();
        }
    }
    return runProperties;
}

Text parseText(const rapidxml::xml_node<> *node)
{
    if (std::string(node->name(), node->name_size()) != TAG_T)
    {
        return Text();
    }

    Text text;
    text.text = node->value();
    rapidxml::xml_attribute<> *spaceAttr = node->first_attribute("xml:space");
    if (spaceAttr)
    {
        text.xml_space = spaceAttr->value();
    }
    return text;
}

vector<Tab> parseTabs(const rapidxml::xml_node<> *node)
{
    if (std::string(node->name(), node->name_size()) != TAG_TABS)
    {
        return vector<Tab>();
    }

    vector<Tab> tabs;
    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        if (std::string(child->name(), child->name_size()) == TAG_TAB)
        {
            Tab tab;
            rapidxml::xml_attribute<> *valAttr = child->first_attribute("val");
            rapidxml::xml_attribute<> *posAttr = child->first_attribute("pos");
            if (valAttr)
            {
                tab.val = valAttr->value();
            }
            if (posAttr)
            {
                tab.pos = posAttr->value();
            }
            tabs.push_back(tab);
        }
    }
    return tabs;
}

Drawing parseDrawing(const rapidxml::xml_node<> *node)
{
    if (std::string(node->name(), node->name_size()) != TAG_DRAWING)
    {
        return Drawing();
    }

    Drawing drawing;
    // Get the <wp:inline> attributes to populate drawing
    rapidxml::xml_node<> *inlineNode = node->first_node(TAG_INLINE);
    if (inlineNode)
    {
        rapidxml::xml_node<> *extentNode = inlineNode->first_node(TAG_INLINE);
        if (extentNode)
        {
            rapidxml::xml_attribute<> *distTAttr = extentNode->first_attribute("distT");
            rapidxml::xml_attribute<> *distBAttr = extentNode->first_attribute("distB");
            rapidxml::xml_attribute<> *distLAttr = extentNode->first_attribute("distL");
            rapidxml::xml_attribute<> *distRAttr = extentNode->first_attribute("distR");
            if (distTAttr)
            {
                drawing.distT = distTAttr->value();
            }
            if (distBAttr)
            {
                drawing.distB = distBAttr->value();
            }
            if (distLAttr)
            {
                drawing.distL = distLAttr->value();
            }
            if (distRAttr)
            {
                drawing.distR = distRAttr->value();
            }
        }
        rapidxml::xml_node<> *graphicNode = inlineNode->first_node(TAG_GRAPHIC);
        if (graphicNode)
        {
            // Get to the <a:blip> node that has the r:embed attribute that contains the ID
            rapidxml::xml_node<> *graphicDataNode = graphicNode->first_node(TAG_GRAPHICDATA);
            if (graphicDataNode)
            {
                // TAG_PICPIC
                rapidxml::xml_node<> *picNode = graphicDataNode->first_node(TAG_PIC);
                if (picNode)
                {
                    rapidxml::xml_node<> *blipFillNode = picNode->first_node(TAG_BLIPFILL);
                    if (blipFillNode)
                    {
                        rapidxml::xml_node<> *blipNode = blipFillNode->first_node(TAG_BLIP);
                        if (blipNode)
                        {
                            rapidxml::xml_attribute<> *embedAttr = blipNode->first_attribute("r:embed");
                            if (embedAttr)
                            {
                                auto id = embedAttr->value();
                                drawing.graphicId = id;
                            }
                        }
                    }
                }
            }
        }
    }

    return drawing;
}
