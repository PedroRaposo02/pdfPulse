#include "pdf_builder.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const Debugger debugger;



void createPDF(const PDFStructure &pdfStructure, const std::string &outputFile) {
    HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
    if (!pdf) {
        throw std::runtime_error("Error: unable to create PDF document.");
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", nullptr);
    HPDF_Page_SetFontAndSize(page, font, 12);

    // Add header
    createHeader(pdf, page, pdfStructure.headers[0]);

    // Add footer
    createFooter(pdf, page, pdfStructure.footers[0]);

    // Add body content
    float pageHeight = HPDF_Page_GetHeight(page);
    float y = pageHeight - 100;  // Adjust starting y position
    float x = 50;  // Adjust starting x position

    for (const auto &paragraph : pdfStructure.content.body.paragraphs) {
        for (const auto &run : paragraph.runs) {
            if (!run.t.text.empty()) {
                addTextToPage(page, run.t, x, y);  // Adjust x, y as needed
                y -= 15;  // Adjust line spacing as needed
            }
        }
    }

    // Save the PDF to a file
    HPDF_SaveToFile(pdf, outputFile.c_str());
    HPDF_Free(pdf);
}

void createHeader(HPDF_Doc pdf, HPDF_Page page, const Header &header) {
    float pageHeight = HPDF_Page_GetHeight(page);
    float marginTop = 30;  // Adjust margin as needed
    float y = pageHeight - marginTop;
    float x = 50;  // Adjust starting x position

    for (const auto &paragraph : header.paragraphs) {
        for (const auto &run : paragraph.runs) {
            if (!run.t.text.empty()) {
                addTextToPage(page, run.t, x, y);  // Adjust x, y as needed
                y -= 15;  // Adjust line spacing as needed
            }
        }
    }
}

void createFooter(HPDF_Doc pdf, HPDF_Page page, const Footer &footer) {
    float marginBottom = 30;  // Adjust margin as needed
    float y = marginBottom;
    float x = 50;  // Adjust starting x position

    for (const auto &paragraph : footer.paragraphs) {
        for (const auto &run : paragraph.runs) {
            if (!run.t.text.empty()) {
                addTextToPage(page, run.t, x, y);  // Adjust x, y as needed
                y -= 15;  // Adjust line spacing as needed
            }
        }
    }
}

void addTextToPage(HPDF_Page page, const Text &text, float &cursorX, float &cursorY) {
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, cursorX, cursorY, text.text.c_str());
    HPDF_Page_EndText(page);
}