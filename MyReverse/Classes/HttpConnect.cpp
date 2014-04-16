
#include "HttpConnect.h"

USING_NS_CC;
USING_NS_CC_EXT;

void HttpConnect::getRequest(char* url, CCObject* target,SEL_CallFuncND selector)
{
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl(url);
    request->setRequestType(CCHttpRequest::kHttpGet);
    request->setResponseCallback(target, selector);
    CCHttpClient::getInstance()->send(request);
    request->release();
    
    
}