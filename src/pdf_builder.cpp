#include "pdf_builder.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int buildPdf(const string &outputPdfPath, const vector<string> &text)
{

    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf)
    {
        cerr << "Error creating PDF document" << endl;
        return 1;
    }

    if (HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL) != HPDF_OK)
    {
        cerr << "Error setting compression mode" << endl;
        HPDF_Free(pdf);
        return 1;
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    if (!page)
    {
        cerr << "Error adding page" << endl;
        HPDF_Free(pdf);
        return 1;
    }

    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    if (!font)
    {
        cerr << "Error getting font" << endl;
        HPDF_Free(pdf);
        return 1;
    }

    HPDF_Page_SetFontAndSize(page, font, 12);

    HPDF_Page_BeginText(page);
    HPDF_Page_MoveTextPos(page, 50, 750);

    for (const string &line : text)
    {
        HPDF_Page_ShowText(page, line.c_str());
        HPDF_Page_MoveTextPos(page, 0, -20);
    }

    HPDF_Page_EndText(page);

    if (HPDF_SaveToFile(pdf, outputPdfPath.c_str()) != HPDF_OK)
    {
        cerr << "Error saving PDF to file" << endl;
        HPDF_Free(pdf);
        return 1;
    }

    HPDF_Free(pdf);

    return 0;
}