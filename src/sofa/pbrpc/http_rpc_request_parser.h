#ifndef _SOFA_PBRPC_HTTP_RPC_REQUEST_PARSER_H_
#define _SOFA_PBRPC_HTTP_RPC_REQUEST_PARSER_H_

#include <sofa/pbrpc/rpc_request_parser.h>
#include <sofa/pbrpc/http_rpc_request.h>

namespace sofa {
namespace pbrpc {

class HTTPRpcRequestParser : public RpcRequestParser
{
public:
    HTTPRpcRequestParser();
    virtual ~HTTPRpcRequestParser();

    virtual const char* Name();

    virtual void Reset();

    virtual bool CheckMagicString(const char* magic_string);

    virtual int Parse(const char* buf, int data_size, int offset, int* bytes_consumed);

    virtual RpcRequestPtr GetRequest();

private:
    // HTTP state machine based parser.
    //
    // @retval 1  request data ready
    // @retval 0  there are more bytes to be read
    // @retval -1  parse request fail
    int ParseInternal(char c);

private:
    enum ParseState
    {
        PS_METHOD,
        PS_PATH,
        PS_HTTP_VERSION,
        PS_EXPECT_NEW_LINE1,
        PS_HEAD_LINE_START,
        PS_HEAD_NAME,
        PS_HEAD_COLON,
        PS_HEAD_VALUE,
        PS_EXPECT_NEW_LINE2,
        PS_BODY
    };
    ParseState _state; // current parsing state
    std::string _header_name; // current parsing header name
    std::string _header_value; // currrent parsing header value
    int64 _content_length; // body content length
    HTTPRpcRequestPtr _req;
}; // class HTTPRpcRequestParser

} // namespace pbrpc
} // namespace sofa

#endif // _SOFA_PBRPC_HTTP_RPC_REQUEST_PARSER_H_

/* vim: set ts=4 sw=4 sts=4 tw=100 */
