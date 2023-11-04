// #import <Cocoa/Cocoa.h>
// #include <NSPasteboard.h>

#include <string>

#include <CoreFoundation/CoreFoundation.h>
#include <Foundation/Foundation.h>
#include <AppKit/AppKit.h>


extern "C"
void copy_string_to_clipboard(const std::string& str)
{
    NSPasteboard* pasteboard = [NSPasteboard generalPasteboard];
    [pasteboard clearContents];
    [pasteboard setString:str forType:NSPasteboardTypeString];
}