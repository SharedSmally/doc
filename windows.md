## Tips to use Windows commands

### convert doc to xml
- [Tip](http://www.snee.com/bobdc.blog/2007/09/using-word-for-command-line-co.html)
1. Add macro for word: Open a doc in Winword, add macro: (View->Macros->View Macros: word commands).
Windows saved Format is [available](https://msdn.microsoft.com/en-us/vba/word-vba/articles/wdsaveformat-enumeration-word)
```
Sub SaveAsXML()
   NewFilename = (Replace(ActiveDocument.FullName, ".doc", ".xml"))
   ActiveDocument.SaveAs FileName:=NewFilename, FileFormat:=wdFormatFlatXML
   Application.Quit
End Sub
```

2. word2xml.bat batch file to tell Word to start up with a given file and run the macro looks like this:
```
"C:\Program Files (x86)\Microsoft Office\Office14\winword" %1 /mSaveAsXML 
```
3. In command line, run the command:
```
.\word2xml.bat .\*.doc
```
### makefile to convert
```
LOCAL=.
HOST=xxx@yyyy
REMOTE=${HOST}:~/workspace/xdia/meta
DOC2XML="/cygdrive/c/Program Files (x86)/Microsoft Office/root/Office16/WINWORD.EXE"

main:init pull

init:
	mkdir -p doc/
	mkdir -p docx/
	
pull:
	scp ${REMOTE}/doc/*.doc ${LOCAL}/doc

test:
	${DOC2XML} doc/29061-e40.doc /mSaveAsXml

convert:
	for f in `ls doc/*.doc`; do ${DOC2XML} $$f /mSaveAsXml;  done
	mv doc/*.xml docx/

push:
	for f in `ls docx/*.xml`; do scp $$f ${REMOTE}/docx; done
```
