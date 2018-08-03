# jeffersonize: a CHAT/CAlite converter
jeffersonize allows bi-directional conversion between Talk-bank’s CHAT and the Conversation Analysis (CA) format. 

It enables conversation analysis (CA) transcribers to convert transcripts between [CAlite](https://github.com/saulalbert/CABNC/wiki/CHAT-CA-lite) using the [CLAN transcript editor](http://dali.talkbank.org/clan/) and adhering to [de-facto CA transcription standards](https://us.sagepub.com/en-us/nam/transcribing-for-social-research/book237847) and computer readable [CHAT formatted](https://talkbank.org/manuals/CHAT.pdf) transcripts.


## Status

We've tested jeffersonize on
* Mac OSX
* Microsoft Windows OS

The current version is an early alpha, feel free to provide feedback at: hilab-dev@elist.tufts.edu

## Build 
* Download or clone the repository, open the directory with a terminal.
* ‘make’ to compile.
* This will generate the jeffersonize executable in the same directory. 

## Usage

jeffersonize is a command line tool that that does bi-directional conversions between CHAT and CAlite. If you convert from calite2chat, it will take a CA (.ca) file as input, and create a CHAT (.cha) file as output. If you go from chat2calite, it will do the opposite.

* Use the 'mode' argument to specify which direction you're converting:
  * calite2chat
  * chat2calite
* Examples:
  * ./jefersonize calite2chat /path/to/file/KB0RE000.S.ca
  * ./jefersonize chat2calite /path/to/file/KB0RE000.cha

## Usage Constraints

**File Constraints**
* .S.ca or .cha file extensions
  * jeffersonize will only convert from calite2chat if you use the ‘.S.ca’ extension on your CA transcript files.
  * Similarly, it will only convert CHAT files that use the ‘.cha’ extension.
* File metadata should end with ‘@New Episode’
  * the transcription file for both CAlite and CHAT should begin with a ‘@New Episode’ header.
  * the transcription file for both CAlite and CHAT should end with an ‘@End’ footer.

**Check Constraints**
* jeffersonize uses [CLAN's](http://dali.talkbank.org/clan/) ‘CHECK’ script to verify CHAT transcripts
* It assumes that CA transcribers are adhereing to the guidelines for [CAlite](https://github.com/saulalbert/CABNC/wiki/CHAT-CA-lite)
* **NOTE:** jeffersonize does not guarantee an error free conversion since transcripts of conversation are, quite naturally, not always organized with computer-readable formatting in mind. It therefore attempts to produce a 'good enough' version that can be manually corrected, so we recommend running CHECK after conversion and fixing any errors before converting or uploading CHAT files to TalkBank or other transcript databases.

  
## Contribute

Please send feedback, bugs & requests to:
* hilab-dev@elist.tufts.edu

## Collaborators and Acknowledgments

The [HiLab](https://sites.tufts.edu/hilab/people/), including

* [Muhammad Umair](http://sites.tufts.edu/hilab/people) (Lead developer)
* [Saul Albert](http://twitter.com/saul)
* [Jan P. Deruiter](http://twitter.com/jpderuiter)




