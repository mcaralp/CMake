/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef cmGeneratedFileStream_h
#define cmGeneratedFileStream_h

#include "cmStandardIncludes.h"

// This is the first base class of cmGeneratedFileStream.  It will be
// created before and destroyed after the ofstream portion and can
// therefore be used to manage the temporary file.
class cmGeneratedFileStreamBase
{
protected:
  // This constructor does not prepare the temporary file.  The open
  // method must be used.
  cmGeneratedFileStreamBase();

  // This constructor prepares the temporary output file.
  cmGeneratedFileStreamBase(const char* name);

  // The destructor renames the temporary output file to the real name.
  ~cmGeneratedFileStreamBase();

  // Internal methods to handle the temporary file.  Open is always
  // called before the real stream is opened.  Close is always called
  // after the real stream is closed and m_Okay is set to whether the
  // real stream was still valid for writing when it was closed.
  void Open(const char* name);
  void Close();

  // Internal file replacement implementation.
  int RenameFile(const char* oldname, const char* newname);

  // Internal file compression implementation.
  int CompressFile(const char* oldname, const char* newname);

  // The name of the final destination file for the output.
  std::string m_Name;

  // The name of the temporary file.
  std::string m_TempName;

  // Whether to do a copy-if-different.
  bool m_CopyIfDifferent;

  // Whether the real file stream was valid when it was closed.
  bool m_Okay;

  // Whether the destionation file is compressed
  bool m_Compress;
};

/** \class cmGeneratedFileStream
 * \brief Output stream for generated files.
 *
 * File generation should be atomic so that if CMake is killed then a
 * generated file is either the original version or the complete new
 * version.  This stream is used to make sure file generation is
 * atomic.  Optionally the output file is only replaced if its
 * contents have changed to prevent the file modification time from
 * being updated.
 */
class cmGeneratedFileStream: private cmGeneratedFileStreamBase,
                             public std::ofstream
{
public:
  typedef std::ofstream Stream;

  /**
   * This constructor prepares a default stream.  The open method must
   * be used before writing to the stream.
   */
  cmGeneratedFileStream();

  /**
   * This constructor takes the name of the file to be generated.  It
   * automatically generates a name for the temporary file.  If the
   * file cannot be opened an error message is produced unless the
   * second argument is set to true.
   */
  cmGeneratedFileStream(const char* name, bool quiet=false);

  /**
   * The destructor checks the stream status to be sure the temporary
   * file was successfully written before allowing the original to be
   * replaced.
   */
  ~cmGeneratedFileStream();

  /**
   * Open an output file by name.  This should be used only with a
   * non-open stream.  It automatically generates a name for the
   * temporary file.  If the file cannot be opened an error message is
   * produced unless the second argument is set to true.
   */
  cmGeneratedFileStream& Open(const char* name, bool quiet=false);

  /**
   * Close the output file.  This should be used only with an open
   * stream.  The temporary file is atomically renamed to the
   * destionation file if the stream is still valid when this method
   * is called.
   */
  cmGeneratedFileStream& Close();

  /**
   * Set whether copy-if-different is done.
   */
  void SetCopyIfDifferent(bool copy_if_different);

  /**
   * Set whether compression is done.
   */
  void SetCompression(bool compression);
};

#endif
