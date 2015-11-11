![round_logo](./img/round_logo.png)

## Round-RPC

Round is based on [JSON-RPC over HTTP][json-rpc-http], but we extends the specification as the following.

## Protocol

### HTTPMU and HTTPU

Round supports not only HTTP but HTTPU and HTTPMU. HTTPU is unicast version, and HTTPMU is multicast version of HTTP.

## Request

### Request-Line

Round-RPC supports POST and GET methods. The request entry point must be begin with "/rpc" as the following.

```
Request-Line = Method SP Request-URI SP HTTP-Version CRLF
Method = "PUT" | "GET"
Request-URI = "/rpc" [Get-Params]
```

### GET

Round-RPC add an 'encode' parameter to disable only base64 encode for the 'params' parameter of [JSON-RPC over HTTP][json-rpc-http] to request from HTTP command line utility such as 'curl' easily.

```
Encode-Param = "encode" "=" "none"
```

## Examples

### PUT Request

```
PUT /rpc HTTP/1.1
Host : ....
Content-Type : "application/json"
Accept : "application/json"
Content-Length : ....

{
  "jsonrpc": "2.0",
  "method": "sum",
  "params": [42, 23],
  "id": 1
  ....
}
```

### GET Request

#### JSON-RPC encoding (Base64 + URLEncode)

```
GET /rpc?jsonrpc=2.0&method=sum&params=JTVCNDIlMkMlMjAyMyU1RAo=&id=1&.... HTTP/1.1
Host : ....
Accept : "application/json"
Content-Length : 0

```

#### JSON-RPC encoding without Base64  (Only URLEncode)

```
GET /rpc?jsonrpc=2.0&method=sum&encode=none&params=%5B42%2C%2023%5D&id=1&.... HTTP/1.1
Host : ....
Accept : "application/json"
Content-Length : 0

```

[rpc]: http://en.wikipedia.org/wiki/Remote_procedure_call
[json-rpc]: http://www.jsonrpc.org/specification
[json-rpc-http]: http://jsonrpc.org/historical/json-rpc-over-http.html
