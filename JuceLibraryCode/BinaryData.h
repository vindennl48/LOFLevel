/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   AnalyzeButton_hover_png;
    const int            AnalyzeButton_hover_pngSize = 210403;

    extern const char*   AnalyzeButton_off_png;
    const int            AnalyzeButton_off_pngSize = 214703;

    extern const char*   Background_png;
    const int            Background_pngSize = 1585477;

    extern const char*   Background_Layout_png;
    const int            Background_Layout_pngSize = 1589236;

    extern const char*   GainSlider_png;
    const int            GainSlider_pngSize = 173147;

    extern const char*   ProcessingButton_on_png;
    const int            ProcessingButton_on_pngSize = 213506;

    extern const char*   ProcessingButton_on_hover_png;
    const int            ProcessingButton_on_hover_pngSize = 213522;

    extern const char*   reset_down_png;
    const int            reset_down_pngSize = 44180;

    extern const char*   reset_hover_png;
    const int            reset_hover_pngSize = 45184;

    extern const char*   reset_off_png;
    const int            reset_off_pngSize = 44677;

    extern const char*   TargetSlider_png;
    const int            TargetSlider_pngSize = 173148;

    extern const char*   ThresholdSlider_png;
    const int            ThresholdSlider_pngSize = 177023;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 12;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
