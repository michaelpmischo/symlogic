##>
#! /usr/python

import os, re, shutil, datetime
from time import ctime
from tkinter import SEL

class Header():
    def __init__(self):
        self.default_author = "Michael P. Mischo"
        
        self.comment_extension = {
            ".cpp" : [("//", "\n"), ("/*", "*/")],
            ".cxx" : [("//", "\n"), ("/*", "*/")],
            ".c" : [("//", "\n"), ("/*", "*/")],
            ".hxx" : [("//", "\n"), ("/*", "*/")],
            ".hpp" : [("//", "\n"), ("/*", "*/")],
            ".h" : [("//", "\n"), ("/*", "*/")],
            ".py" : [("#", "\n")],
            ".txt" : [("#", "\n")],
            ".mk" : [("#", "\n")],
            ".mak" : [("#", "\n")],
            "" : [("#", "\n")],
        }
        self.header_header_format = (
"""{line_comment} ____________________________________________________________________________
{line_comment}{doxy_start} @file {file_name}
{line_comment}{doxy_start} @author {author}
{line_comment}{doxy_start} @date {creation_date}
{line_comment}{doxy_start} Modified: {modified_date}
{line_comment}{doxy_start} @brief {brief}
{line_comment} ____________________________________________________________________________
""")

        self.source_header_format = (
"""{line_comment} ____________________________________________________________________________
{line_comment}{doxy_start} @file {file_name}
{line_comment}{doxy_start} @author {author}
{line_comment}{doxy_start} @date {creation_date}
{line_comment}{doxy_start} Modified: {modified_date}
{line_comment}{doxy_start} @headerfile {header_file}
{line_comment}{doxy_start} @brief {brief}
{line_comment} ____________________________________________________________________________
""")

        self.copyright_format = (
"""{line_comment}{doxy_start} @copyright Copyright (C) 2022-{year} {author} - All Rights Reserved
{line_comment}{doxy_start}
{line_comment}{doxy_start} This program is free software; you can redistribute it and /or modify
{line_comment}{doxy_start} it under the terms of the GNU General Public License as published by
{line_comment}{doxy_start} the Free Software Foundation; either version 2 of the License, or
{line_comment}{doxy_start} (at your option) any later version.
{line_comment}{doxy_start}
{line_comment}{doxy_start} This program is distributed in the hope that it will be useful,
{line_comment}{doxy_start} but WITHOUT ANY WARRANTY; without even the implied warranty of
{line_comment}{doxy_start} MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
{line_comment}{doxy_start} GNU General Public License for more details.
{line_comment}{doxy_start} 
{line_comment}{doxy_start} You should have received a copy of the GNU General Public License
{line_comment}{doxy_start} along with this program; if not, write to the Free Software
{line_comment}{doxy_start} Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 
{line_comment}{doxy_start} 1301  USA
{line_comment}{doxy_start} 
{line_comment}{doxy_start} You may use, distribute and modify this code under the terms of the GPL
{line_comment}{doxy_start} license. You should have received a copy of the GPL license with this 
{line_comment}{doxy_start} file. If not, please write to: , or visit :
{line_comment}{doxy_start} https://www.gnu.org/licenses/
{line_comment}{doxy_start} ____________________________________________________________________________
""")

        self.footer_format = (
"""
{line_comment}  __________________________________________________________________________
{line_comment} |                                                                          |
{line_comment} |__________________________________________________________________________|
""")

    def process_directory(self, directory_in=os.getcwd(), depth_in=0):
        path = os.path.abspath(directory_in)
        print("Header [{depth}]: Entering {directory}".format(
            directory=path, depth=depth_in))

        last_root = ""
        for (root, directories, files) in os.walk(path):
            if (root != last_root):
                print("Entering: {root}".format(root=root))
            for file in files:
                if (self.interest(file)):
                    self.process_file(os.path.join(root, file))

    def process_file(self, file_name_in):
        print("Processiong File: {file_name}".format(file_name=file_name_in))
        data = self.read(file_name_in)
        #print("Input Data: \n{0:}".format(data))

        data = self.strip(data, file_name_in)
        #print("Stripped Data: \n{0:}".format(data))

        data = self.header(file_name_in) + data
        print("Reformatted Data: \n{0:}".format(data))


        file_name_in = (os.path.splitext(file_name_in)[0] + 
            ".update" + 
            os.path.splitext(file_name_in)[1])
        self.write(file_name_in, data)

    def strip(self, data_in, file_name_in):
        out = ""
        in_comment = False
        body = False
        line_comment = self.comment_extension[os.path.splitext(file_name_in)[1]][0][0]
        for line in data_in.split("\n"):
            if (line.strip().startswith(line_comment) and not body):
                ## All the header lines...
                pass

            elif (not body):
                ## End of the Header.
                body = True
                out += line + "\n"

            else:
                out += line + "\n"

        print(out)
        return out

    def header(self, file_name_in):
        out = ""
        creation_date = datetime.datetime.fromtimestamp(
            os.path.getctime(file_name_in))
        modification_date = datetime.datetime.fromtimestamp(
            os.path.getctime(file_name_in))
        author = self.default_author
        if (file_name_in.endswith(".cpp") or 
            file_name_in.endswith(".c")):
            out += self.source_header_format.format(
                line_comment="//", 
                doxy_start="!",
                file_name=os.path.basename(file_name_in),
                author=author,
                creation_date=creation_date.strftime("%B %d, %Y"),
                modified_date=modification_date.strftime("%B %d, %Y %I:%M:%S.%f %p"),
                header_file=os.path.basename(file_name_in).replace(
                    os.path.splitext(file_name_in)[1], ".h"),
                brief="")
            line_comment = "//"
            doxy_start = "!"
        elif (file_name_in.endswith(".h")):
            out += self.header_header_format.format(
                line_comment="//", 
                doxy_start="!",
                file_name=os.path.basename(file_name_in),
                author=author,
                creation_date=creation_date.strftime("%B %d, %Y"),
                modified_date=modification_date.strftime("%B %d, %Y %I:%M:%S.%f %p"),
                brief="")
            line_comment = "//"
            doxy_start = "!"
        else:
            out += self.header_header_format.format(
                line_comment="#", 
                doxy_start="#",
                file_name=os.path.basename(file_name_in),
                author=author,
                creation_date=creation_date.strftime("%B %d, %Y"),
                modified_date=modification_date.strftime("%B %d, %Y %I:%M:%S.%f %p"),
                mtime=modification_date.time(),
                brief="")
            line_comment = "#"
            doxy_start = "#"

        return out + self.copyright_format.format(
            line_comment=line_comment,
            doxy_start=doxy_start,
            author=author,
            year=modification_date.strftime("%Y"))

    def read(sef, file_name_in):
        data = ""
        try:
            with open(file_name_in, "r") as file:
                try:
                    data = file.read()

                except Exception as error:
                    raise

                finally:
                    file.close()

        except OSError as error:
            raise

        finally:
            return data

    def write(sef, file_name_in, data):
        try:
            with open(file_name_in, "w") as file:
                try:
                    file.write(data)

                except Exception as error:
                    raise

                finally:
                    file.close()

        except OSError as error:
            raise

    def interest(self, file_name_in):
        return (os.path.splitext(file_name_in)[1] in self.comment_extension)

if __name__ == '__main__':
    header = Header()
    header.process_directory("./src")