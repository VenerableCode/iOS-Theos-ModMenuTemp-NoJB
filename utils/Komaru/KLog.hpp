#pragma once

#include <string>

#import <Foundation/Foundation.h>

namespace KLOG
{
    inline void MsgToFile(const std::string& filename, const std::string& message)
    {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(
            NSDocumentDirectory,
            NSUserDomainMask,
            YES
        );

        NSString *docdir = [paths firstObject];

        NSString *fileName =
            [NSString stringWithUTF8String:filename.c_str()];

        NSString *logPath =
            [docdir stringByAppendingPathComponent:fileName];

        NSString *line =
            [NSString stringWithFormat:@"%s\n", message.c_str()];

        NSFileHandle *file =
            [NSFileHandle fileHandleForWritingAtPath:logPath];

        if (file)
        {
            [file seekToEndOfFile];

            NSData *data =
                [line dataUsingEncoding:NSUTF8StringEncoding];

            [file writeData:data];
            [file closeFile];
        }
        
        else
        {
            [line writeToFile:logPath
                   atomically:YES
                     encoding:NSUTF8StringEncoding
                        error:nil];
        }
    }
}