
struct XercesInit
{
    XercesInit() { XMLPlatformUtils::Initialize(); }
    ~XercesInit() { XMLPlatformUtils::Terminate(); }
};

XercesInit & usingXerces()
{
    static XercesInit xercesInit;
    return xercesInit;
}

class SimpleBuffer : public MemoryManager {
public:
	void* allocate (size_t /*size*/) { return buffer_; }
	void deallocate (void* /*p*/) {}

  MemoryManager* getExceptionMemoryManager() { return this; }
	char buffer_[256];
};

static inline XMLCh* TC(const char *str,SimpleBuffer&sb) {
	return(XMLString::transcode(str,&sb));
}

static inline char* TC(const XMLCh *str,SimpleBuffer&sb) {
	return(XMLString::transcode(str,&sb));
}

bool load(const std::string & xmlfile)
{
    usingXerces();
    XercesDOMParser parser;
    DOMParseErrorHandler errHandler;

    parser.setValidationScheme(XercesDOMParser::Val_Always);
    parser.setIncludeIgnorableWhitespace(false);
    parser.setDoNamespaces(false);
    parser.setDoSchema(false);
    parser.setValidationConstraintFatal(true);
    parser.cacheGrammarFromParse(true);
    parser.setCreateCommentNodes(false);

    parser.setErrorHandler(&errHandler);
    
    try {
 		    parser.loadGrammar("(xxx.dtd", Grammar::DTDGrammarType, true);
        parser.parse(profileName.c_str());        
    } catch (const SAXParseException & ex) {
    } catch (const XMLException & ex) {
    } catch (const DOMException & ex) {
    } catch (const SAXParseException & ex) {
    } catch (...) {
    }
    
    DOMDocument *doc(parser.getDocument());
    if (doc==nullptr) {    
    }
    
    DOMDocumentType *doctype(doc->getDoctype());
    if (doctype==nullptr) {
    }
    
    DOMElement *root(doc->getDocumentElement());
    if (root == nullptr) {
    }
    
    SimpleBuffer sb;
    DOMNodeList *list = root->getElementsByTagName(TC("name",sb));
    DOMNode *elem;
    for (XMLSize_t i = 0; (elem = list->item(i)); ++i) {
    
    }
}
