#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

#define CONTENT_TYPES "word/_rels/document.xml.rels"
#define DOCUMENT_XML "word/document.xml"
#define STYLES_XML "word/styles.xml"
#define NUMBERING_XML "word/numbering.xml"
#define FOOTNOTES_XML "word/footnotes.xml"
#define ENDNOTES_XML "word/endnotes.xml"
#define HEADER1_XML "word/header1.xml"
#define FOOTER1_XML "word/footer1.xml"
#define MEDIA "word/media/"

// define all the xml tags present in word document
#define TAG_DOCUMENT "document"         // Document tag
#define TAG_BODY "body"                 // Body tag
#define TAG_SECTPR "sectPr"             // Section properties tag
#define TAG_PG_SZ "pgSz"                // Page size tag
#define TAG_PG_MAR "pgMar"              // Page margin tag
#define TAG_COLS "cols"                 // Columns tag
#define TAG_DOCGRID "docGrid"           // Document grid tag
#define TAG_P "p"                       // Paragraph tag
#define TAG_R "r"                       // Run tag
#define TAG_T "t"                       // Text tag
#define TAG_TAB "tab"                   // Tab tag
#define TAG_TABS "tabs"                 // Tab tags
#define TAG_BR "br"                     // Break tag
#define TAG_PPR "pPr"                   // Paragraph properties
#define TAG_SPACING "spacing"           // Spacing tag
#define TAG_RPR "rPr"                   // Run properties
#define TAG_B "b"                       // Bold tag
#define TAG_BCS "bCs"                   // Bold tag
#define TAG_I "i"                       // Italic tag
#define TAG_U "u"                       // Underline tag
#define TAG_KEEPNEXT "keepNext"         // Keep next tag
#define TAG_SZ "sz"                     // Font size tag
#define TAG_SZCS "szCs"                 // Font size tag
#define TAG_LANG "lang"                 // Language tag
#define TAG_FONTS "fonts"               // Font family tag
#define TAG_COLOR "color"               // Font color tag
#define TAG_HYPERLINK "hyperlink"       // Hyperlink tag
#define TAG_NUMPR "numPr"               // Numbering properties
#define TAG_NUMID "numId"               // Numbering id
#define TAG_ILVL "ilvl"                 // Numbering level
#define TAG_PSTYLE "pStyle"             // Paragraph style
#define TAG_STYLE "style"               // Style tag
#define TAG_STYLEID "styleId"           // Style id tag
#define TAG_NAME "name"                 // Name tag
#define TAG_VAL "val"                   // Value tag
#define TAG_NUM "num"                   // Number tag
#define TAG_ILS "ilvl"                  // Numbering level start
#define TAG_FTR "ftr"                   // Footer tag
#define TAG_FOOTNOTE "footnote"         // Footnote tag
#define TAG_ENDNOTE "endnote"           // Endnote tag
#define TAG_PIC "imagedata"             // Picture tag
#define TAG_RELATIONSHIPS "Relationships" // Relationships tag
#define TAG_RELATIONSHIP "Relationship"   // Relationship tag
#define TAG_ID "Id"                       // Id tag
#define TAG_TYPE "Type"                   // Type tag
#define TAG_TARGET "Target"               // Target tag
#define TAG_HEADER "hdr"                // Header tag
#define TAG_JC "jc"                     // Justification tag
#define TAG_TBL "tbl"                   // Table tag
#define TAG_TBLPR "tblPr"               // Table properties tag
#define TAG_TBLGRID "tblGrid"           // Table grid tag
#define TAG_GRIDCOL "gridCol"           // Grid column tag
#define TAG_TR "tr"                     // Table row tag
#define TAG_TC "tc"                     // Table cell tag
#define TAG_TCPR "tcPr"                 // Table cell properties tag
#define TAG_DRAWING "drawing"           // Drawing tag
#define TAG_INLINE "wp:inline"            // Inline tag
#define TAG_GRAPHIC "a:graphic"           // Graphic tag
#define TAG_GRAPHICDATA "a:graphicData"   // Graphic data tag
#define TAG_PICPIC "pic:pic"              // Picture tag
#define TAG_BLIPFILL "a:blipFill"         // Blip fill tag
#define TAG_BLIP "a:blip"                 // Blip tag
#define TAG_EXT "wp:extent"               // Extent tag
#define TAG_TBLW "w:tblW"                 // Table width tag
#define TAG_TBLIND "w:tblInd"             // Table indentation tag
#define TAG_TBLLAYOUT "w:tblLayout"       // Table layout tag
#define TAG_TBLCELLMAR "w:tblCellMar"     // Table cell margin tag
#define TAG_TOP "w:top"                   // Top tag
#define TAG_BOTTOM "w:bottom"             // Bottom tag
#define TAG_LEFT "w:left"                 // Left tag
#define TAG_RIGHT "w:right"               // Right tag
#define TAG_INSTRTEXT "w:instrText"       // Instruction text tag

using namespace std;


struct DocxRelationship;

struct Tab;
struct Drawing;
struct Text;
struct RunProperties;
struct Run;
struct ParagraphProperties;
struct Paragraph;
struct PageSize;
struct PageMargin;
struct SectProperties;
struct Body;
struct Header;
struct Footer;
struct PDFStructure;
struct DocxRelationship;
struct Content;
struct PDFStructure;

struct Tab {
    string val;
    string pos;
};

struct Drawing
{
    string graphicId;
    string distT;
    string distB;
    string distL;
    string distR;
};

struct Text {
    string text;
    string xml_space;
};

struct RunProperties
{
    string size;
    string szCs;
    string bCs;
    string spacing;
    string lang;
    string color;
    bool bold;
    bool underline;
    bool italic;
};

struct Run
{
    struct RunProperties runProperties;
    struct Text t;
    struct Drawing drawing;
    bool tab;
    bool br;
};

struct ParagraphProperties
{
    struct RunProperties runProperties;
    vector<struct Tab> tabs;
    string style;
    string spacing;
    string justification;
    string u;
    bool keepNext;
};

struct Paragraph
{
    vector<struct Run> runs;
    struct ParagraphProperties paragraphProperties;
};

struct PageSize {
    string width;
    string height;
};

struct PageMargin {
    string top;
    string bottom;
    string left;
    string right;
    string header;
    string footer;
    string gutter;
};

struct SectProperties {
    struct PageSize pageSize;
    struct PageMargin pageMargin;
    string columns;
    string docGrid;
};

struct Body
{
    vector<struct Paragraph> paragraphs;
    SectProperties sectProperties;
};

struct Header
{
    vector<Paragraph> paragraphs;
};

struct Footer
{
    vector<Paragraph> paragraphs;
};

struct Content
{
    struct Body body;
};

struct DocxRelationship
{
    string id;
    string type;
    string target;
};

struct PDFStructure
{
    struct vector<Header> headers;
    struct vector<Footer> footers;
    struct vector<DocxRelationship> relationships;
    struct Content content;
};
