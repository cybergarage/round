![round_logo](../img/round_logo.png)

# Installing Round from source

### Package requirements

To compile from source, install the following packages on your platform.

| Package | Version | Mandatory |
|---|---|---|
| [OpenSSL](https://www.openssl.org) | 1.0.1 or later | O |
| [libxml2](http://xmlsoft.org/) | 2.2 or later | O |
| [Jansson](http://www.digip.org/jansson/) | 2.6 or later | O |
| [Spider Monkey ](https://developer.mozilla.org/ja/docs/SpiderMonkey) | 1.8.5 or later | O |
| [uHTTP for C++](http://www.cybergarage.org/do/view/Main/HttpEngineForCC) | 0.7.1 or later | O |
| [mUPnP for C++](http://www.cybergarage.org/do/view/Main/CyberLinkForCC) | 0.8 or later | O |
| [Chrome V8](https://developers.google.com/v8/) | 3.25.30 or later | - |
| [Java (JNI)](https://java.com/) | 1.6.0 or later | - |
| [Tcl](http://www.tcl.tk/) | 8.5.9 or later | - |
| [Lua](http://www.lua.org/) | 5.2.0 or later | - |

### Installation

To install on your platform, run the following in a terminal:

```
./boostrap && ./configure && make && sudo make install
```
