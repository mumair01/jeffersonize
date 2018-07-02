# Converter 2.0: Bidirectional CHAT/CA Conversion Script
Converter 2.0 is the product of the Tufts Human Interaction (HI) Lab’s efforts to create a command line tool that allows bi-directional conversion between Talk-bank’s CHAT and the Conversation Analysis (CA) format. It implements a set of solutions, proposed by Dr. Albert Saul (Postdoctoral Associate in Psychology, Tufts University), for integrating new de-facto CA transcription standards into CLAN.

The CAlite standard is currently documented at: https://github.com/saulalbert/CABNC/wiki/CHAT-CA-lite
This new workflow for CA transcribers involves working on CA transcripts in CAlite in order to allow a conversion to CHAT, thereby presenting the opportunity for further conversions.

## Motivation
The Converter 2.0 project draws its inspiration from Brian MacWhinney’s (Carnegie Mellon University) Talk-Bank project, which included the introduction of the CHAT format and conversion scripts from CA to CHAT. 
However, use of the existing CHAT format for everyday Conversation Analytics transcripts has revealed a lack of certain markers that are required for an accurate representation of conversation. This stems from the fact that CHAT is designed to be a completely unambiguous, machine-readable format, fully capable of being analyzed by existing tools or converted into structured formats such as XML.
On the other hand, the CA format has traditionally been designed and used so as to provide a better visual representation of conversation being transcribed. It’s power in Conversation Analytics stems from the fact that the written version of the conversation being reviewed, perhaps through a visual media, is easy and natural to follow with the said visual media. The same functionality cannot be achieved using CHAT due to its extensive efforts to remain unambiguous, often times causing speech delimiters to become too complicated to follow for manual analysis.

Therefore, there was a need to introduce a new version of CA, namely CAlite, that will introduce a slightly modified workflow to the original, such that it maintains the original power of visual representation, includes representation of a larger amount of speech delimiters, and requires minimal adjustments to CLAN’s existing format verification system: Check.

This increased detail in transcription, coupled with the ability for bi-directional CAlite and CHAT conversion will allow CA transcribers to contribute to the CABNC Corpus (https://github.com/saulalbert/CABNC/wiki/CHAT-CA-lite) incrementally. In addition, pre-existing databases of CA files can be converted to more structured formats, allowing for automated analysis, and effectively removing the need for a slower manual analysis.

## Build Status

The current version of Converter 2.0 has undergone Alpha Testing by members of the Tufts Human Interaction lab and is currently in the Beta Testing phase.
If a user discovers problems with script functionality, feel free to provide feedback at: (email address)

## Platform Support and Usage

Converter 2.0 is fully compatible with:
* Mac OSX
* Microsoft Windows OS

It acts as a simple command line tool that performs simple bi-directional conversions between CHAT and CAlite.

To use Converter 2.0 on Mac, please follow the following guidelines:
* Download Converter 2.0 from the Tufts Human Interaction Lab database.
* Open Terminal.
* Use terminal to move to the command line directory containing the downloaded files.
* If the download version includes the original source code, simply use the Linux command ‘make’ to compile.
* This should generate the Converter 2.0 Binary executable file within the same directory. Skip the above step if the   download package already only consists of the binary executable.
* Converter 2.0 consists of the following three arguments on the command line:
  * Specification of the executable -> 	./converter
  * Specification of the mode Converter 2.0 is to operate under. There are two modes:
    * calite2chat
    * chat2calite
  * Specification of the complete file path for the file that is to be converted.
  * Example Commands:
    * ./converter calite2chat /Users/Username/Documents/KB0RE000.S.ca
    * ./converter chat2calite /Users/Username/Documents/KB0RE000.cha

## Usage Constraints

Converter 2.0 has certain intentional usage constraints, intended to provide a better overall experience for its users.

**Command Line Constraints**
* C++11 or Higher:
** Converter 2.0 uses libraries that will only be compiled by compilers that support C++11 by default

**File Constraints**
* .S.ca or .cha file extensions
  * Converter 2.0 will only work with CAlite files that have the ‘.S.ca’ extension.
  * Similarly, the program will only work with CHAT files that have the ‘.cha’ extension.
* File metadata should end with ‘@New Episode’
  * Converter 2.0 expects that the CAlite and CHAT files it converts have already been manually or algorithmically checked.
  * As such, in line with the existing practice, the transcription for both CAlite and CHAT should begin with ‘@New Episode’.
* Transcription end
  * As mentioned above, and in line with proper transcription standards, the CAlite and CHAT files should end with ‘@End’.

**Check Constraints**
* Converter 2.0 counts on the verification script, ‘Check’, written as part of Brian MacWhinney’s (Carnegie Mellon University) Talk-Bank project and built into the CLAN editor.
* It assumes that the transcriber ensures that proper transcription standards have been made.
* We recommend that the user runs ‘Check’ (Esc-l) using the CLAN editor for every converted file.
* **NOTE:** Converter 2.0 does not guarantee a completely error free conversion. Instead, the project depends on the feedback from the Conversation Analytics community, along with all its users, to ensure a satisfactory conversion. We are fully committed to updating program preferences in the hopes of generating a completely error free version of Converter 2.0.

**Formatting Constraints**
* The Converter 2.0 project assumes that in its workflow design that future CA transcription standards, at least for the next few years, will be based on or up to par with ‘Transcribing for Social Research’ by Alexa Hepburn and Galina B. Bolden.
* For all CAlite files, the transcriber should follow the existing guidelines along with CAlite guidelines for additional features. (https://github.com/saulalbert/CABNC/wiki/CHAT-CA-lite)
* For CHAT files, the transcriber should ensure that check reports no errors before using Converter 2.0.

## Design Overview

Converter 2.0 consists of the basic design flow described below

                                               Main
                                                |
                                                |
                                            Converter 
                                                |                              
                          |---------------------|----------------------------|
      CAlite to CHAT converter           CHAT to CAlite Converter        Future Converters


As shown above, Converter 2.0 consists of:
* Driver Script
  * This script is responsible for instantiating an instance of Converter with the parameters described in the Converter header file.
* Converter Script
  * A separate class that deals with all file read/write operations and all file verification operations.
* CAlite to CHAT
  * A separate class, generic to the maximum possible extent, that defines the rules for conversion between CAlite and CHAT.
* CHAT to CAlite
  * A separate class, generic to the maximum possible extent, that defines the rules for conversion between CHAT and CAlite.
* Other Formats
  * With this design, converter 2.0 maintains the possibility of being updated to convert between other formats in a future version.
  
## Contribute

All users are welcome to contribute to the Converter 2.0 project by sending feedback regarding any new bugs or edge cases, as well as requests for additional functionality at:
* (Email)

## Collaborators and Acknowledgments

The Converter 2.0 project is the product of the efforts of the following members of the Tufts Human Interaction Lab:

**Professor Jan P. Deruiter:** 
Department of Computer Science and Psychology, 
Tufts University

**Dr. Saul Albert:**
Postdoctoral Associate in Psychology,
Tufts University

**Muhammad Umair:**
BS Computer Science Candidate in Engineering,
Tufts University

