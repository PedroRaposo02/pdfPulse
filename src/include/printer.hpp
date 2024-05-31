#pragma once

#include "globals.hpp"

using namespace std;

// Helper function to print indentation
inline void printIndent(int level) {
    for (int i = 0; i < level; ++i) {
        cout << "    "; // Adjust indentation as needed
    }
}

// Generic print method for printing a vector of any type
template<typename T, typename Printer>
inline void printVector(const vector<T>& vec, int level, Printer printer) {
    for (const auto& elem : vec) {
        printIndent(level);
        cout << "- ";
        printer(elem, level + 1);
    }
}

// Print method for struct Tab
inline void printTab(const struct Tab& tab, int level) {
    printIndent(level);
    cout << "Tab:" << endl;
    printIndent(level + 1);
    cout << "val: " << tab.val << endl;
    printIndent(level + 1);
    cout << "pos: " << tab.pos << endl;
}

// Print method for struct Drawing
inline void printDrawing(const struct Drawing& drawing, int level) {
    printIndent(level);
    cout << "Drawing:" << endl;
    printIndent(level + 1);
    cout << "graphicId: " << drawing.graphicId << endl;
    printIndent(level + 1);
    cout << "distT: " << drawing.distT << endl;
    printIndent(level + 1);
    cout << "distB: " << drawing.distB << endl;
    printIndent(level + 1);
    cout << "distL: " << drawing.distL << endl;
    printIndent(level + 1);
    cout << "distR: " << drawing.distR << endl;
}

// Print method for struct Text
inline void printText(const struct Text& text, int level) {
    printIndent(level);
    cout << "Text:" << endl;
    printIndent(level + 1);
    cout << "text: " << text.text << endl;
    printIndent(level + 1);
    cout << "xml_space: " << text.xml_space << endl;
}

// Print method for struct RunProperties
inline void printRunProperties(const struct RunProperties& runProperties, int level) {
    printIndent(level);
    cout << "RunProperties:" << endl;
    printIndent(level + 1);
    cout << "size: " << runProperties.size << endl;
    // Print other properties similarly
}

// Print method for struct Run
inline void printRun(const struct Run& run, int level) {
    printIndent(level);
    cout << "Run:" << endl;
    printRunProperties(run.runProperties, level + 1);
    if (!run.t.text.empty())
        printText(run.t, level + 1);
    if (!run.drawing.graphicId.empty())
        printDrawing(run.drawing, level + 1);
    // Print other members similarly
}

// Print method for struct ParagraphProperties
inline void printParagraphProperties(const struct ParagraphProperties& paragraphProperties, int level) {
    printIndent(level);
    cout << "ParagraphProperties:" << endl;
    printRunProperties(paragraphProperties.runProperties, level + 1);
    printVector(paragraphProperties.tabs, level + 1, printTab);
    // Print other members similarly
}

// Print method for struct Paragraph
inline void printParagraph(const struct Paragraph& paragraph, int level) {
    printIndent(level);
    cout << "Paragraph:" << endl;
    printVector(paragraph.runs, level + 1, printRun);
    printParagraphProperties(paragraph.paragraphProperties, level + 1);
}

// Print method for struct PageSize
inline void printPageSize(const struct PageSize& pageSize, int level) {
    printIndent(level);
    cout << "PageSize:" << endl;
    printIndent(level + 1);
    cout << "width: " << pageSize.width << endl;
    printIndent(level + 1);
    cout << "height: " << pageSize.height << endl;
}

// Print method for struct PageMargin
inline void printPageMargin(const struct PageMargin& pageMargin, int level) {
    printIndent(level);
    cout << "PageMargin:" << endl;
    printIndent(level + 1);
    cout << "top: " << pageMargin.top << endl;
    printIndent(level + 1);
    cout << "bottom: " << pageMargin.bottom << endl;
}

// Define print methods for other structs similarly

// Print method for struct SectProperties
inline void printSectProperties(const struct SectProperties& sectProperties, int level) {
    printIndent(level);
    cout << "SectProperties:" << endl;
    printPageSize(sectProperties.pageSize, level + 1);
    printPageMargin(sectProperties.pageMargin, level + 1);
}

// Print method for struct Body
inline void printBody(const struct Body& body, int level) {
    printIndent(level);
    cout << "Body:" << endl;
    printVector(body.paragraphs, level + 1, printParagraph);
    printSectProperties(body.sectProperties, level + 1);
}

// Print method for struct Header
inline void printHeader(const struct Header& header, int level) {
    printIndent(level);
    cout << "Header:" << endl;
    printVector(header.paragraphs, level + 1, printParagraph);
}

// Print method for struct Footer
inline void printFooter(const struct Footer& footer, int level) {
    printIndent(level);
    cout << "Footer:" << endl;
    printVector(footer.paragraphs, level + 1, printParagraph);
}

// Print method for struct Content
inline void printContent(const struct Content& content, int level) {
    printIndent(level);
    cout << "Content:" << endl;
    printBody(content.body, level + 1);
}

// Print method for struct DocxRelationship
inline void printDocxRelationship(const struct DocxRelationship& docxRelationship, int level) {
    printIndent(level);
    cout << "DocxRelationship:" << endl;
    printIndent(level + 1);
    cout << "id: " << docxRelationship.id << endl;
    printIndent(level + 1);
    cout << "type: " << docxRelationship.type << endl;
    printIndent(level + 1);
    cout << "target: " << docxRelationship.target << endl;
}

// Print method for struct PDFStructure
inline void printPDFStructure(const struct PDFStructure& pdfStructure, int level) {
    printIndent(level);
    cout << "PDFStructure:" << endl;
    printVector(pdfStructure.headers, level + 1, printHeader);
    printVector(pdfStructure.footers, level + 1, printFooter);
    printContent(pdfStructure.content, level + 1);
    printVector(pdfStructure.relationships, level + 1, printDocxRelationship);
}
